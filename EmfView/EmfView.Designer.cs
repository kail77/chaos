namespace EmfView
{
	partial class formEmfView
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
			this.btnOpen = new System.Windows.Forms.Button();
			this.picBox = new System.Windows.Forms.PictureBox();
			this.btnZoomIn = new System.Windows.Forms.Button();
			this.btnZoomOut = new System.Windows.Forms.Button();
			this.btnPrev = new System.Windows.Forms.Button();
			this.txPage = new System.Windows.Forms.TextBox();
			this.btnGo = new System.Windows.Forms.Button();
			this.btnNext = new System.Windows.Forms.Button();
			this.txInfo = new System.Windows.Forms.TextBox();
			this.chkTempFont = new System.Windows.Forms.CheckBox();
			((System.ComponentModel.ISupportInitialize)(this.picBox)).BeginInit();
			this.SuspendLayout();
			// 
			// btnOpen
			// 
			this.btnOpen.Location = new System.Drawing.Point(12, 12);
			this.btnOpen.Name = "btnOpen";
			this.btnOpen.Size = new System.Drawing.Size(75, 27);
			this.btnOpen.TabIndex = 0;
			this.btnOpen.Text = "Open";
			this.btnOpen.UseVisualStyleBackColor = true;
			this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
			// 
			// picBox
			// 
			this.picBox.BackColor = System.Drawing.Color.White;
			this.picBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.picBox.Location = new System.Drawing.Point(12, 47);
			this.picBox.Name = "picBox";
			this.picBox.Size = new System.Drawing.Size(738, 541);
			this.picBox.TabIndex = 2;
			this.picBox.TabStop = false;
			this.picBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picBox_MouseDown);
			this.picBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.picBox_MouseUp);
			// 
			// btnZoomIn
			// 
			this.btnZoomIn.Location = new System.Drawing.Point(515, 12);
			this.btnZoomIn.Name = "btnZoomIn";
			this.btnZoomIn.Size = new System.Drawing.Size(75, 27);
			this.btnZoomIn.TabIndex = 3;
			this.btnZoomIn.Text = "ZoomIn";
			this.btnZoomIn.UseVisualStyleBackColor = true;
			this.btnZoomIn.Click += new System.EventHandler(this.btnZoomIn_Click);
			// 
			// btnZoomOut
			// 
			this.btnZoomOut.Location = new System.Drawing.Point(610, 12);
			this.btnZoomOut.Name = "btnZoomOut";
			this.btnZoomOut.Size = new System.Drawing.Size(75, 27);
			this.btnZoomOut.TabIndex = 4;
			this.btnZoomOut.Text = "ZoomOut";
			this.btnZoomOut.UseVisualStyleBackColor = true;
			this.btnZoomOut.Click += new System.EventHandler(this.btnZoomOut_Click);
			// 
			// btnPrev
			// 
			this.btnPrev.Location = new System.Drawing.Point(823, 11);
			this.btnPrev.Name = "btnPrev";
			this.btnPrev.Size = new System.Drawing.Size(36, 27);
			this.btnPrev.TabIndex = 5;
			this.btnPrev.Text = "<";
			this.btnPrev.UseVisualStyleBackColor = true;
			this.btnPrev.Click += new System.EventHandler(this.btnPrev_Click);
			// 
			// txPage
			// 
			this.txPage.Location = new System.Drawing.Point(865, 11);
			this.txPage.Name = "txPage";
			this.txPage.Size = new System.Drawing.Size(31, 26);
			this.txPage.TabIndex = 6;
			// 
			// btnGo
			// 
			this.btnGo.Location = new System.Drawing.Point(902, 11);
			this.btnGo.Name = "btnGo";
			this.btnGo.Size = new System.Drawing.Size(36, 27);
			this.btnGo.TabIndex = 7;
			this.btnGo.Text = "go";
			this.btnGo.UseVisualStyleBackColor = true;
			this.btnGo.Click += new System.EventHandler(this.btnGo_Click);
			// 
			// btnNext
			// 
			this.btnNext.Location = new System.Drawing.Point(944, 11);
			this.btnNext.Name = "btnNext";
			this.btnNext.Size = new System.Drawing.Size(36, 27);
			this.btnNext.TabIndex = 8;
			this.btnNext.Text = ">";
			this.btnNext.UseVisualStyleBackColor = true;
			this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
			// 
			// txInfo
			// 
			this.txInfo.Location = new System.Drawing.Point(756, 47);
			this.txInfo.Multiline = true;
			this.txInfo.Name = "txInfo";
			this.txInfo.Size = new System.Drawing.Size(224, 541);
			this.txInfo.TabIndex = 9;
			// 
			// chkTempFont
			// 
			this.chkTempFont.AutoSize = true;
			this.chkTempFont.Location = new System.Drawing.Point(410, 16);
			this.chkTempFont.Name = "chkTempFont";
			this.chkTempFont.Size = new System.Drawing.Size(91, 20);
			this.chkTempFont.TabIndex = 10;
			this.chkTempFont.Text = "TempFont";
			this.chkTempFont.UseVisualStyleBackColor = true;
			// 
			// formEmfView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(992, 600);
			this.Controls.Add(this.chkTempFont);
			this.Controls.Add(this.txInfo);
			this.Controls.Add(this.btnNext);
			this.Controls.Add(this.btnGo);
			this.Controls.Add(this.txPage);
			this.Controls.Add(this.btnPrev);
			this.Controls.Add(this.btnZoomOut);
			this.Controls.Add(this.btnZoomIn);
			this.Controls.Add(this.picBox);
			this.Controls.Add(this.btnOpen);
			this.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "formEmfView";
			this.Text = "Emf Viewer";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.formEmfView_Paint);
			this.SizeChanged += new System.EventHandler(this.formEmfView_SizeChanged);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formEmfView_FormClosed);
			((System.ComponentModel.ISupportInitialize)(this.picBox)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnOpen;
		private System.Windows.Forms.PictureBox picBox;
		private System.Windows.Forms.Button btnZoomIn;
		private System.Windows.Forms.Button btnZoomOut;
		private System.Windows.Forms.Button btnPrev;
		private System.Windows.Forms.TextBox txPage;
		private System.Windows.Forms.Button btnGo;
		private System.Windows.Forms.Button btnNext;
		private System.Windows.Forms.TextBox txInfo;
		private System.Windows.Forms.CheckBox chkTempFont;
	}
}

