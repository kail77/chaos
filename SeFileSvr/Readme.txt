TCP File Transfer service �ļ���������

���ڲ���ʹ��dcom135�˿ڵĳ��ϣ�֧�ֿͻ����ϴ���PCReader������ҵ�ļ���TCP����IOCPģ�ͣ�ռ��ϵͳ��Դ�١�
�ֿ鷢��������ݴ�Сblocksize=8M.����xml���á�

����ʱ�ر����ӡ�
�߳�Thread_ConnManage()������ʱ10�벻������ӣ������رա�

��ͨѶЭ�顿
<head> <length> <cmd> <param> <data...>
<head> 'H'(0x48)
<length> �����������ݳ��ȣ�һ���ֽڣ���δʹ��

<cmd>=U �ϴ�
  <param>=F, data='C:\Job\ab12.dat' �ϴ��ļ��������� Server ret: H 6 U B blocksize
  �ͻ��˷���H0UD0,�ٷ������ݿ�

<cmd>=D ����
  <param>=F, data='C:\Job\cd34.dat' ���ط��������ļ� Server ret: H 6 D F blocksize,filesizeL,filesizeH
  �ͻ����������� H 2 D D blockIndex �������������ݿ� 
  ������ɣ��ͻ��˷��� H0C0 �ر�����

<cmd>=C �رյ�ǰsocket����

<cmd>=E �˳�����

���������
H0R0f:\a.txt ɾ���ļ�[F:\a.txt]

H0UFf:\a.txt �ϴ��ļ�������˷������ݿ��С(8M) H0UB8
H0UD0 ׼���ϴ����ݣ��ٴη������ݰ�������˷����յ����ֽ���H0UD8388608
H0C0 �رյ�ǰ����

H0DFf:\a.txt �����ļ�������˷��ؿ��С���ļ���С���ļ���С��λ H0DF8,10xxxx,0
H0DD0,H0DD1,H0DD2... ��ȡ���ݣ�����˷������ݿ�����
H0C0 �رյ�ǰ����

H0E0 �˳�����
