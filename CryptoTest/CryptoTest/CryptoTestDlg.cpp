// CryptoTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTest.h"
#include "CryptoTestDlg.h"
#include "Rijndael.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestDlg dialog

CCryptoTestDlg::CCryptoTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptoTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCryptoTestDlg)
	m_sCipher = _T("");
	m_sPlain = _T("");
	m_sIV = _T("1234567890123456");
	m_nKeyBit = 0;
	m_nMode = 0;
	m_sPWD = _T("1234567890123456");
	m_nPadding = 1;
	m_nBlockSize = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCryptoTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCryptoTestDlg)
	DDX_Text(pDX, IDC_DATACIPHER, m_sCipher);
	DDX_Text(pDX, IDC_DATAPLAIN, m_sPlain);
	DDX_Text(pDX, IDC_IV, m_sIV);
	DDX_CBIndex(pDX, IDC_CBKEYBIT, m_nKeyBit);
	DDX_CBIndex(pDX, IDC_CBMODE, m_nMode);
	DDX_Text(pDX, IDC_PWD, m_sPWD);
	DDX_CBIndex(pDX, IDC_CBPADDING, m_nPadding);
	DDX_CBIndex(pDX, IDC_CBBLOCKSIZE, m_nBlockSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCryptoTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCryptoTestDlg)
	ON_BN_CLICKED(IDC_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(IDC_DECRYPT, OnDecrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptoTestDlg message handlers

BOOL CCryptoTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCryptoTestDlg::OnOK() 
{

	//CDialog::OnOK();
}

void CCryptoTestDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

// abcdef, pwd=iv=1234567890123456, CBC,128bit, 2717512e4aceab948363d60c71449486 
void CCryptoTestDlg::OnEncrypt() 
{
	UpdateData(TRUE);
	CRijndael rj;
	//rj.InitKeyIv(rj);
	int i,n, nLen;
	char szPwd[64]={0},szIV[64]={0},szDataIn[512]={0},szDataOut[512]={0};

	nLen = m_sPlain.GetLength();
	int nBlockSize = 16+m_nBlockSize*8;
	int nBlock = nLen / nBlockSize;

	strcpy(szPwd, m_sPWD);
	strcpy(szIV, m_sIV);
	rj.MakeKey(szPwd, szIV, 16+m_nKeyBit*8, nBlockSize);

	strcpy(szDataIn, m_sPlain);
	if (m_nPadding)	// pkcs7 padding
	{
		n = nBlockSize - nLen%nBlockSize;
		for (i=0; i<n; i++)
		{
			szDataIn[nLen+i] = n;
		}
		nLen += n;
	}
	rj.Encrypt(szDataIn, szDataOut, (nBlock+1)*nBlockSize, m_nMode);

	m_sCipher.Empty();
	for (i=0; i<nLen; i++)
	{
		sprintf(szPwd, "%02X ", (BYTE)szDataOut[i]);
		m_sCipher += szPwd;
	}
	SetDlgItemText(IDC_DATACIPHER, m_sCipher);
}

void CCryptoTestDlg::OnDecrypt() 
{
	
}
