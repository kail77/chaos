namespace ComViewer
{
	partial class ComViewerForm
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
			this.lbProgName = new System.Windows.Forms.Label();
			this.tbName = new System.Windows.Forms.TextBox();
			this.btnQuery = new System.Windows.Forms.Button();
			this.tbInfo = new System.Windows.Forms.TextBox();
			this.tbInterface = new System.Windows.Forms.TextBox();
			this.lbInterface = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// lbProgName
			// 
			this.lbProgName.AutoSize = true;
			this.lbProgName.Location = new System.Drawing.Point(13, 17);
			this.lbProgName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.lbProgName.Name = "lbProgName";
			this.lbProgName.Size = new System.Drawing.Size(50, 19);
			this.lbProgName.TabIndex = 0;
			this.lbProgName.Text = "Name";
			// 
			// tbName
			// 
			this.tbName.Location = new System.Drawing.Point(97, 14);
			this.tbName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.tbName.Name = "tbName";
			this.tbName.Size = new System.Drawing.Size(594, 27);
			this.tbName.TabIndex = 1;
			// 
			// btnQuery
			// 
			this.btnQuery.Location = new System.Drawing.Point(710, 10);
			this.btnQuery.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.btnQuery.Name = "btnQuery";
			this.btnQuery.Size = new System.Drawing.Size(112, 36);
			this.btnQuery.TabIndex = 2;
			this.btnQuery.Text = "Query";
			this.btnQuery.UseVisualStyleBackColor = true;
			this.btnQuery.Click += new System.EventHandler(this.btnQuery_Click);
			// 
			// tbInfo
			// 
			this.tbInfo.Location = new System.Drawing.Point(12, 86);
			this.tbInfo.Multiline = true;
			this.tbInfo.Name = "tbInfo";
			this.tbInfo.Size = new System.Drawing.Size(810, 386);
			this.tbInfo.TabIndex = 10;
			// 
			// tbInterface
			// 
			this.tbInterface.Location = new System.Drawing.Point(97, 51);
			this.tbInterface.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.tbInterface.Name = "tbInterface";
			this.tbInterface.Size = new System.Drawing.Size(594, 27);
			this.tbInterface.TabIndex = 12;
			// 
			// lbInterface
			// 
			this.lbInterface.AutoSize = true;
			this.lbInterface.Location = new System.Drawing.Point(13, 54);
			this.lbInterface.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.lbInterface.Name = "lbInterface";
			this.lbInterface.Size = new System.Drawing.Size(71, 19);
			this.lbInterface.TabIndex = 11;
			this.lbInterface.Text = "Interface";
			// 
			// ComViewerForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 19F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(836, 484);
			this.Controls.Add(this.tbInterface);
			this.Controls.Add(this.lbInterface);
			this.Controls.Add(this.tbInfo);
			this.Controls.Add(this.btnQuery);
			this.Controls.Add(this.tbName);
			this.Controls.Add(this.lbProgName);
			this.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
			this.Name = "ComViewerForm";
			this.Text = "ComViewer";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label lbProgName;
		private System.Windows.Forms.TextBox tbName;
		private System.Windows.Forms.Button btnQuery;
		private System.Windows.Forms.TextBox tbInfo;
		private System.Windows.Forms.TextBox tbInterface;
		private System.Windows.Forms.Label lbInterface;
	}
}

