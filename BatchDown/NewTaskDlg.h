#if !defined(AFX_NEWTASKDLG_H__C0C0B816_6EEB_466C_B4EF_1C3A0E9E3493__INCLUDED_)
#define AFX_NEWTASKDLG_H__C0C0B816_6EEB_466C_B4EF_1C3A0E9E3493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewTaskDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewTaskDlg dialog

class CNewTaskDlg : public CDialog
{
// Construction
public:
	CNewTaskDlg(CWnd* pParent = NULL, CString sUrlMon="");   // standard constructor
	~CNewTaskDlg();
	inline CStringList& GetUrlList(){return m_strListUrl;}

// Dialog Data
	//{{AFX_DATA(CNewTaskDlg)
	enum { IDD = IDD_NEWTASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTaskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	CStringList m_strListUrl;
	CString m_sUrlMon; // url from clipboard

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewTaskDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnMatch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTASKDLG_H__C0C0B816_6EEB_466C_B4EF_1C3A0E9E3493__INCLUDED_)
