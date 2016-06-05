// FileTransClient.h : main header file for the FILETRANSCLIENT application
//

#if !defined(AFX_FILETRANSCLIENT_H__17CD5227_4DFF_414D_87AA_09BADB48D385__INCLUDED_)
#define AFX_FILETRANSCLIENT_H__17CD5227_4DFF_414D_87AA_09BADB48D385__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileTransClientApp:
// See FileTransClient.cpp for the implementation of this class
//

class CFileTransClientApp : public CWinApp
{
public:
	CFileTransClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileTransClientApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSCLIENT_H__17CD5227_4DFF_414D_87AA_09BADB48D385__INCLUDED_)
