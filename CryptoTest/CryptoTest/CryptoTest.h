// CryptoTest.h : main header file for the CRYPTOTEST application
//

#if !defined(AFX_CRYPTOTEST_H__8BF8CCE9_EB5D_482F_B31D_B254F0D3808E__INCLUDED_)
#define AFX_CRYPTOTEST_H__8BF8CCE9_EB5D_482F_B31D_B254F0D3808E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestApp:
// See CryptoTest.cpp for the implementation of this class
//

class CCryptoTestApp : public CWinApp
{
public:
	CCryptoTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptoTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCryptoTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTOTEST_H__8BF8CCE9_EB5D_482F_B31D_B254F0D3808E__INCLUDED_)
