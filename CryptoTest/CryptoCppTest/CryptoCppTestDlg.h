// CryptoCppTestDlg.h : header file
//

#if !defined(AFX_CRYPTOCPPTESTDLG_H__50230CA7_3B64_4798_9C2C_7C980B2B3879__INCLUDED_)
#define AFX_CRYPTOCPPTESTDLG_H__50230CA7_3B64_4798_9C2C_7C980B2B3879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestDlg dialog

class CCryptoCppTestDlg : public CDialog
{
// Construction
public:
	CCryptoCppTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCryptoCppTestDlg)
	enum { IDD = IDD_CRYPTOCPPTEST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptoCppTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BYTE m_key[256];
	BYTE m_iv[256];

	// Generated message map functions
	//{{AFX_MSG(CCryptoCppTestDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTOCPPTESTDLG_H__50230CA7_3B64_4798_9C2C_7C980B2B3879__INCLUDED_)
