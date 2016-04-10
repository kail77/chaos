//  Devmode.h : Define common data types, and external function prototypes for devmode functions.

#pragma once

////////////////////////////////////////////////////////
//      OEM Devmode Defines
////////////////////////////////////////////////////////

#define OEM_SIGNATURE   'VIMG'
#define OEM_VERSION     0x00000012L

////////////////////////////////////////////////////////
//      OEM Devmode Type Definitions
////////////////////////////////////////////////////////

//
// This structure must be prefixed by OEM_DMEXTRAHEADER
//    Plug-ins must implement the IPrintOemUI::DevMode method
//
typedef struct tagOEMDEV
{
    OEM_DMEXTRAHEADER   dmOEMExtra;
    DWORD               dwDriverData;
    DWORD               dwAdvancedData;

    //Private DevMode Members
	int iImageFormat; //0=bmp,1=tif
	WCHAR szOutputDir[MAX_PATH]; // image output dir, e.g. [C:\Temp\]
} OEMDEV, *POEMDEV;

typedef const OEMDEV *PCOEMDEV;


/////////////////////////////////////////////////////////
//        ProtoTypes
/////////////////////////////////////////////////////////

HRESULT hrOEMDevMode(DWORD dwMode, POEMDMPARAM pOemDMParam);
BOOL ConvertOEMDevmode(PCOEMDEV pOEMDevIn, POEMDEV pOEMDevOut);
BOOL MakeOEMDevmodeValid(POEMDEV pOEMDevmode);

BOOL bConvertOEMDevmode(PCOEMDEV pOEMDevIn, POEMDEV pOEMDevOut);
BOOL bMakeOEMDevmodeValid(POEMDEV pOEMDevmode);
