namespace CryptoTest
{
	partial class FormCrypto
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
			this.btnEncryt = new System.Windows.Forms.Button();
			this.textContent = new System.Windows.Forms.TextBox();
			this.btnDecrypt = new System.Windows.Forms.Button();
			this.btnInfo = new System.Windows.Forms.Button();
			this.textItem = new System.Windows.Forms.TextBox();
			this.tbHexData = new System.Windows.Forms.TextBox();
			this.tbCipher = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// btnEncryt
			// 
			this.btnEncryt.Location = new System.Drawing.Point(821, 15);
			this.btnEncryt.Margin = new System.Windows.Forms.Padding(4);
			this.btnEncryt.Name = "btnEncryt";
			this.btnEncryt.Size = new System.Drawing.Size(100, 31);
			this.btnEncryt.TabIndex = 0;
			this.btnEncryt.Text = "Encrypt";
			this.btnEncryt.UseVisualStyleBackColor = true;
			this.btnEncryt.Click += new System.EventHandler(this.btnEncryt_Click);
			// 
			// textContent
			// 
			this.textContent.Location = new System.Drawing.Point(17, 17);
			this.textContent.Margin = new System.Windows.Forms.Padding(4);
			this.textContent.Multiline = true;
			this.textContent.Name = "textContent";
			this.textContent.Size = new System.Drawing.Size(742, 200);
			this.textContent.TabIndex = 1;
			// 
			// btnDecrypt
			// 
			this.btnDecrypt.Location = new System.Drawing.Point(820, 55);
			this.btnDecrypt.Margin = new System.Windows.Forms.Padding(4);
			this.btnDecrypt.Name = "btnDecrypt";
			this.btnDecrypt.Size = new System.Drawing.Size(100, 31);
			this.btnDecrypt.TabIndex = 2;
			this.btnDecrypt.Text = "Decrypt";
			this.btnDecrypt.UseVisualStyleBackColor = true;
			this.btnDecrypt.Click += new System.EventHandler(this.btnDecrypt_Click);
			// 
			// btnInfo
			// 
			this.btnInfo.Location = new System.Drawing.Point(820, 93);
			this.btnInfo.Margin = new System.Windows.Forms.Padding(4);
			this.btnInfo.Name = "btnInfo";
			this.btnInfo.Size = new System.Drawing.Size(100, 31);
			this.btnInfo.TabIndex = 3;
			this.btnInfo.Text = "Info";
			this.btnInfo.UseVisualStyleBackColor = true;
			this.btnInfo.Click += new System.EventHandler(this.btnInfo_Click);
			// 
			// textItem
			// 
			this.textItem.AcceptsReturn = true;
			this.textItem.Location = new System.Drawing.Point(767, 132);
			this.textItem.Margin = new System.Windows.Forms.Padding(4);
			this.textItem.Multiline = true;
			this.textItem.Name = "textItem";
			this.textItem.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textItem.Size = new System.Drawing.Size(201, 481);
			this.textItem.TabIndex = 4;
			// 
			// tbHexData
			// 
			this.tbHexData.Location = new System.Drawing.Point(17, 224);
			this.tbHexData.Multiline = true;
			this.tbHexData.Name = "tbHexData";
			this.tbHexData.Size = new System.Drawing.Size(742, 200);
			this.tbHexData.TabIndex = 5;
			// 
			// tbCipher
			// 
			this.tbCipher.Location = new System.Drawing.Point(17, 430);
			this.tbCipher.Multiline = true;
			this.tbCipher.Name = "tbCipher";
			this.tbCipher.Size = new System.Drawing.Size(742, 183);
			this.tbCipher.TabIndex = 6;
			// 
			// FormCrypto
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(985, 631);
			this.Controls.Add(this.tbCipher);
			this.Controls.Add(this.tbHexData);
			this.Controls.Add(this.textItem);
			this.Controls.Add(this.btnInfo);
			this.Controls.Add(this.btnDecrypt);
			this.Controls.Add(this.textContent);
			this.Controls.Add(this.btnEncryt);
			this.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "FormCrypto";
			this.Text = "Crypto Test";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnEncryt;
		private System.Windows.Forms.TextBox textContent;
		private System.Windows.Forms.Button btnDecrypt;
		private System.Windows.Forms.Button btnInfo;
		private System.Windows.Forms.TextBox textItem;
		private System.Windows.Forms.TextBox tbHexData;
		private System.Windows.Forms.TextBox tbCipher;
	}
}

