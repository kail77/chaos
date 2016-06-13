// FileTransClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileTransClient.h"
#include "FileTransClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BLOCKM 8 // 分块最大8M内存

/////////////////////////////////////////////////////////////////////////////
// CFileTransClientDlg dialog

CFileTransClientDlg::CFileTransClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTransClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileTransClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTransClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTransClientDlg)
	DDX_Control(pDX, IDC_PRGSTRANS, m_prgsTransfer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileTransClientDlg, CDialog)
	//{{AFX_MSG_MAP(CFileTransClientDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransClientDlg message handlers

BOOL CFileTransClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CheckRadioButton(IDC_UPLOAD, IDC_DOWNLOAD, IDC_UPLOAD);
	SetDlgItemText(IDC_SERVER, "127.0.0.1");
	SetDlgItemInt(IDC_PORT, 15500);

	WSADATA wd;
	int nStart = WSAStartup(MAKEWORD(2,2), &wd);//0=succ
	m_nState = 0;
	m_hThreadTrans = NULL;
	m_pBuf = NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileTransClientDlg::OnOK() 
{
	unsigned long dwID;

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	int n = GetCheckedRadioButton(IDC_UPLOAD, IDC_DOWNLOAD);
	m_nState = 0;
	if(n == IDC_DOWNLOAD)
		m_nState |= FLAG_DOWNLOAD;
	m_bMemOnly = ((CButton*)GetDlgItem(IDC_MEMONLY))->GetCheck();

	TCHAR szText[256];
	GetDlgItemText(IDC_SERVER, szText, 256);
	n = GetDlgItemInt(IDC_PORT);
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(n);
	m_addr.sin_addr.S_un.S_addr = inet_addr(szText);

	if(m_hThreadTrans == NULL)
		m_hThreadTrans = CreateThread(NULL,0, Thread_Transfering, this, 0,&dwID);
	if(m_hThreadTrans == NULL)
		AfxMessageBox("CreateThread fail");
	//CDialog::OnOK();
}

unsigned long CFileTransClientDlg::Thread_Transfering(LPVOID pParam)
{
	TCHAR szServerFile[256],szLocalFile[256],szText[256];
	CFileTransClientDlg *pDlg = (CFileTransClientDlg *)pParam;
	OutputDebugString(_T("Enter Thread_Transfering\n"));

	pDlg->GetDlgItemText(IDC_SERVERFILE, szServerFile, 256);
	pDlg->GetDlgItemText(IDC_LOCALFILE, szLocalFile, 256);

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sockClient)
		AfxMessageBox("create socket fail");

	if(SOCKET_ERROR==connect(sockClient, (SOCKADDR*)&pDlg->m_addr, sizeof(sockaddr_in)))
	{
		sprintf(szText, "connect error=%d\n", WSAGetLastError());
		AfxMessageBox(szText);
		return 0;
	}
	if (!pDlg->m_pBuf)
		pDlg->m_pBuf = (char*)malloc(MAX_BLOCKM*1024*1024);

	//while (pDlg->m_nState & FLAG_RUNNING)
	{
		pDlg->m_prgsTransfer.SetPos(0);
		pDlg->m_prgsTransfer.SetRange32(0, 100);
		pDlg->TransFile(sockClient, pDlg->m_nState, szServerFile, szLocalFile, pDlg->m_pBuf);
		Sleep(1000);
	}
	send(sockClient, "H0C0", 5, 0); // tell server to close connection
	shutdown(sockClient, SD_BOTH);
	closesocket(sockClient);

	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->m_hThreadTrans = NULL;
	OutputDebugString(_T("Exit Thread_Transfering\n"));
	return 0;
}
// iPos: 0~100
void CFileTransClientDlg::UpdateProgress(int iPos)
{
	CFileTransClientDlg *pDlg = (CFileTransClientDlg *)AfxGetApp()->GetMainWnd();
	pDlg->m_prgsTransfer.SetPos(iPos);
}

int CFileTransClientDlg::TransFile(SOCKET sock, int nState, LPTSTR pServerFile, LPTSTR pLocalFile, LPSTR pBuf) 
{
	char szCmd[256], szBuf[256]={0};
	int nBlockM=MAX_BLOCKM, nBlockSize=MAX_BLOCKM*1024*1024;
	int i,n,nTimes,nLeft;
	DWORD cbData, dwSize, dwHigh;
	HANDLE hFile = NULL;
	LONGLONG lSize,lSaved; // file size

	if (!pServerFile || !pLocalFile)
		return ERROR_INVALID_PARAMETER;

	if(nState & FLAG_DOWNLOAD)
	{
		hFile = CreateFile(pLocalFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return GetLastError();
		sprintf(szCmd, "H0DF%s", pServerFile);
	} else // upload
	{
		hFile = CreateFile(pLocalFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return GetLastError();
		GetFileSizeEx(hFile, (PLARGE_INTEGER)&lSize);
		if(lSize == 0)
		{
			CloseHandle(hFile);
			return ERROR_EMPTY;
		}
		sprintf(szCmd, "H0UF%u,%u,%s", (DWORD)(lSize&0xffffffff), (DWORD)(lSize>>32), pServerFile);
	}
	send(sock, szCmd, 1+strlen(szCmd), 0);
	Sleep(10);
	n = recv(sock, szBuf, 256, 0);
	if (szBuf[0] != 'H' || n <= 0)
	{
		CloseHandle(hFile);
		return ERROR_BAD_COMMAND;
	}

	sscanf(szBuf+4, "%d,%u,%u", &nBlockM, &dwSize, &dwHigh);
	if(nBlockM <= 0 || nBlockM > MAX_BLOCKM)
		nBlockM = MAX_BLOCKM;
	nBlockSize = nBlockM*1024*1024;
	szCmd[3] = 'D'; //data
	lSaved = 0;
	if(nState & FLAG_DOWNLOAD)
	{
		lSize = dwHigh;
		lSize = (lSize<<32) + dwSize;
		nTimes = (int)(lSize/nBlockSize) + ((lSize%nBlockSize)>0);
		for(i=0; i<nTimes; i++)
		{
			sprintf(szCmd, "H0DD%d", i);
			send(sock, szCmd, 1+strlen(szCmd), 0);
			nLeft = nBlockSize;
			if (i==nTimes-1 && (lSize%nBlockSize)>0)
				nLeft = (int)(lSize % nBlockSize);
			dwSize = nLeft;
			char *pb = pBuf;
			while (nLeft > 0)
			{
				n = recv(sock, pb, nLeft, 0);
				if(n <= 0)
				{
					TRACE("recv failed: %d,err=%d", n, WSAGetLastError());
					CloseHandle(hFile);
					return ERROR_CONNECTION_INVALID;
				}
				nLeft -= n;
				pb += n;
				lSaved += n;
				UpdateProgress((int)(100*lSaved/lSize));
			}
			WriteFile(hFile, pBuf, dwSize, &cbData, NULL);
		}
	} else // upload
	{
		nTimes = (int)(lSize/nBlockSize) + ((lSize%nBlockSize)>0);
		for(i=0; i<nTimes; i++)
		{
			nLeft = nBlockSize;
			if (i==nTimes-1 && (lSize%nBlockSize)>0)
				nLeft = (int)(lSize % nBlockSize);
			sprintf(szCmd, "H0UD%d,%d", i, nLeft); // upload data #
			send(sock, szCmd, 1+strlen(szCmd), 0);
			Sleep(10);
			ReadFile(hFile, pBuf, nLeft, &cbData, NULL);
			n = send(sock, pBuf, nLeft, 0); // will return immediately 
			if(n <= 0)
			{
				TRACE("send failed: %d,err=%d", n, WSAGetLastError());
				CloseHandle(hFile);
				return ERROR_CONNECTION_ABORTED;
			}
			lSaved += n;
			recv(sock, szBuf, 256, 0);
			UpdateProgress((int)(100*lSaved/lSize));
			Sleep(10);
		}
	}
	if(hFile)
		CloseHandle(hFile);
	send(sock, "H0F0", 5, 0); // finish file transfer
	return 0;
}

void CFileTransClientDlg::OnCancel() 
{
	m_nState = 0;
	WSACleanup();
	if(m_hThreadTrans)
		WaitForSingleObject(m_hThreadTrans, INFINITE);
	if(m_pBuf)
		free(m_pBuf);
	CDialog::OnCancel();
}
