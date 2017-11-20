// BatchDownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BatchDown.h"
#include "BatchDownDlg.h"
#include "NewTaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchDownDlg dialog

CBatchDownDlg::CBatchDownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchDownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBatchDownDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dwFlag = 0;
}

void CBatchDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchDownDlg)
	DDX_Control(pDX, IDC_LISTTASK, m_listTask);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBatchDownDlg, CDialog)
	//{{AFX_MSG_MAP(CBatchDownDlg)
	ON_BN_CLICKED(IDC_ADDTASK, OnAddtask)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchDownDlg message handlers

BOOL CBatchDownDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_listTask.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString strText;
	strText.LoadString(IDS_NAME);
	m_listTask.InsertColumn(COL_NAME, strText, LVCFMT_LEFT, 70);
	strText.LoadString(IDS_SIZE);
	m_listTask.InsertColumn(COL_SIZE, strText, LVCFMT_LEFT, 70);
	strText.LoadString(IDS_STATE);
	m_listTask.InsertColumn(COL_STATE, strText, LVCFMT_LEFT, 60);
	strText.LoadString(IDS_URL);
	m_listTask.InsertColumn(COL_URL, strText, LVCFMT_LEFT, 260);

	LoadConfig();
	//m_nBufSize = 2*1024*1024; // 2M
	m_pBuf = new BYTE[m_nBufSize];
	//m_sDestPath = "F:\\";

	SetTimer(TMID_MONITOR, 1500, NULL);
	m_dwFlag |= FLAG_RUNNING;
	DWORD dwThreadID;
	HANDLE hThread = CreateThread(NULL, 0, Thread_Down, this, 0, &dwThreadID);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

int CBatchDownDlg::LoadConfig()
{
	TCHAR szPath[MAX_PATH],szText[256]={0};

	theApp.GetCurPath(szPath);
	lstrcat(szPath, "\\BatchDown.ini");
	m_nBufSize = 1024*GetPrivateProfileInt("Config", "BufSize", 2048, szPath);
	GetPrivateProfileString("Config", "DestPath", NULL, szText,256, szPath);
	m_sDestPath = szText[0]? szText : "F:\\";
	if(m_sDestPath.GetAt(m_sDestPath.GetLength()-1) != '\\')
		m_sDestPath += '\\';
	return 0;
}

DWORD WINAPI CBatchDownDlg::Thread_Down(LPVOID pParam)
{
	CBatchDownDlg *pDlg = (CBatchDownDlg*)pParam;
	CString sState;
	int i, nCount, nRet;

	OutputDebugString("enter Thread_Down");
	while (pDlg->m_dwFlag & FLAG_RUNNING)
	{
		Sleep(200);
		if(!(pDlg->m_dwFlag & FLAG_DOWNING))
		{
			continue;
		}
		sState.LoadString(IDS_DOWNING);
		pDlg->SetDlgItemText(IDC_INFO, sState);
		nCount = pDlg->m_listTask.GetItemCount();
		for (i=0; i<nCount; i++)
		{
			sState = pDlg->m_listTask.GetItemText(i, COL_STATE);
			if(!sState.IsEmpty())
				continue;
			pDlg->m_listTask.SetItemText(i, COL_STATE, "D...");
			nRet = pDlg->DownINetFile(i);
			if (nRet == 0)
			{
				sState = "OK";
			} 
			else // error
			{
				sState.Format("er:%d", nRet);
			}
			pDlg->m_listTask.SetItemText(i, COL_STATE, sState);
		}
		pDlg->m_dwFlag &= ~FLAG_DOWNING;
		sState.LoadString(IDS_ADDTASK);
		pDlg->SetDlgItemText(IDC_INFO, sState);
	}
	OutputDebugString("exit Thread_Down");
	return 0;
}

int CBatchDownDlg::DownINetFile(int idx) 
{
	CString sUrl, sDestFile,sNum;
	sUrl = m_listTask.GetItemText(idx, COL_URL);
	if (sUrl.IsEmpty())
		return -1;

	DWORD dwStatusCode = 0;
	int nSize, nRet=0;
	try
	{
		CInternetSession session(_T("HttpClient"));
		CHttpFile *pfile = (CHttpFile *)session.OpenURL(sUrl);
		if (!pfile)
		{
			theApp.DbgMsg(_T("OpenURL:%s =%d"), sUrl, GetLastError());
			return -2;
		}
		pfile->QueryInfoStatusCode(dwStatusCode);
		if(dwStatusCode == HTTP_STATUS_OK)
		{
			if(m_sSubFolder.IsEmpty())
				sDestFile = m_sDestPath;
			else
				sDestFile.Format("%s%s\\", m_sDestPath, m_sSubFolder);
			sDestFile += sUrl.Mid(sUrl.ReverseFind('/')+1); // filename
			nSize = pfile->SeekToEnd();//GetLength();
			pfile->SeekToBegin();
			if(nSize > 0)
			{
				if(nSize < 1024)
					sNum.Format("%dB", nSize);
				else if(nSize < 1024*1024)
					sNum.Format("%dK", nSize/1024);
				else
					sNum.Format("%.2fM", nSize/1024/1024.0f);
				m_listTask.SetItemText(idx, COL_SIZE, sNum);
				nRet = SaveHttpFile(pfile, nSize, sDestFile);
			} else
			{
				nRet = -5;
			}
		} else
		{
			theApp.DbgMsg(_T("QueryInfoStatusCode:%s =%d"), sUrl, dwStatusCode);
		}
		pfile->Close();
		delete pfile;
		session.Close();
	}
	catch (CException* pEx)//
	{
		TCHAR szErr[256];
		pEx->GetErrorMessage(szErr, 256);
		theApp.DbgMsg(_T("readurl fail:%s"), sUrl, szErr);
	}
	if(dwStatusCode != HTTP_STATUS_OK)
		nRet = dwStatusCode;
	return nRet;
}

int CBatchDownDlg::SaveHttpFile(CHttpFile *pfile, int nSize, CString sDestFile) 
{
	int nRead=1;
	DWORD cbData;

	theApp.DbgMsg("save %s, size=%d", sDestFile, nSize);
	HANDLE hFile = CreateFile(sDestFile, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return -4;
	while (nSize > 0)
	{
		nRead = pfile->Read(m_pBuf, m_nBufSize);
		WriteFile(hFile, m_pBuf, nRead, &cbData, NULL);
		nSize -= nRead;
	}
	CloseHandle(hFile);
	return 0;
}

// check clipboard for new url
int CBatchDownDlg::CheckClipBoard()
{
	if(!OpenClipboard())
		return -1;
	CString sClipText;
	int nRet = 0;
	if(IsClipboardFormatAvailable(CF_TEXT))
	{
		HANDLE hClip = GetClipboardData(CF_TEXT);
		char* pBuf=(char*)GlobalLock(hClip);
		sClipText = pBuf;
		GlobalUnlock(hClip);
	}
	CloseClipboard();
	if (sClipText.Find("http")==0 && m_sClipText.Compare(sClipText))
	{
		m_sClipText = sClipText;
		nRet = 1;
	}
	return nRet;
}
void CBatchDownDlg::OnTimer(UINT nIDEvent) 
{
	if (TMID_MONITOR == nIDEvent)
	{
		if (!(m_dwFlag&FLAG_ADDTASK) && CheckClipBoard() > 0) // new url find
		{
			OnAddtask();
		}
	}	
	CDialog::OnTimer(nIDEvent);
}

void CBatchDownDlg::OnAddtask() 
{
	m_dwFlag |= FLAG_ADDTASK;
	CNewTaskDlg dlg(this, m_sClipText);
	if(IDCANCEL == dlg.DoModal())
	{
		m_dwFlag &= ~FLAG_ADDTASK;
		return;
	}

	int i=0, il,ir;
	CString sUrl,sName;
	CStringList& listUrl = dlg.GetUrlList();
	m_sSubFolder = dlg.GetSubFolder();
	POSITION pos;
	pos = listUrl.GetHeadPosition();
	while (pos != NULL)
	{
		sUrl = listUrl.GetNext(pos);
		il = sUrl.ReverseFind('/') + 1;
		ir = sUrl.ReverseFind('.');
		sName = sUrl.Mid(il, ir-il);
		m_listTask.InsertItem(i, sName);
		m_listTask.SetItemText(i, COL_URL, sUrl);
		i++;
	}
	m_dwFlag &= ~FLAG_ADDTASK;
}

void CBatchDownDlg::OnOK() 
{
	m_dwFlag |= FLAG_DOWNING;
	//CDialog::OnOK();
}

void CBatchDownDlg::OnClear() 
{
	m_listTask.DeleteAllItems();
}

void CBatchDownDlg::OnCancel() 
{
	if(m_pBuf)
		delete [] m_pBuf;
	m_dwFlag = 0;
	KillTimer(TMID_MONITOR);
	Sleep(500); // wait thread exit
	CDialog::OnCancel();
}
