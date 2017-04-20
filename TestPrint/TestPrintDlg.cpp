// TestPrintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestPrint.h"
#include "TestPrintDlg.h"
//#include "prvdm.h"
#include <Winspool.h>
//#include <process.h>

//#include <atlbase.h>
//#include <exception>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPrintDlg dialog

CTestPrintDlg::CTestPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPrintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPrintDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hDrv = NULL;
	m_pdm = NULL;
	m_nDMSize = 0;
	//m_pOemdm = NULL;
	//m_hPrinter = NULL;
	m_bRunning = FALSE;
}

void CTestPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPrintDlg)
	DDX_Control(pDX, IDC_CBPRINTERS, m_cbPrinters);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestPrintDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPrintDlg)
	ON_BN_CLICKED(IDC_PRINTCONFIG, OnPrintconfig)
	ON_CBN_SELCHANGE(IDC_CBPRINTERS, OnSelchangeCbprinters)
	ON_BN_CLICKED(IDC_DEVICECAPS, OnDevicecaps)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPrintDlg message handlers

BOOL CTestPrintDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyle(WS_CHILD,WS_POPUP);
	SetParent(NULL);

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	HRESULT hr = CoInitialize(NULL);
	
	int i, nRet=0;
	DWORD cbData, dwSize=MAX_PATH;
	TCHAR szName[MAX_PATH];

	GetDefaultPrinter(szName, &dwSize);

	dwSize = 0;
	LPBYTE pBuf;
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &dwSize, (LPDWORD)&nRet);
	if(dwSize > 0)
		pBuf = new BYTE[dwSize];
	else
		return TRUE;
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, pBuf, dwSize, &cbData, (LPDWORD)&nRet);
	PRINTER_INFO_4 *pInfo = (PRINTER_INFO_4 *)pBuf;

	for(i=0; i<nRet; i++)
	{
		m_cbPrinters.AddString(pInfo->pPrinterName);
		pInfo++;
	}
	delete [] pBuf;
	m_cbPrinters.SelectString(-1, szName);

	return TRUE;
}

void CTestPrintDlg::OnOK() 
{
}

void CTestPrintDlg::OnCancel() 
{
	CoUninitialize();
	//if(m_hDrv)
	//	FreeLibrary(m_hDrv);
	m_bRunning = FALSE;
	if(m_pdm)
		delete [] m_pdm;
	//if(m_pOemdm)
	//	delete [] m_pOemdm;
	m_bRunning = FALSE;
	//ClosePrinter(m_hPrinter);
	CDialog::OnCancel();
}

// 应用程序—打印—属性，打印机—打印首选项
void CTestPrintDlg::OnPrintconfig() 
{
	//m_dm = *(LPENVIRONMENT)dlg.GetDevMode();
	//GetDlgItem(IDC_DOCPROP)->EnableWindow();

	TCHAR szName[MAX_PATH];
	m_cbPrinters.GetWindowText(szName, MAX_PATH);
	HANDLE hPrinter;
	OpenPrinter(szName, &hPrinter, NULL);
	if(!m_pdm)
	{
		m_nDMSize = DocumentProperties(GetSafeHwnd(), hPrinter, szName, NULL, NULL, 0);
		m_pdm = new BYTE[m_nDMSize];
		DocumentProperties(GetSafeHwnd(), hPrinter, szName, (PDEVMODE)m_pdm, NULL, DM_COPY);
	}
	int nRet = AdvancedDocumentProperties(GetSafeHwnd(), hPrinter, szName, (PDEVMODE)m_pdm, (PDEVMODE)m_pdm);
	//DocumentProperties(GetSafeHwnd(), hPrinter, szName, (PDEVMODE)&m_dm, (PDEVMODE)&m_dm, DM_MODIFY|DM_COPY);
	ClosePrinter(hPrinter);
	if (!nRet)
	{
		SetDlgItemText(IDC_VALUE, NULL);
		return;
	}

	CString sText, sCaps;
	int n,nOffx,nOffy,nPhyw,nPhyh,nSizeh,nSizev,nPixh,nPixv,nDpix,nDpiy,nScalex,nScaley,nColor;
	PDEVMODE pdm = (PDEVMODE)m_pdm;
	HDC hPrintDC = CreateDC(_T("WINSPOOL"), szName, NULL, pdm);
	nOffx = GetDeviceCaps(hPrintDC, PHYSICALOFFSETX);
	nOffy = GetDeviceCaps(hPrintDC, PHYSICALOFFSETY);
	nPhyw = GetDeviceCaps(hPrintDC, PHYSICALWIDTH);
	nPhyh = GetDeviceCaps(hPrintDC, PHYSICALHEIGHT);
	nSizeh = GetDeviceCaps(hPrintDC, HORZSIZE);
	nSizev = GetDeviceCaps(hPrintDC, VERTSIZE);
	nPixh = GetDeviceCaps(hPrintDC, HORZRES);
	nPixv = GetDeviceCaps(hPrintDC, VERTRES);
	nScalex = GetDeviceCaps(hPrintDC, SCALINGFACTORX); // always=0?
	nScaley = GetDeviceCaps(hPrintDC, SCALINGFACTORY);
	n = GetDeviceCaps(hPrintDC, TECHNOLOGY);
	nDpix = GetDeviceCaps(hPrintDC, LOGPIXELSX);
	nDpiy = GetDeviceCaps(hPrintDC, LOGPIXELSY);
	nColor = GetDeviceCaps(hPrintDC, NUMCOLORS);

	int nShadeBlend = GetDeviceCaps(hPrintDC, SHADEBLENDCAPS);
	int nRaster = GetDeviceCaps(hPrintDC, RASTERCAPS);
	int nCurve = GetDeviceCaps(hPrintDC, CURVECAPS);
	int nLine = GetDeviceCaps(hPrintDC, LINECAPS);
	int nPolygon = GetDeviceCaps(hPrintDC, POLYGONALCAPS);
	int nTextCaps = GetDeviceCaps(hPrintDC, TEXTCAPS);
	int nColormm = GetDeviceCaps(hPrintDC, COLORMGMTCAPS);

	//sText.Format(_T("field=%08X,size=%d,%d-%d,name=%s"), pdm->dmFields, pdm->dmPaperSize,pdm->dmPaperWidth,pdm->dmPaperLength,pdm->dmFormName);
	sText.Format(_T("Size=%d,%d(mm), offset=%d,%d(pix), Phy=%d,%d(pix), Printable=%d,%d(pix), DPI=%d,%d,color=%d \r\n",), 
		nSizeh,nSizev, nOffx,nOffy, nPhyw,nPhyh, nPixh,nPixv, nDpix,nDpiy,nColor);
	sCaps.Format(_T("Caps: ShadeBlend=%x,Raster=%x,Curve=%x,Line=%x,Polygon=%x,Text=%x,ColorMM=%x \n"), 
		nShadeBlend,nRaster,nCurve,nLine,nPolygon,nTextCaps,nColormm);
	sText += sCaps;
	SetDlgItemText(IDC_VALUE, sText);

	//DOCINFO di;
	//memset(&di, 0, sizeof di);
	//di.cbSize = sizeof di;
	//di.lpszDocName = _T("TestPrint doc1");
	//n = StartDoc(hPrintDC, &di);
	//n = StartPage(hPrintDC);
	//TextOut(hPrintDC, 200,300, _T("TestPrint testText1"), 10);
	//n = EndPage(hPrintDC);
	//n = EndDoc(hPrintDC);

	DeleteDC(hPrintDC);
	//OEMDEVMODE *pOemdm = (OEMDEVMODE *)(m_pdm + sizeof(DEVMODE));
}

void CTestPrintDlg::OnSelchangeCbprinters() 
{
	if(m_pdm)
	{
		delete [] m_pdm;
		m_pdm = NULL;
		m_nDMSize = 0;
	}
}

void CTestPrintDlg::OnDevicecaps() 
{
	TCHAR szName[MAX_PATH];
	int i,n, nPaper;

	m_cbPrinters.GetWindowText(szName, MAX_PATH);

	nPaper = DeviceCapabilities(szName,0, DC_PAPERS, NULL, NULL);
	LPVOID pBuf = malloc(nPaper*(2+128+8));
	WORD *pPaper = (WORD *)pBuf;
	n = DeviceCapabilities(szName,0, DC_PAPERS, pPaper, NULL);
	LPPOINT pPaperSize = (LPPOINT)(pPaper+nPaper);
	n = DeviceCapabilities(szName,0, DC_PAPERSIZE, (LPTSTR)pPaperSize, NULL);
	LPTSTR pPaperNames = (LPTSTR)(pPaperSize+nPaper);
	n = DeviceCapabilities(szName,0, DC_PAPERNAMES, pPaperNames, NULL);

	CString sText,sLine;
	for (i=0; i<nPaper; i++)
	{
		sLine.Format(_T("%s=%d %dx%d \r\n"), pPaperNames+i*64, pPaper[i], pPaperSize[i].x,pPaperSize[i].y);
		sText += sLine;
	}
	free(pBuf);
	SetDlgItemText(IDC_VALUE, sText);
}

void CTestPrintDlg::OnExport() 
{
	if(!m_pdm)
		return;
	CFileDialog dlg(FALSE);
	if(IDCANCEL == dlg.DoModal())
		return;
	CString sPath = dlg.GetPathName();
	CFile f(sPath, CFile::modeCreate|CFile::modeWrite);
	f.Write(m_pdm, m_nDMSize);
	f.Close();
}
