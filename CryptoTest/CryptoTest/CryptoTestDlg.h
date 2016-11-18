// CryptoTestDlg.h : header file
//

#if !defined(AFX_CRYPTOTESTDLG_H__77C2603F_BBF1_4E8C_85A9_2BBB212C9EAC__INCLUDED_)
#define AFX_CRYPTOTESTDLG_H__77C2603F_BBF1_4E8C_85A9_2BBB212C9EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestDlg dialog

class CCryptoTestDlg : public CDialog
{
// Construction
public:
	CCryptoTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCryptoTestDlg)
	enum { IDD = IDD_CRYPTOTEST };
	CString	m_sCipher;
	CString	m_sPlain;
	CString	m_sIV;
	int		m_nKeyBit;
	int		m_nMode;
	CString	m_sPWD;
	int		m_nPadding;
	int		m_nBlockSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptoTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCryptoTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTOTESTDLG_H__77C2603F_BBF1_4E8C_85A9_2BBB212C9EAC__INCLUDED_)
