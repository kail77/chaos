// SparseCodec.h : main header file for the SPARSECODEC application
//

#if !defined(AFX_SPARSECODEC_H__E3B0A610_50F8_49F4_B540_60B73CA4129B__INCLUDED_)
#define AFX_SPARSECODEC_H__E3B0A610_50F8_49F4_B540_60B73CA4129B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSparseCodecApp:
// See SparseCodec.cpp for the implementation of this class
//

class CSparseCodecApp : public CWinApp
{
public:
	CSparseCodecApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSparseCodecApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSparseCodecApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPARSECODEC_H__E3B0A610_50F8_49F4_B540_60B73CA4129B__INCLUDED_)
