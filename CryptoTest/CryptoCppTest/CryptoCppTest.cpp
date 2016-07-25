// CryptoCppTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CryptoCppTest.h"
#include "CryptoCppTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestApp

BEGIN_MESSAGE_MAP(CCryptoCppTestApp, CWinApp)
	//{{AFX_MSG_MAP(CCryptoCppTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestApp construction

CCryptoCppTestApp::CCryptoCppTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCryptoCppTestApp object

CCryptoCppTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestApp initialization

BOOL CCryptoCppTestApp::InitInstance()
{
	// Standard initialization

	CCryptoCppTestDlg dlg;
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
