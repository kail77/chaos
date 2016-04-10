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

namespace comTest
{
	public partial class comTest : Form
	{
		int m_tick = 0;
		public comTest()
		{
			InitializeComponent();
			comNum.SelectedIndex = 0;
			baudRate.SelectedIndex = 6;
		}

		private void openPort_Click(object sender, EventArgs e)
		{
			if (serPort.IsOpen)	// close port
			{
				serPort.Close();
				btnSend.Enabled = false;
				btnOpen.Text = Properties.Resources.strOpen;
				comNum.Enabled = true;
				baudRate.Enabled = true;
			}
			else// open port
			{
				serPort.PortName = comNum.Text;
				serPort.BaudRate = Int32.Parse(baudRate.Text);//Convert.ToInt32(baudRate.Text);
				try
				{
					serPort.Open();
				}
				catch (System.IO.IOException)
				{
                    
					MessageBox.Show(Properties.Resources.strComError, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
					return;
				}
				finally
				{
				}
				btnSend.Enabled = true;
				btnOpen.Text = Properties.Resources.strClose;
				comNum.Enabled = false;
				baudRate.Enabled = false;
			}
		}

		private void btnSend_Click(object sender, EventArgs e)
		{
			//Thread threadSending = new Thread(new ThreadStart(sendingData));
			//threadSending.Start();
            btnSend.Enabled = false;
            bkSending.RunWorkerAsync();
		}

        private void sendingData(object sender, DoWorkEventArgs e)
		{
			byte[] cmd;
			cmd = new byte[128];
			int len, i;
			if (listCmd.Items.Count == 0)
			{
				len = str2cmd(textCmd.Text, cmd);
				if (len > 0)
					serPort.Write(cmd, 0, len);
				return;
			}
            bool bCycle = chkCycle.Checked;
			for(i=0; i<listCmd.Items.Count; i++)
			{
                listCmd.SelectedIndex = i;
				len = str2cmd(listCmd.GetItemText(listCmd.Items[i]), cmd);
                if (len > 0 && serPort.IsOpen)
					serPort.Write(cmd, 0, len);
				else if (len < 0)
					Thread.Sleep(-len);
				if (bCycle && i == listCmd.Items.Count - 1)
				{
					i = -1;
					if (len > 0)	// wait 500 ms to run next
						Thread.Sleep(500);
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

		private void comDataRecv(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
		{
			byte rb;
			string strb;
			if (chkHide.Checked)
			{
				serPort.ReadExisting();
				return;
			}
			if (Environment.TickCount - m_tick > 100)
			{
				if (textRecv.Text.Length > 0)
					textRecv.AppendText("\r\n");
				strb = String.Format("{0:d}: ", Environment.TickCount);
				textRecv.AppendText(strb);
			}
			while (serPort.BytesToRead > 0)
			{
				rb = (byte)serPort.ReadByte();
				if (chkHex.Checked)
					strb = String.Format("{0:x2} ", rb);
				else
					strb = String.Format("{0:g}", (char)rb);
				textRecv.AppendText(strb);
			}
			m_tick = Environment.TickCount;
		}

		private void formClosed(object sender, FormClosedEventArgs e)
		{
			if (serPort.IsOpen)
				serPort.Close();
			if(bkSending.IsBusy)
				bkSending.CancelAsync();
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
				byte[] cmd;
				cmd = new byte[128];
				int len;
				len = str2cmd(listCmd.Text, cmd);
				if (len > 0 && serPort.IsOpen)
					serPort.Write(cmd, 0, len);
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
			string strCmd = ";Com Test Commands";
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
			string strCmd = sr.ReadLine();
			if (strCmd.CompareTo(";Com Test Commands") != 0)
			{
				MessageBox.Show(Properties.Resources.strCmdError, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
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
           System.ComponentModel.ComponentResourceManager res = new ComponentResourceManager(typeof(comTest));
           foreach (Control ctl in Controls)
           {
               res.ApplyResources(ctl, ctl.Name);
           }
       }
   }
}
