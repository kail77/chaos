// TestPrint.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestPrint.h"
#include "TestPrintDlg.h"
#include <initguid.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #if defined(UNICODE) || defined(_UNICODE)
#pragma comment (linker, "/ENTRY:wWinMainCRTStartup")
// #else
// #pragma comment (linker, "/ENTRY:WinMainCRTStartup")
// #endif


/////////////////////////////////////////////////////////////////////////////
// CTestPrintApp

BEGIN_MESSAGE_MAP(CTestPrintApp, CWinApp)
	//{{AFX_MSG_MAP(CTestPrintApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPrintApp construction

CTestPrintApp::CTestPrintApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestPrintApp object

CTestPrintApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestPrintApp initialization

BOOL CTestPrintApp::InitInstance()
{
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}
	// Standard initialization

	//Enable3dControls();			// Call this when using MFC in a shared DLL

	CTestPrintDlg dlg;
	m_pMainWnd = &dlg;
	//int nResponse = (int)dlg.DoModal();
	dlg.Create(dlg.IDD);
	dlg.ShowWindow(SW_SHOWNORMAL);
	dlg.RunModalLoop();
	dlg.DestroyWindow();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTestPrintApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
