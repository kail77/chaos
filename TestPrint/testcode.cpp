
/// <summary>运行命令+参数，获取其命令行输出</summary>
/// <param name="pszApp">IN 执行程序完整路径，如[c:\windows\cmd.exe]</param>
/// <param name="pszCmd">IN 命令或参数，如" -a -b xyz"</param>
/// <param name="nMaxDelayMs">IN 命令执行所需的最长时间（毫秒），超时退出。0=不等待立即返回</param>
/// <param name="bAsUser">IN WIN7以上，System服务，以当前用户运行，否则失败1314,ERROR_PRIVILEGE_NOT_HELD</param>
/// <param name="pszOut">OUT 命令行输出信息</param>
/// <returns>返回信息长度，-1=失败</returns>
int CTestPrintDlg::RunConsoleCmd(LPTSTR pszApp, LPTSTR pszCmd, int nMaxDelayMs, int bAsUser, LPTSTR pszOut)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead=NULL,hWrite=NULL, hToken=NULL,hTokenNew=NULL;
	int nRet = 0;

	if(!pszApp)
		return -1;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if(pszOut && !CreatePipe(&hRead, &hWrite, &sa, 0)) // need read output
		return -2;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;	//StdError重定向到pipe
	si.hStdOutput = hWrite;	//StdOutput重定向到pipe
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES;//STARTF_USESHOWWINDOW | 

	if(bAsUser) // Vista, Server2008 above
	{
		typedef int (WINAPI  *FP_WTSQueryUserToken)(ULONG SessionId, PHANDLE phToken);
		FP_WTSQueryUserToken pfWTSQueryUserToken = NULL;
		DWORD dwSessionID = WTSGetActiveConsoleSessionId();
		HMODULE hDll = LoadLibrary(_T("Wtsapi32.dll"));
		if(hDll)
			pfWTSQueryUserToken = (FP_WTSQueryUserToken)GetProcAddress(hDll, "WTSQueryUserToken");
		if(pfWTSQueryUserToken)
		{
			nRet = pfWTSQueryUserToken(dwSessionID, &hToken);
			//nRet = GetLastError();
			if(nRet && hToken)
			{
				nRet = DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, &sa, SecurityIdentification, TokenPrimary, &hTokenNew);
				nRet = CreateProcessAsUser(hTokenNew, pszApp, pszCmd, &sa,&sa,FALSE,0, NULL,NULL, &si,&pi);
			} else
			{
				OutputDebugString(_T("WTSQueryUserToken failed"));
			}
		} else
		{
			OutputDebugString(_T("WTSQueryUserToken not found"));
		}
		if(hDll)
			FreeLibrary(hDll);
	} else
	{
		nRet = CreateProcess(pszApp, pszCmd, NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi);
	}
	if(nRet)
	{
		if(nMaxDelayMs > 0)
			WaitForSingleObject(pi.hProcess, nMaxDelayMs);
		if(pszOut)
		{
			DWORD cbData;
			nRet = ReadFile(hRead, pszOut,1024, &cbData, NULL);
		}
	} else
	{
		nRet = GetLastError();
	}
	if(hWrite)	CloseHandle(hWrite);
	if(hRead)	CloseHandle(hRead);
	if(hTokenNew)	CloseHandle(hTokenNew);
	return 0;
}


void CTestPrintDlg::OnSave() 
{
	//HINSTANCE hInstance = ShellExecute(NULL,L"printto",L"f:\\info.txt", L"\"SII Teriostar LP-2050\"", NULL, SW_HIDE);
	//TCHAR szSql[256],szSqlNew[256];
	//GetDlgItemText(IDC_VALUE, szSql, 256);
	//if (VerifySqlSyntax(szSql, szSqlNew))
	//{
	//	SetDlgItemText(IDC_VALUE, szSqlNew);
	//}

	typedef int (*FunSaveLogs)(wchar_t* securitySystemPushesUrl, wchar_t* jsonString);
	TCHAR szUrl[256], szJson[1024];

	GetDlgItemText(IDC_CONTENT, szUrl, 256);//_T("http://localhost:8086/")
	GetDlgItemText(IDC_VALUE, szJson, 1024);	//_T("printlog...")

	HINSTANCE hDllPushRecord = LoadLibrary(L"SecuritySystemPushes.dll");
	FunSaveLogs  fpSaveLogs = (FunSaveLogs)GetProcAddress(hDllPushRecord, "SaveLogs");

	int nRet = fpSaveLogs(szUrl, szJson);
	SetDlgItemInt(IDC_RETURN, nRet);

	FreeLibrary(hDllPushRecord);
}

int GetValueFromJson(TCHAR *pJson, TCHAR *pName, TCHAR *pValue)
{
	TCHAR szName[64], *pn;
	if(!pJson || !pName || !pValue)
		return ERROR_INVALID_PARAMETER;//87

	_stprintf(szName, _T("\"%s\""), pName);//"Name"
	pn = _tcsstr(pJson, szName);
	if(!pn) // not found
		return ERROR_FILE_NOT_FOUND;//2

	pn += _tcslen(szName);
	LPTSTR pColon=NULL,pEnd=NULL,pQuota1=NULL,pQuota2=NULL;
	pColon = _tcschr(pn, ':');
	pEnd = _tcschr(pn, ',');
	if(!pEnd)
		pEnd = _tcschr(pn, '}');
	if(!pColon || !pEnd)
		return ERROR_INVALID_NAME;//123
	pQuota1 = _tcschr(pn, '"');
	if(pQuota1)
		pQuota2 = _tcschr(pQuota1+1, '"');
	if(pQuota1>pColon && pQuota1<pEnd && pQuota2>pColon && pQuota2<pEnd) // "value"
	{
		_tcsncpy(pValue, pQuota1+1, pQuota2-pQuota1-1);
		pValue[pQuota2-pQuota1-1] = 0;
	} else // number
	{
		while(pColon[1]==' ')	pColon++; // skip blank
		while(*(pEnd-1)==' ')	pEnd--;
		_tcsncpy(pValue, pColon+1, pEnd-pColon-1);
		pValue[pEnd-pColon-1] = 0;
	}
	return ERROR_SUCCESS;//0
}
// \u6d4b\u8bd5\u90e81 ->测试部1
int ConvertUnicodeMixStr(char *pUniMix, char *pAnsi)
{
	char *pc = pUniMix,*pn;
	WCHAR wszText[256]={0},wch;
	int len=0;
	while(*pc)
	{
		if(pc[0]=='\\' && pc[1]=='u')
		{
			pn = pc + 2;
			wch = 0;
			while(*pn!=0 && *pn!='\\' && pn-pc<6)
			{
				wch <<= 4;
				if(*pn>='0' && *pn<='9')
					wch += *pn - '0';
				else if(*pn>='a' && *pn<='f')
					wch += *pn - 'a'+0xa;
				pn++;
			}
			wszText[len++] = wch;
			pc = pn;
		} else
		{
			wszText[len++] = *pc++;
		}
	}
	WideCharToMultiByte(CP_ACP,0, wszText,-1, pAnsi,256, NULL,NULL);
	return 0;
}

void CTestPrintDlg::FormatText() 
{
	CFileDialog dlg(TRUE,L"txt",NULL,0,L"Text File(*.txt)|*.txt||");
	if(IDCANCEL == dlg.DoModal())
		return;
	//必须是ANSI编码 
	int nSize,i,k,bCr;
	LPBYTE pTxt,pc, pTxtNew;
	
	CString strFile = dlg.GetPathName();
	CFile file(strFile, CFile::modeRead);
	nSize = file.GetLength();
	pTxt = new BYTE[nSize*2];
	file.Read(pTxt, nSize);
	file.Close();
	
	pc = pTxt;
	k = 0;
	for(i=0; i<nSize-4; i++, pc++)
	{
		bCr = FALSE;
		if(pc[2]==0x0d && pc[3]==0x0a)
		{
			// check 。？！；…： 
			if( (pc[0]==0xa1 && pc[1]==0xa3) || (pc[0]==0xa3 && pc[1]==0xbf) || (pc[0]==0xa1 && pc[1]==0xb1) ||
				(pc[0]==0xa3 && pc[1]==0xa1) || (pc[0]==0xa3 && pc[1]==0xbb) || 
				(pc[0]==0xa1 && pc[1]==0xad) || (pc[0]==0xa3 && pc[1]==0xba) )
				bCr = true;// 正常换行——保留 
			else if(i-k < 50)
				bCr = true;// 长度短，标题行——保留 
			else
				pc[2] = 0xff, pc[3] = 0xff;
			k = i;
		}
	}
	// copy to new txt
	pTxtNew = pTxt + nSize;
	k = 0;
	for(i=0; i<nSize; i++, pc++)
	{
		if(pTxt[i] != 0xff)
		{
			pTxtNew[k] = pTxt[i];
			k++;
		}
	}
	CFile fileNew(strFile+".new", CFile::modeCreate+CFile::modeWrite);
	fileNew.Write(pTxtNew, k);
	fileNew.Close();
	delete [] pTxt;
}
