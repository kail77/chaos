using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.IO;

namespace CryptoTest
{
	public partial class FormCrypto : Form
	{
		private SymmetricAlgorithm mobjCryptoService;
		public FormCrypto()
		{
			InitializeComponent();
			mobjCryptoService = new RijndaelManaged(); // AES
			mobjCryptoService.KeySize = 32 * 8;
			mobjCryptoService.BlockSize = 16 * 8;
			mobjCryptoService.Mode = CipherMode.CBC;
			mobjCryptoService.Padding = PaddingMode.PKCS7;
		}

		/// <summary>获得密钥</summary>
		private byte[] GetLegalKey()
		{
			string sTemp = "LM0017Guz(%&hj7x89H$yuBI0456Ftma";//T5&fvHUFCy76*h%(HilJ$lhj!y6&(*jkP87jH7";
			mobjCryptoService.GenerateKey();
			byte[] bytTemp = mobjCryptoService.Key;
			int KeyLength = bytTemp.Length; //32
			if (sTemp.Length > KeyLength)
				sTemp = sTemp.Substring(0, KeyLength);
			else if (sTemp.Length < KeyLength)
				sTemp = sTemp.PadRight(KeyLength, ' ');
			return ASCIIEncoding.ASCII.GetBytes(sTemp);
		}
		/// <summary>获得初始向量IV</summary>
		private byte[] GetLegalIV()
		{
			string sTemp = "LM0017E4ghj*Ghg7";//!rNIfb&95GUY86GfghUb#er57HBh(u%g6HJ($jhWk7&!hg4ui%$hjk";
			mobjCryptoService.GenerateIV();
			byte[] bytTemp = mobjCryptoService.IV;
			int IVLength = bytTemp.Length; //16
			if (sTemp.Length > IVLength)
				sTemp = sTemp.Substring(0, IVLength);
			else if (sTemp.Length < IVLength)
				sTemp = sTemp.PadRight(IVLength, ' ');
			return ASCIIEncoding.ASCII.GetBytes(sTemp);
		}
		string ByteArrayToString(byte[] arBytes)
		{
			string sOut = null;
			foreach (byte b in arBytes)
			{
				sOut += string.Format("{0:x2} ", b);
			}
			return sOut;
		}
		private void btnEncryt_Click(object sender, EventArgs e)
		{
			byte[] bytIn = UTF8Encoding.UTF8.GetBytes(textContent.Text);
			MemoryStream ms = new MemoryStream();
			mobjCryptoService.Key = GetLegalKey();
			mobjCryptoService.IV = GetLegalIV();
			ICryptoTransform encrypto = mobjCryptoService.CreateEncryptor();
			CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Write);
			cs.Write(bytIn, 0, bytIn.Length);
			cs.FlushFinalBlock();
			ms.Close();
			byte[] bytOut = ms.ToArray();
			//ms = null;
			//cs = null;
			tbHexData.Text = ByteArrayToString(bytOut);
			tbCipher.Text = Convert.ToBase64String(bytOut);
		}

		private void btnDecrypt_Click(object sender, EventArgs e)
		{
			string sRet = "";
			byte[] bytIn = Convert.FromBase64String(tbCipher.Text);
			tbHexData.Text = ByteArrayToString(bytIn);
			MemoryStream ms = new MemoryStream(bytIn, 0, bytIn.Length);
			mobjCryptoService.Key = GetLegalKey();
			mobjCryptoService.IV = GetLegalIV();
			ICryptoTransform encrypto = mobjCryptoService.CreateDecryptor();
			CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Read);
			StreamReader sr = new StreamReader(cs);
			sRet = sr.ReadToEnd();
			//ms = null;
			//cs = null;
			//sr = null;
			textContent.Text = sRet;
		}

		private void btnInfo_Click(object sender, EventArgs e)
		{
			string[] strItem = { "name", "authlang", "authver", "authvertype", "printers", "sysid", "users", 
			"dbtype", "chkauthority", "chkmanual", "usecard", "viewcontent", "netbarmode", "mfp", "updatever", 
			"outdate", "financeoutdate", "usbdogsn", "exdays", "authoritystart", "printervendor", "memo", 
			"printaudit", "printbilling", "auditbycard", "printright", "printbilling2", "userquota", 
			"statistics", "printaudit2", "secret", "watermark", "barrecycle", "keyword", "copybilling", 
			"copyaudit", "copyrecycle", "copycontent", "copyright", "copyters", "printersofsmartnet", 
			"copystatistics", "documentflow", "cdwriters", "recordright", "recordusecard", "recordbyadmin", 
			"recordlogs", "recordstatistics", "recordaudit", "recordsecret", "recordbar", "recordencrypt", 
			"recordsavefile", "cdflow", "cdclose", "roamingprint", "smb", "ex_doc_import", "ex_doc_transfer", 
			"barcode_gen", "mobile_print", "domain_sync", "copy_with_card" };
			string[] arstrValues = textContent.Text.Split(',');
			if (arstrValues.Length < 10)
				return;
			string strResult = null;
			for (int i = 0; i < arstrValues.Length; i++)
			{
				if (i < strItem.Length)
					strResult += strItem[i] + " - ";
				strResult += arstrValues[i] + "\r\n";
			}
			textItem.Text = strResult;
		}
	}
}
