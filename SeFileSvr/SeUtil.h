// SecuPrint utilities lib
#ifndef SEUTIL_H
#define SEUTIL_H

#ifdef SEUTIL_EXPORTS
#define SEUTIL_API __declspec(dllexport)
#else
#define SEUTIL_API __declspec(dllimport)
#endif

extern "C"
{
// 以文件大小为crc因子，对文件进行快速稀疏加密，解密过程相同.
// nDis 加密间隔，默认128, 即每128字节加密4字节
int PASCAL SparseEncodeFile(LPSTR pszFile, int nDis);
}

// =================================================================
//	m_log.SetPathAndName(NULL, "IccVPF");
//	m_log.Output(LOG_WARN, _T("Service Start! %08x \r\n"), dwID);
// NOTICE: MAXIMUM STRING LENGTH IS 2048!

// log level, (10+i)-OutputDebugString
#define LOG_CRASH	1
#define LOG_ERROR	2
#define LOG_WARN	3
#define LOG_INFO	4
#define LOG_DEBUG	5

class SEUTIL_API CMsgLog
{
private:
	TCHAR m_szName[64]; // Caller(exe) name, [SePrintSvr]
	TCHAR m_szLogPath[MAX_PATH]; // log path, e.g.[C:\SecuPrint\Server64\log]
	TCHAR m_szCurPath[MAX_PATH]; // App path, e.g.[C:\SecuPrint\Server64]
	HANDLE m_hMutex;
	int m_iLevel;
	BOOL m_bMsg; // OutputDebugString(TRUE) or log to file(FALSE)
	DWORD m_dwLastUpdate;

private:
	int UpdateConfig(void);
	void LogToFile(LPSTR pszMsg, int nLen);

public:
	CMsgLog();
	~CMsgLog(void);

#ifdef UNICODE
#define SetPathAndName  SetPathAndNameW
#define Output  OutputW
#else
#define SetPathAndName  SetPathAndNameA
#define Output  OutputA
#endif // !UNICODE

	void SetPathAndNameA(LPSTR pszPath=NULL, LPSTR pszName=NULL);
	void SetPathAndNameW(LPWSTR pszPath=NULL, LPWSTR pszName=NULL);
	void OutputA(int iLevel, LPCSTR pFormat, ...);
	void OutputW(int iLevel, LPCWSTR pFormat, ...);
};

#endif //SEUTIL_H
