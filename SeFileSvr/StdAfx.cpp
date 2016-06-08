#include "stdafx.h"

int CServiceModule::InitSocketServer(void)
{
	WSADATA wd = {0};
	// load params from xml
	m_wPort = 5500;//PORT_FILESVR;
	m_nConnTimeout = 100; // 10sec
	m_nBlock = 8; // 8M
	memset(m_bufState, 0, MAX_MEMBUFS);
	memset(m_arBufs, 0, MAX_MEMBUFS*sizeof(LPSTR));

	m_hMutexClientInfo = CreateMutex(NULL, FALSE, "Mu_FileSvr_Clients66");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return ERROR_ALREADY_EXISTS;
	m_hMutexBuf = CreateMutex(NULL, FALSE, NULL);

	int nStart = WSAStartup(MAKEWORD(2,2), &wd);//0=succ
	if(nStart)
		return -1;
	m_hCompPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (NULL == m_hCompPort)
		return 1;

	m_sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockServer)
	{
		_Module.LogEvent(_T("create socket fail: %x"), WSAGetLastError());
		return 3;
	}
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_wPort);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("192.168.x.x");
	int nBind = bind(m_sockServer, (sockaddr *)&addr, sizeof(addr));
	if (0 != nBind)
		return 4;

	if(SOCKET_ERROR == listen(m_sockServer, 10))
		return 5;

	unsigned long dwID;
	m_hThreadAccept = CreateThread(NULL,0, Thread_Accepting, this, 0,&dwID);
	m_hThreadConnManage = CreateThread(NULL,0, Thread_ConnManage, this, 0,&dwID);
	if(m_hThreadAccept==NULL || m_hThreadConnManage==NULL)
		return 7;
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	m_nRecvThread = min(MAX_RECVTHREAD, sysInfo.dwNumberOfProcessors*2);
	for(int i=0; i<m_nRecvThread; i++)
	{
		m_hThreadRecv[i] = CreateThread(NULL, 0, Thread_Receiving, this, 0, &dwID);
		if(NULL == m_hThreadRecv[i])
			return 6;
	}
	m_vClientInfo.resize(CONNPOOLSIZE);
	CLIENT_INFO *pClient = m_vClientInfo.begin();
	memset(pClient, 0, sizeof(CLIENT_INFO)*CONNPOOLSIZE);
	//nOpt = 16*1024;// send buffer
	//setsockopt(m_sockServer, SOL_SOCKET, SO_SNDBUF, (const char *)&nOpt, sizeof(nOpt));
	return 0;
}

void CServiceModule::FreeSocketServer(void)
{
	VEC_ClientInfo::iterator it;
	for(it = m_vClientInfo.begin(); it!=m_vClientInfo.end(); it++)
	{
		shutdown(it->sock, SD_BOTH);
		closesocket(it->sock);
	}
	shutdown(m_sockServer, SD_BOTH); // let Thread_Accepting-accept() quit
	closesocket(m_sockServer);
	WSACleanup();
	
	int i;
	for(i=0; i<MAX_MEMBUFS; i++)
	{
		if(m_bufState[i] > 0)
			free(m_arBufs[i]);
	}

	CloseHandle(m_hCompPort); // let Thread_Receiving-GetQueuedCompletionStatus() quit
	for(i=0; i<m_nRecvThread; i++)
	{
		WaitForSingleObject(m_hThreadRecv[i], INFINITE);
		CloseHandle(m_hThreadRecv[i]);
	}
	WaitForSingleObject(m_hThreadAccept, INFINITE);
	CloseHandle(m_hThreadAccept);
	CloseHandle(m_hThreadConnManage);
	CloseHandle(m_hMutexClientInfo);
	CloseHandle(m_hMutexBuf);
	m_vClientInfo.clear();
}

// get an empty clientInfo from connection pool, or expand the pool
CLIENT_INFO * CServiceModule::GetConnFromPool()
{
	CLIENT_INFO *pClient = NULL;
	VEC_ClientInfo::iterator it;

	for(it=m_vClientInfo.begin(); it!=m_vClientInfo.end(); it++)
	{
		if(it->sock == 0)
		{
			pClient = it;
			break;
		}
	}
	if(pClient == NULL && m_vClientInfo.size() < MAX_POOLSIZE)
	{
		WaitForSingleObject(m_hMutexClientInfo, INFINITE);
		int nSize = m_vClientInfo.size();
		m_vClientInfo.resize(nSize + CONNPOOLSIZE);
		pClient = m_vClientInfo.begin() + nSize;
		memset(pClient, 0, sizeof(CLIENT_INFO)*CONNPOOLSIZE);
		ReleaseMutex(m_hMutexClientInfo);
	}
	return pClient;
}
// get an idle mem from pool, or expand the pool
PSTR CServiceModule::GetMemFromPool(int &index)
{
	char * pbuf = NULL;
	int i;
	for(i=0; i<MAX_MEMBUFS && m_bufState[i]>0; i++)
	{
		if(m_bufState[i] == MEMSTAT_IDLE)
		{
			pbuf = m_arBufs[i];
			index = i;
		}
	}
	if(pbuf)
		return pbuf;
	if(i == MAX_MEMBUFS)
	{
		OutputDebugString(_T("exceed max bufs\n"));
		return NULL;
	}
	pbuf = (char*)malloc(m_nBlock*1024*1024);
	if(pbuf)
	{
		WaitForSingleObject(m_hMutexBuf, INFINITE);
		m_arBufs[i] = pbuf;
		index = i;
		ReleaseMutex(m_hMutexBuf);
	} else
	{
		OutputDebugString(_T("alloc failed\n"));
	}
	return pbuf;
}

void CServiceModule::ClearClientConn(CLIENT_INFO *pClient)
{
	WaitForSingleObject(m_hMutexClientInfo, INFINITE);
	//shutdown(pClient->sock, SD_BOTH);
	_Module.LogEvent(_T("clear conn=%x:%d"), pClient->addr.sin_addr.S_un.S_addr, htons(pClient->addr.sin_port));
	closesocket(pClient->sock);
	if(pClient->pBlockBuf)
		m_bufState[pClient->iBuf] = MEMSTAT_IDLE;
	if(pClient->hFile)
		CloseHandle(pClient->hFile);
	memset(pClient, 0, sizeof(CLIENT_INFO));
	ReleaseMutex(m_hMutexClientInfo);
}

int CServiceModule::SendCmd(SOCKET sock, char cmd, char param, void *pdata, int len)
{
	static char cmdBuf[256];
	cmdBuf[0] = 'H';
	cmdBuf[1] = (char)('0'+len);
	cmdBuf[2] = cmd;
	cmdBuf[3] = param;
	if(pdata)
		memcpy(cmdBuf+4, pdata, len);
	return send(sock, cmdBuf, len+4, 0);
}

unsigned long CServiceModule::Thread_ConnManage(LPVOID pParam)
{
	CServiceModule *pServ = (CServiceModule *)pParam;
	DWORD dwNow=0;
	OutputDebugString(_T("Enter Thread_ConnManage\n"));
	VEC_ClientInfo::iterator it;
	

	while (pServ->m_status.dwCurrentState == SERVICE_RUNNING)
	{
		dwNow = GetTickCount();
		for(it=pServ->m_vClientInfo.begin(); it!=pServ->m_vClientInfo.end(); it++)
		{
			if(it->sock && dwNow-it->lastActTick>(DWORD)pServ->m_nConnTimeout*1000)
			{
				OutputDebugString(_T("close conn"));
				pServ->ClearClientConn(it);
			}
		}
		Sleep(1000);
	}
	OutputDebugString(_T("Exit Thread_ConnManage"));
	return 0;
}

unsigned long CServiceModule::Thread_Accepting(LPVOID pParam)
{
	CServiceModule *pServ = (CServiceModule *)pParam;
	CLIENT_INFO *pClient;
	SOCKET sockClient;
	sockaddr_in addr;

	OutputDebugString(_T("Enter Thread_Accepting\n"));
	DWORD dwRecv=0, dwFlag=0;
	WSABUF wsaBuf;
	wsaBuf.len = CMDBUFSIZE;
	int nLen = sizeof(sockaddr_in);
	while (pServ->m_status.dwCurrentState == SERVICE_RUNNING)
	{
		sockClient = accept(pServ->m_sockServer, (SOCKADDR*)&addr, &nLen);
		if(SOCKET_ERROR == sockClient)
		{
			_Module.LogEvent(_T("sock accept failed=%d"), WSAGetLastError());
			break;
		}
		_Module.LogEvent(_T("accept conn=%x:%d"), addr.sin_addr.S_un.S_addr, htons(addr.sin_port));
		pClient = pServ->GetConnFromPool();
		if(pClient == NULL)
		{
			_Module.LogEvent(_T("too many connections"));
			continue;
		}
		pClient->sock = sockClient;
		pClient->addr = addr;
		pClient->lastActTick = GetTickCount();

		CreateIoCompletionPort((HANDLE)pClient->sock, pServ->m_hCompPort, (ULONG_PTR)pClient, 0);
		wsaBuf.buf = pClient->cmdBuf;
		WSARecv(pClient->sock, &wsaBuf, 1, &dwRecv, &dwFlag, &pClient->overlap, NULL);
	}
	OutputDebugString(_T("Exit Thread_Accepting"));
	return 0;
}

unsigned long CServiceModule::Thread_Receiving(LPVOID pParam)
{
	CServiceModule *pServ = (CServiceModule *)pParam;
	VEC_ClientInfo::iterator it;
	struct ClientInfo *pClient=NULL;
	LPOVERLAPPED pOverlap=NULL;
	DWORD dwRecv=0,dwFlag=0,dwThreadID,dwSize,dwHigh=0,cbData;
	int i=0, bRecv=0, nBlockSize=pServ->m_nBlock*1024*1024;
	//char *pBuf;
	TCHAR szText[256];
	WSABUF wsaBuf;

	dwThreadID = GetCurrentThreadId();
	_stprintf(szText, _T("Enter Thread_Receiving:%d\n"), dwThreadID);
	OutputDebugString(szText);
	while (_Module.m_status.dwCurrentState == SERVICE_RUNNING)
	{
		if(!GetQueuedCompletionStatus(pServ->m_hCompPort, &dwRecv, (PULONG_PTR)&pClient, &pOverlap, 3000))
		{
			DWORD dwErr = GetLastError();
			if(WAIT_TIMEOUT==dwErr || ERROR_NETNAME_DELETED==dwErr)//ERROR_OPERATION_ABORTED
			{
				Sleep(100);
				continue;
			} else //ERROR_INVALID_HANDLE
			{
				_Module.LogEvent(_T("GetQueuedCompletionStatus:=%d"), GetLastError());
				break;
			}
		}
		if(dwRecv == 0) // client close or quit
		{
			OutputDebugString(_T("dwRecv == 0"));
			pServ->ClearClientConn(pClient);
			//closesocket(pClient->sock);
			continue;
		}
		pClient->lastActTick = GetTickCount();
		OutputDebugStringA(pClient->cmdBuf);
		//if(!pClient->hFile && pClient->cmdBuf[0] !='H')
		//{
		//	OutputDebugString(_T("error cmd"));
		//	continue;
		//}
		if(pClient->hFile && pClient->nState&FLAG_DATA && pClient->pBlockBuf) // upload,write data
		{
			pClient->nState &= ~FLAG_DATA;
			pClient->cmdBuf[2] = 0; // receive next cmd
			WriteFile(pClient->hFile, pClient->pBlockBuf, dwRecv, &cbData, NULL);
			sprintf(szText, "%u", dwRecv);
			pServ->SendCmd(pClient->sock, 'U', 'D', szText, strlen(szText)+1);
		}
		wsaBuf.len = CMDBUFSIZE;
		wsaBuf.buf = pClient->cmdBuf;
		bRecv = 1;
		ZeroMemory(&pClient->overlap, sizeof(OVERLAPPED));
		switch(pClient->cmdBuf[2])
		{
		case 'Q':	// qury status
			dwSize = 0, dwHigh = 0;
			for(it=pServ->m_vClientInfo.begin(); it!=pServ->m_vClientInfo.end(); it++)
			{
				if(it->sock)
					dwSize++;
			}
			for(i=0; i<MAX_MEMBUFS; i++)
			{
				if(pServ->m_bufState[i] > 0)
					dwHigh++;
			}
			sprintf(szText, "C%d,M%d", dwSize, dwHigh);
			pServ->SendCmd(pClient->sock, 'Q', '0', szText, strlen(szText)+1);
			break;
		case 'U':	// upload
			pClient->nState = FLAG_UP;
			if(pClient->cmdBuf[3]=='F' && !pClient->hFile)
			{
				sscanf(pClient->cmdBuf+4, "%u,%u,%s", &dwSize, &dwHigh, szText);
				// TODO: file already exist
				pClient->hFile = CreateFile(szText, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL,NULL);
				if(pClient->hFile == INVALID_HANDLE_VALUE)
					pClient->hFile = NULL;
				if(pClient->hFile && !pClient->pBlockBuf)
					pClient->pBlockBuf = pServ->GetMemFromPool(i);

				if(pClient->pBlockBuf)
				{
					pClient->iBuf = i;
					pServ->m_bufState[i] = MEMSTAT_USED;
					sprintf(szText, "%d,0,0", pServ->m_nBlock);
					pServ->SendCmd(pClient->sock, 'U', 'B', szText, strlen(szText)+1);
				} else // create file, or alloc mem fail
				{
					pServ->SendCmd(pClient->sock, 'U', 'B', "0,0,0", 4);
				}
			}
			if(pClient->cmdBuf[3]=='D' && pClient->pBlockBuf) // data
			{
				pClient->nState |= FLAG_DATA;
				pClient->index = atoi(pClient->cmdBuf+4);//TODO: check index
				wsaBuf.len = nBlockSize;
				wsaBuf.buf = pClient->pBlockBuf;
			}
			break;
		case 'D':	// download
			pClient->nState = FLAG_DOWN;
			if(pClient->cmdBuf[3]=='F' && !pClient->hFile)
			{
				dwSize = 0, dwHigh = 0;
				pClient->hFile = CreateFile(pClient->cmdBuf+4, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL,NULL);
				if(pClient->hFile == INVALID_HANDLE_VALUE)
					pClient->hFile = NULL;
				if(pClient->hFile && !pClient->pBlockBuf)
				{
					pClient->pBlockBuf = pServ->GetMemFromPool(i);
					pClient->iBuf = i;
					pServ->m_bufState[i] = MEMSTAT_USED;
					dwSize = GetFileSize(pClient->hFile, &dwHigh);
				}
				if(pClient->pBlockBuf)
					sprintf(szText, "%d,%u,%u", pServ->m_nBlock, dwSize, dwHigh);
				else // file not exist, or alloc mem failed
					sprintf(szText, "%d,%u,%u", 0, dwSize, dwHigh);
				pServ->SendCmd(pClient->sock, 'D', 'F', szText, strlen(szText)+1);
			}
			if(pClient->cmdBuf[3]=='D' && pClient->hFile && pClient->pBlockBuf) // data
			{
				dwSize = GetFileSize(pClient->hFile, NULL);
				pClient->index = atoi(pClient->cmdBuf+4);//TODO: check index
				dwSize = min((int)dwSize-pClient->index*nBlockSize, nBlockSize);
				ReadFile(pClient->hFile, pClient->pBlockBuf, dwSize, &cbData, NULL);
				send(pClient->sock, pClient->pBlockBuf, cbData, 0);
			}
			break;
		case 'R':	// remove file
			i = DeleteFile(pClient->cmdBuf + 4);
			pServ->SendCmd(pClient->sock, 'R', (char)('0'+i), NULL, 0);
			break;
		case 'C':	// close connection
			pServ->SendCmd(pClient->sock, 'C', '0', NULL, 0);
			pServ->ClearClientConn(pClient);
			bRecv = 0;
			break;
		case 'E':	// exit service
			OutputDebugString("Exit File Server by command H0E0\n");
			pServ->SendCmd(pClient->sock, 'E', '0', NULL, 0);
			PostThreadMessage(pServ->m_dwMainThreadID, WM_QUIT, 0, 0);
			break;
		default:
			break;
		}
		ZeroMemory(&pClient->cmdBuf, CMDBUFSIZE);
		if(bRecv)
			WSARecv(pClient->sock, &wsaBuf, 1, &dwRecv, &dwFlag, &pClient->overlap, NULL);
	}
	_stprintf(szText, _T("Exit Thread_Receiving:%d\n"), dwThreadID);
	OutputDebugString(szText);
	return 0;
}
