namespace ComTest
{
	partial class ComTestForm
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
			this.labelFunc = new System.Windows.Forms.Label();
			this.cbFunction = new System.Windows.Forms.ComboBox();
			this.btnInvoke = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.tbModule = new System.Windows.Forms.TextBox();
			this.btnLoad = new System.Windows.Forms.Button();
			this.lbParam = new System.Windows.Forms.Label();
			this.tbRet = new System.Windows.Forms.TextBox();
			this.lblRet = new System.Windows.Forms.Label();
			this.tbParams = new System.Windows.Forms.TextBox();
			this.lblParams = new System.Windows.Forms.Label();
			this.tbClass = new System.Windows.Forms.TextBox();
			this.lbName = new System.Windows.Forms.Label();
			this.chkAnsi = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// labelFunc
			// 
			this.labelFunc.AutoSize = true;
			this.labelFunc.Location = new System.Drawing.Point(12, 55);
			this.labelFunc.Name = "labelFunc";
			this.labelFunc.Size = new System.Drawing.Size(69, 19);
			this.labelFunc.TabIndex = 0;
			this.labelFunc.Text = "Function";
			// 
			// cbFunction
			// 
			this.cbFunction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbFunction.FormattingEnabled = true;
			this.cbFunction.Location = new System.Drawing.Point(87, 52);
			this.cbFunction.Name = "cbFunction";
			this.cbFunction.Size = new System.Drawing.Size(612, 27);
			this.cbFunction.Sorted = true;
			this.cbFunction.TabIndex = 1;
			this.cbFunction.SelectedIndexChanged += new System.EventHandler(this.cbFunction_SelectedIndexChanged);
			// 
			// btnInvoke
			// 
			this.btnInvoke.Enabled = false;
			this.btnInvoke.Location = new System.Drawing.Point(705, 52);
			this.btnInvoke.Name = "btnInvoke";
			this.btnInvoke.Size = new System.Drawing.Size(75, 28);
			this.btnInvoke.TabIndex = 2;
			this.btnInvoke.Text = "Invoke";
			this.btnInvoke.UseVisualStyleBackColor = true;
			this.btnInvoke.Click += new System.EventHandler(this.btnInvoke_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 15);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(52, 19);
			this.label1.TabIndex = 3;
			this.label1.Text = "Lib.dll";
			// 
			// tbModule
			// 
			this.tbModule.Location = new System.Drawing.Point(87, 12);
			this.tbModule.Name = "tbModule";
			this.tbModule.Size = new System.Drawing.Size(240, 27);
			this.tbModule.TabIndex = 4;
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(705, 11);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.Size = new System.Drawing.Size(75, 28);
			this.btnLoad.TabIndex = 5;
			this.btnLoad.Text = "Load";
			this.btnLoad.UseVisualStyleBackColor = true;
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// lbParam
			// 
			this.lbParam.AllowDrop = true;
			this.lbParam.AutoSize = true;
			this.lbParam.Location = new System.Drawing.Point(83, 86);
			this.lbParam.Name = "lbParam";
			this.lbParam.Size = new System.Drawing.Size(61, 19);
			this.lbParam.TabIndex = 17;
			this.lbParam.Text = "Params";
			// 
			// tbRet
			// 
			this.tbRet.Location = new System.Drawing.Point(87, 251);
			this.tbRet.Multiline = true;
			this.tbRet.Name = "tbRet";
			this.tbRet.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.tbRet.Size = new System.Drawing.Size(693, 140);
			this.tbRet.TabIndex = 21;
			// 
			// lblRet
			// 
			this.lblRet.AutoSize = true;
			this.lblRet.Location = new System.Drawing.Point(16, 304);
			this.lblRet.Name = "lblRet";
			this.lblRet.Size = new System.Drawing.Size(56, 19);
			this.lblRet.TabIndex = 20;
			this.lblRet.Text = "Return";
			// 
			// tbParams
			// 
			this.tbParams.Location = new System.Drawing.Point(87, 114);
			this.tbParams.Multiline = true;
			this.tbParams.Name = "tbParams";
			this.tbParams.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.tbParams.Size = new System.Drawing.Size(693, 131);
			this.tbParams.TabIndex = 19;
			// 
			// lblParams
			// 
			this.lblParams.AutoSize = true;
			this.lblParams.Location = new System.Drawing.Point(11, 159);
			this.lblParams.Name = "lblParams";
			this.lblParams.Size = new System.Drawing.Size(61, 19);
			this.lblParams.TabIndex = 18;
			this.lblParams.Text = "Params";
			// 
			// tbClass
			// 
			this.tbClass.Location = new System.Drawing.Point(485, 12);
			this.tbClass.Name = "tbClass";
			this.tbClass.Size = new System.Drawing.Size(214, 27);
			this.tbClass.TabIndex = 22;
			// 
			// lbName
			// 
			this.lbName.AutoSize = true;
			this.lbName.Location = new System.Drawing.Point(349, 15);
			this.lbName.Name = "lbName";
			this.lbName.Size = new System.Drawing.Size(130, 19);
			this.lbName.TabIndex = 23;
			this.lbName.Text = "Namespace.Class";
			// 
			// chkAnsi
			// 
			this.chkAnsi.AutoSize = true;
			this.chkAnsi.Location = new System.Drawing.Point(16, 85);
			this.chkAnsi.Name = "chkAnsi";
			this.chkAnsi.Size = new System.Drawing.Size(59, 23);
			this.chkAnsi.TabIndex = 24;
			this.chkAnsi.Text = "Ansi";
			this.chkAnsi.UseVisualStyleBackColor = true;
			// 
			// ComTestForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 19F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(792, 403);
			this.Controls.Add(this.chkAnsi);
			this.Controls.Add(this.lbName);
			this.Controls.Add(this.tbClass);
			this.Controls.Add(this.tbRet);
			this.Controls.Add(this.lblRet);
			this.Controls.Add(this.tbParams);
			this.Controls.Add(this.lblParams);
			this.Controls.Add(this.lbParam);
			this.Controls.Add(this.btnLoad);
			this.Controls.Add(this.tbModule);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnInvoke);
			this.Controls.Add(this.cbFunction);
			this.Controls.Add(this.labelFunc);
			this.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.Name = "ComTestForm";
			this.Text = "Com Interface Test";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label labelFunc;
		private System.Windows.Forms.ComboBox cbFunction;
		private System.Windows.Forms.Button btnInvoke;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox tbModule;
		private System.Windows.Forms.Button btnLoad;
		private System.Windows.Forms.Label lbParam;
		private System.Windows.Forms.TextBox tbRet;
		private System.Windows.Forms.Label lblRet;
		private System.Windows.Forms.TextBox tbParams;
		private System.Windows.Forms.Label lblParams;
		private System.Windows.Forms.TextBox tbClass;
		private System.Windows.Forms.Label lbName;
		private System.Windows.Forms.CheckBox chkAnsi;
	}
}

