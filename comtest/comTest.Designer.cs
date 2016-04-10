namespace comTest
{
	partial class comTest
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(comTest));
			this.comNum = new System.Windows.Forms.ComboBox();
			this.btnOpen = new System.Windows.Forms.Button();
			this.serPort = new System.IO.Ports.SerialPort(this.components);
			this.textCmd = new System.Windows.Forms.TextBox();
			this.listCmd = new System.Windows.Forms.ListBox();
			this.btnCommand = new System.Windows.Forms.Button();
			this.textDelay = new System.Windows.Forms.TextBox();
			this.btnDelay = new System.Windows.Forms.Button();
			this.btnSend = new System.Windows.Forms.Button();
			this.chkCycle = new System.Windows.Forms.CheckBox();
			this.textRecv = new System.Windows.Forms.TextBox();
			this.baudRate = new System.Windows.Forms.ComboBox();
			this.btnClearRecv = new System.Windows.Forms.Button();
			this.btnClearCmd = new System.Windows.Forms.Button();
			this.chkHex = new System.Windows.Forms.CheckBox();
			this.btnSave = new System.Windows.Forms.Button();
			this.btnLoad = new System.Windows.Forms.Button();
			this.bkSending = new System.ComponentModel.BackgroundWorker();
			this.btnChangeLang = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.chkHide = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// comNum
			// 
			this.comNum.AccessibleDescription = null;
			this.comNum.AccessibleName = null;
			resources.ApplyResources(this.comNum, "comNum");
			this.comNum.BackgroundImage = null;
			this.comNum.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comNum.Font = null;
			this.comNum.FormattingEnabled = true;
			this.comNum.Items.AddRange(new object[] {
            resources.GetString("comNum.Items"),
            resources.GetString("comNum.Items1"),
            resources.GetString("comNum.Items2"),
            resources.GetString("comNum.Items3"),
            resources.GetString("comNum.Items4"),
            resources.GetString("comNum.Items5"),
            resources.GetString("comNum.Items6"),
            resources.GetString("comNum.Items7"),
            resources.GetString("comNum.Items8"),
            resources.GetString("comNum.Items9")});
			this.comNum.Name = "comNum";
			// 
			// btnOpen
			// 
			this.btnOpen.AccessibleDescription = null;
			this.btnOpen.AccessibleName = null;
			resources.ApplyResources(this.btnOpen, "btnOpen");
			this.btnOpen.BackgroundImage = null;
			this.btnOpen.Font = null;
			this.btnOpen.Name = "btnOpen";
			this.btnOpen.UseVisualStyleBackColor = true;
			this.btnOpen.Click += new System.EventHandler(this.openPort_Click);
			// 
			// serPort
			// 
			this.serPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.comDataRecv);
			// 
			// textCmd
			// 
			this.textCmd.AccessibleDescription = null;
			this.textCmd.AccessibleName = null;
			resources.ApplyResources(this.textCmd, "textCmd");
			this.textCmd.BackgroundImage = null;
			this.textCmd.Font = null;
			this.textCmd.Name = "textCmd";
			// 
			// listCmd
			// 
			this.listCmd.AccessibleDescription = null;
			this.listCmd.AccessibleName = null;
			resources.ApplyResources(this.listCmd, "listCmd");
			this.listCmd.BackgroundImage = null;
			this.listCmd.Font = null;
			this.listCmd.FormattingEnabled = true;
			this.listCmd.Name = "listCmd";
			this.listCmd.DoubleClick += new System.EventHandler(this.dblClickCmd);
			this.listCmd.KeyUp += new System.Windows.Forms.KeyEventHandler(this.keyUpList);
			// 
			// btnCommand
			// 
			this.btnCommand.AccessibleDescription = null;
			this.btnCommand.AccessibleName = null;
			resources.ApplyResources(this.btnCommand, "btnCommand");
			this.btnCommand.BackgroundImage = null;
			this.btnCommand.Font = null;
			this.btnCommand.Name = "btnCommand";
			this.btnCommand.UseVisualStyleBackColor = true;
			this.btnCommand.Click += new System.EventHandler(this.btnCommand_Click);
			// 
			// textDelay
			// 
			this.textDelay.AccessibleDescription = null;
			this.textDelay.AccessibleName = null;
			resources.ApplyResources(this.textDelay, "textDelay");
			this.textDelay.BackgroundImage = null;
			this.textDelay.Font = null;
			this.textDelay.Name = "textDelay";
			// 
			// btnDelay
			// 
			this.btnDelay.AccessibleDescription = null;
			this.btnDelay.AccessibleName = null;
			resources.ApplyResources(this.btnDelay, "btnDelay");
			this.btnDelay.BackgroundImage = null;
			this.btnDelay.Font = null;
			this.btnDelay.Name = "btnDelay";
			this.btnDelay.UseVisualStyleBackColor = true;
			this.btnDelay.Click += new System.EventHandler(this.btnDelay_Click);
			// 
			// btnSend
			// 
			this.btnSend.AccessibleDescription = null;
			this.btnSend.AccessibleName = null;
			resources.ApplyResources(this.btnSend, "btnSend");
			this.btnSend.BackgroundImage = null;
			this.btnSend.Font = null;
			this.btnSend.Name = "btnSend";
			this.btnSend.UseVisualStyleBackColor = true;
			this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
			// 
			// chkCycle
			// 
			this.chkCycle.AccessibleDescription = null;
			this.chkCycle.AccessibleName = null;
			resources.ApplyResources(this.chkCycle, "chkCycle");
			this.chkCycle.BackgroundImage = null;
			this.chkCycle.Font = null;
			this.chkCycle.Name = "chkCycle";
			this.chkCycle.UseVisualStyleBackColor = true;
			// 
			// textRecv
			// 
			this.textRecv.AccessibleDescription = null;
			this.textRecv.AccessibleName = null;
			resources.ApplyResources(this.textRecv, "textRecv");
			this.textRecv.BackgroundImage = null;
			this.textRecv.Name = "textRecv";
			// 
			// baudRate
			// 
			this.baudRate.AccessibleDescription = null;
			this.baudRate.AccessibleName = null;
			resources.ApplyResources(this.baudRate, "baudRate");
			this.baudRate.BackgroundImage = null;
			this.baudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.baudRate.Font = null;
			this.baudRate.FormattingEnabled = true;
			this.baudRate.Items.AddRange(new object[] {
            resources.GetString("baudRate.Items"),
            resources.GetString("baudRate.Items1"),
            resources.GetString("baudRate.Items2"),
            resources.GetString("baudRate.Items3"),
            resources.GetString("baudRate.Items4"),
            resources.GetString("baudRate.Items5"),
            resources.GetString("baudRate.Items6"),
            resources.GetString("baudRate.Items7"),
            resources.GetString("baudRate.Items8"),
            resources.GetString("baudRate.Items9"),
            resources.GetString("baudRate.Items10"),
            resources.GetString("baudRate.Items11"),
            resources.GetString("baudRate.Items12")});
			this.baudRate.Name = "baudRate";
			// 
			// btnClearRecv
			// 
			this.btnClearRecv.AccessibleDescription = null;
			this.btnClearRecv.AccessibleName = null;
			resources.ApplyResources(this.btnClearRecv, "btnClearRecv");
			this.btnClearRecv.BackgroundImage = null;
			this.btnClearRecv.Font = null;
			this.btnClearRecv.Name = "btnClearRecv";
			this.btnClearRecv.UseVisualStyleBackColor = true;
			this.btnClearRecv.Click += new System.EventHandler(this.btnClearRecv_Click);
			// 
			// btnClearCmd
			// 
			this.btnClearCmd.AccessibleDescription = null;
			this.btnClearCmd.AccessibleName = null;
			resources.ApplyResources(this.btnClearCmd, "btnClearCmd");
			this.btnClearCmd.BackgroundImage = null;
			this.btnClearCmd.Font = null;
			this.btnClearCmd.Name = "btnClearCmd";
			this.btnClearCmd.UseVisualStyleBackColor = true;
			this.btnClearCmd.Click += new System.EventHandler(this.btnClearCmd_Click);
			// 
			// chkHex
			// 
			this.chkHex.AccessibleDescription = null;
			this.chkHex.AccessibleName = null;
			resources.ApplyResources(this.chkHex, "chkHex");
			this.chkHex.BackgroundImage = null;
			this.chkHex.Checked = true;
			this.chkHex.CheckState = System.Windows.Forms.CheckState.Checked;
			this.chkHex.Font = null;
			this.chkHex.Name = "chkHex";
			this.chkHex.UseVisualStyleBackColor = true;
			// 
			// btnSave
			// 
			this.btnSave.AccessibleDescription = null;
			this.btnSave.AccessibleName = null;
			resources.ApplyResources(this.btnSave, "btnSave");
			this.btnSave.BackgroundImage = null;
			this.btnSave.Font = null;
			this.btnSave.Name = "btnSave";
			this.btnSave.UseVisualStyleBackColor = true;
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// btnLoad
			// 
			this.btnLoad.AccessibleDescription = null;
			this.btnLoad.AccessibleName = null;
			resources.ApplyResources(this.btnLoad, "btnLoad");
			this.btnLoad.BackgroundImage = null;
			this.btnLoad.Font = null;
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.UseVisualStyleBackColor = true;
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// bkSending
			// 
			this.bkSending.DoWork += new System.ComponentModel.DoWorkEventHandler(this.sendingData);
			// 
			// btnChangeLang
			// 
			this.btnChangeLang.AccessibleDescription = null;
			this.btnChangeLang.AccessibleName = null;
			resources.ApplyResources(this.btnChangeLang, "btnChangeLang");
			this.btnChangeLang.BackgroundImage = null;
			this.btnChangeLang.Font = null;
			this.btnChangeLang.Name = "btnChangeLang";
			this.btnChangeLang.UseVisualStyleBackColor = true;
			this.btnChangeLang.Click += new System.EventHandler(this.btnChangeLang_Click);
			// 
			// label1
			// 
			this.label1.AccessibleDescription = null;
			this.label1.AccessibleName = null;
			resources.ApplyResources(this.label1, "label1");
			this.label1.Font = null;
			this.label1.Name = "label1";
			// 
			// chkHide
			// 
			this.chkHide.AccessibleDescription = null;
			this.chkHide.AccessibleName = null;
			resources.ApplyResources(this.chkHide, "chkHide");
			this.chkHide.BackgroundImage = null;
			this.chkHide.Font = null;
			this.chkHide.Name = "chkHide";
			this.chkHide.UseVisualStyleBackColor = true;
			// 
			// comTest
			// 
			this.AccessibleDescription = null;
			this.AccessibleName = null;
			resources.ApplyResources(this, "$this");
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackgroundImage = null;
			this.Controls.Add(this.chkHide);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnChangeLang);
			this.Controls.Add(this.btnLoad);
			this.Controls.Add(this.btnSave);
			this.Controls.Add(this.chkHex);
			this.Controls.Add(this.btnClearCmd);
			this.Controls.Add(this.btnClearRecv);
			this.Controls.Add(this.baudRate);
			this.Controls.Add(this.textRecv);
			this.Controls.Add(this.chkCycle);
			this.Controls.Add(this.btnSend);
			this.Controls.Add(this.btnDelay);
			this.Controls.Add(this.textDelay);
			this.Controls.Add(this.btnCommand);
			this.Controls.Add(this.listCmd);
			this.Controls.Add(this.textCmd);
			this.Controls.Add(this.btnOpen);
			this.Controls.Add(this.comNum);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "comTest";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formClosed);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox comNum;
		private System.Windows.Forms.Button btnOpen;
		private System.IO.Ports.SerialPort serPort;
		private System.Windows.Forms.TextBox textCmd;
		private System.Windows.Forms.ListBox listCmd;
		private System.Windows.Forms.Button btnCommand;
		private System.Windows.Forms.TextBox textDelay;
		private System.Windows.Forms.Button btnDelay;
		private System.Windows.Forms.Button btnSend;
		private System.Windows.Forms.CheckBox chkCycle;
		private System.Windows.Forms.TextBox textRecv;
		private System.Windows.Forms.ComboBox baudRate;
		private System.Windows.Forms.Button btnClearRecv;
		private System.Windows.Forms.Button btnClearCmd;
		private System.Windows.Forms.CheckBox chkHex;
		private System.Windows.Forms.Button btnSave;
		private System.Windows.Forms.Button btnLoad;
        private System.ComponentModel.BackgroundWorker bkSending;
        private System.Windows.Forms.Button btnChangeLang;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox chkHide;
	}
}

