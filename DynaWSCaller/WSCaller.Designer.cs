namespace DynaWSCaller
{
	partial class WSCaller
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.lblWsdl = new System.Windows.Forms.Label();
			this.textWsdl = new System.Windows.Forms.TextBox();
			this.lblAddress = new System.Windows.Forms.Label();
			this.textAddress = new System.Windows.Forms.TextBox();
			this.chkSave = new System.Windows.Forms.CheckBox();
			this.btnInvoke = new System.Windows.Forms.Button();
			this.lblFunction = new System.Windows.Forms.Label();
			this.btnLoad = new System.Windows.Forms.Button();
			this.lblService = new System.Windows.Forms.Label();
			this.lblServiceName = new System.Windows.Forms.Label();
			this.lblParams = new System.Windows.Forms.Label();
			this.textParams = new System.Windows.Forms.TextBox();
			this.lblRet = new System.Windows.Forms.Label();
			this.textRet = new System.Windows.Forms.TextBox();
			this.cbFunction = new System.Windows.Forms.ComboBox();
			this.lblParam = new System.Windows.Forms.Label();
			this.chkHttpPost = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// lblWsdl
			// 
			this.lblWsdl.AutoSize = true;
			this.lblWsdl.Location = new System.Drawing.Point(13, 11);
			this.lblWsdl.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.lblWsdl.Name = "lblWsdl";
			this.lblWsdl.Size = new System.Drawing.Size(40, 16);
			this.lblWsdl.TabIndex = 0;
			this.lblWsdl.Text = "Wsdl";
			// 
			// textWsdl
			// 
			this.textWsdl.Location = new System.Drawing.Point(103, 8);
			this.textWsdl.Margin = new System.Windows.Forms.Padding(4);
			this.textWsdl.Name = "textWsdl";
			this.textWsdl.Size = new System.Drawing.Size(568, 26);
			this.textWsdl.TabIndex = 1;
			// 
			// lblAddress
			// 
			this.lblAddress.AutoSize = true;
			this.lblAddress.Location = new System.Drawing.Point(13, 45);
			this.lblAddress.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.lblAddress.Name = "lblAddress";
			this.lblAddress.Size = new System.Drawing.Size(64, 16);
			this.lblAddress.TabIndex = 2;
			this.lblAddress.Text = "Address";
			// 
			// textAddress
			// 
			this.textAddress.Location = new System.Drawing.Point(104, 42);
			this.textAddress.Margin = new System.Windows.Forms.Padding(4);
			this.textAddress.Name = "textAddress";
			this.textAddress.Size = new System.Drawing.Size(568, 26);
			this.textAddress.TabIndex = 3;
			// 
			// chkSave
			// 
			this.chkSave.AutoSize = true;
			this.chkSave.Location = new System.Drawing.Point(679, 10);
			this.chkSave.Margin = new System.Windows.Forms.Padding(4);
			this.chkSave.Name = "chkSave";
			this.chkSave.Size = new System.Drawing.Size(91, 20);
			this.chkSave.TabIndex = 4;
			this.chkSave.Text = "Save dll";
			this.chkSave.UseVisualStyleBackColor = true;
			// 
			// btnInvoke
			// 
			this.btnInvoke.Enabled = false;
			this.btnInvoke.Location = new System.Drawing.Point(679, 107);
			this.btnInvoke.Margin = new System.Windows.Forms.Padding(4);
			this.btnInvoke.Name = "btnInvoke";
			this.btnInvoke.Size = new System.Drawing.Size(100, 31);
			this.btnInvoke.TabIndex = 5;
			this.btnInvoke.Text = "Invoke";
			this.btnInvoke.UseVisualStyleBackColor = true;
			this.btnInvoke.Click += new System.EventHandler(this.btnInvoke_Click);
			// 
			// lblFunction
			// 
			this.lblFunction.AutoSize = true;
			this.lblFunction.Location = new System.Drawing.Point(13, 114);
			this.lblFunction.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.lblFunction.Name = "lblFunction";
			this.lblFunction.Size = new System.Drawing.Size(72, 16);
			this.lblFunction.TabIndex = 6;
			this.lblFunction.Text = "Function";
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(679, 38);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.Size = new System.Drawing.Size(100, 31);
			this.btnLoad.TabIndex = 8;
			this.btnLoad.Text = "Load";
			this.btnLoad.UseVisualStyleBackColor = true;
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// lblService
			// 
			this.lblService.AutoSize = true;
			this.lblService.Location = new System.Drawing.Point(13, 82);
			this.lblService.Name = "lblService";
			this.lblService.Size = new System.Drawing.Size(64, 16);
			this.lblService.TabIndex = 9;
			this.lblService.Text = "Service";
			// 
			// lblServiceName
			// 
			this.lblServiceName.AutoSize = true;
			this.lblServiceName.Location = new System.Drawing.Point(101, 82);
			this.lblServiceName.Name = "lblServiceName";
			this.lblServiceName.Size = new System.Drawing.Size(104, 16);
			this.lblServiceName.TabIndex = 10;
			this.lblServiceName.Text = "Service Name";
			// 
			// lblParams
			// 
			this.lblParams.AutoSize = true;
			this.lblParams.Location = new System.Drawing.Point(13, 195);
			this.lblParams.Name = "lblParams";
			this.lblParams.Size = new System.Drawing.Size(56, 16);
			this.lblParams.TabIndex = 11;
			this.lblParams.Text = "Params";
			// 
			// textParams
			// 
			this.textParams.Location = new System.Drawing.Point(104, 157);
			this.textParams.Multiline = true;
			this.textParams.Name = "textParams";
			this.textParams.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textParams.Size = new System.Drawing.Size(676, 131);
			this.textParams.TabIndex = 12;
			// 
			// lblRet
			// 
			this.lblRet.AutoSize = true;
			this.lblRet.Location = new System.Drawing.Point(13, 343);
			this.lblRet.Name = "lblRet";
			this.lblRet.Size = new System.Drawing.Size(56, 16);
			this.lblRet.TabIndex = 13;
			this.lblRet.Text = "Return";
			// 
			// textRet
			// 
			this.textRet.Location = new System.Drawing.Point(104, 294);
			this.textRet.Multiline = true;
			this.textRet.Name = "textRet";
			this.textRet.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textRet.Size = new System.Drawing.Size(676, 140);
			this.textRet.TabIndex = 14;
			// 
			// cbFunction
			// 
			this.cbFunction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbFunction.FormattingEnabled = true;
			this.cbFunction.Location = new System.Drawing.Point(103, 111);
			this.cbFunction.Name = "cbFunction";
			this.cbFunction.Size = new System.Drawing.Size(569, 24);
			this.cbFunction.Sorted = true;
			this.cbFunction.TabIndex = 15;
			this.cbFunction.SelectedIndexChanged += new System.EventHandler(this.cbFunction_SelectedIndexChanged);
			// 
			// lblParam
			// 
			this.lblParam.AllowDrop = true;
			this.lblParam.AutoSize = true;
			this.lblParam.Location = new System.Drawing.Point(101, 138);
			this.lblParam.Name = "lblParam";
			this.lblParam.Size = new System.Drawing.Size(56, 16);
			this.lblParam.TabIndex = 16;
			this.lblParam.Text = "Params";
			// 
			// chkHttpPost
			// 
			this.chkHttpPost.AutoSize = true;
			this.chkHttpPost.Location = new System.Drawing.Point(679, 78);
			this.chkHttpPost.Name = "chkHttpPost";
			this.chkHttpPost.Size = new System.Drawing.Size(99, 20);
			this.chkHttpPost.TabIndex = 17;
			this.chkHttpPost.Text = "Http-Post";
			this.chkHttpPost.UseVisualStyleBackColor = true;
			// 
			// WSCaller
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(792, 446);
			this.Controls.Add(this.chkHttpPost);
			this.Controls.Add(this.lblParam);
			this.Controls.Add(this.cbFunction);
			this.Controls.Add(this.textRet);
			this.Controls.Add(this.lblRet);
			this.Controls.Add(this.textParams);
			this.Controls.Add(this.lblParams);
			this.Controls.Add(this.lblServiceName);
			this.Controls.Add(this.lblService);
			this.Controls.Add(this.btnLoad);
			this.Controls.Add(this.lblFunction);
			this.Controls.Add(this.btnInvoke);
			this.Controls.Add(this.chkSave);
			this.Controls.Add(this.textAddress);
			this.Controls.Add(this.lblAddress);
			this.Controls.Add(this.textWsdl);
			this.Controls.Add(this.lblWsdl);
			this.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "WSCaller";
			this.Text = "Dynamic Webservice/C#Lib Caller";
			this.Load += new System.EventHandler(this.WSCaller_Load);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.WSCaller_FormClosed);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label lblWsdl;
		private System.Windows.Forms.TextBox textWsdl;
		private System.Windows.Forms.Label lblAddress;
		private System.Windows.Forms.TextBox textAddress;
		private System.Windows.Forms.CheckBox chkSave;
		private System.Windows.Forms.Button btnInvoke;
		private System.Windows.Forms.Label lblFunction;
		private System.Windows.Forms.Button btnLoad;
		private System.Windows.Forms.Label lblService;
		private System.Windows.Forms.Label lblServiceName;
		private System.Windows.Forms.Label lblParams;
		private System.Windows.Forms.TextBox textParams;
		private System.Windows.Forms.Label lblRet;
		private System.Windows.Forms.TextBox textRet;
		private System.Windows.Forms.ComboBox cbFunction;
		private System.Windows.Forms.Label lblParam;
		private System.Windows.Forms.CheckBox chkHttpPost;
	}
}

