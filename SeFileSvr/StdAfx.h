// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D1545CF6_3F58_40F8_9FEB_B4E858CBD24A__INCLUDED_)
#define AFX_STDAFX_H__D1545CF6_3F58_40F8_9FEB_B4E858CBD24A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define _ATL_APARTMENT_THREADED
#include <afxwin.h>         // MFC core and standard components

#include <winsock2.h>
#include <atlbase.h>
#include <process.h>    // _beginthread, _endthread 
#include <vector>
using namespace std;

#define PORT_FILESVR 5500
#define MAX_RECVTHREAD 64
#define CMDBUFSIZE 128
#define CONNPOOLSIZE 256	// connection pool size
#define MAX_POOLSIZE 65536	// max connections
#define MAX_MEMBUFS	64	// max number of mem buffer

#define MEMSTAT_EMPTY	0
#define MEMSTAT_IDLE	1
#define MEMSTAT_USED	2

#define FLAG_UP		0x0001
#define FLAG_DOWN	0x0002
#define FLAG_DATA	0x0004 // receiving data
typedef struct ClientInfo
{
	sockaddr_in addr;//client address
	SOCKET sock;	// client socket
	OVERLAPPED overlap;
	int nState;
	DWORD lastActTick; // last active time(tick)
	int index;	// index of upload/download
	HANDLE hFile;
	char cmdBuf[CMDBUFSIZE];// cmd buf
	char * pBlockBuf;// mem block buf in m_vBufs
	int iBuf;	// index in m_arBufs
} CLIENT_INFO;
typedef vector<CLIENT_INFO> VEC_ClientInfo;
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

class CServiceModule : public CComModule
{
public:
	HRESULT RegisterServer(BOOL bRegTypeLib, BOOL bService);
	HRESULT UnregisterServer();
	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid = NULL);
    void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
    void Run();
    BOOL IsInstalled();
    BOOL Install();
    BOOL Uninstall();
	LONG Unlock();
	void LogEvent(LPCTSTR pszFormat, ...);
    void SetServiceStatus(DWORD dwState);
    void SetupAsLocalServer();

	int InitSocketServer(void);
	void FreeSocketServer(void);
	CLIENT_INFO * GetConnFromPool();
	PSTR GetMemFromPool(int &index);
	int SendCmd(SOCKET sock, char cmd, char param, void *pdata=NULL, int len=0);
	void ClearClientConn(CLIENT_INFO *pClient);
	static unsigned long WINAPI Thread_Receiving(LPVOID pParam);
	static unsigned long WINAPI Thread_Accepting(LPVOID pParam);
	static unsigned long WINAPI Thread_ConnManage(LPVOID pParam);

//Implementation
private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

// data members
public:
    TCHAR m_szServiceName[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;

	SOCKET m_sockServer;//Server Socket
	WORD m_wPort;
	HANDLE m_hCompPort;	// IO Complete port
	HANDLE m_hMutexClientInfo;
	VEC_ClientInfo m_vClientInfo;
	int m_nRecvThread; // num of receiving thread
	int m_nConnTimeout;	// connection timeout, in sec
	int m_nBlock;	// up/down block size, in MB
	HANDLE m_hThreadAccept, m_hThreadConnManage;
	HANDLE m_hThreadRecv[MAX_RECVTHREAD];
	HANDLE m_hMutexBuf;
	//vector<char *> m_vBufs;
	BYTE m_bufState[MAX_MEMBUFS]; // mem state: 0=null, 1=idle, 2=used
	LPSTR m_arBufs[MAX_MEMBUFS];
	DWORD m_dwMainThreadID;
};

extern CServiceModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D1545CF6_3F58_40F8_9FEB_B4E858CBD24A__INCLUDED)
