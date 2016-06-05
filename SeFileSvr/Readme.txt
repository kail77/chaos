TCP File Transfer service 文件传输服务端

用于不能使用dcom135端口的场合，支持客户端上传和PCReader下载作业文件。TCP采用IOCP模型，占用系统资源少。
分块发传输的数据大小blocksize=8M.可在xml配置。

【超时关闭连接】
线程Thread_ConnManage()处理，超时10秒不活动的连接，主动关闭。

【通讯协议】
<head> <length> <cmd> <param> <data...>
<head> 'H'(0x48)
<length> 后面命令数据长度，一个字节，暂未使用

<cmd>=U 上传
  <param>=F, data='C:\Job\ab12.dat' 上传文件到服务器 Server ret: H 6 U B blocksize
  客户端发送H0UD0,再发送数据块

<cmd>=D 下载
  <param>=F, data='C:\Job\cd34.dat' 下载服务器的文件 Server ret: H 6 D F blocksize,filesizeL,filesizeH
  客户端请求数据 H 2 D D blockIndex 服务器返回数据块 
  下载完成，客户端发送 H0C0 关闭连接

<cmd>=C 关闭当前socket连接

<cmd>=E 退出程序

【测试命令】
H0R0f:\a.txt 删除文件[F:\a.txt]

H0UFf:\a.txt 上传文件，服务端返回数据块大小(8M) H0UB8
H0UD0 准备上传数据，再次发送数据包，服务端返回收到的字节数H0UD8388608
H0C0 关闭当前连接

H0DFf:\a.txt 下载文件，服务端返回块大小、文件大小、文件大小高位 H0DF8,10xxxx,0
H0DD0,H0DD1,H0DD2... 读取数据，服务端返回数据块内容
H0C0 关闭当前连接

H0E0 退出程序
