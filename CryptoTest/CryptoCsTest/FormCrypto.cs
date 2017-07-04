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
		const string _sEncKeyName = "encoder_key_name_1";
		const string _sDecKeyName = "decoder_key_name_2";
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
			else if (cbAlg.SelectedIndex == 2) // ECC
			{
				ECDiffieHellmanCng encoder, decoder; // need .net 3.5
				CngKey encKey, decKey;
				CngKeyCreationParameters creationParam = new CngKeyCreationParameters();
				creationParam.ExportPolicy = CngExportPolicies.AllowPlaintextExport; // allow export priv-key
				//creationParam.KeyUsage = CngKeyUsages.AllUsages;
				//creationParam.KeyCreationOptions = CngKeyCreationOptions.MachineKey;
				//creationParam.Provider = CngProvider.MicrosoftSoftwareKeyStorageProvider;
				//creationParam.UIPolicy = new CngUIPolicy(CngUIProtectionLevels.None);

				if (CngKey.Exists(FormCrypto._sEncKeyName))
					encKey = CngKey.Open(FormCrypto._sEncKeyName);
				else
					encKey = CngKey.Create(CngAlgorithm.ECDiffieHellmanP256, FormCrypto._sEncKeyName, creationParam);
				encoder = new ECDiffieHellmanCng(encKey);

				// create decoder:其实不应该在这里创建，而是把pubkey传过来。这里仅为了测试方便.
				if (CngKey.Exists(FormCrypto._sDecKeyName))
					decKey = CngKey.Open(FormCrypto._sDecKeyName);
				else
					decKey = CngKey.Create(CngAlgorithm.ECDiffieHellmanP256, FormCrypto._sDecKeyName, creationParam);
				// decoder should save this private key, then load later
				txPrvKey.Text = Convert.ToBase64String(decKey.Export(CngKeyBlobFormat.EccPrivateBlob)); // decode priv-key
				decoder = new ECDiffieHellmanCng(decKey);

				string sEncPrvKey = Convert.ToBase64String(encKey.Export(CngKeyBlobFormat.EccPrivateBlob)); // encoder save this priv-key
				encoder.KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash;
				decoder.KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash;
				encoder.HashAlgorithm = CngAlgorithm.Sha256;
				decoder.HashAlgorithm = CngAlgorithm.Sha256;

				this.tbKey1.Text = Convert.ToBase64String(encoder.PublicKey.ToByteArray());//encoder's pub key

				Aes aes = new AesCryptoServiceProvider();
				CngKey k = CngKey.Import(decoder.PublicKey.ToByteArray(), CngKeyBlobFormat.EccPublicBlob);
				aes.Key = encoder.DeriveKeyMaterial(k);
				this.tbKey2.Text = Convert.ToBase64String(aes.IV);
				// Encrypt text
				using (MemoryStream ciphertext = new MemoryStream())
				using (CryptoStream cs = new CryptoStream(ciphertext, aes.CreateEncryptor(), CryptoStreamMode.Write))
				{
					cs.Write(bytIn, 0, bytIn.Length);
					cs.Close();
					bytOut = ciphertext.ToArray();
				}
				encKey.Delete();
				decKey.Delete();
			}
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
			else if (cbAlg.SelectedIndex == 2) // ECC
			{
				CngKey decKey = CngKey.Import(Convert.FromBase64String(txPrvKey.Text), CngKeyBlobFormat.EccPrivateBlob);
				ECDiffieHellmanCng decoder = new ECDiffieHellmanCng(decKey);
				decoder.KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash;
				decoder.HashAlgorithm = CngAlgorithm.Sha256;

				Aes aes = new AesCryptoServiceProvider();
				aes.IV = Convert.FromBase64String(this.tbKey2.Text);
				CngKey k = CngKey.Import(Convert.FromBase64String(this.tbKey1.Text), CngKeyBlobFormat.EccPublicBlob);
				aes.Key = decoder.DeriveKeyMaterial(k);

				MemoryStream plaintext = new MemoryStream();
				using (CryptoStream cs = new CryptoStream(plaintext, aes.CreateDecryptor(), CryptoStreamMode.Write))
				{
					cs.Write(bytIn, 0, bytIn.Length);
					cs.Close();
					sRet = Encoding.UTF8.GetString(plaintext.ToArray());
				}
				decKey.Delete();
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
			else if (cbAlg.SelectedIndex == 2) // ECC
			{
				labelKey1.Text = "Pub Key";
				labelKey2.Text = "IV";
			}
		}

	}
}
