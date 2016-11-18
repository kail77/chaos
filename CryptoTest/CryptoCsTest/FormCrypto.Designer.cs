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
			this.lbPlain = new System.Windows.Forms.Label();
			this.lbHexData = new System.Windows.Forms.Label();
			this.lbCipher = new System.Windows.Forms.Label();
			this.lbItems = new System.Windows.Forms.Label();
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
			this.textContent.Location = new System.Drawing.Point(17, 35);
			this.textContent.Margin = new System.Windows.Forms.Padding(4);
			this.textContent.Multiline = true;
			this.textContent.Name = "textContent";
			this.textContent.Size = new System.Drawing.Size(742, 182);
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
			this.textItem.Location = new System.Drawing.Point(767, 174);
			this.textItem.Margin = new System.Windows.Forms.Padding(4);
			this.textItem.Multiline = true;
			this.textItem.Name = "textItem";
			this.textItem.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textItem.Size = new System.Drawing.Size(201, 439);
			this.textItem.TabIndex = 4;
			// 
			// tbHexData
			// 
			this.tbHexData.Location = new System.Drawing.Point(17, 251);
			this.tbHexData.Multiline = true;
			this.tbHexData.Name = "tbHexData";
			this.tbHexData.Size = new System.Drawing.Size(742, 173);
			this.tbHexData.TabIndex = 5;
			// 
			// tbCipher
			// 
			this.tbCipher.Location = new System.Drawing.Point(17, 462);
			this.tbCipher.Multiline = true;
			this.tbCipher.Name = "tbCipher";
			this.tbCipher.Size = new System.Drawing.Size(742, 151);
			this.tbCipher.TabIndex = 6;
			// 
			// lbPlain
			// 
			this.lbPlain.AutoSize = true;
			this.lbPlain.Location = new System.Drawing.Point(14, 15);
			this.lbPlain.Name = "lbPlain";
			this.lbPlain.Size = new System.Drawing.Size(144, 16);
			this.lbPlain.TabIndex = 7;
			this.lbPlain.Text = "Plain Text(UTF-8)";
			// 
			// lbHexData
			// 
			this.lbHexData.AutoSize = true;
			this.lbHexData.Location = new System.Drawing.Point(14, 232);
			this.lbHexData.Name = "lbHexData";
			this.lbHexData.Size = new System.Drawing.Size(72, 16);
			this.lbHexData.TabIndex = 8;
			this.lbHexData.Text = "Hex Data";
			// 
			// lbCipher
			// 
			this.lbCipher.AutoSize = true;
			this.lbCipher.Location = new System.Drawing.Point(14, 443);
			this.lbCipher.Name = "lbCipher";
			this.lbCipher.Size = new System.Drawing.Size(160, 16);
			this.lbCipher.TabIndex = 9;
			this.lbCipher.Text = "Cipher Text(base64)";
			// 
			// lbItems
			// 
			this.lbItems.AutoSize = true;
			this.lbItems.Location = new System.Drawing.Point(818, 154);
			this.lbItems.Name = "lbItems";
			this.lbItems.Size = new System.Drawing.Size(48, 16);
			this.lbItems.TabIndex = 10;
			this.lbItems.Text = "Items";
			// 
			// FormCrypto
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(985, 631);
			this.Controls.Add(this.lbItems);
			this.Controls.Add(this.lbCipher);
			this.Controls.Add(this.lbHexData);
			this.Controls.Add(this.lbPlain);
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
		private System.Windows.Forms.Label lbPlain;
		private System.Windows.Forms.Label lbHexData;
		private System.Windows.Forms.Label lbCipher;
		private System.Windows.Forms.Label lbItems;
	}
}

