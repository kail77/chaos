动态调用COM接口

1.Visual Studio 2008 Command Prompt, 输入[tlbimp xxxCom.dll], 生成一个xxxComLib.dll的接口文件。
2.输入上述接口文件的位置，如"D:\Test\xxxComLib.dll", NameSpace.Class一般为"xxxComLib.xxxComClass"
  （可以指定 /namespace:Namespace 默认为文件名）
3.可以把上述配置，写入exe.config, <add key="ComDll" value="ICCVPFLib.dll" /> <add key="ClassName" value="ICCVPFLib.VpfCOMClass" />
4.在64位系统下，如果目标组件是32位的，则ComDllTest也必须以platformTarget-x86编译，否则会因为“组件未注册”报错
5.好像只能调用debug版本的dll, 否则会“发生内部错误”

ConnDB()
Driver={SQL Server};Server=localhost\SQLEXPRESS;Address=localhost\SQLEXPRESS,1433;Network=DBMSSOCN;Trusted_Connection=no;Uid=sa;Pwd=asd123465QWE;Pooling=True;Database=SecuPrintBase

ANSI字符串
如果COM接口的参数使用了LPCTSTR, 则暴露在接口的类型为String(Unicode). 如果参数为LPCSTR,则接口类型为String(Ansi),COM调用会自动转换。

