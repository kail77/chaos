// SparseCodecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SparseCodec.h"
#include "SparseCodecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSparseCodecDlg dialog

CSparseCodecDlg::CSparseCodecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSparseCodecDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSparseCodecDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSparseCodecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSparseCodecDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSparseCodecDlg, CDialog)
	//{{AFX_MSG_MAP(CSparseCodecDlg)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_DESTFILE, OnDestfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSparseCodecDlg message handlers

BOOL CSparseCodecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_progress.SetRange32(0, 100);
	SetDlgItemInt(IDC_STEP, 256);
	SetDlgItemText(IDC_KEY, _T("video encryt key for net disk, by chaos77"));
	SetDlgItemText(IDC_COMMENT, _T("video encryt for net disk, by chaos77"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSparseCodecDlg::OnDropFiles(HDROP hDropInfo) 
{
	TCHAR szPath[MAX_PATH];

	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);
	SetDlgItemText(IDC_FILEPATH, szPath);
	SetDlgItemText(IDC_DESTPATH, szPath);

	CFile f(szPath, CFile::modeRead);
	DWORD dwSize = f.GetLength();
	CString sText;
	sText.Format(_T("filesize:%d"), dwSize);
	SetDlgItemText(IDC_INFO, sText);
	CDialog::OnDropFiles(hDropInfo);
}

void CSparseCodecDlg::OnOpenfile() 
{
}

void CSparseCodecDlg::OnDestfile() 
{
	CButton *pBtn = (CButton *)GetDlgItem(IDC_DESTFILE);
	int bCheck = pBtn->GetCheck();
	GetDlgItem(IDC_DESTPATH)->EnableWindow(bCheck);
	if(bCheck)
	{
		TCHAR szPath[MAX_PATH], *pc;
		GetDlgItemText(IDC_DESTPATH, szPath, MAX_PATH);
		pc = strrchr(szPath, '.');
		if(pc && strcmpi(pc+1, "enc"))
		{
			*pc = '-';
			lstrcat(szPath, ".enc");
			SetDlgItemText(IDC_DESTPATH, szPath);
		}
	}
}

void CSparseCodecDlg::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	UINT dwThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_ProcessCodec, this, 0, &dwThreadId);
	CloseHandle(hThread);
	//CDialog::OnOK();
}

void CSparseCodecDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

int CSparseCodecDlg::CodecProgressProc(int iCur, int nTotal, LPVOID pParam)
{
	CSparseCodecDlg *pDlg = (CSparseCodecDlg *)pParam;
	TRACE("progress: %d/%d\n", iCur, nTotal);
	pDlg->m_progress.SetPos(iCur*100/nTotal);
	return 0;
}

unsigned int CSparseCodecDlg::Thread_ProcessCodec(LPVOID pParam)
{
	int nStep=32;
	TCHAR szPath[MAX_PATH],szDest[MAX_PATH], szKey[64], szStep[32], *pszDest=NULL;
	CSparseCodecDlg *pDlg = (CSparseCodecDlg *)pParam;
	
	pDlg->GetDlgItemText(IDC_FILEPATH, szPath, MAX_PATH);
	CButton *pBtn = (CButton *)pDlg->GetDlgItem(IDC_DESTFILE);
	if (pBtn->GetCheck())
	{
		pDlg->GetDlgItemText(IDC_DESTPATH, szDest, MAX_PATH);
		pszDest = szDest;
	}
	pDlg->GetDlgItemText(IDC_KEY, szKey, 64);
	nStep = pDlg->GetDlgItemInt(IDC_STEP);
	sprintf(szStep, "step=%d", nStep);
	pDlg->SparseFileCodec(szPath, pszDest, szStep, szKey, CodecProgressProc);
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	return 0;
}

// 对前1024字节完全加密，后面每step=32字节加密4个字节，解密方式也相同.
// infile outfile step=32 asd123465QWE
int CSparseCodecDlg::SparseFileCodec(char* pInFile, char* pOutFile, char* pParam, char* pKey, SparseCodecProgressProc pProgressProc)
{
	if(!pInFile || !pParam || !pKey)
		return -1; // param error

	int nDis = 64;
	char *pc = strstr(pParam, "step=");
	if(pc)
		nDis = atoi(pc+5);

	FILE *fpIn=NULL, *fpOut=NULL;
	if(pOutFile)
	{
		fpIn = fopen(pInFile, "rb");
		fpOut = fopen(pOutFile, "wb");
	} else // same as InFile
	{
		fpIn = fpOut = fopen(pInFile, "rb+");
	}
	if(!fpIn || !fpOut)
		return -2;
	// get file size
	fseek(fpIn, 0, SEEK_END);
	fpos_t fpos;//__int64
	fgetpos(fpIn, &fpos);

	unsigned int i,j, dwSize,dwCRC, crcTbl[256], srcData[256]={0};
	int nlen = strlen(pKey);
#ifdef WIN32
	dwSize = (DWORD)fpos;//.__pos;
#else
	dwSize = fpos.__pos;
#endif
	for(i=0; i<256; i++) // init CRC Table
	{
		dwCRC = i;
		for(j=0; j<8; j++)
		{
			if(dwCRC & 1)
				dwCRC = (dwCRC >> 1) ^ 0x8320DDB8;
			else
				dwCRC = dwCRC >> 1;
		}
		crcTbl[i] = dwCRC + dwSize + pKey[i%nlen];
	}
	// 先对前1024字节完全加密
	nlen = dwSize;
	if(nlen > 1024)	nlen = 1024;
	fseek(fpIn, 0, SEEK_SET);
	fread(srcData, nlen, 1, fpIn);
	for(i=0; i<256; i++)
		srcData[i] ^= crcTbl[i];
	fseek(fpOut, 0, SEEK_SET);
	fwrite(srcData, nlen, 1, fpOut);
	//if(dwSize <= 1024)	dwSize = 1024; // 退出

	pProgressProc(nlen, dwSize, this);
	// 后面数据稀疏加密
	if(fpOut == fpIn) // in=out
	{
		for(i=0; i<(dwSize-nlen)/nDis; i++)
		{
			fread(&dwCRC, 4, 1, fpIn);
			dwCRC ^= crcTbl[i%256];
			fseek(fpIn, -4, SEEK_CUR);
			fwrite(&dwCRC, 4, 1, fpIn);
			if((i & 0xffff)==0)
				pProgressProc(i, dwSize/nDis, this);

			fseek(fpIn, nDis-4, SEEK_CUR);
		}
	} else	// in -> out
	{
		for(i=0; i<(dwSize-nlen)/nDis; i++)
		{
			fread(&dwCRC, 4, 1, fpIn);
			dwCRC ^= crcTbl[i%256];
			fwrite(&dwCRC, 4, 1, fpOut);

			fread(srcData, nDis-4, 1, fpIn);
			fwrite(srcData, nDis-4, 1, fpOut);
			if((i & 0xffff)==0)
				pProgressProc(i, dwSize/nDis, this);
		}
		nlen = (dwSize-nlen) - i*nDis;
		if(nlen > 0)
		{
			fread(srcData, nlen, 1, fpIn);
			fwrite(srcData, nlen, 1, fpOut);
		}
		fclose(fpOut);
	}
	fclose(fpIn);
	pProgressProc(dwSize/nDis, dwSize/nDis, this);
	return 0;
}
