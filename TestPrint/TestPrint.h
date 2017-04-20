// TestPrint.h : main header file for the TESTPRINT application
//

#if !defined(AFX_TESTPRINT_H__C171EE40_35E0_446A_87C0_C5D8B7E1D16B__INCLUDED_)
#define AFX_TESTPRINT_H__C171EE40_35E0_446A_87C0_C5D8B7E1D16B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestPrintApp:
// See TestPrint.cpp for the implementation of this class
//

class CTestPrintApp : public CWinApp
{
public:
	CTestPrintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestPrintApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINT_H__C171EE40_35E0_446A_87C0_C5D8B7E1D16B__INCLUDED_)
