// BatchDown.h : main header file for the BATCHDOWN application
//

#if !defined(AFX_BATCHDOWN_H__0F1A7A16_AC91_48BD_B8E9_4123BBA77DE0__INCLUDED_)
#define AFX_BATCHDOWN_H__0F1A7A16_AC91_48BD_B8E9_4123BBA77DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBatchDownApp:
// See BatchDown.cpp for the implementation of this class
//

class CBatchDownApp : public CWinApp
{
public:
	CBatchDownApp();
	void DbgMsg(LPCTSTR pfmt, ... );
	inline void GetCurPath(LPTSTR pszPath) {lstrcpy(pszPath, m_szCurPath);}

private:
	TCHAR m_szCurPath[MAX_PATH];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchDownApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBatchDownApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CBatchDownApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHDOWN_H__0F1A7A16_AC91_48BD_B8E9_4123BBA77DE0__INCLUDED_)
