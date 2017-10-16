svn https://101.201.54.155:18491/svn/00.code/WinApp/SeerWin  
chaochun/seeR1234


使用说明：

1.用13811626980/6980登录西禾口语。

2.上课测试->在线课堂测试

3.用另外一台电脑/手机，下载zoom，加入会议：9591556438

    1）电脑下载地址：https://zoom.us/client/latest/ZoomInstaller.exe

    2) 手机下载地址：商店中搜索：“zoom”

4.共享屏幕。

5.测试多人的时候，分别用其他设备(pc/pad/mobile)下载zoom，加入会议：9591556438

SeerWinDlg 嵌入Explorer控件{8856F961-340A-11D0-A96B-00C04FD705A2} 初始化连接"http://seerenglish.com/ensprivate/sschedule"
BeforeNavigate2Explorer1()相应url连接消息，当用户点击“在线课堂测试”链接"zoommtg://seerenglish.com/join?confno=6589485989&uname=Student_Jessie"时，启动客户端本地Zoom组件InitZoom()

InitZoom() - m_pAuthServiceMgr->Init("https://zoom.us"), m_pMeetingServiceMgr->init(appKey,appSecret)

zoom怎么与对话框关联？响应消息？
  m_pMeetingServiceMgr创建了ZoomService

GetMeetingUIWnd(m_hmeeting, secondview); //zoom的主窗口
m_hleft = ::FindWindowEx(m_hmeeting, NULL, NULL, L"ContentLeftPanel"); //LeftPanel
m_hdock = ::FindWindow(NULL, L"DockVideoContainer"); // 视频容器窗口
if (m_hdock == NULL)
	m_hdock = ::FindWindowEx(m_hleft, NULL, NULL, L"DockVideoContainer");
m_hshare = ::FindWindowEx(m_hleft, NULL, NULL, L"ShareContainerWnd"); // 共享桌面窗口


onMeetingStatusChanged, onUserJoin, onUserLeft, onSharingStatus,

现有的zoom会议功能与不足
教师与学生在会议中是同等角色，无法控制学生的屏幕显示，也无法给学生奖励等交互反馈；

需求分析
多人会议，教师仍使用zoom客户端，多个学生都使用SeerWin客户端，从网页进入会议后，基本上没有需要输入的操作，只显示状态和呈现教师的操作。
1.教师在网页课件指定当前对话学生，SeerWin以放大居中、标记框等方式显示该学生视频窗口。
2.教师在网页课件奖励某学生，SeerWin在该学生视频窗口加上标记。
教师在zoom中看不到这些变化，但可以在课件中显示。

概要设计

1.SeerWin与服务端webSocket通讯
String GetMettingInfo(String param);

2.客户端识别各窗口对应的用户
多人在线时，SeerWin不知道zoom生成的视频窗口与用户名的对应关系。从服务端调用接口GetMettingInfo(),从获取到的Members段中提取当前用户列表，如"Tom,Jack",然后再与视频窗口左下角的名称匹配。

3.响应教师的奖励操作
教师在网页课件奖励某学生，同时向webSocket后端服务发送消息，后端服务将此消息转发给该学生。
