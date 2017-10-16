
// SeerWin.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSeerWinApp:
// See SeerWin.cpp for the implementation of this class
//

class CSeerWinApp : public CWinApp
{
public:
	CSeerWinApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSeerWinApp theApp;