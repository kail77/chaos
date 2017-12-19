// test.cpp for syncif.so functions
// ./testso ./xxmod.so funcname1 param1 *int=4 *pint=1 *str64=hello

#include <windows.h>
#include <stdio.h>

typedef int (*fnTestFoo)(char *param, ...);

#define PARAM_INT	"*int="
#define PARAM_PINT	"*pint="
#define PARAM_STR	"*str"
#define PARAM_BYTE	"*byte"

int HexStr2ByteBuf(const char *pHex, unsigned char *pBuf)
{
	int i,k,n;
	char ch;

	n = lstrlen(pHex);
	memset(pBuf, 0, n/2);
	k = 0;
	for (i=0; i<n; i++)
	{
		ch = pHex[i];
		if(ch>='0' && ch<='9')
			ch = '0';
		else if(ch>='a' && ch<='f')
			ch = 'a'-0xa;
		else if(ch>='A' && ch<='F')
			ch = 'A'-0xa;
		if(i & 0x1)
		{
			pBuf[k] = (unsigned char)(pBuf[k] +pHex[i]-ch);
			k++;
		} else
		{
			pBuf[k] = (unsigned char)(pHex[i]-ch);
			pBuf[k] <<= 4;
		}
	}
	return n/2;
}
int ByteBuf2HexStr(unsigned char *pBuf, int nBufLen, char *pHex)
{
	int i;
	char szNum[8];
	*pHex = 0;
	for (i=0; i<nBufLen; i++)
	{
		sprintf(szNum, "%02X", pBuf[i]);
		lstrcat(pHex, szNum);
	}
	return nBufLen;
}

void callFunc(int nArgc, char** pArgv, fnTestFoo fnTest)
{
	char szBuf[32768]={0},szRet[1024],szNum[256],*pm,*pc;
	int i,nBufLen=32768, nRet,n=0, pnAr[256]={0};
	char * pAr[256];

	char *pb = szBuf;
	for(i=0; i<nArgc-3; i++)
	{
		pm = pArgv[i+3];
		if(strstr(pm, PARAM_INT)==pm) // in - int
		{
			pAr[i] = (char*)atoi(pm+lstrlen(PARAM_INT));
		} else if(strstr(pm, PARAM_PINT)==pm) // int OUT - pointer of int
		{
			pnAr[i] = atoi(pm+lstrlen(PARAM_PINT));
			pAr[i] = (char*)(pnAr+i);
		} else if(strstr(pm, PARAM_STR)==pm) // str IN/OUT - pointer of string buf
		{
			pc = strchr(pm, '=');
			if(pb-szBuf > nBufLen || !pc)
			{
				printf("not enough buf, or format err(str64=xxx)\n");
				return;
			}
			pAr[i] = pb;
			strcpy(pAr[i], pc+1);
			pb += atoi(pm+lstrlen(PARAM_STR));

		} else if(strstr(pm, PARAM_BYTE)==pm) // IN/OUT - pointer to byte buf
		{
			pc = strchr(pm, '=');
			if(pb-szBuf > nBufLen || !pc)
			{
				printf("not enough buf, or format err(byte32=1A2B3C...)\n");
				return;
			}
			pAr[i] = pb;
			HexStr2ByteBuf(pc+1, (unsigned char*)pAr[i]);
			pnAr[i] = atoi(pm+lstrlen(PARAM_BYTE));
			pb += pnAr[i];
			
		} else // in - const string
			pAr[i] = pm;
	}
	if(nArgc-3 == 1)
		nRet = fnTest(pAr[0]);
	else if(nArgc-3 == 2)
		nRet = fnTest(pAr[0], pAr[1]);
	else if(nArgc-3 == 3)
		nRet = fnTest(pAr[0], pAr[1], pAr[2]);
	else if(nArgc-3 == 4)
		nRet = fnTest(pAr[0], pAr[1], pAr[2], pAr[3]);
	else if(nArgc-3 == 5)
		nRet = fnTest(pAr[0], pAr[1], pAr[2], pAr[3], pAr[4]);
	else if(nArgc-3 == 6)
		nRet = fnTest(pAr[0], pAr[1], pAr[2], pAr[3], pAr[4], pAr[5]);
	else
	{
		printf("testso: too many arguments: %d\n", nArgc-3);
		return;
	}
	sprintf(szRet, "testso:ret=%d ", nRet);
	for(i=0; i<nArgc-3; i++)
	{
		pm = pArgv[i+3];
		if(strstr(pm, PARAM_PINT)==pm) // INT/OUT - pointer of int
		{
			sprintf(szNum, "%d ", pnAr[i]);
			strcat(szRet, szNum);
		} else if(strstr(pm, PARAM_STR)==pm) // IN/OUT - pointer of string buf
		{
			strcat(szRet, pAr[i]);
			strcat(szRet, " ");
		} else if(strstr(pm, PARAM_BYTE)==pm) // IN/OUT - pointer of byte buf
		{
			ByteBuf2HexStr((unsigned char*)pAr[i], pnAr[i], szNum);
			strcat(szRet, szNum);
			strcat(szRet, " ");
		}
	}
	strcat(szRet, " \n");
	printf(szRet);
}

int main(int nArgc, char* pArgv[])
{
	if(nArgc < 4)
	{
		printf("testdll xxx.dll funcName strParam1 *int=4 *pint=1 *str64=hello *byte32=1A2B ...\n");
		return 1;
	}

	HMODULE hMod = LoadLibrary(pArgv[1]);//RTLD_LAZY);//
	if(!hMod)
	{
		printf("LoadLibrary failed:%d\n", GetLastError());
		return 2;
	}
	fnTestFoo fnTest = (fnTestFoo)GetProcAddress(hMod, pArgv[2]);
	if(!fnTest)
		printf("load symbol failed:%d\n", GetLastError());
	else
		callFunc(nArgc, pArgv, fnTest);

	FreeLibrary(hMod);
	return 0;
}
