svn https://101.201.54.155:18491/svn/00.code/WinApp/SeerWin  
chaochun/seeR1234


ʹ��˵����

1.��13811626980/6980��¼���̿��

2.�Ͽβ���->���߿��ò���

3.������һ̨����/�ֻ�������zoom��������飺9591556438

    1���������ص�ַ��https://zoom.us/client/latest/ZoomInstaller.exe

    2) �ֻ����ص�ַ���̵�����������zoom��

4.������Ļ��

5.���Զ��˵�ʱ�򣬷ֱ��������豸(pc/pad/mobile)����zoom��������飺9591556438

SeerWinDlg Ƕ��Explorer�ؼ�{8856F961-340A-11D0-A96B-00C04FD705A2} ��ʼ������"http://seerenglish.com/ensprivate/sschedule"
BeforeNavigate2Explorer1()��Ӧurl������Ϣ�����û���������߿��ò��ԡ�����"zoommtg://seerenglish.com/join?confno=6589485989&uname=Student_Jessie"ʱ�������ͻ��˱���Zoom���InitZoom()

InitZoom() - m_pAuthServiceMgr->Init("https://zoom.us"), m_pMeetingServiceMgr->init(appKey,appSecret)

zoom��ô��Ի����������Ӧ��Ϣ��
  m_pMeetingServiceMgr������ZoomService

GetMeetingUIWnd(m_hmeeting, secondview); //zoom��������
m_hleft = ::FindWindowEx(m_hmeeting, NULL, NULL, L"ContentLeftPanel"); //LeftPanel
m_hdock = ::FindWindow(NULL, L"DockVideoContainer"); // ��Ƶ��������
if (m_hdock == NULL)
	m_hdock = ::FindWindowEx(m_hleft, NULL, NULL, L"DockVideoContainer");
m_hshare = ::FindWindowEx(m_hleft, NULL, NULL, L"ShareContainerWnd"); // �������洰��


onMeetingStatusChanged, onUserJoin, onUserLeft, onSharingStatus,

���е�zoom���鹦���벻��
��ʦ��ѧ���ڻ�������ͬ�Ƚ�ɫ���޷�����ѧ������Ļ��ʾ��Ҳ�޷���ѧ�������Ƚ���������

�������
���˻��飬��ʦ��ʹ��zoom�ͻ��ˣ����ѧ����ʹ��SeerWin�ͻ��ˣ�����ҳ�������󣬻�����û����Ҫ����Ĳ�����ֻ��ʾ״̬�ͳ��ֽ�ʦ�Ĳ�����
1.��ʦ����ҳ�μ�ָ����ǰ�Ի�ѧ����SeerWin�ԷŴ���С���ǿ�ȷ�ʽ��ʾ��ѧ����Ƶ���ڡ�
2.��ʦ����ҳ�μ�����ĳѧ����SeerWin�ڸ�ѧ����Ƶ���ڼ��ϱ�ǡ�
��ʦ��zoom�п�������Щ�仯���������ڿμ�����ʾ��

��Ҫ���

1.SeerWin������webSocketͨѶ
String GetMettingInfo(String param);

2.�ͻ���ʶ������ڶ�Ӧ���û�
��������ʱ��SeerWin��֪��zoom���ɵ���Ƶ�������û����Ķ�Ӧ��ϵ���ӷ���˵��ýӿ�GetMettingInfo(),�ӻ�ȡ����Members������ȡ��ǰ�û��б���"Tom,Jack",Ȼ��������Ƶ�������½ǵ�����ƥ�䡣

3.��Ӧ��ʦ�Ľ�������
��ʦ����ҳ�μ�����ĳѧ����ͬʱ��webSocket��˷�������Ϣ����˷��񽫴���Ϣת������ѧ����
