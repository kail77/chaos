namespace NeTest
{
	partial class NeTest
	{
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NeTest));
			this.btnConnect = new System.Windows.Forms.Button();
			this.textCmd = new System.Windows.Forms.TextBox();
			this.listCmd = new System.Windows.Forms.ListBox();
			this.btnCommand = new System.Windows.Forms.Button();
			this.textDelay = new System.Windows.Forms.TextBox();
			this.btnDelay = new System.Windows.Forms.Button();
			this.btnSend = new System.Windows.Forms.Button();
			this.chkCycle = new System.Windows.Forms.CheckBox();
			this.textRecv = new System.Windows.Forms.TextBox();
			this.btnClearRecv = new System.Windows.Forms.Button();
			this.btnClearCmd = new System.Windows.Forms.Button();
			this.chkHex = new System.Windows.Forms.CheckBox();
			this.btnSave = new System.Windows.Forms.Button();
			this.btnLoad = new System.Windows.Forms.Button();
			this.bkSending = new System.ComponentModel.BackgroundWorker();
			this.btnChangeLang = new System.Windows.Forms.Button();
			this.ipAdress = new System.Windows.Forms.MaskedTextBox();
			this.tcPort = new System.Windows.Forms.TextBox();
			this.bkReceiving = new System.ComponentModel.BackgroundWorker();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.chkHide = new System.Windows.Forms.CheckBox();
			this.udpDestIP = new System.Windows.Forms.MaskedTextBox();
			this.udPort = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.cbMode = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// btnConnect
			// 
			this.btnConnect.Location = new System.Drawing.Point(16, 143);
			this.btnConnect.Margin = new System.Windows.Forms.Padding(4);
			this.btnConnect.Name = "btnConnect";
			this.btnConnect.Size = new System.Drawing.Size(104, 28);
			this.btnConnect.TabIndex = 17;
			this.btnConnect.Text = "连接";
			this.btnConnect.UseVisualStyleBackColor = true;
			this.btnConnect.Click += new System.EventHandler(this.Connect_Click);
			// 
			// textCmd
			// 
			this.textCmd.Location = new System.Drawing.Point(131, 325);
			this.textCmd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.textCmd.Name = "textCmd";
			this.textCmd.Size = new System.Drawing.Size(453, 26);
			this.textCmd.TabIndex = 16;
			// 
			// listCmd
			// 
			this.listCmd.FormattingEnabled = true;
			this.listCmd.ItemHeight = 16;
			this.listCmd.Location = new System.Drawing.Point(131, 16);
			this.listCmd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.listCmd.Name = "listCmd";
			this.listCmd.Size = new System.Drawing.Size(561, 260);
			this.listCmd.TabIndex = 15;
			this.listCmd.DoubleClick += new System.EventHandler(this.dblClickCmd);
			this.listCmd.KeyUp += new System.Windows.Forms.KeyEventHandler(this.keyUpList);
			// 
			// btnCommand
			// 
			this.btnCommand.Location = new System.Drawing.Point(15, 322);
			this.btnCommand.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnCommand.Name = "btnCommand";
			this.btnCommand.Size = new System.Drawing.Size(104, 28);
			this.btnCommand.TabIndex = 14;
			this.btnCommand.Text = "输入命令 >>";
			this.btnCommand.UseVisualStyleBackColor = true;
			this.btnCommand.Click += new System.EventHandler(this.btnCommand_Click);
			// 
			// textDelay
			// 
			this.textDelay.Location = new System.Drawing.Point(15, 286);
			this.textDelay.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.textDelay.Name = "textDelay";
			this.textDelay.Size = new System.Drawing.Size(59, 26);
			this.textDelay.TabIndex = 13;
			// 
			// btnDelay
			// 
			this.btnDelay.Location = new System.Drawing.Point(15, 248);
			this.btnDelay.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnDelay.Name = "btnDelay";
			this.btnDelay.Size = new System.Drawing.Size(104, 28);
			this.btnDelay.TabIndex = 12;
			this.btnDelay.Text = "延时 >>";
			this.btnDelay.UseVisualStyleBackColor = true;
			this.btnDelay.Click += new System.EventHandler(this.btnDelay_Click);
			// 
			// btnSend
			// 
			this.btnSend.Enabled = false;
			this.btnSend.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnSend.Location = new System.Drawing.Point(16, 180);
			this.btnSend.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnSend.Name = "btnSend";
			this.btnSend.Size = new System.Drawing.Size(104, 28);
			this.btnSend.TabIndex = 11;
			this.btnSend.Text = "批量发送";
			this.btnSend.UseVisualStyleBackColor = true;
			this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
			// 
			// chkCycle
			// 
			this.chkCycle.Location = new System.Drawing.Point(15, 218);
			this.chkCycle.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.chkCycle.Name = "chkCycle";
			this.chkCycle.Size = new System.Drawing.Size(59, 20);
			this.chkCycle.TabIndex = 10;
			this.chkCycle.Text = "循环";
			this.chkCycle.UseVisualStyleBackColor = true;
			// 
			// textRecv
			// 
			this.textRecv.Location = new System.Drawing.Point(16, 398);
			this.textRecv.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.textRecv.Multiline = true;
			this.textRecv.Name = "textRecv";
			this.textRecv.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textRecv.Size = new System.Drawing.Size(676, 253);
			this.textRecv.TabIndex = 9;
			// 
			// btnClearRecv
			// 
			this.btnClearRecv.Location = new System.Drawing.Point(16, 360);
			this.btnClearRecv.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnClearRecv.Name = "btnClearRecv";
			this.btnClearRecv.Size = new System.Drawing.Size(104, 28);
			this.btnClearRecv.TabIndex = 8;
			this.btnClearRecv.Text = "清空接收区";
			this.btnClearRecv.UseVisualStyleBackColor = true;
			this.btnClearRecv.Click += new System.EventHandler(this.btnClearRecv_Click);
			// 
			// btnClearCmd
			// 
			this.btnClearCmd.Location = new System.Drawing.Point(592, 325);
			this.btnClearCmd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnClearCmd.Name = "btnClearCmd";
			this.btnClearCmd.Size = new System.Drawing.Size(100, 28);
			this.btnClearCmd.TabIndex = 7;
			this.btnClearCmd.Text = "清空命令";
			this.btnClearCmd.UseVisualStyleBackColor = true;
			this.btnClearCmd.Click += new System.EventHandler(this.btnClearCmd_Click);
			// 
			// chkHex
			// 
			this.chkHex.Checked = true;
			this.chkHex.CheckState = System.Windows.Forms.CheckState.Checked;
			this.chkHex.Location = new System.Drawing.Point(617, 368);
			this.chkHex.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.chkHex.Name = "chkHex";
			this.chkHex.Size = new System.Drawing.Size(75, 20);
			this.chkHex.TabIndex = 6;
			this.chkHex.Text = "16进制";
			this.chkHex.UseVisualStyleBackColor = true;
			// 
			// btnSave
			// 
			this.btnSave.Location = new System.Drawing.Point(264, 360);
			this.btnSave.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size(100, 28);
			this.btnSave.TabIndex = 5;
			this.btnSave.Text = "保存命令";
			this.btnSave.UseVisualStyleBackColor = true;
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(372, 360);
			this.btnLoad.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.Size = new System.Drawing.Size(100, 28);
			this.btnLoad.TabIndex = 4;
			this.btnLoad.Text = "载入命令";
			this.btnLoad.UseVisualStyleBackColor = true;
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// bkSending
			// 
			this.bkSending.DoWork += new System.ComponentModel.DoWorkEventHandler(this.sendingData);
			// 
			// btnChangeLang
			// 
			this.btnChangeLang.Location = new System.Drawing.Point(480, 362);
			this.btnChangeLang.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnChangeLang.Name = "btnChangeLang";
			this.btnChangeLang.Size = new System.Drawing.Size(49, 26);
			this.btnChangeLang.TabIndex = 3;
			this.btnChangeLang.Text = "En";
			this.btnChangeLang.UseVisualStyleBackColor = true;
			this.btnChangeLang.Visible = false;
			this.btnChangeLang.Click += new System.EventHandler(this.btnChangeLang_Click);
			// 
			// ipAdress
			// 
			this.ipAdress.Location = new System.Drawing.Point(16, 49);
			this.ipAdress.Margin = new System.Windows.Forms.Padding(4);
			this.ipAdress.Name = "ipAdress";
			this.ipAdress.Size = new System.Drawing.Size(103, 26);
			this.ipAdress.TabIndex = 2;
			// 
			// tcPort
			// 
			this.tcPort.Location = new System.Drawing.Point(59, 83);
			this.tcPort.Margin = new System.Windows.Forms.Padding(4);
			this.tcPort.Name = "tcPort";
			this.tcPort.Size = new System.Drawing.Size(60, 26);
			this.tcPort.TabIndex = 1;
			// 
			// bkReceiving
			// 
			this.bkReceiving.DoWork += new System.ComponentModel.DoWorkEventHandler(this.ReceivingData);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 88);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(40, 16);
			this.label2.TabIndex = 19;
			this.label2.Text = "端口";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(79, 296);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(40, 16);
			this.label1.TabIndex = 20;
			this.label1.Text = "毫秒";
			// 
			// chkHide
			// 
			this.chkHide.AutoSize = true;
			this.chkHide.Location = new System.Drawing.Point(131, 368);
			this.chkHide.Name = "chkHide";
			this.chkHide.Size = new System.Drawing.Size(75, 20);
			this.chkHide.TabIndex = 21;
			this.chkHide.Text = "不显示";
			this.chkHide.UseVisualStyleBackColor = true;
			// 
			// udpDestIP
			// 
			this.udpDestIP.Location = new System.Drawing.Point(226, 286);
			this.udpDestIP.Margin = new System.Windows.Forms.Padding(4);
			this.udpDestIP.Name = "udpDestIP";
			this.udpDestIP.Size = new System.Drawing.Size(138, 26);
			this.udpDestIP.TabIndex = 24;
			// 
			// udPort
			// 
			this.udPort.Location = new System.Drawing.Point(372, 286);
			this.udPort.Margin = new System.Windows.Forms.Padding(4);
			this.udPort.Name = "udPort";
			this.udPort.Size = new System.Drawing.Size(63, 26);
			this.udPort.TabIndex = 25;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(147, 296);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(72, 16);
			this.label3.TabIndex = 26;
			this.label3.Text = "UDP Dest";
			// 
			// cbMode
			// 
			this.cbMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbMode.FormattingEnabled = true;
			this.cbMode.Items.AddRange(new object[] {
            "TCP Server",
            "TCP Client",
            "UDP"});
			this.cbMode.Location = new System.Drawing.Point(15, 12);
			this.cbMode.Name = "cbMode";
			this.cbMode.Size = new System.Drawing.Size(105, 24);
			this.cbMode.TabIndex = 27;
			this.cbMode.SelectedIndexChanged += new System.EventHandler(this.cbMode_SelectedIndexChanged);
			// 
			// NeTest
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(709, 665);
			this.Controls.Add(this.cbMode);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.udPort);
			this.Controls.Add(this.udpDestIP);
			this.Controls.Add(this.chkHide);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.tcPort);
			this.Controls.Add(this.ipAdress);
			this.Controls.Add(this.btnChangeLang);
			this.Controls.Add(this.btnLoad);
			this.Controls.Add(this.btnSave);
			this.Controls.Add(this.chkHex);
			this.Controls.Add(this.btnClearCmd);
			this.Controls.Add(this.btnClearRecv);
			this.Controls.Add(this.textRecv);
			this.Controls.Add(this.chkCycle);
			this.Controls.Add(this.btnSend);
			this.Controls.Add(this.btnDelay);
			this.Controls.Add(this.textDelay);
			this.Controls.Add(this.btnCommand);
			this.Controls.Add(this.listCmd);
			this.Controls.Add(this.textCmd);
			this.Controls.Add(this.btnConnect);
			this.Font = new System.Drawing.Font("SimSun", 12F);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Margin = new System.Windows.Forms.Padding(4, 8, 4, 8);
			this.MaximizeBox = false;
			this.Name = "NeTest";
			this.Text = "网络TCP工具";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formClosed);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnConnect;
		private System.Windows.Forms.TextBox textCmd;
		private System.Windows.Forms.ListBox listCmd;
		private System.Windows.Forms.Button btnCommand;
		private System.Windows.Forms.TextBox textDelay;
		private System.Windows.Forms.Button btnDelay;
		private System.Windows.Forms.Button btnSend;
		private System.Windows.Forms.CheckBox chkCycle;
		private System.Windows.Forms.TextBox textRecv;
		private System.Windows.Forms.Button btnClearRecv;
		private System.Windows.Forms.Button btnClearCmd;
		private System.Windows.Forms.CheckBox chkHex;
		private System.Windows.Forms.Button btnSave;
		private System.Windows.Forms.Button btnLoad;
        private System.ComponentModel.BackgroundWorker bkSending;
		private System.Windows.Forms.Button btnChangeLang;
		private System.Windows.Forms.MaskedTextBox ipAdress;
		private System.Windows.Forms.TextBox tcPort;
		private System.ComponentModel.BackgroundWorker bkReceiving;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox chkHide;
		private System.Windows.Forms.MaskedTextBox udpDestIP;
		private System.Windows.Forms.TextBox udPort;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox cbMode;
	}
}

