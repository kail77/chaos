using System;
using System.Collections.Generic;
using System.ComponentModel;
//using System.Data;
//using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.Configuration;
using System.Text.RegularExpressions;

namespace ComTest
{
	public partial class ComTestForm : Form
	{
		private Type _asmType;
		private object _objClient;
		private ParameterInfo[] _paramInfos;
		public ComTestForm()
		{
			InitializeComponent();
			tbModule.Text = ConfigurationSettings.AppSettings["ComDll"];
			tbClass.Text = ConfigurationSettings.AppSettings["ClassName"];
		}
		/// <summary>
		/// convert unicode string to ansi, for com function which is using ansi string params
		/// </summary>
		/// <param name="sUni">(in) unicode string</param>
		/// <returns>ansi string</returns>
		private string Unicode2Ansi(string sUni)
		{
			byte[] arbAscii = Encoding.GetEncoding("GB2312").GetBytes(sUni); // 字符1字节，汉字2字节
			char[] arAnsi = new char[(arbAscii.Length + 1) / 2]; // combine 2 bytes into 1 char
			int n = 0, k = 0;
			for (int i = 0; i < arbAscii.Length; i++)
			{
				if ((i & 1) > 0)
				{
					n += arbAscii[i] << 8;
					arAnsi[k++] = Convert.ToChar(n);
				}
				else if (i == arbAscii.Length - 1)
				{
					arAnsi[k++] = Convert.ToChar(arbAscii[i]);
				}
				else
				{
					n = arbAscii[i];
				}
			}
			return new string(arAnsi);
		}

		private void btnLoad_Click(object sender, EventArgs e)
		{
			try
			{
				Assembly asmFuncs = Assembly.LoadFrom(tbModule.Text);
				if (asmFuncs == null)
				{
					MessageBox.Show("err Load Assembly");
					return;
				}
				_asmType = asmFuncs.GetType(tbClass.Text);
				if (_asmType == null)
				{
					MessageBox.Show("err Assembly.GetType");
					return;
				}
				MethodInfo[] arMethods = _asmType.GetMethods();
				foreach (MethodInfo m in arMethods)
				{
					//if (m.Name.EndsWith("Async") || m.Name.EndsWith("Completed"))
					//	continue;
					cbFunction.Items.Add(m.Name);
				}
				cbFunction.SelectedIndex = 0;
				btnInvoke.Enabled = true;
				_objClient = Activator.CreateInstance(_asmType);
				this.btnLoad.Enabled = false;
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
			}
		}

		private void cbFunction_SelectedIndexChanged(object sender, EventArgs e)
		{
			MethodInfo method = _asmType.GetMethod(cbFunction.Text);
			_paramInfos = method.GetParameters();
			string sParam = "(";
			foreach (ParameterInfo p in _paramInfos)
			{
				if (p.IsOut)
					sParam += "out ";
				sParam += p.ParameterType.Name + " ";
				sParam += p.Name + ",";
			}
			sParam.TrimEnd(',');
			sParam += ") : ";
			sParam += method.ReturnType.Name + " ";
			sParam += method.ReturnParameter.Name; // null?
			lbParam.Text = sParam;
		}

		private void btnInvoke_Click(object sender, EventArgs e)
		{
			object[] arObj = null;
			if (_paramInfos.Length > 0)
			{
				//string[] sParams = tbParams.Text.Split(new char[2] { '\r', '\n' });
				string[] sParams = Regex.Split(tbParams.Text, "\r\n");
				if (sParams.Length != _paramInfos.Length)
				{
					MessageBox.Show("params count should be:" + _paramInfos.Length);
					return;
				}
				arObj = new object[sParams.Length];
				for (int i = 0; i < sParams.Length; i++)
				{
					//if (_paramInfos[i].IsOut == true)
					//	break;
					if (_paramInfos[i].ParameterType.Name.Contains("Int32")) 
					{
						arObj[i] = Convert.ToInt32(sParams[i]);
					}
					else // string
					{
						if (chkAnsi.Checked)
							arObj[i] = Unicode2Ansi(sParams[i]);
						else
							arObj[i] = sParams[i];
					}
				}
			}
			MethodInfo method = _asmType.GetMethod(cbFunction.Text);
			object oret = null;
			try
			{
				oret = method.Invoke(_objClient, arObj);
			}
			catch (Exception ex)
			{
				//MessageBox.Show(ex.Message);
				tbRet.Text = ex.Message;
				return;
			}
			if (oret == null)
				tbRet.Text = null;
			//else if (oret.GetType().Name == "Data")
			else
				tbRet.Text = oret.ToString();
			for (int i = 0; i < _paramInfos.Length; i++)
			{
				if (_paramInfos[i].IsOut && arObj[i] != null)
				{
					tbRet.Text += "\r\n";
					tbRet.Text += arObj[i].ToString();
				}
			}
		}
	}
}
