// DDIHook.cpp : Implementation of DDI Hook OEMEndDoc. This function dumps the buffered bitmap data out. 

#include "precomp.h"
#include "image.h"
#include "debug.h"

// This indicates to Prefast that this is a usermode driver file.
__user_driver;

//
// Function prototype is defined in printoem.h
//
BOOL APIENTRY OEMEndDoc(SURFOBJ *pso, FLONG fl)

/*++

Routine Description:

    Implementation of DDI hook for DrvEndDoc.

    DrvEndDoc is called by GDI when it has finished 
    sending a document to the driver for rendering.
    
    Please refer to DDK documentation for more details.

    This particular implementation of OEMEndDoc performs
    the following operations:
    - Dump the bitmap file header
    - Dump the bitmap info header
    - Dump the color table if one exists
    - Dump the buffered bitmap data
    - Free the memory for the data buffers

Arguments:

    pso - Defines the surface object
    flags - A set of flag bits

Return Value:

    TRUE if successful, FALSE if there is an error

--*/

{
    PDEVOBJ pDevObj = (PDEVOBJ)pso->dhpdev;
    POEMPDEV pOemPDEV = (POEMPDEV)pDevObj->pdevOEM;
    //DWORD dwWritten;
    //int cScans;

	VERBOSE("OEMEndDoc.");
/*    if (pOemPDEV->pBufStart)
    {
        // Fill BitmapFileHeader
        //
        DWORD dwTotalBytes = pOemPDEV->cbHeaderOffBits + pOemPDEV->bmInfoHeader.biSizeImage;        // File size
    
        pOemPDEV->bmFileHeader.bfType = 0x4d42;     // Signature = 'BM'
        pOemPDEV->bmFileHeader.bfSize = dwTotalBytes;  // Bytes in whole file.
        pOemPDEV->bmFileHeader.bfReserved1 = 0;
        pOemPDEV->bmFileHeader.bfReserved2 = 0;
        pOemPDEV->bmFileHeader.bfOffBits   = pOemPDEV->cbHeaderOffBits; // Offset to bits in file.

        if (pOemPDEV->bColorTable)
            pOemPDEV->bmFileHeader.bfOffBits += pOemPDEV->cPalColors * sizeof(ULONG);

        // Num of scanlines
        //
        cScans = pOemPDEV->bmInfoHeader.biHeight;

        // Flip the biHeight member so that it denotes top-down bitmap 
        //
        pOemPDEV->bmInfoHeader.biHeight = cScans * -1;

        // Dump headers first
        //
        dwWritten = pDevObj->pDrvProcs->DrvWriteSpoolBuf(pDevObj, (void*)&(pOemPDEV->bmFileHeader), sizeof(BITMAPFILEHEADER));
        dwWritten = pDevObj->pDrvProcs->DrvWriteSpoolBuf(pDevObj, (void*)&(pOemPDEV->bmInfoHeader), sizeof(BITMAPINFOHEADER));
        if (pOemPDEV->bColorTable)
        {
            dwWritten = pDevObj->pDrvProcs->DrvWriteSpoolBuf(pDevObj, pOemPDEV->prgbq, pOemPDEV->cPalColors * sizeof(ULONG));
            LocalFree(pOemPDEV->prgbq);
        }

        // Dump the data now
        //
        dwWritten = pDevObj->pDrvProcs->DrvWriteSpoolBuf(pDevObj, pOemPDEV->pBufStart, pOemPDEV->bmInfoHeader.biSizeImage);

        // Free memory for the data buffers
        vFreeBuffer(pOemPDEV);
    }
*/
    // Punt call back to UNIDRV.
    //
    return (pOemPDEV->m_pfnDrvEndDoc)(pso, fl);
}
BOOL APIENTRY OEMStartPage(SURFOBJ *pso)
{
	VERBOSE("OEMStartPage.");
	PDEVOBJ pDevObj = (PDEVOBJ)pso->dhpdev;
	POEMPDEV pOemPDEV = (POEMPDEV)pDevObj->pdevOEM;
	//WCHAR szPath[256];

	//swprintf_s(szPath, 256, L"size:%d-%d, bits:%d-%x-%x, format:%d, bpl:%d", pso->sizlBitmap.cx,pso->sizlBitmap.cy, 
	//	pso->cjBits,pso->pvBits,pso->pvScan0, pso->iBitmapFormat, pso->lDelta);
	//OutputDebugString(szPath);
	memset(pso->pvBits, 0xff, pso->cjBits);
	return (pOemPDEV->m_pfnDrvStartPage)(pso);
}

// before ImageProcessing
BOOL APIENTRY OEMSendPage(SURFOBJ *pso)
{
	VERBOSE("OEMSendPage.");
	PDEVOBJ pDevObj = (PDEVOBJ)pso->dhpdev;
	POEMPDEV pOemPDEV = (POEMPDEV)pDevObj->pdevOEM;
	WCHAR szPath[256];

	swprintf_s(szPath, 256, L"size:%d-%d, bits:%d-%x-%x, format:%d, bpl:%d", pso->sizlBitmap.cx,pso->sizlBitmap.cy, 
		pso->cjBits,pso->pvBits,pso->pvScan0, pso->iBitmapFormat, pso->lDelta);
	OutputDebugString(szPath);

	int i;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	ULONG ulMonoPalette[2] = { RGB(0, 0, 0), RGB(255, 255, 255), };
	DWORD cbData;

	memset(&bfh, 0, sizeof bfh);
	bfh.bfType = 0x4d42;     // Signature = 'BM'
	bfh.bfSize = pso->cjBits;  // Bytes in whole file.
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	memset(&bih, 0, sizeof bih);
	bih.biSize = sizeof bih;
	bih.biWidth = pso->sizlBitmap.cx;
	bih.biHeight = pso->sizlBitmap.cy;
	bih.biPlanes = 1;
	bih.biSizeImage = pso->cjBits;
	if(pso->iBitmapFormat == BMF_1BPP)//(pOemPDEV->cPalColors)
	{
		pOemPDEV->cPalColors = 2;
		bih.biBitCount = 1;
		pOemPDEV->prgbq = (RGBQUAD *)ulMonoPalette;
	} else if(pso->iBitmapFormat == BMF_4BPP)
	{
		pOemPDEV->cPalColors = 16;
		bih.biBitCount = 4;
	} else if(pso->iBitmapFormat == BMF_8BPP)
	{
		pOemPDEV->cPalColors = 256;
		bih.biBitCount = 8;
	} else if(pso->iBitmapFormat == BMF_24BPP)
	{
		pOemPDEV->cPalColors = 0;
		bih.biBitCount = 24;
	} else
	{
		return (pOemPDEV->m_pfnDrvSendPage)(pso);
	}
	bfh.bfOffBits += pOemPDEV->cPalColors * sizeof(ULONG);
	if(pOemPDEV->prgbq==NULL && pOemPDEV->cPalColors>2)
		bFillColorTable(pOemPDEV);

    pOemPDEV->iPage++;
    wcscpy_s(szPath, 256, pOemPDEV->szOutputDir);
    i = (int)wcslen(szPath);

	SYSTEMTIME st;
	GetLocalTime(&st);
	// NOTICE: xxx_s 系列函数会检查buffer长度，否则可能越界.
	swprintf_s(szPath+i, 256-i, L"%02d%02d%02d-%d.bmp", st.wHour,st.wMinute,st.wSecond, pOemPDEV->iPage);
	HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE && GetLastError()==ERROR_FILE_EXISTS)
	{
		swprintf_s(szPath+i, 256-i, L"%02d%02d%02d%d-%d.bmp", st.wHour,st.wMinute,st.wSecond,st.wMilliseconds, pOemPDEV->iPage);
		hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(szPath);
		swprintf_s(szPath, 256, L"CreateFile : %d", GetLastError());
		OutputDebugString(szPath);
		return (pOemPDEV->m_pfnDrvSendPage)(pso);
	}

	WriteFile(hFile, (void*)&bfh, sizeof(bfh), &cbData, NULL);
	WriteFile(hFile, (void*)&bih, sizeof(bih), &cbData, NULL);
	if (pso->iBitmapFormat < BMF_24BPP)
		WriteFile(hFile, pOemPDEV->prgbq, sizeof(RGBQUAD)*pOemPDEV->cPalColors, &cbData, NULL);
	LPBYTE pBuf = (LPBYTE)pso->pvBits + pso->lDelta*(pso->sizlBitmap.cy-1);
	for(i=0; i<pso->sizlBitmap.cy; i++)
	{
		WriteFile(hFile, pBuf, pso->lDelta, &cbData, NULL);
		pBuf -= pso->lDelta;
	}
	//pDevObj->pDrvProcs->DrvWriteSpoolBuf(pDevObj, pso->pvBits, pso->cjBits);
	CloseHandle(hFile);
	return (pOemPDEV->m_pfnDrvSendPage)(pso);
}
