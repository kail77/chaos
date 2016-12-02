// SparseCodecDlg.h : header file
//

#if !defined(AFX_SPARSECODECDLG_H__2EF55767_F211_4386_B9A1_11FC11753888__INCLUDED_)
#define AFX_SPARSECODECDLG_H__2EF55767_F211_4386_B9A1_11FC11753888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <process.h>

typedef int (*SparseCodecProgressProc)(int iCur, int nTotal, LPVOID pParam);
/////////////////////////////////////////////////////////////////////////////
// CSparseCodecDlg dialog

class CSparseCodecDlg : public CDialog
{
// Construction
public:
	CSparseCodecDlg(CWnd* pParent = NULL);	// standard constructor
	int SparseFileCodec(char* pInFile, char* pOutFile, char* pParam, char* pKey, SparseCodecProgressProc pProgressProc);
	static int CodecProgressProc(int iCur, int nTotal, LPVOID pParam);
	int AddFileTail(LPTSTR pszFile, LPBYTE pszTail, int nLen);
	static unsigned int __stdcall Thread_ProcessCodec(LPVOID pParam);	

// Dialog Data
	//{{AFX_DATA(CSparseCodecDlg)
	enum { IDD = IDD_SPARSECODEC };
	CProgressCtrl	m_progress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSparseCodecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSparseCodecDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnOpenfile();
	afx_msg void OnDestfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPARSECODECDLG_H__2EF55767_F211_4386_B9A1_11FC11753888__INCLUDED_)
