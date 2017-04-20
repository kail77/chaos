// TestPrintDlg.h : header file
//

#if !defined(AFX_TESTPRINTDLG_H__EBD076BE_31EF_4A84_81FF_F8B101FF0ACF__INCLUDED_)
#define AFX_TESTPRINTDLG_H__EBD076BE_31EF_4A84_81FF_F8B101FF0ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_OEMDRV 8
#define MAX_OEMDEV 8
#define NAMELEN 16
#define MAX_DRVPAGE 8

typedef LONG_PTR (CALLBACK *PFNCOMPROPSHEET)(HANDLE hComPropSheet, UINT Function, LPARAM lParam1, LPARAM lParam2);
//typedef HWND (WINAPI *PFNSHOWDEVICECONFIG)(HWND hWndParent, BOOL bShow);
//typedef int (WINAPI *PFNGETPROPPAGES)(int nPage, CPropertyPage **pPages, LPVOID lpVoid);
typedef int (WINAPI *PFNUIPROPShEETS)(LPVOID pUiData);

#define PATH_REG _T("Printers\\Settings")
#define PATH_DRV _T("F:\\")


#define PROPSHEETUI_INFO_VERSION            0x0100
#define PSUIINFO_UNICODE                    0x0001
#define PROPSHEETUI_REASON_INIT             0
#define PROPSHEETUI_REASON_DESTROY          2

typedef struct _PROPSHEETUI_INFO {
	WORD  cbSize;
	WORD  Version;
	WORD  Flags;
	WORD  Reason;
	HANDLE  hComPropSheet;
	PFNCOMPROPSHEET  pfnComPropSheet;
	LPARAM  lParamInit;
	ULONG_PTR  UserData;
	ULONG_PTR  Result;
} PROPSHEETUI_INFO, *PPROPSHEETUI_INFO;

typedef struct _DOCUMENTPROPERTYHEADER {
	WORD    cbSize;
	WORD    Reserved;
	HANDLE  hPrinter;
	LPTSTR  pszPrinterName;
	PDEVMODE  pdmIn;
	PDEVMODE  pdmOut;
	DWORD   cbOut;
	DWORD   fMode;
} DOCUMENTPROPERTYHEADER, *PDOCUMENTPROPERTYHEADER;

typedef LONG (WINAPI *PFNDRVDOCPST)(PPROPSHEETUI_INFO  pPSUIInfo, LPARAM  lParam);

/////////////////////////////////////////////////////////////////////////////
// CTestPrintDlg dialog

class CTestPrintDlg : public CDialog
{
// Construction
public:
	CTestPrintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPrintDlg)
	enum { IDD = IDD_TESTPRINT };
	CComboBox	m_cbPrinters;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	//PROPSHEETPAGE m_psp[MAX_DRVPAGE];
	//int m_nPropPage;

	LPBYTE m_pdm;
	int m_nDMSize;
	//LPBYTE m_pOemdm;
	//int m_nOemSize;
	//TCHAR m_szDevName[256];
	HANDLE m_hPrinter;
	//HMODULE m_hDrv;
	BOOL m_bRunning;


	// Generated message map functions
	//{{AFX_MSG(CTestPrintDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPrintconfig();
	afx_msg void OnSelchangeCbprinters();
	afx_msg void OnDevicecaps();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINTDLG_H__EBD076BE_31EF_4A84_81FF_F8B101FF0ACF__INCLUDED_)
