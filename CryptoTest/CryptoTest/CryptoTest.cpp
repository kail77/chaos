// CryptoTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CryptoTest.h"
#include "CryptoTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestApp

BEGIN_MESSAGE_MAP(CCryptoTestApp, CWinApp)
	//{{AFX_MSG_MAP(CCryptoTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestApp construction

CCryptoTestApp::CCryptoTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCryptoTestApp object

CCryptoTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestApp initialization

BOOL CCryptoTestApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCryptoTestDlg dlg;
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
