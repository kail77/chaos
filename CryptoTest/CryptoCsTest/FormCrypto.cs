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
		public FormCrypto()
		{
			InitializeComponent();
			cbAlg.SelectedIndex = 0; // AES
		}

		/// <summary>获得密钥</summary>
		private byte[] GetLegalKey(SymmetricAlgorithm symAlg)
		{
			string sTemp = "LM0017Guz(%&hj7x89H$yuBI0456Ftma";//T5&fvHUFCy76*h%(HilJ$lhj!y6&(*jkP87jH7";
			symAlg.GenerateKey();
			byte[] bytTemp = symAlg.Key;
			int KeyLength = bytTemp.Length; //32
			if (sTemp.Length > KeyLength)
				sTemp = sTemp.Substring(0, KeyLength);
			else if (sTemp.Length < KeyLength)
				sTemp = sTemp.PadRight(KeyLength, ' ');
			return ASCIIEncoding.ASCII.GetBytes(sTemp);
		}
		/// <summary>获得初始向量IV</summary>
		private byte[] GetLegalIV(SymmetricAlgorithm symAlg)
		{
			string sTemp = "LM0017E4ghj*Ghg7";//!rNIfb&95GUY86GfghUb#er57HBh(u%g6HJ($jhWk7&!hg4ui%$hjk";
			symAlg.GenerateIV();
			byte[] bytTemp = symAlg.IV;
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
			byte[] bytOut = null;
			if (cbAlg.SelectedIndex == 0) // AES
			{
				MemoryStream ms = new MemoryStream();
				SymmetricAlgorithm symAlg = new RijndaelManaged(); // AES
				symAlg.KeySize = 32 * 8;
				symAlg.BlockSize = 16 * 8;
				symAlg.Mode = CipherMode.CBC;
				symAlg.Padding = PaddingMode.PKCS7;

				symAlg.Key = GetLegalKey(symAlg);
				symAlg.IV = GetLegalIV(symAlg);
				ICryptoTransform encrypto = symAlg.CreateEncryptor();
				CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Write);
				cs.Write(bytIn, 0, bytIn.Length);
				cs.FlushFinalBlock();
				ms.Close();
				bytOut = ms.ToArray();
			}
			else if (cbAlg.SelectedIndex == 1) // RSA
			{
				//声明一个RSA算法的实例，指定了密钥长度为1024位，会自动生成密钥信息。
				RSACryptoServiceProvider rsaProvider = new RSACryptoServiceProvider(1024);
				tbKey1.Text = rsaProvider.ToXmlString(false);//export pub key only
				tbKey2.Text = rsaProvider.ToXmlString(true);//export pub+prv keys

				//rsaProvider.FromXmlString(PublicKey);	//将公钥导入到RSA对象中，准备加密；
				//第二个参数用来选择Padding的格式
				bytOut = rsaProvider.Encrypt(bytIn, false);	//对数据data进行加密，并返回加密结果；
			}
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
			if (cbAlg.SelectedIndex == 0) // AES
			{
				MemoryStream ms = new MemoryStream(bytIn, 0, bytIn.Length);
				SymmetricAlgorithm symAlg = new RijndaelManaged();
				symAlg.KeySize = 32 * 8;
				symAlg.BlockSize = 16 * 8;
				symAlg.Mode = CipherMode.CBC;
				symAlg.Padding = PaddingMode.PKCS7;

				symAlg.Key = GetLegalKey(symAlg);
				symAlg.IV = GetLegalIV(symAlg);

				ICryptoTransform encrypto = symAlg.CreateDecryptor();
				CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Read);
				StreamReader sr = new StreamReader(cs);
				sRet = sr.ReadToEnd();
			}
			else if (cbAlg.SelectedIndex == 1) // RSA
			{
				//声明一个RSA算法的实例，指定了密钥长度为1024位，会自动生成密钥信息。
				RSACryptoServiceProvider rsaProvider = new RSACryptoServiceProvider(1024);
				rsaProvider.FromXmlString(tbKey2.Text);	//将私钥导入到RSA对象
				byte[] bytOut = rsaProvider.Decrypt(bytIn, false);	//对数据data解密，并返回加密结果；
				sRet = Encoding.UTF8.GetString(bytOut);
			}
			textContent.Text = sRet;
		}

		private void btnSign_Click(object sender, EventArgs e)
		{
			cbAlg.SelectedIndex = 1;
			byte[] bytIn = UTF8Encoding.UTF8.GetBytes(textContent.Text);
			RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(1024);
			tbKey1.Text = rsa.ToXmlString(false);//将RSA算法的公钥导出
			tbKey2.Text = rsa.ToXmlString(true);//将RSA算法的私钥导出
			rsa.FromXmlString(tbKey2.Text);	//导入私钥，准备签名
			//将数据使用MD5进行消息摘要，然后对摘要进行签名并返回签名数据
			byte[] bytOut = rsa.SignData(bytIn, "MD5");
			tbHexData.Text = ByteArrayToString(bytOut);
			tbCipher.Text = Convert.ToBase64String(bytOut);
		}

		private void btnVerify_Click(object sender, EventArgs e)
		{
			byte[] bytIn = Convert.FromBase64String(tbCipher.Text);
			tbHexData.Text = ByteArrayToString(bytIn);

			RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(1024);
			rsa.FromXmlString(tbKey1.Text);	////导入公钥，准备验证签名
			byte[] srcData = UTF8Encoding.UTF8.GetBytes(textContent.Text);
			bool bVerify = rsa.VerifyData(srcData, "MD5", bytIn);
			MessageBox.Show("Verify " + bVerify);
		}

		private void cbAlg_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (cbAlg.SelectedIndex == 0) // AES
			{
				labelKey1.Text = "Key pass";
				labelKey2.Text = "Key IV";
			}
			else if (cbAlg.SelectedIndex == 1) // RSA
			{
				labelKey1.Text = "Pub Key";
				labelKey2.Text = "Prv Key";
			}
		}

	}
}
