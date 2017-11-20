// BatchDownDlg.h : header file
//

#if !defined(AFX_BATCHDOWNDLG_H__E2AB4361_B557_4590_9618_C261A5051943__INCLUDED_)
#define AFX_BATCHDOWNDLG_H__E2AB4361_B557_4590_9618_C261A5051943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COL_NAME	0
#define COL_SIZE	1
#define COL_STATE	2
#define COL_URL		3

#define TMID_MONITOR	0x1007

#define FLAG_RUNNING	0x0001
#define FLAG_DOWNING	0x0002
#define FLAG_ADDTASK	0x0004 // popup addTask Dlg
/////////////////////////////////////////////////////////////////////////////
// CBatchDownDlg dialog

class CBatchDownDlg : public CDialog
{
// Construction
public:
	CBatchDownDlg(CWnd* pParent = NULL);	// standard constructor
	static DWORD WINAPI Thread_Down(LPVOID pParam);
	int DownINetFile(int idx);
	int SaveHttpFile(CHttpFile *pfile, int nSize, CString sDestFile);
	int CheckClipBoard();
	int LoadConfig();

// Dialog Data
	//{{AFX_DATA(CBatchDownDlg)
	enum { IDD = IDD_BATCHDOWN };
	CListCtrl	m_listTask;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchDownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	DWORD m_dwFlag;
	int m_nBufSize;	// 
	LPBYTE m_pBuf; //  downloading buf
	CString m_sDestPath; // save to path, end with '\'
	CString m_sSubFolder;
	CString m_sClipText; // text in clip board

	// Generated message map functions
	//{{AFX_MSG(CBatchDownDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAddtask();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHDOWNDLG_H__E2AB4361_B557_4590_9618_C261A5051943__INCLUDED_)
