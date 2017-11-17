// BatchDown.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BatchDown.h"
#include "BatchDownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchDownApp

BEGIN_MESSAGE_MAP(CBatchDownApp, CWinApp)
	//{{AFX_MSG_MAP(CBatchDownApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchDownApp construction

CBatchDownApp::CBatchDownApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBatchDownApp object

CBatchDownApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBatchDownApp initialization

BOOL CBatchDownApp::InitInstance()
{
	// Standard initialization
	GetModuleFileName(NULL, m_szCurPath, MAX_PATH);
	LPTSTR pc = strrchr(m_szCurPath, '\\');
	if(pc)	*pc = 0;

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CBatchDownDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CBatchDownApp::DbgMsg(LPCTSTR pfmt, ... )
{
	va_list pArgs;
	TCHAR szMsg[512];//,szPath[256];
	
	va_start(pArgs, pfmt);
	wvsprintf(szMsg, pfmt, pArgs);
	va_end(pArgs);
	OutputDebugString(szMsg);
	/*if(!(gdwFlag & FLAG_SAVEMSG))
		return;

	char szLog[512];
	int nLen = WideCharToMultiByte(CP_ACP,0, szMsg,-1, szLog,512, NULL,NULL);
	strcat(szLog, "\r\n");
	_stprintf(szPath, _T("%s\\PRNDATA\\urllogon.log"), gszCurPath);
	FILE *fpLog = _tfopen(szPath, _T("a+"));
	if(fpLog)
	{
		fwrite(szLog, nLen+1, 1, fpLog);
		fclose(fpLog);
	}*/
}
