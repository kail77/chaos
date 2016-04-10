using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Resources;
using System.Globalization;
using System.Net;
using System.Net.Sockets;

namespace NeTest
{
	public partial class NeTest : Form
	{
		enum socketMode {TcpServer, TcpClient, UdpClient};
		socketMode nSocketMode;
		Socket sockTcpServer, sockClient;
		private byte [] recvBuf = new byte[1024];
		byte[] cmd = new byte[128];
		int m_tick = 0;
		const string strHead = ";Net-Test-Commands-";
		EndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);
		public NeTest()
		{
			InitializeComponent();
			ipAdress.Text = "127.0.0.1";
			udpDestIP.Text = "127.0.0.1";
			tcPort.Text = "4700";
			udPort.Text = "4800";
			textDelay.Text = "300";
			nSocketMode  = socketMode.TcpClient;
			cbMode.SelectedIndex = (int)nSocketMode;
			listCmd.Enabled = false;
		}

		private void Disconnect()
		{
			if (sockClient != null)
			{
				sockClient.Shutdown(SocketShutdown.Both);
				if(nSocketMode == socketMode.TcpClient)
					sockClient.Disconnect(false);
				sockClient.Close();
				sockClient = null;
			}
			if (sockTcpServer != null)
			{
				//sockTcpServer.Shutdown(SocketShutdown.Both);
				sockTcpServer.Close();
				sockTcpServer = null;
			}
			InitConnectBtnState();
			ipAdress.Enabled = true;
			tcPort.Enabled = true;
			btnConnect.Enabled = true;
			btnSend.Enabled = false;
			listCmd.Enabled = false;
		}

		private void Connect_Click(object sender, EventArgs e)
		{
			// close port
			if (sockTcpServer != null || sockClient != null)
			{
				Disconnect();
				return;
			}
			// check ip & port
			string [] ips = ipAdress.Text.Split('.');
			int np = 0, i = 0;
			if (ips.Length == 4)
			{
				foreach (string str in ips)
				{
					np = Int32.Parse(str);
					if (np >= 0 && np <= 255)
						i++;
				}
			}
			if (tcPort.Text.Length > 0)
			{
				np = Int32.Parse(tcPort.Text);
				if (np > 0 && np < 65536)
					i++;
			}
			if (i < 5)
			{
				MessageBox.Show(Properties.Resources.strIPError, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			if (nSocketMode == socketMode.TcpServer)
				sockTcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			if (nSocketMode == socketMode.TcpClient)
				sockClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			if (nSocketMode == socketMode.UdpClient)
			{
				sockClient = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
				udpDestIP.Enabled = true;
				udPort.Enabled = true;
			}
			try
			{
				IPAddress ip = IPAddress.Parse(ipAdress.Text);
				IPEndPoint ipe = new IPEndPoint(ip, np);
				if (nSocketMode == socketMode.TcpClient)
					sockClient.Connect(ipe);
				if (nSocketMode == socketMode.TcpServer)
				{
					sockTcpServer.Bind(ipe);
					sockTcpServer.Listen(1);
				}
				if (nSocketMode == socketMode.UdpClient)
					sockClient.Bind(ipe);
				btnConnect.Text = Properties.Resources.strClose;
				ipAdress.Enabled = false;
				tcPort.Enabled = false;
				btnSend.Enabled = true;
				listCmd.Enabled = true;
				bkReceiving.RunWorkerAsync(); //start ReceivingData
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		private void ReceivingData(object sender, DoWorkEventArgs e)
		{
			// TCP server : Accept connection
			if (nSocketMode == socketMode.TcpServer)
			{
				sockClient = sockTcpServer.Accept();//blocked until client connect in
				btnSend.Enabled = true;
			}
			int nc, i;
			string strb, strText;
			while (true)
			{
				if (nSocketMode == socketMode.UdpClient)
				{
					nc = sockClient.ReceiveFrom(recvBuf, ref remoteEP);//blocked until data coming
					IPEndPoint ipep = (IPEndPoint)remoteEP;
					udpDestIP.Text = Convert.ToString(ipep.Address);
					udPort.Text = Convert.ToString(ipep.Port);
				}
				else
					nc = sockClient.Receive(recvBuf);//blocked until data coming
				if (0 == nc) // error
					break;
				if (chkHide.Checked)
					continue;
				recvBuf[nc] = 0;
				if (textRecv.Text.Length > 0 && Environment.TickCount - m_tick > 100)
					textRecv.AppendText("\r\n");
				strText = String.Format("{0:d}: ", Environment.TickCount);
				for (i = 0; i < nc; i++)
				{
					if (chkHex.Checked)
						strb = String.Format("{0:x2} ", recvBuf[i]);
					else
						strb = String.Format("{0:g}", (char)recvBuf[i]);
					strText += strb;
				}
				textRecv.AppendText(strText);
				m_tick = Environment.TickCount;
			}
		}

		private void GetUdpDest()
		{
			IPEndPoint ipep = (IPEndPoint)remoteEP;	// for UDP
			if (udpDestIP.Text != Convert.ToString(ipep.Address)
				|| udPort.Text != Convert.ToString(ipep.Port))
			{
				IPAddress ip = IPAddress.Parse(udpDestIP.Text);
				int np = Int32.Parse(udPort.Text);
				remoteEP = new IPEndPoint(ip, np);
			}
		}

		private void btnSend_Click(object sender, EventArgs e)
		{
			GetUdpDest();
			bkSending.RunWorkerAsync();// run sendingData
		}

		private void sendingData(object sender, DoWorkEventArgs e)
		{
			int len, i;
			if (listCmd.Items.Count == 0)
			{
				len = str2cmd(textCmd.Text, cmd);
				if (len > 0)
				{
					if (nSocketMode == socketMode.UdpClient)
						sockClient.SendTo(cmd, len, SocketFlags.None, remoteEP);
					else
						sockClient.Send(cmd, len, SocketFlags.None);
				}
				return;
			}
			btnSend.Enabled = false;
			for(i=0; i<listCmd.Items.Count; i++)
			{
				listCmd.SelectedIndex = i;
				len = str2cmd(listCmd.GetItemText(listCmd.Items[i]), cmd);
				if (len > 0)
					sockClient.Send(cmd, len, SocketFlags.None);
				else if (len < 0)
					Thread.Sleep(-len);
				if (chkCycle.Checked && i == listCmd.Items.Count - 1)
				{
					i = -1;
					if (len > 0)	// wait 500 ms to run next
						Thread.Sleep(50);
				}
			}
			btnSend.Enabled = true;
			listCmd.SelectedIndex = -1;
		}

		private void btnCommand_Click(object sender, EventArgs e)
		{
			if (textCmd.Text.Length > 0)
			{
				if (listCmd.SelectedIndex < 0)
					listCmd.Items.Add(textCmd.Text);
				else
					listCmd.Items.Insert(listCmd.SelectedIndex, textCmd.Text);
			}
		}

		private int str2cmd(string strText, byte [] cmd)
		{
			int i = 0;
			if (strText.StartsWith("Delay "))
			{
				string strNum = strText.Substring(5);
				i = Convert.ToInt32(strNum);
				return -i;
			}
			if (strText.StartsWith(";"))	// comment
				return 0;
			char[] cNums;
			cNums = strText.ToCharArray();
			byte ch;
			foreach (char cn in cNums)
			{
				if (cn == ';')	// comment
					break;
				if (!chkHex.Checked)// string
				{
					cmd[i] = (byte)cn;
					if (cn == '!')	// cr
						cmd[i] = (byte)'\r';
					i++;
					continue;
				}
				// hex format
				if (cn == ' ')	// space
					continue;
				if (cn >= '0' && cn <= '9')
					ch = (byte)(cn - '0');
				else if (cn >= 'a' && cn <= 'f')
					ch = (byte)(cn - 'a' + 0xa);
				else if (cn >= 'A' && cn <= 'F')
					ch = (byte)(cn - 'A' + 0xa);
				else
				{
					//ch = 0;
					MessageBox.Show("Error Hex Format!", null, MessageBoxButtons.OK, MessageBoxIcon.Error);
					return 0;
				}
				cmd[i/2] <<= 4;
				cmd[i/2] += ch;
				i++;
			}
			if (chkHex.Checked)
				i /= 2;
			return i;
		}

		private void btnDelay_Click(object sender, EventArgs e)
		{
			string strDelay = "Delay ";
			strDelay += textDelay.Text;
			//strDelay += " ms";
			if (listCmd.SelectedIndex < 0)
				listCmd.Items.Add(strDelay);
			else
				listCmd.Items.Insert(listCmd.SelectedIndex, strDelay);
		}

		private void formClosed(object sender, FormClosedEventArgs e)
		{
			Disconnect();
		}

		private void btnClearRecv_Click(object sender, EventArgs e)
		{
			textRecv.Clear();
		}

		private void btnClearCmd_Click(object sender, EventArgs e)
		{
			textCmd.Clear();
			listCmd.Items.Clear();
		}

		private void dblClickCmd(object sender, EventArgs e)
		{
			if (listCmd.Text.Length > 0)
			{
				int len;
				len = str2cmd(listCmd.Text, cmd);
				if (len == 0)
					return;
				try
				{
					if (nSocketMode == socketMode.UdpClient)
					{
						GetUdpDest();
						sockClient.SendTo(cmd, len, SocketFlags.None, remoteEP);
					}
					else
						sockClient.Send(cmd, len, SocketFlags.None);
				}
				catch (SocketException ex)
				{
					MessageBox.Show(ex.Message);
					if (ex.ErrorCode == 10053)//WSAECONNABORTED
						Disconnect();
				}
			}
		}

		private void btnSave_Click(object sender, EventArgs e)
		{
			if (listCmd.Items.Count == 0)	// no items to be saved
				return;
			SaveFileDialog dlg = new SaveFileDialog();
			dlg.Filter = "Text Files|*.txt||";
			if (DialogResult.Cancel == dlg.ShowDialog())
				return;
			StreamWriter sw = new StreamWriter(dlg.FileName);
			// write head & ip_port
			string strCmd = strHead;
			strCmd += ipAdress.Text + ":" + tcPort.Text;
			sw.WriteLine(strCmd);
			for (int i = 0; i < listCmd.Items.Count; i++)
			{
				strCmd = listCmd.GetItemText(listCmd.Items[i]);
				sw.WriteLine(strCmd);
			}
			sw.Close();
		}

		private void btnLoad_Click(object sender, EventArgs e)
		{
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.Filter = "Text Files|*.txt||";
			if (DialogResult.Cancel == dlg.ShowDialog())
				return;
			listCmd.Items.Clear();
			StreamReader sr = new StreamReader(dlg.FileName);
			string strCmd = sr.ReadLine();	//";Net-Test-Commands-192.168.9.17:4700,192.168.9.16:12105"
			if (!strCmd.StartsWith(strHead))
			{
				MessageBox.Show(Properties.Resources.strCmdError, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			int i, k;
			i = strCmd.IndexOf(':');
			k = strCmd.IndexOf(',');
			if (i>0 && strCmd.Length > strHead.Length)	// read local ip_port
			{
				ipAdress.Text = strCmd.Substring(strHead.Length, i-strHead.Length);
				tcPort.Text = strCmd.Substring(i+1, k<0? strCmd.Length-i-1 : k-i-1);
			}
			i = strCmd.LastIndexOf(':');
			if (i>0 && k>0)	// read dest udp ip_port
			{
				udpDestIP.Text = strCmd.Substring(k+1, i-k-1);
				udPort.Text = strCmd.Substring(i+1, strCmd.Length-i-1);
			}
			while (true)
			{
				strCmd = sr.ReadLine();
				if (strCmd == null)
					break;
				listCmd.Items.Add(strCmd);
			}
			sr.Close();
		}

		private void keyUpList(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Delete)
			{
				listCmd.Items.RemoveAt(listCmd.SelectedIndex);
			}
		}

		private void btnChangeLang_Click(object sender, EventArgs e)
		{
			if (Thread.CurrentThread.CurrentUICulture == CultureInfo.GetCultureInfo("zh-CHS"))
				Thread.CurrentThread.CurrentUICulture = CultureInfo.GetCultureInfo("en");
			else
				Thread.CurrentThread.CurrentUICulture = CultureInfo.GetCultureInfo("zh-CHS");
			ApplyResource();
	   }
	   private void ApplyResource()
	   {
		   System.ComponentModel.ComponentResourceManager res = new ComponentResourceManager(typeof(NeTest));
		   foreach (Control ctl in Controls)
		   {
			   res.ApplyResources(ctl, ctl.Name);
		   }
	   }

		private void InitConnectBtnState()
		{
			if(nSocketMode == socketMode.TcpServer)
				btnConnect.Text = Properties.Resources.strCreate;
			if(nSocketMode == socketMode.TcpClient)
				btnConnect.Text = Properties.Resources.strConnect;
			if(nSocketMode == socketMode.UdpClient)
				btnConnect.Text = Properties.Resources.strOpen;
		}
		private void cbMode_SelectedIndexChanged(object sender, EventArgs e)
		{
			nSocketMode = (socketMode)cbMode.SelectedIndex;
			InitConnectBtnState();
		}
   }
}
