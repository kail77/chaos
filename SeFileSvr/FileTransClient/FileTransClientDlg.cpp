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
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
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
	SetDlgItemInt(IDC_PORT, 5500);

	WSADATA wd;
	int nStart = WSAStartup(MAKEWORD(2,2), &wd);//0=succ
	m_nState = 0;
	m_hThreadTrans = NULL;
	m_pBuf = (char*)malloc(8*1024*1024);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileTransClientDlg::OnBrowser() 
{
	
}

void CFileTransClientDlg::OnOK() 
{
	unsigned long dwID;

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	m_nState = FLAG_RUNNING;
	int n = GetCheckedRadioButton(IDC_UPLOAD, IDC_DOWNLOAD);
	if(n == IDC_DOWNLOAD)
		m_nState |= FLAG_DOWNLOAD;
	m_prgsTransfer.SetStep(1);
	m_bMemOnly = ((CButton*)GetDlgItem(IDC_MEMONLY))->GetCheck();

	TCHAR szText[256];
	GetDlgItemText(IDC_SERVER, szText, 256);
	n = GetDlgItemInt(IDC_PORT);
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(n);
	m_addr.sin_addr.S_un.S_addr = inet_addr(szText);

	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockClient)
		AfxMessageBox("create socket fail");

	if(SOCKET_ERROR==connect(m_sockClient, (SOCKADDR*)&m_addr, sizeof(sockaddr_in)))
	{
		sprintf(szText, "connect error=%d\n", WSAGetLastError());
		AfxMessageBox(szText);
		return;
	}

	if(m_hThreadTrans == NULL)
		m_hThreadTrans = CreateThread(NULL,0, Thread_Transfering, this, 0,&dwID);
	if(m_hThreadTrans == NULL)
		AfxMessageBox("CreateThread fail");
	//CDialog::OnOK();
}

unsigned long CFileTransClientDlg::Thread_Transfering(LPVOID pParam)
{
	TCHAR szServerFile[256],szLocalFile[256];
	char szCmd[256]="H0UF";
	CFileTransClientDlg *pDlg = (CFileTransClientDlg *)pParam;
	OutputDebugString(_T("Enter Thread_Transfering\n"));

	pDlg->GetDlgItemText(IDC_SERVERFILE, szServerFile, 256);
	pDlg->GetDlgItemText(IDC_LOCALFILE, szLocalFile, 256);
	//while (pDlg->m_nState & FLAG_RUNNING)
	{
		pDlg->TransFile(szServerFile, szLocalFile);
		Sleep(1000);
	}
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->m_hThreadTrans = NULL;
	OutputDebugString(_T("Exit Thread_Transfering\n"));
	return 0;
}

int CFileTransClientDlg::TransFile(LPTSTR pServerFile, LPTSTR pLocalFile) 
{
	char szCmd[256], szBuf[256]={0}, *pbuf;
	int nBlockM, nBlockSize=8*1024*1024;
	int i,n,nTimes,nLeft,nSize;
	DWORD dwSize,dwHigh,cbData;
	HANDLE hFile = NULL;
	LONGLONG lSize;

	m_prgsTransfer.SetPos(0);
	if(m_nState & FLAG_DOWNLOAD)
	{
		sprintf(szCmd, "H0DF%s", pServerFile);
	} else // upload
	{
		hFile = CreateFile(pLocalFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return GetLastError();
		GetFileSizeEx(hFile, (PLARGE_INTEGER)&lSize);
		if(lSize == 0)
			return -1;
		sprintf(szCmd, "H0UF%u,%u,%s", lSize&0xffffffff, lSize>>32, pServerFile);
	}
	send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
	Sleep(10);
	n = recv(m_sockClient, szBuf, 256, 0);
	if (szBuf[0] != 'H' || n == 0)
	{
		return -2;
	}

	szCmd[3] = 'D'; //data
	if(m_nState & FLAG_DOWNLOAD)
	{
		sscanf(szBuf+4, "%d,%u,%u", &nBlockM, &dwSize, &dwHigh);
		lSize = dwHigh;
		lSize = (lSize<<32) + dwSize;
		if(!m_bMemOnly)
			hFile = CreateFile(pLocalFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return GetLastError();
		nTimes = (int)(lSize/nBlockSize) + ((lSize%nBlockSize)>0);
		m_prgsTransfer.SetRange32(0, nTimes);
		for(i=0; i<nTimes; i++)
		{
			sprintf(szCmd, "H0DD%d", i);
			send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
			nLeft = nBlockSize;
			if (i==nTimes-1 && (lSize%nBlockSize)>0)
				nLeft = (int)(lSize % nBlockSize);
			nSize = nLeft;
			pbuf = m_pBuf;
			while (nLeft > 0)
			{
				n = recv(m_sockClient, pbuf, nLeft, 0);
				if(n == 0)
				{
					TRACE("recv %d bytes", n);
					CloseHandle(hFile);
					return -3;
				}
				nLeft -= n;
				pbuf += n;
			}
			if(!m_bMemOnly)
				WriteFile(hFile, m_pBuf, nSize, &cbData, NULL);
			m_prgsTransfer.StepIt();
		}
		send(m_sockClient, "H0C0", 5, 0);
	} else // upload
	{
		sscanf(szBuf+4, "%d", &nBlockM);
		nTimes = (int)(lSize/nBlockSize) + ((lSize%nBlockSize)>0);
		m_prgsTransfer.SetRange32(0, nTimes);
		for(i=0; i<nTimes; i++)
		{
			sprintf(szCmd, "H0UD%d", i); // upload data #
			send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
			n = min(lSize-i*nBlockSize, nBlockSize);
			ReadFile(hFile, m_pBuf, n, &cbData, NULL);
			send(m_sockClient, m_pBuf, n, 0);
			recv(m_sockClient, szBuf, 256, 0);
			m_prgsTransfer.StepIt();
		}
		send(m_sockClient, "H0C0", 5, 0); // tell server to close connection
	}
	shutdown(m_sockClient, SD_BOTH);
	closesocket(m_sockClient);
	if(hFile)
		CloseHandle(hFile);
	return 0;
}

void CFileTransClientDlg::OnCancel() 
{
	m_nState = 0;
	shutdown(m_sockClient, SD_BOTH);
	closesocket(m_sockClient);
	WSACleanup();
	WaitForSingleObject(m_hThreadTrans, INFINITE);
	free(m_pBuf);
	CDialog::OnCancel();
}
