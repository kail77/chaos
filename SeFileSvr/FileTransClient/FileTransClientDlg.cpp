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
		// NOTE: the ClassWizard will add DDX and DDV calls here
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
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sockClient)
		AfxMessageBox("create socket fail");
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

	TCHAR szText[256];
	GetDlgItemText(IDC_SERVER, szText, 256);
	n = GetDlgItemInt(IDC_PORT);
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(n);
	m_addr.sin_addr.S_un.S_addr = inet_addr(szText);

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
	OutputDebugString(_T("Exit Thread_Transfering\n"));
	return 0;
}

int CFileTransClientDlg::TransFile(LPTSTR pServerFile, LPTSTR pLocalFile) 
{
	char szCmd[256]="H0UF", szBuf[256];
	int nBlock,i,n,nBlockSize=8*1024*1024;
	DWORD dwSize,dwHigh,cbData;
	HANDLE hFile;

	strcat(szCmd, pServerFile);
	if(m_nState & FLAG_DOWNLOAD)
		szCmd[2] = 'D';
	else
		szCmd[2] = 'U';
	send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
	Sleep(10);
	recv(m_sockClient, szBuf, 256, 0);
	OutputDebugString(szBuf);
	szCmd[3] = 'D';
	if(m_nState & FLAG_DOWNLOAD)
	{
		sscanf(szBuf+4, "%d,%d,%d", &nBlock, &dwSize, &dwHigh);
		//TODO:check file size
		for(i=0; i<=(int)(dwSize/nBlockSize); i++)
		{
			sprintf(szCmd, "H0DD%d", i);
			send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
			recv(m_sockClient, m_pBuf, nBlockSize, 0);
			OutputDebugString(m_pBuf);
		}
		send(m_sockClient, "H0C0", 5, 0);
	} else // upload
	{
		hFile = CreateFile(pLocalFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			return GetLastError();
		dwSize = GetFileSize(hFile, &dwHigh);
		sscanf(szBuf+4, "%d", &nBlock);
		for(i=0; i<=(int)(dwSize/nBlockSize); i++)
		{
			sprintf(szCmd, "H0UD%d", i);
			send(m_sockClient, szCmd, 1+strlen(szCmd), 0);
			n = min(dwSize-i*nBlock, (DWORD)nBlockSize);
			ReadFile(hFile, m_pBuf, n, &cbData, NULL);
			send(m_sockClient, m_pBuf, n, 0);
			recv(m_sockClient, szBuf, 256, 0);
			OutputDebugString(szBuf);
		}
		send(m_sockClient, "H0C0", 5, 0);
	}
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
