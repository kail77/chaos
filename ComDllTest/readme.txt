��̬����COM�ӿ�

1.Visual Studio 2008 Command Prompt, ����[tlbimp xxxCom.dll], ����һ��xxxComLib.dll�Ľӿ��ļ���
2.���������ӿ��ļ���λ�ã���"D:\Test\xxxComLib.dll", NameSpace.Classһ��Ϊ"xxxComLib.xxxComClass"
  ������ָ�� /namespace:Namespace Ĭ��Ϊ�ļ�����
3.���԰��������ã�д��exe.config, <add key="ComDll" value="ICCVPFLib.dll" /> <add key="ClassName" value="ICCVPFLib.VpfCOMClass" />
4.��64λϵͳ�£����Ŀ�������32λ�ģ���ComDllTestҲ������platformTarget-x86���룬�������Ϊ�����δע�ᡱ����
5.����ֻ�ܵ���debug�汾��dll, ����ᡰ�����ڲ�����

ConnDB()
Driver={SQL Server};Server=localhost\SQLEXPRESS;Address=localhost\SQLEXPRESS,1433;Network=DBMSSOCN;Trusted_Connection=no;Uid=sa;Pwd=asd123465QWE;Pooling=True;Database=SecuPrintBase

ANSI�ַ���
���COM�ӿڵĲ���ʹ����LPCTSTR, ��¶�ڽӿڵ�����ΪString(Unicode). �������ΪLPCSTR,��ӿ�����ΪString(Ansi),COM���û��Զ�ת����

