// CryptoCppTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoCppTest.h"
#include "CryptoCppTestDlg.h"

#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "dll.h"
#include "cryptlib.h"
#include "filters.h"

using namespace std;
using namespace CryptoPP;

#define NUM_PADING 16

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestDlg dialog

CCryptoCppTestDlg::CCryptoCppTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptoCppTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCryptoCppTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCryptoCppTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCryptoCppTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCryptoCppTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCryptoCppTestDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ENCRYPT, &CCryptoCppTestDlg::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDC_DECRYPT, &CCryptoCppTestDlg::OnBnClickedDecrypt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptoCppTestDlg message handlers

BOOL CCryptoCppTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	strcpy((PSTR)m_key, "LM0017Guz(%&hj7x89H$yuBI0456FtmaT5&fvHUFCy76*h%(HilJ$lhj!y6&(*jkP87jH7");
	strcpy((PSTR)m_iv, "LM0017E4ghj*Ghg7!rNIfb&95GUY86GfghUb#er57HBh(u%g6HJ($jhWk7&!hg4ui%$hjk");
	return TRUE;  // return TRUE  unless you set the focus to a control
}
int Base64Encode(const unsigned char* pData, int nDataLen, char *pStr)
{
	//编码表
	const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//返回值
	//string strEncode;
	unsigned char Tmp[4]={0};
	int LineLength=0, nLen=0;
	for(int i=0; i<nDataLen/3; i++)
	{
		Tmp[1] = *pData++;
		Tmp[2] = *pData++;
		Tmp[3] = *pData++;
		pStr[nLen++] = EncodeTable[Tmp[1] >> 2];
		pStr[nLen++] = EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		pStr[nLen++] = EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		pStr[nLen++] = EncodeTable[Tmp[3] & 0x3F];
		LineLength += 4;
		if(LineLength==76)
		{
			pStr[nLen++]='\r',pStr[nLen++]='\n';//strEncode+="\r\n";
			LineLength=0;
		}
	}
	//对剩余数据进行编码
	int Mod=nDataLen % 3;
	if(Mod==1)
	{
		Tmp[1] = *pData++;
		pStr[nLen++] = EncodeTable[(Tmp[1] & 0xFC) >> 2];
		pStr[nLen++] = EncodeTable[((Tmp[1] & 0x03) << 4)];
		pStr[nLen++]='=',pStr[nLen++]='='; //strEncode+= "==";
	}
	else if(Mod==2)
	{
		Tmp[1] = *pData++;
		Tmp[2] = *pData++;
		pStr[nLen++] = EncodeTable[(Tmp[1] & 0xFC) >> 2];
		pStr[nLen++] = EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		pStr[nLen++] = EncodeTable[((Tmp[2] & 0x0F) << 2)];
		pStr[nLen++] = '=';
	}
	pStr[nLen] = 0;
	return nLen;
}
int Base64Decode(const char* pData, int nDataLen, unsigned char *pOut)
{
	//解码表
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	//返回值
	//string strDecode;
	int nValue, nLen = 0;
	int i= 0;
	while (i < nDataLen)
	{
		if (*pData != '\r' && *pData!='\n')
		{
			nValue = DecodeTable[*pData++] << 18;
			nValue += DecodeTable[*pData++] << 12;
			pOut[nLen++] =(nValue & 0x00FF0000) >> 16;
			if (*pData != '=')
			{
				nValue += DecodeTable[*pData++] << 6;
				pOut[nLen++] =(nValue & 0x0000FF00) >> 8;
				if (*pData != '=')
				{
					nValue += DecodeTable[*pData++];
					pOut[nLen++] =nValue & 0x000000FF;
				}
			}
			i += 4;
		}
		else// 回车换行,跳过
		{
			pData++;
			i++;
		}
	}
	return nLen;
}
void CCryptoCppTestDlg::OnOK() 
{
	//CDialog::OnOK();
}

void CCryptoCppTestDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CCryptoCppTestDlg::OnBnClickedEncrypt()
{
	CBC_Mode<AES>::Encryption encryptor;
	char szText[1024]={0},szCipher[1024]={0}, szNum[16];
	int i,n,nLen;

	nLen = GetDlgItemText(IDC_PLAIN, szText, 1024);
	// pkcs7 padding(16 Bytes)
	n = NUM_PADING - nLen%NUM_PADING;
	for(i=0; i<n; i++)
		szText[nLen+i] = (char)n;
	nLen += n;

	encryptor.SetKeyWithIV(m_key, 32, m_iv, 16);
	encryptor.ProcessString((byte*)szCipher, (byte*)szText, nLen);

	CString sText;
	for(i=0; i<nLen; i++)
	{
		sprintf(szNum, "%02x ", (BYTE)szCipher[i]);
		sText += szNum;
	}
	SetDlgItemText(IDC_HEXDATA, sText);

	Base64Encode((unsigned char *)szCipher, nLen, szText);
	SetDlgItemText(IDC_CIPHER, szText);
}

void CCryptoCppTestDlg::OnBnClickedDecrypt()
{
	CBC_Mode<AES>::Decryption decryptor;
	char szText[1024]={0},szCipher[1024]={0}, szNum[16];
	int i,nLen;

	GetDlgItemText(IDC_CIPHER, szText, 1024);
	nLen = Base64Decode(szText, strlen(szText), (LPBYTE)szCipher);

	CString sText;
	for(i=0; i<nLen; i++)
	{
		sprintf(szNum, "%02x ", (BYTE)szCipher[i]);
		sText += szNum;
	}
	SetDlgItemText(IDC_HEXDATA, sText);

	decryptor.SetKeyWithIV(m_key, 32, m_iv, 16);
	memset(szText, 0, 1024);
	decryptor.ProcessString((byte*)szText, (byte*)szCipher, nLen);
	//remove pkcs7 padding
	for(i=1; i<=NUM_PADING; i++)
	{
		if(szText[nLen-i]>0 && szText[nLen-i]<=NUM_PADING)
			szText[nLen-i] = 0;
	}
	SetDlgItemText(IDC_PLAIN, szText);
}
