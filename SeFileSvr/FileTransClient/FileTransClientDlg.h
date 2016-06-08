// FileTransClientDlg.h : header file
//

#if !defined(AFX_FILETRANSCLIENTDLG_H__FC2897CF_5C2B_4D21_A08D_3FEBD249275A__INCLUDED_)
#define AFX_FILETRANSCLIENTDLG_H__FC2897CF_5C2B_4D21_A08D_3FEBD249275A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock2.h"

#define FLAG_RUNNING	0X0001
#define FLAG_DOWNLOAD	0X0002
#define FLAG_CONNECT	0X0004
/////////////////////////////////////////////////////////////////////////////
// CFileTransClientDlg dialog

class CFileTransClientDlg : public CDialog
{
// Construction
public:
	CFileTransClientDlg(CWnd* pParent = NULL);	// standard constructor
	static unsigned long WINAPI Thread_Transfering(LPVOID pParam);
	int TransFile(LPTSTR pServerFile, LPTSTR pLocalFile);

// Dialog Data
	//{{AFX_DATA(CFileTransClientDlg)
	enum { IDD = IDD_FILETRANSCLIENT };
	CProgressCtrl	m_prgsTransfer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
	SOCKET m_sockClient;
	HANDLE m_hThreadTrans;
	int m_nState;
	sockaddr_in m_addr;
	char * m_pBuf;
	BOOL m_bMemOnly;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileTransClientDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSCLIENTDLG_H__FC2897CF_5C2B_4D21_A08D_3FEBD249275A__INCLUDED_)
