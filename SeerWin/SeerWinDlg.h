
// SeerWinDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "AuthServiceMgr.h"
#include "MeetingServiceMgr.h"
#include <vector>
#include "SeerBrowser.h"

using namespace ZOOM_SDK_NAMESPACE;
using namespace std;


class CAuthServiceMgr;
class CMeetingServiceMgr;

// CSeerWinDlg dialog
class CSeerWinDlg : public CDialog,
	public IAuthServiceMgrEvent,
	public IMeetingserviceMgrEvent
{
// Construction
public:
	CSeerWinDlg(CWnd* pParent = NULL);	// standard constructor
	~CSeerWinDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEERWIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	bool InitZoom();
	bool InitZoomWindows();
	void InitBrowser();
	void SwitchUI(bool enterMeeting);
	void RefreshZoomWindows(const char* caller);
	void Leave();
	bool SeerJoin();
	void LogWindow(HWND window, char* log);
	void SeerLog(const char* format, ...);
	void SeerLog(LPCWSTR log);
	int MatchVideoWithText(HWND hWndVidio, int nOffset, CString sText);
	int UpdateUsersList(CString sUserName, BOOL bJoin);
	int UpdateVideoWithUser();

private:
	bool IsVideoInVector(HWND video);
	void RefreshVideos();
	void RefreshShare();
	void LogVideos();
public:
	CAuthServiceMgr*		m_pAuthServiceMgr;
	CMeetingServiceMgr*		m_pMeetingServiceMgr;
	wstring m_strMeetingNumber;
	wstring m_strUserName; // current user, from url
	vector<HWND> m_videos;
	vector<HWND> m_videoParents;
	vector<CString> m_vsUsers;
	HWND m_hmeeting;
	HWND m_hleft;
	HWND m_hdock;
	HWND m_hshare;

public:
	//
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) {};
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo) {};
	virtual void onLogout() {};

	//
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) {};
	virtual void onRecording2MP4Processing(int iPercentage) {};
	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL);
	virtual void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId) {};
	virtual void onSharingStatus(SharingStatus status, unsigned int userId);
	virtual void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) {};
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status) {};
	virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc) {};
	virtual void onUserVideoStatusChange(unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status) {};
	virtual void onHostChangeNotification(unsigned int userId) {};
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) {};
	virtual void onRecordPriviligeChanged(bool bCanRec) {};
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) {};



	CExplorer1 m_browser;
	DECLARE_EVENTSINK_MAP()
	void BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	CButton m_btleave;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnRefreshVideos();
	afx_msg void OnBnClickedButton5();
};
