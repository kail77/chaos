
// SeerWinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeerWin.h"
#include "SeerWinDlg.h"
//#include "afxdialogex.h"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




typedef LRESULT(CALLBACK* WNDPROC) (HWND, UINT, WPARAM, LPARAM);
CSeerWinDlg* g_Demo;
map<HWND, WNDPROC> g_mapproc;


LRESULT CALLBACK VideoWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_WINDOWPOSCHANGING || message == WM_WINDOWPOSCHANGED)
	{
		WINDOWPOS* pos = (WINDOWPOS*)lParam;
		pos->flags |= SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER;
	}
	return CallWindowProc(g_mapproc[hwnd], hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildVideoWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_RBUTTONUP || message == WM_LBUTTONUP || message == WM_LBUTTONDBLCLK || message == WM_RBUTTONDBLCLK || message== WM_MOUSEMOVE)
	{
		return 0;
	}
	return CallWindowProc(g_mapproc[hwnd], hwnd, message, wParam, lParam);
}

// CSeerWinDlg dialog
CSeerWinDlg::CSeerWinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SEERWIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAuthServiceMgr = new CAuthServiceMgr(this);
	m_pMeetingServiceMgr = new CMeetingServiceMgr(this);
	g_Demo = this;
	m_strMeetingNumber = _T("");
	m_strUserName = _T("");
	m_hmeeting = NULL;
	m_hleft = NULL;
	m_hdock = NULL;
	m_hshare = NULL;
}

CSeerWinDlg::~CSeerWinDlg()
{
	if (m_pAuthServiceMgr)
	{
		delete m_pAuthServiceMgr;
		m_pAuthServiceMgr = NULL;
	}

	if (m_pMeetingServiceMgr)
	{
		delete m_pMeetingServiceMgr;
		m_pMeetingServiceMgr = NULL;
	}
}

void CSeerWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	DDX_Control(pDX, IDC_BUTTON2, m_btleave);
}
BOOL CSeerWinDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_NCLBUTTONDBLCLK)
	{
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CSeerWinDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSeerWinDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSeerWinDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &CSeerWinDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CSeerWinDlg::OnRefreshVideos)
	ON_BN_CLICKED(IDC_BUTTON5, &CSeerWinDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CSeerWinDlg message handlers

BOOL CSeerWinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MAXIMIZE);
	//SetBackgroundColor(RGB(0, 255, 255));
	InitBrowser();
	InitZoom();
	SeerLog("SeerWinDlg Init done.");


	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

bool CSeerWinDlg::InitZoom()
{
	//Auth
	InitParam initParam;
	initParam.strWebDomain = L"https://zoom.us";
	if (!m_pAuthServiceMgr->Init(initParam))
		return false;
	AuthParam authParam;
	authParam.appKey = L"DrwWNF4yxhzstuKToQFIFmqc3II0pmZ3fYiH";
	authParam.appSecret = L"pvyVRfUEC04I5mrItGNzBHLcbLuMGmx8vAaT";
	if (!m_pAuthServiceMgr->SDKAuth(authParam))
		return false;

	if (!m_pMeetingServiceMgr->Init())
		return false;
	return true;
}

bool CSeerWinDlg::InitZoomWindows()
{
	//需要研究：
	//1.全屏，共享屏幕，单击，双击，哪些会影响到viewmode。
	//2.当把父窗口改变之后，当发生这些改变时，是否窗口关系链又发生了变化。
	//
	//DockVideoContainer
	// -VideoContainerWnd
	//  -Video Content
	//MeetingUI
	// -ContentLeftPanel
	//  -Meeting Tools
	//  -Meeting details
	//  -ZPVideoScrollBtnClass
	//  -ZPVideoScrollBtnClass
	//  -VideoContainerWnd
	//   -Video Content
	//  -ShareContainerWnd
	//   -Share Content
	//    -""(CASView_xxxxx)
	//   -VideoPaginationBarWndCls	
	//   -VideoPaginationBarWndCls	
	// -ContentRightPanel
	//  -PListContainer
	//  -PChatContainer
	//Screen share viewing options(	ZPControlPanelHintClass)
	SeerLog("InitZoomWindows");
	IMeetingService* pservice = m_pMeetingServiceMgr->m_pMeetingService;
	IMeetingUIController* pctrl = m_pMeetingServiceMgr->m_pMeetingService->GetUIController();
	IMeetingRemoteController* premote = m_pMeetingServiceMgr->m_pMeetingService->GetMeetingRemoteController();
	IMeetingVideoController* pvideo = m_pMeetingServiceMgr->m_pMeetingService->GetMeetingVideoController();
	IMeetingConfiguration* pconfig = m_pMeetingServiceMgr->m_pMeetingService->GetMeetingConfiguration();
	IMeetingShareController* pshare = m_pMeetingServiceMgr->m_pMeetingService->GetMeetingShareController();
	IAnnotationController* pannotation = m_pMeetingServiceMgr->m_pMeetingService->GetAnnotationController();
	IMeetingAudioController* paudio = m_pMeetingServiceMgr->m_pMeetingService->GetMeetingAudioController();
	ISettingService* psetting = m_pMeetingServiceMgr->m_pSettingService;
	psetting->EnableAutoFullScreenVideoWhenJoinMeeting(false);
	psetting->EnableAutoFitToWindowWhenViewSharing(true);
	psetting->EnableAutoAdjustMic(true);
	psetting->EnableAutoJoinAudio(true);
	psetting->EnableDualScreenMode(false);
	pconfig->SetSharingToolbarVisibility(false);
	pconfig->SetBottomFloatToolbarWndVisibility(false);
	pconfig->DisablePopupMeetingWrongPSWDlg(true);
	pconfig->DisableWaitingForHostDialog(true);
	pconfig->EnableApproveRemoteControlDlg(false);
	pconfig->EnableAutoAdjustMicVolumeWhenJoinAudio(true);
	pconfig->EnableAutoAdjustSpeakerVolumeWhenJoinAudio(true);
	pconfig->EnableAutoEndOtherMeetingWhenStartMeeting(false);
	pconfig->EnableDeclineRemoteControlResponseDlg(false);
	pconfig->EnableEnterAndExitFullScreenButtonOnMeetingUI(false);
	pconfig->EnableInputMeetingPasswordDlg(false);
	pconfig->EnableInviteButtonOnMeetingUI(false);
	pconfig->EnableLButtonDBClick4SwitchFullScreenMode(false);
	pconfig->EnableLeaveMeetingOptionForHost(false);
	pconfig->HideMeetingInfoFromMeetingUITitle(true);
	pvideo->HideOrShowNoVideoUserOnVideoWall(false);
	pservice->LockMeeting();
	pctrl->HideChatDlg();
	pctrl->HideJoinAudioDlg();
	pctrl->ShowBottomFloatToolbarWnd(false);
	pctrl->ShowSharingToolbar(false);
	pvideo->UnmuteVideo();
	HWND secondview;
	pctrl->GetMeetingUIWnd(m_hmeeting, secondview);
	LogWindow(m_hmeeting, "m_hmeeting.created.");

	m_hleft = ::FindWindowEx(m_hmeeting, NULL, NULL, L"ContentLeftPanel");
	LogWindow(m_hleft, "m_hleft.created");

	m_hdock = ::FindWindow(NULL, L"DockVideoContainer");
	if (m_hdock == NULL)
	{
		m_hdock = ::FindWindowEx(m_hleft, NULL, NULL, L"DockVideoContainer");
	}
	LogWindow(m_hdock, "m_hdock.created");

	m_hshare = ::FindWindowEx(m_hleft, NULL, NULL, L"ShareContainerWnd");
	LogWindow(m_hshare, "m_hshare.created");
	return false;
}

void CSeerWinDlg::InitBrowser()
{
	CRect rect;
	GetClientRect(&rect);
	m_browser.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), 0);

	COleVariant varEmpty;
	CString str("http://seerenglish.com/ensprivate/sschedule");
	COleVariant varUrl(str);

	m_browser.Navigate2(varUrl, varEmpty, varEmpty, varEmpty, varEmpty);
	m_browser.put_Silent(true);
}

void CSeerWinDlg::SwitchUI(bool enterMeeting)
{
	if (enterMeeting)
	{
		::ShowWindow(m_browser.GetSafeHwnd(), SW_HIDE);
		::ShowWindow(m_btleave.GetSafeHwnd(), SW_SHOW);
	}
	else
	{
		::ShowWindow(m_btleave.GetSafeHwnd(), SW_HIDE);
		::ShowWindow(m_browser.GetSafeHwnd(), SW_SHOW);
	}
}


void CSeerWinDlg::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
	SeerLog("onMeetingStatusChanged, status:%d, iResult:%d", status, iResult); // status 1-3-4-7
	if (status == ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING)
	{
		InitZoomWindows();
		RefreshZoomWindows("MEETING_STATUS_INMEETING");
		SwitchUI(true);
	}
}

void CSeerWinDlg::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	SeerLog("onUserJoin enter");
	if (lstUserID && m_pMeetingServiceMgr)
	{
		int count = lstUserID->GetCount();
		SeerLog("onUserJoin, count:%d", count);
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			SeerLog("onUserJoin, userid:%d", userId);
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pMeetingServiceMgr->GetUserByUserID(userId);
			if (pUserInfo)
			{
				TCHAR szUserID[MAX_PATH] = { 0 };
				wsprintf(szUserID, _T("%d"), pUserInfo->GetUserID());
				TCHAR szLog[MAX_PATH] = { 0 };
				wsprintf(szLog, _T("onUserJoin:User (%s) join meeting, userid(%d)(0x%08X), Is host(%d), Video is on(%d), Is myself(%d), userrole:%d"), pUserInfo->GetUserName(), pUserInfo->GetUserID(), pUserInfo->GetUserID(),pUserInfo->IsHost(), pUserInfo->IsVideoOn(), pUserInfo->IsMySelf(),pUserInfo->GetUserRole());
				SeerLog(szLog);
				//if(!pUserInfo->IsMySelf())
					UpdateUsersList(pUserInfo->GetUserName(), TRUE);
			}
		}

		RefreshZoomWindows("onUserJoin");
	}
}

void CSeerWinDlg::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	SeerLog("onUserLeft enter");
	if (lstUserID && m_pMeetingServiceMgr)
	{
		int count = lstUserID->GetCount();
		SeerLog("onUserLeft, count:%d", count);
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			SeerLog("onUserJoin, userid:%d", userId);
			IUserInfo* pUserInfo = m_pMeetingServiceMgr->GetUserByUserID(userId);
			if (pUserInfo)
			{
				TCHAR szUserID[MAX_PATH] = { 0 };
				wsprintf(szUserID, _T("%d"), pUserInfo->GetUserID());
				TCHAR szLog[MAX_PATH] = { 0 };
				wsprintf(szLog, _T("onUserLeft:User (%s) join meeting, userid(%d)(0x%08X), Is host(%d), Video is on(%d), Is myself(%d), userrole:%d"), pUserInfo->GetUserName(), pUserInfo->GetUserID(), pUserInfo->GetUserID(), pUserInfo->IsHost(), pUserInfo->IsVideoOn(), pUserInfo->IsMySelf(), pUserInfo->GetUserRole());
				OutputDebugString(szLog);
				SeerLog(szLog);
				UpdateUsersList(pUserInfo->GetUserName(), FALSE);
			}
		}
	}
}

void CSeerWinDlg::onSharingStatus(SharingStatus status, unsigned int userId)
{
	SeerLog("onSharingStatus, status:%d, userId:%d", status, userId);
	if (status == Sharing_View_Other_Sharing)
		RefreshZoomWindows("Sharing_View_Other_Sharing");
	else if(status == Sharing_Other_Share_End)
		RefreshZoomWindows("Sharing_Other_Share_End");
}

void CSeerWinDlg::SeerLog(const char* format, ...)
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	time_t timep;
	time(&timep);
	tm localtime;
	localtime_s(&localtime, &timep);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S ", &localtime);
	int len = strnlen_s(buffer, sizeof(buffer));

	va_list args;
	va_start(args, format);
	vsprintf_s(buffer + len, sizeof(buffer) - len - 1, format, args);
	va_end(args);

	//OutputDebugStringA(buffer);
	FILE *stream;
	fopen_s(&stream, "fprintf.out", "a");
	if (stream != NULL)
	{
		fprintf_s(stream, buffer);
		fprintf_s(stream, "\n");
		fclose(stream);
	}
}
void CSeerWinDlg::SeerLog(LPCWSTR log)
{
	char buffer[1024];
	size_t size;
	memset(buffer, 0, sizeof(buffer));
	wcstombs_s(&size, buffer, log, sizeof(buffer));
	SeerLog("%s", buffer);
}
bool CSeerWinDlg::IsVideoInVector(HWND video)
{
	for (UINT i = 0; i < m_videos.size(); i++)
	{
		if (m_videos[i] == video)
			return true;
	}
	return false;
}
void CSeerWinDlg::LogVideos()
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, sizeof(buffer), "m_videos: size(%d)", m_videos.size());
	for (UINT i = 0; i < m_videos.size(); i++)
	{
		sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ",0x%08X", m_videos[i]);
	}
	SeerLog("%s", buffer);
}
void CSeerWinDlg::RefreshVideos()
{
	if (m_hmeeting == NULL || m_hleft == NULL || m_hshare == NULL || m_hdock == NULL)
	{
		SeerLog("RefreshVideos.zoom window is null.");
		return;
	}
	//1.1找到videos
	//1.1.1 位于LeftPanel下的VideoContainerWnd 
	HWND hVideoContainer = ::FindWindowEx(m_hleft, NULL, NULL, L"VideoContainerWnd");
	while (hVideoContainer != NULL)
	{
		if (::IsWindowVisible(hVideoContainer) && !IsVideoInVector(hVideoContainer))
		{
			m_videos.push_back(hVideoContainer);
			m_videoParents.push_back(m_hleft);
			LogWindow(hVideoContainer, "VideoContainerWnd.left");
		}
		hVideoContainer = ::FindWindowEx(m_hleft, hVideoContainer, NULL, L"VideoContainerWnd");
	}
	//1.1.2 位于DockVideoContainer下的VideoContainerWnd
	hVideoContainer = ::FindWindowEx(m_hdock, NULL, NULL, L"VideoContainerWnd");
	while (hVideoContainer != NULL)
	{
		if (::IsWindowVisible(hVideoContainer) && !IsVideoInVector(hVideoContainer))
		{
			m_videos.push_back(hVideoContainer);
			m_videoParents.push_back(m_hdock);
			LogWindow(hVideoContainer, "VideoContainerWnd.dock");
		}
		hVideoContainer = ::FindWindowEx(m_hdock, hVideoContainer, NULL, L"VideoContainerWnd");
	}

	if (m_videos.size() <= 0)
	{
		SeerLog("RefreshVideos.m_videos is null.");
		return;
	}
	//for (int i = m_videos.size() - 1; i >= 0; i--)
	//{
	//	if (!::IsWindowVisible(m_videos[i]))
	//	{
	//		m_videos.erase(m_videos.begin() + i);
	//	}
	//}
	int count = 0;
	for (UINT i = 0; i < m_videos.size(); i++)
	{
		if (::IsWindowVisible(m_videos[i]))
			count++;
	}

	if (count <= 0)
	{
		SeerLog("RefreshVideos.visabled videos is null.");
		return;
	}
	CRect rect;
	GetClientRect(&rect);
	int x = rect.Width() / 3 * 2 + 5;
	int cx = rect.Width() / 3 - 10;
	int y = 0;
	int cy = rect.Height() / count - 10;

	int j = 0;
	for (UINT i = 0; i < m_videos.size(); i++)
	{
		if (::IsWindowVisible(m_videos[i]))
		{
			//1.set pos
			y = rect.top + 5 + j*(cy + 10);
			j++;
			if (::GetParent(m_videos[i]) != GetSafeHwnd())
			{
				::SetParent(m_videos[i], GetSafeHwnd());
			}
			::SetWindowPos(m_videos[i], NULL, x, y, cx, cy, SWP_NOSENDCHANGING);
			SeerLog("videoPos.%d.0x%08X: %d,%d,%d,%d", i, m_videos[i],x, y, cx, cy);
			//2.set region
			/*HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
			if (::GetWindowRgn(m_videos[i], hrgn) != COMPLEXREGION)
			{
				HRGN ScreenRgn;
				ScreenRgn = CreateRoundRectRgn(0, 0, cx, cy, 40, 40);
				::SetWindowRgn(m_videos[i], ScreenRgn, TRUE);
				::DeleteObject(ScreenRgn);
				SeerLog("RefreshVideos.SetRgn.0x%08X.",m_videos[i]);
			}
			::DeleteObject(hrgn);*/
			//3.set new proc
			if (g_mapproc.find(m_videos[i]) == g_mapproc.end())
			{
				g_mapproc[m_videos[i]] = (WNDPROC)GetWindowLong(m_videos[i], GWL_WNDPROC);//获取旧的窗口过程函数指针保存 
				SetWindowLong(m_videos[i], GWL_WNDPROC, long(VideoWndProc));
				//SeerLog("VideoWndProc.add: 0x%08X", m_videos[i]);
				HWND hchild = ::FindWindowEx(m_videos[i], NULL, NULL, NULL);
				if (hchild && g_mapproc.find(hchild) == g_mapproc.end())
				{
					g_mapproc[hchild] = (WNDPROC)GetWindowLong(hchild, GWL_WNDPROC);//获取旧的窗口过程函数指针保存 
					SetWindowLong(hchild, GWL_WNDPROC, long(ChildVideoWndProc));
					//SeerLog("VideoWndProc.child.add: 0x%08X", hchild);
				}
			}
		}
	}
	LogVideos();
}
void CSeerWinDlg::RefreshShare()
{
	if (m_hshare == NULL || !::IsWindow(m_hshare) || !::IsWindowVisible(m_hshare))
	{
		SeerLog("RefreshShare null or disable");
	}
	if (::GetParent(m_hshare) != GetSafeHwnd())
	{
		::SetParent(m_hshare, GetSafeHwnd());
	}
	CRect rect,rect2;
	GetClientRect(&rect);
	int x = rect.left + 5;
	int y = rect.top + 5+50;
	int cx = rect.Width() / 3 * 2 - 10;
	int cy = rect.Height() - 10-50;
	::GetWindowRect(m_hshare, &rect2);
	if (x!=rect2.left || y!=rect2.top || cx!=rect2.Width() || cy!=rect2.Height())
	{
		::SetWindowPos(m_hshare, NULL, x, y, cx, cy, 0);
	}

	HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
	if (::GetWindowRgn(m_hshare, hrgn) != COMPLEXREGION)
	{
		HRGN ScreenRgn;
		ScreenRgn = CreateRoundRectRgn(0, 0, cx, cy, 40, 40);
		::SetWindowRgn(m_hshare, ScreenRgn, TRUE);
		::DeleteObject(ScreenRgn);
		SeerLog("RefreshShare.SetRgn.");
	}
	::DeleteObject(hrgn);
}
void CSeerWinDlg::LogWindow(HWND window, char* log)
{
	if (::IsWindow(window))
	{
		LPTSTR name = new TCHAR[256];
		memset(name, 0, 256 * sizeof(TCHAR));
		::GetClassName(window, name, 256);

		LPTSTR text = new TCHAR[256];
		memset(text, 0, 256 * sizeof(TCHAR));
		::GetWindowText(window, text, 256);

		char buffer[1024];
		memset(buffer, 0, 1024);
		sprintf_s(buffer, 1023, "%s, window:0x%08X, class:%S, text:%S, enable:%d, visible:%d\n", log, window, name, text, ::IsWindowEnabled(window), ::IsWindowVisible(window));
		FILE *stream;
		fopen_s(&stream, "fprintf.out", "a");
		if (stream != NULL)
		{
			fprintf(stream, buffer);
			fclose(stream);
		}
	}
}
bool CSeerWinDlg::SeerJoin()
{
	//Create Meeting Service
	if (m_pMeetingServiceMgr == NULL) return false;

	bool result;// = m_pMeetingServiceMgr->Init();
	ZOOM_SDK_NAMESPACE::JoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_APIUSER;
	ZOOM_SDK_NAMESPACE::JoinParam4APIUser& apiParam = joinParam.param.apiuserJoin;
	apiParam.meetingNumber = _wtoi64(m_strMeetingNumber.c_str());
	apiParam.userName = m_strUserName.c_str();
	apiParam.isVideoOff = false;
	apiParam.isAudioOff = false;
	//apiParam.psw = strUserToken.c_str();

	AuthResult authResult = m_pAuthServiceMgr->m_pAuthService->GetAuthResult();
	result = m_pMeetingServiceMgr->Join(joinParam);
	authResult = m_pAuthServiceMgr->m_pAuthService->GetAuthResult();
	return result;

}
void CSeerWinDlg::RefreshZoomWindows(const char* caller)
{
	SeerLog("RefreshZoomWindows.%s",caller);
	if (m_hmeeting && m_hdock && ::IsWindow(m_hmeeting) && IsWindow(m_hdock))
	{
		if(!::IsWindowVisible(m_hmeeting))
			::ShowWindow(m_hmeeting, SW_SHOW);
		if (!::IsWindowVisible(m_hdock))
			::ShowWindow(m_hdock, SW_SHOW);
		//1.refresh videos and share
		RefreshVideos();
		RefreshShare();
		//2.hide meeting ui
		if (::IsWindowVisible(m_hmeeting))
			::ShowWindow(m_hmeeting, SW_HIDE);
		if (::IsWindowVisible(m_hdock))
			::ShowWindow(m_hdock, SW_HIDE);
	}
}
void CSeerWinDlg::Leave()
{
	if (m_hmeeting != NULL)
	{
		SwitchUI(false);
		for (UINT i = 0; i < m_videos.size(); i++)
		{
			HWND child = m_videos[i];
			HWND parent = m_videoParents[i];
			if (::IsWindow(child) && ::IsWindow(parent) && ::GetParent(child) != parent)
				::SetParent(child, parent);
		}
		if (::IsWindow(m_hshare) && ::IsWindow(m_hleft) && ::GetParent(m_hshare) != m_hleft)
			::SetParent(m_hshare, m_hleft);
		m_pMeetingServiceMgr->Leave();
		m_strMeetingNumber = _T("");
		m_strUserName = _T("");
		m_hmeeting = NULL;
		m_hleft = NULL;
		m_hdock = NULL;
		m_hshare = NULL;
		m_videos.clear();
		m_videoParents.clear();
		m_vsUsers.clear();
		g_mapproc.clear();
	}
}
BEGIN_EVENTSINK_MAP(CSeerWinDlg, CDialog)
	ON_EVENT(CSeerWinDlg, IDC_EXPLORER1, 250, CSeerWinDlg::BeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CSeerWinDlg::BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	wstring str = URL->bstrVal;
	//L"zoommtg://seerenglish.com/join?confno=6589485989&uname=Student_Jessie"
	if ((int)str.find(L"zoommtg") >= 0)
	{
		int meetingPos = str.find(L"?confno=") + 8;
		int meetingLen = (int)str.find(L"&uname") - meetingPos;
		m_strMeetingNumber = str.substr(meetingPos, meetingLen);
		int namePos = (int)str.find(L"&uname") + 7;// "&uname="
		m_strUserName = str.substr(namePos);
		SeerJoin();
		*Cancel = VARIANT_TRUE;
	}
}


void CSeerWinDlg::OnBnClickedButton1()
{
	m_strMeetingNumber = _T("6589485989");
	m_strUserName = _T("RRTest");
	SeerJoin();
}


void CSeerWinDlg::OnBnClickedButton2()
{
	Leave();
}

void CSeerWinDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	Leave();
	__super::OnClose();
}


void CSeerWinDlg::OnBnClickedButton4()
{
	RefreshShare();
}


void CSeerWinDlg::OnRefreshVideos()
{
	//RefreshVideos();
	CString sUserName;
	GetDlgItemText(IDC_TEXT, sUserName);
	if(m_videos.size() < 1)// || sUserName.IsEmpty())
		return;

	//int nMatch = MatchVideoWithText(m_videos[0], 4, sUserName);
	UpdateVideoWithUser();
}

void CSeerWinDlg::OnBnClickedButton5()
{
	RefreshZoomWindows("test");
}

// update other users window<=>username
int CSeerWinDlg::UpdateVideoWithUser()
{
	UINT i,j;
	int nMatch,nMax,jBest,nOffset=0;

	//if(m_videos.size()>0 && ::IsWindowVisible(m_videos[0]))
	//	nMatch = MatchVideoWithText(m_videos[0], 4, m_strUserName.c_str());
	for (i=0; i<m_videos.size(); i++)
	{
		if (!::IsWindowVisible(m_videos[i]))
			continue;
		nMax = 0;
		jBest = 0;
		for (j=0; j<m_vsUsers.size(); j++)
		{
			nMatch = MatchVideoWithText(m_videos[i], 4, m_vsUsers[j]);
			if(nMax < nMatch)
			{
				jBest = j;
				nMax = nMatch;
				nOffset = 4;
			}
			nMatch = MatchVideoWithText(m_videos[i], 21, m_vsUsers[j]);
			if(nMax < nMatch)
			{
				jBest = j;
				nMax = nMatch;
				nOffset = 21;
			}
		}
		nMatch = MatchVideoWithText(m_videos[i], nOffset, m_vsUsers[jBest]);//DBG_ONLY 
	}
	return 0;
}
int CSeerWinDlg::UpdateUsersList(CString sUserName, BOOL bJoin)
{
	int bFound=FALSE;
	vector<CString>::iterator it;
	for(it=m_vsUsers.begin(); it!=m_vsUsers.end(); it++)
	{
		if((*it) == sUserName)
		{
			bFound = TRUE;
			break;
		}
	}
	if(bJoin && !bFound)
	{
		m_vsUsers.push_back(sUserName);
		SeerLog("UpdaetUser %s", sUserName);
	}
	if(!bJoin && bFound)
		m_vsUsers.erase(it);
	return 0;
}

#define FONTNAME_VDO	_T("微软雅黑")	// font name,size in video window
#define FONTSIZE_VDO	-12
#define OFFSET_VDONAME	21 // x_pos of username in video window
int CSeerWinDlg::MatchVideoWithText(HWND hWndVidio, int nOffset, CString sText)
{
	LPBYTE pImg = NULL;
	BITMAPINFOHEADER bih;
	int x,y, nwTxt,nhTxt, nMatch=0;
	
	if(hWndVidio==NULL || sText.GetLength()<=0)
		return -1;
	RECT rcVideo;
	::GetClientRect(hWndVidio, &rcVideo);
	HDC hDCVideo = ::GetDC(hWndVidio);

	// create memDC and font
	HDC hMemDC = ::CreateCompatibleDC(hDCVideo);
	CFont* pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lstrcpy(lf.lfFaceName, FONTNAME_VDO);
	lf.lfHeight = FONTSIZE_VDO;
	//lf.lfQuality = ANTIALIASED_QUALITY;
	HFONT hFont = ::CreateFontIndirect(&lf);
	HFONT hoFont = (HFONT)::SelectObject(hMemDC, hFont);
	// get text size
	CDC memDC;
	memDC.Attach(hMemDC);
	memDC.SetMapMode(MM_TEXT);
	CSize sizeTxt = memDC.GetTextExtent(sText, sText.GetLength());
	memDC.Detach();
	nwTxt = sizeTxt.cx;
	nhTxt = sizeTxt.cy;

	memset(&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biBitCount = 24;
	bih.biPlanes = 1;
	bih.biWidth = nwTxt;
	bih.biHeight = nhTxt * 2; //about 34 pix
	HBITMAP hBmp = CreateDIBSection(hDCVideo, (CONST BITMAPINFO *)&bih, DIB_RGB_COLORS, (void**)&pImg, NULL, 0);
	HBITMAP hoBmp = (HBITMAP)::SelectObject(hMemDC, hBmp);
	::PatBlt(hMemDC, 0,0, nwTxt,nhTxt*2, BLACKNESS);

	// generate white text to mem dc
	SetTextColor(hMemDC, 0xffffff);
	SetBkColor(hMemDC, 0x2c2c2c);
	::TextOut(hMemDC, 0,nhTxt, sText, sText.GetLength());
	::SelectObject(hMemDC, hoFont);
	::DeleteObject(hFont);
	
	// copy video's txt area(left-bottom) to mem dc
	::BitBlt(hMemDC, 0,0, nwTxt,nhTxt, hDCVideo, nOffset,rcVideo.bottom-nhTxt-1, SRCCOPY);
	::ReleaseDC(hWndVidio, hDCVideo);
	
	// match video's text with generated text
	int nwb = (nwTxt*3+3)/4*4; // bytes per line
	int nGrey1,nGrey2;
	for(y=0; y<nhTxt; y++)
	{
		LPBYTE pTxt = pImg + (nhTxt+y)*nwb;
		LPBYTE pSrc = pImg + y*nwb;
		for(x=0; x<nwTxt; x++)
		{
			nGrey1 = (pTxt[0]*74 + pTxt[1]*155 + pTxt[2]*27)/256;
			nGrey2 = (pSrc[0]*74 + pSrc[1]*155 + pSrc[2]*27)/256;
			nMatch += abs(nGrey1-nGrey2);
			pTxt+=3, pSrc+=3;
		}
	}
	nMatch = 100 - nMatch/(nwTxt*nhTxt);

	// ========== DBG_ONLY ==========
	::GetWindowRect(hWndVidio, &rcVideo);
	::PatBlt(GetDC()->m_hDC, rcVideo.left-120,rcVideo.top, nwTxt*2,nhTxt*2, WHITENESS);
	::BitBlt(GetDC()->m_hDC, rcVideo.left-120,rcVideo.top, nwTxt,nhTxt*2, hMemDC, 0,0, SRCCOPY);
	CString sMatch;
	sMatch.Format(_T("Match=%d%%"), nMatch);
	::TextOut(GetDC()->m_hDC, rcVideo.left-120,rcVideo.top+40, sMatch, sMatch.GetLength());
	// ========== DBG_ONLY ==========
	
	::SelectObject(hMemDC, hoBmp);
	::DeleteObject(hBmp);
	::DeleteObject(hMemDC);
	return nMatch;
}
