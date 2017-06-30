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
			this.tbHexData = new System.Windows.Forms.TextBox();
			this.tbCipher = new System.Windows.Forms.TextBox();
			this.lbPlain = new System.Windows.Forms.Label();
			this.lbHexData = new System.Windows.Forms.Label();
			this.lbCipher = new System.Windows.Forms.Label();
			this.labelAlg = new System.Windows.Forms.Label();
			this.cbAlg = new System.Windows.Forms.ComboBox();
			this.labelKey1 = new System.Windows.Forms.Label();
			this.tbKey1 = new System.Windows.Forms.TextBox();
			this.tbKey2 = new System.Windows.Forms.TextBox();
			this.labelKey2 = new System.Windows.Forms.Label();
			this.btnSign = new System.Windows.Forms.Button();
			this.btnVerify = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnEncryt
			// 
			this.btnEncryt.Location = new System.Drawing.Point(17, 601);
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
			this.textContent.Location = new System.Drawing.Point(17, 112);
			this.textContent.Margin = new System.Windows.Forms.Padding(4);
			this.textContent.Multiline = true;
			this.textContent.Name = "textContent";
			this.textContent.Size = new System.Drawing.Size(854, 132);
			this.textContent.TabIndex = 1;
			// 
			// btnDecrypt
			// 
			this.btnDecrypt.Location = new System.Drawing.Point(157, 601);
			this.btnDecrypt.Margin = new System.Windows.Forms.Padding(4);
			this.btnDecrypt.Name = "btnDecrypt";
			this.btnDecrypt.Size = new System.Drawing.Size(100, 31);
			this.btnDecrypt.TabIndex = 2;
			this.btnDecrypt.Text = "Decrypt";
			this.btnDecrypt.UseVisualStyleBackColor = true;
			this.btnDecrypt.Click += new System.EventHandler(this.btnDecrypt_Click);
			// 
			// tbHexData
			// 
			this.tbHexData.Location = new System.Drawing.Point(17, 276);
			this.tbHexData.Multiline = true;
			this.tbHexData.Name = "tbHexData";
			this.tbHexData.Size = new System.Drawing.Size(855, 159);
			this.tbHexData.TabIndex = 5;
			// 
			// tbCipher
			// 
			this.tbCipher.Location = new System.Drawing.Point(17, 463);
			this.tbCipher.Multiline = true;
			this.tbCipher.Name = "tbCipher";
			this.tbCipher.Size = new System.Drawing.Size(854, 131);
			this.tbCipher.TabIndex = 6;
			// 
			// lbPlain
			// 
			this.lbPlain.AutoSize = true;
			this.lbPlain.Location = new System.Drawing.Point(14, 92);
			this.lbPlain.Name = "lbPlain";
			this.lbPlain.Size = new System.Drawing.Size(144, 16);
			this.lbPlain.TabIndex = 7;
			this.lbPlain.Text = "Plain Text(UTF-8)";
			// 
			// lbHexData
			// 
			this.lbHexData.AutoSize = true;
			this.lbHexData.Location = new System.Drawing.Point(14, 257);
			this.lbHexData.Name = "lbHexData";
			this.lbHexData.Size = new System.Drawing.Size(128, 16);
			this.lbHexData.TabIndex = 8;
			this.lbHexData.Text = "Cipher Hex Data";
			// 
			// lbCipher
			// 
			this.lbCipher.AutoSize = true;
			this.lbCipher.Location = new System.Drawing.Point(14, 444);
			this.lbCipher.Name = "lbCipher";
			this.lbCipher.Size = new System.Drawing.Size(160, 16);
			this.lbCipher.TabIndex = 9;
			this.lbCipher.Text = "Cipher Text(base64)";
			// 
			// labelAlg
			// 
			this.labelAlg.AutoSize = true;
			this.labelAlg.Location = new System.Drawing.Point(14, 9);
			this.labelAlg.Name = "labelAlg";
			this.labelAlg.Size = new System.Drawing.Size(80, 16);
			this.labelAlg.TabIndex = 10;
			this.labelAlg.Text = "Algorithm";
			// 
			// cbAlg
			// 
			this.cbAlg.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbAlg.FormattingEnabled = true;
			this.cbAlg.Items.AddRange(new object[] {
            "AES",
            "RSA",
            "ECC"});
			this.cbAlg.Location = new System.Drawing.Point(100, 9);
			this.cbAlg.Name = "cbAlg";
			this.cbAlg.Size = new System.Drawing.Size(121, 24);
			this.cbAlg.TabIndex = 11;
			this.cbAlg.SelectedIndexChanged += new System.EventHandler(this.cbAlg_SelectedIndexChanged);
			// 
			// labelKey1
			// 
			this.labelKey1.AutoSize = true;
			this.labelKey1.Location = new System.Drawing.Point(14, 44);
			this.labelKey1.Name = "labelKey1";
			this.labelKey1.Size = new System.Drawing.Size(40, 16);
			this.labelKey1.TabIndex = 12;
			this.labelKey1.Text = "Key1";
			// 
			// tbKey1
			// 
			this.tbKey1.Location = new System.Drawing.Point(100, 41);
			this.tbKey1.Name = "tbKey1";
			this.tbKey1.Size = new System.Drawing.Size(334, 26);
			this.tbKey1.TabIndex = 13;
			// 
			// tbKey2
			// 
			this.tbKey2.Location = new System.Drawing.Point(531, 41);
			this.tbKey2.Name = "tbKey2";
			this.tbKey2.Size = new System.Drawing.Size(340, 26);
			this.tbKey2.TabIndex = 15;
			// 
			// labelKey2
			// 
			this.labelKey2.AutoSize = true;
			this.labelKey2.Location = new System.Drawing.Point(452, 44);
			this.labelKey2.Name = "labelKey2";
			this.labelKey2.Size = new System.Drawing.Size(40, 16);
			this.labelKey2.TabIndex = 14;
			this.labelKey2.Text = "Key2";
			// 
			// btnSign
			// 
			this.btnSign.Location = new System.Drawing.Point(581, 600);
			this.btnSign.Name = "btnSign";
			this.btnSign.Size = new System.Drawing.Size(110, 32);
			this.btnSign.TabIndex = 16;
			this.btnSign.Text = "PrvKey-Sign";
			this.btnSign.UseVisualStyleBackColor = true;
			this.btnSign.Click += new System.EventHandler(this.btnSign_Click);
			// 
			// btnVerify
			// 
			this.btnVerify.Location = new System.Drawing.Point(697, 600);
			this.btnVerify.Name = "btnVerify";
			this.btnVerify.Size = new System.Drawing.Size(121, 32);
			this.btnVerify.TabIndex = 17;
			this.btnVerify.Text = "PubKey-Verify";
			this.btnVerify.UseVisualStyleBackColor = true;
			this.btnVerify.Click += new System.EventHandler(this.btnVerify_Click);
			// 
			// FormCrypto
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(884, 641);
			this.Controls.Add(this.btnVerify);
			this.Controls.Add(this.btnSign);
			this.Controls.Add(this.tbKey2);
			this.Controls.Add(this.labelKey2);
			this.Controls.Add(this.tbKey1);
			this.Controls.Add(this.labelKey1);
			this.Controls.Add(this.cbAlg);
			this.Controls.Add(this.labelAlg);
			this.Controls.Add(this.lbCipher);
			this.Controls.Add(this.lbHexData);
			this.Controls.Add(this.lbPlain);
			this.Controls.Add(this.tbCipher);
			this.Controls.Add(this.tbHexData);
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
		private System.Windows.Forms.TextBox tbHexData;
		private System.Windows.Forms.TextBox tbCipher;
		private System.Windows.Forms.Label lbPlain;
		private System.Windows.Forms.Label lbHexData;
		private System.Windows.Forms.Label lbCipher;
		private System.Windows.Forms.Label labelAlg;
		private System.Windows.Forms.ComboBox cbAlg;
		private System.Windows.Forms.Label labelKey1;
		private System.Windows.Forms.TextBox tbKey1;
		private System.Windows.Forms.TextBox tbKey2;
		private System.Windows.Forms.Label labelKey2;
		private System.Windows.Forms.Button btnSign;
		private System.Windows.Forms.Button btnVerify;
	}
}

