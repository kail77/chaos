// NewTaskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BatchDown.h"
#include "NewTaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewTaskDlg dialog

CNewTaskDlg::CNewTaskDlg(CWnd* pParent /*=NULL*/, CString sUrlMon)
	: CDialog(CNewTaskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewTaskDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_sUrlMon = sUrlMon;
}

CNewTaskDlg::~CNewTaskDlg()
{
	m_strListUrl.RemoveAll();
}

void CNewTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewTaskDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNewTaskDlg, CDialog)
	//{{AFX_MSG_MAP(CNewTaskDlg)
	ON_BN_CLICKED(IDC_MATCH, OnMatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTaskDlg message handlers

BOOL CNewTaskDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_RANGE1, 1);
	SetDlgItemInt(IDC_RANGE2, 1);
	SetDlgItemInt(IDC_WILDNUM, 2);
	SetDlgItemText(IDC_URL, m_sUrlMon);
	OnMatch();
	return TRUE;
}

void CNewTaskDlg::OnMatch() 
{
	CString sUrl,sText,sNum;
	int i, nDot, iNum=0,iEnd=0, nRange;
	TCHAR ch;

	GetDlgItemText(IDC_URL, sUrl);
	nDot = sUrl.ReverseFind('.'); // .jpg
	for (i=nDot-1; i>6; i--)
	{
		ch = sUrl.GetAt(i);
		if(ch>='0' && ch<='9') // digit
		{
			iNum = i;
			if(iEnd == 0)
				iEnd = i;
		} else if(iNum > 0)
			break;
	}
	if(iNum == 0)
		return;

	sNum = sUrl.Mid(iNum, iEnd+1-iNum);
	nRange = atoi(sNum);
	SetDlgItemInt(IDC_RANGE2, nRange);
	SetDlgItemInt(IDC_WILDNUM, sNum.GetLength());
	//sUrl.Replace(sNum, "*");
	sUrl = sUrl.Left(iNum)+"*"+sUrl.Right(sUrl.GetLength()-iEnd-1);
	SetDlgItemText(IDC_URL, sUrl);
}

void CNewTaskDlg::OnOK() 
{
	CString sUrl,sText,sNum;
	TCHAR szNum[16],szFormat[16];
	int i,iRange1,iRange2,nWild;

	iRange1 = GetDlgItemInt(IDC_RANGE1);
	iRange2 = GetDlgItemInt(IDC_RANGE2);
	nWild = GetDlgItemInt(IDC_WILDNUM);
	GetDlgItemText(IDC_URL, sUrl);
	if (iRange1>iRange2 || sUrl.GetLength()<6)
	{
		AfxMessageBox(IDS_ERRINPUT);
		return;
	}
	m_strListUrl.RemoveAll();
	sprintf(szFormat, "%%0%dd", nWild); // e.g.%02d
	for (i=iRange1; i<=iRange2; i++)
	{
		sprintf(szNum, szFormat, i);
		sText = sUrl;
		sText.Replace("*", szNum);
		m_strListUrl.AddTail(sText);
	}
	CDialog::OnOK();
}
