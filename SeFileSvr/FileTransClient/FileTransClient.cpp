// FileTransClient.cpp : Defines the class behaviors for the application.
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
// CFileTransClientApp

BEGIN_MESSAGE_MAP(CFileTransClientApp, CWinApp)
	//{{AFX_MSG_MAP(CFileTransClientApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransClientApp construction

CFileTransClientApp::CFileTransClientApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileTransClientApp object

CFileTransClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFileTransClientApp initialization

BOOL CFileTransClientApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFileTransClientDlg dlg;
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
