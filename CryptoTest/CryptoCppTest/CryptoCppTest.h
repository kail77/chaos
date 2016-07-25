// CryptoCppTest.h : main header file for the CRYPTOCPPTEST application
//

#if !defined(AFX_CRYPTOCPPTEST_H__548FA081_AF59_4970_A3B7_C23DE1515F38__INCLUDED_)
#define AFX_CRYPTOCPPTEST_H__548FA081_AF59_4970_A3B7_C23DE1515F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestApp:
// See CryptoCppTest.cpp for the implementation of this class
//

class CCryptoCppTestApp : public CWinApp
{
public:
	CCryptoCppTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptoCppTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCryptoCppTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTOCPPTEST_H__548FA081_AF59_4970_A3B7_C23DE1515F38__INCLUDED_)
