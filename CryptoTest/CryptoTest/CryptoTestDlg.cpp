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
	m_sIV = "LM0017E4ghj*Ghg7";//_T("1234567890123456");
	m_nKeyBit = 2;
	m_nMode = 1;
	m_sPWD = "LM0017Guz(%&hj7x89H$yuBI0456Ftma";//_T("1234567890123456");
	m_nPadding = 1;
	m_nBlockSize = 0;
	m_nEncode = 2;
	m_sBase64 = _T("");
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
	DDX_CBIndex(pDX, IDC_CBCODEC, m_nEncode);
	DDX_Text(pDX, IDC_DATABASE64, m_sBase64);
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

int Base64Encode(unsigned char *pIn, int nInlen, char *pOut, int* pnOutlen)
{
	const char base64_pad = '=';
	const char base64_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
	};
	const unsigned char *current = pIn;
	char *p = pOut;

	if(!pIn || nInlen<=0 || !pnOutlen)
		return -1;

	while (nInlen > 2) { // keep going until we have less than 24 bits
		*p++ = base64_table[current[0] >> 2];
		*p++= base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
		*p++= base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
		*p++= base64_table[current[2] & 0x3f];

		current += 3;
		nInlen -= 3; // we just handle 3 octets of data
	}

	// now deal with the tail end of things
	if (nInlen != 0) {
		*p++= base64_table[current[0] >> 2];
		if (nInlen > 1) {
			*p++= base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			*p++= base64_table[(current[1] & 0x0f) << 2];
			*p++= base64_pad;
		} else {
			*p++ = base64_table[(current[0] & 0x03) << 4];
			*p++ = base64_pad;
			*p++ = base64_pad;
		}
	}
	*pnOutlen = (int)(p - pOut);
	*p = '\0';
	return 0;
}
int Base64Decode(char *pIn, int nInlen, unsigned char *pOut, int *pnOutlen)
{
	const char base64_pad = '=';
	const short base64_reverse_table[256] = {
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
		-2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
		-2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
	};
	const char *current = pIn;
	int ch, i = 0, j = 0, k;
	unsigned char * result = pOut;

	if(!pIn || nInlen<=0 || !pnOutlen)
		return -1;

	// run through the whole string, converting as we go
	while ((ch = *current++) != '\0' && nInlen-- > 0) {
		if (ch == base64_pad) {
			if (*current != '=' && (i % 4) == 1) {
				return -2;
			}
			continue;
		}
		ch = base64_reverse_table[ch];
		if (ch < 0 || ch == -1) { // a space or some other separator character, we simply skip over
			continue;
		} else if (ch == -2) {
			return -3;
		}

		switch(i % 4) {
		case 0:
			result[j] = ch << 2;
			break;
		case 1:
			result[j++] |= ch >> 4;
			result[j] = (ch & 0x0f) << 4;
			break;
		case 2:
			result[j++] |= ch >>2;
			result[j] = (ch & 0x03) << 6;
			break;
		case 3:
			result[j++] |= ch;
			break;
		}
		i++;
		//cout << "result == " << result << endl;
	}

	k = j;
	// mop things up if we ended on a boundary
	if (ch == base64_pad) {
		switch(i % 4) {
		case 1:
			return -4;
		case 2:
			k++;
		case 3:
			result[k] = 0;
		}
	}
	*pnOutlen = j;
	result[j] = '\0';
	return 0;
}

// abcdef, pwd=iv=1234567890123456, CBC,128bit, 2717512e4aceab948363d60c71449486 
void CCryptoTestDlg::OnEncrypt() 
{
	UpdateData(TRUE);
	CRijndael rj;
	//rj.InitKeyIv(rj);
	int i,n, nLen;
	char szPwd[64]={0},szIV[64]={0},szDataIn[512]={0},szDataOut[512]={0};

	int nBlockSize = 16+m_nBlockSize*8;

	strcpy(szPwd, m_sPWD);
	strcpy(szIV, m_sIV);
	rj.MakeKey(szPwd, szIV, 16+m_nKeyBit*8, nBlockSize);

	if(m_nEncode == 1) // unicode
	{
		MultiByteToWideChar(CP_ACP,0, m_sPlain,-1, (LPWSTR)szDataIn,256);
	} else if(m_nEncode == 2) // utf-8
	{
		WCHAR wszTemp[256];
		MultiByteToWideChar(CP_ACP,0, m_sPlain,-1, wszTemp,256);
		WideCharToMultiByte(CP_UTF8,0, wszTemp,-1, szDataIn,512, NULL,NULL);
	} else // ansi
	{
		strcpy(szDataIn, m_sPlain);
	}
	nLen = strlen(szDataIn);
	if (m_nPadding > 0)	// padding
	{
		n = nBlockSize - nLen%nBlockSize;
		for (i=0; i<n; i++)
		{
			if (m_nPadding == 1)  // pkcs7
				szDataIn[nLen+i] = n;
			else if (m_nPadding == 2) // zero
				szDataIn[nLen+i] = 0;
		}
		nLen += n;
	}
	int nBlock = nLen / nBlockSize;
	rj.Encrypt(szDataIn, szDataOut, nBlock*nBlockSize, m_nMode);

	m_sCipher.Empty();
	for (i=0; i<nLen; i++)
	{
		sprintf(szPwd, "%02X ", (BYTE)szDataOut[i]);
		m_sCipher += szPwd;
	}
	SetDlgItemText(IDC_DATACIPHER, m_sCipher);

	Base64Encode((LPBYTE)szDataOut, nLen, szDataIn, &n);
	SetDlgItemText(IDC_DATABASE64, szDataIn);
}

void CCryptoTestDlg::OnDecrypt() 
{
	UpdateData(TRUE);
	CRijndael rj;
	//rj.InitKeyIv(rj);
	int i, nLen;
	char szPwd[64]={0},szIV[64]={0},szDataIn[512]={0},szDataOut[512]={0};

	//strcpy(szBase, "aGVsbG8gbXkgYmFzZTY0");
	Base64Decode(m_sBase64.GetBuffer(0), m_sBase64.GetLength(), (LPBYTE)szDataOut, &nLen);
	m_sBase64.ReleaseBuffer();
	m_sCipher.Empty();
	for (i=0; i<nLen; i++)
	{
		sprintf(szPwd, "%02X ", (BYTE)szDataOut[i]);
		m_sCipher += szPwd;
	}
	SetDlgItemText(IDC_DATACIPHER, m_sCipher);

	int nBlockSize = 16+m_nBlockSize*8;

	strcpy(szPwd, m_sPWD);
	strcpy(szIV, m_sIV);
	rj.MakeKey(szPwd, szIV, 16+m_nKeyBit*8, nBlockSize);

	int nBlock = nLen / nBlockSize;
	rj.Decrypt(szDataOut, szDataIn, nBlock*nBlockSize, m_nMode);

	// remove pkcs7 padding
	if (m_nPadding == 1)
	{
		for(i=0; i<nBlockSize; i++)
		{
			if (szDataIn[nLen-1-i] <= nBlockSize)
				szDataIn[nLen-1-i] = 0;
		}
	}
	if(m_nEncode == 1) // unicode
	{
		WideCharToMultiByte(CP_ACP,0, (LPWSTR)szDataIn,-1, szDataOut,256, NULL,NULL);
		m_sPlain = szDataOut;
	} else if(m_nEncode == 2) // utf-8
	{
		WCHAR wszTemp[256];
		MultiByteToWideChar(CP_UTF8,0, szDataIn,-1, wszTemp,256);
		WideCharToMultiByte(CP_ACP,0, wszTemp,-1, szDataIn,512, NULL,NULL);
		m_sPlain = szDataIn;
	} else // ansi
	{
		m_sPlain = szDataIn;
	}
	SetDlgItemText(IDC_DATAPLAIN, m_sPlain);
}
