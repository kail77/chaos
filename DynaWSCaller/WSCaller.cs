using System;
using System.Collections.Generic;
using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.Linq;
//using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Net;
using System.Diagnostics;
using System.Reflection;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Web.Services;
using System.Web.Services.Description;
using System.Web.Services.Protocols;
using System.Xml.Serialization;
using System.Xml;

namespace DynaWSCaller
{
	public partial class WSCaller : Form
	{
		private Type _asmType;
		private object _objClient;
		private ParameterInfo[] _paramInfos;
		private string _strServiceName;
		public WSCaller()
		{
			InitializeComponent();
		}

		private void WSCaller_Load(object sender, EventArgs e)
		{
			XmlDocument xmlDoc = new XmlDocument();
			try
			{
				xmlDoc.Load("WSCaller.xml");
				XmlNode node = xmlDoc.SelectSingleNode("Config/Service");
				textWsdl.Text = node.Attributes.GetNamedItem("wsdl").Value;
				textAddress.Text = node.Attributes.GetNamedItem("address").Value;
				cbFunction.Text = node.Attributes.GetNamedItem("function").Value;
				textParams.Text = node.Attributes.GetNamedItem("params").Value;
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
				//return;
			}
		}

		private void btnLoad_Click(object sender, EventArgs e)
		{
			// 1. 使用 WebClient 下载 WSDL 信息。
			WebClient web = new WebClient();
			Stream stream= web.OpenRead(textWsdl.Text); //wsdl url

			// 2. 创建和格式化 WSDL 文档。
			ServiceDescription description;
			try
			{
				description = ServiceDescription.Read(stream);
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
				return;
			}
			_strServiceName = description.Services[0].Name;
			lblServiceName.Text = _strServiceName;

			// 3. 创建客户端代理代理类。
			ServiceDescriptionImporter importer = new ServiceDescriptionImporter();

			importer.ProtocolName = "Soap"; // 指定访问协议。
			importer.Style = ServiceDescriptionImportStyle.Client; // 生成客户端代理。
			importer.CodeGenerationOptions = CodeGenerationOptions.GenerateProperties | CodeGenerationOptions.GenerateNewAsync;

			importer.AddServiceDescription(description, null, null); // 添加 WSDL 文档。

			// 4. 使用 CodeDom 编译客户端代理类。
			CodeNamespace nmspace = new CodeNamespace(); // 为代理类添加命名空间，缺省为全局空间。
			CodeCompileUnit unit = new CodeCompileUnit();
			unit.Namespaces.Add(nmspace);

			ServiceDescriptionImportWarnings warning = importer.Import(nmspace, unit);
			CodeDomProvider provider = CodeDomProvider.CreateProvider("CSharp");

			CompilerParameters parameter = new CompilerParameters();
			parameter.GenerateExecutable = false;
			if (chkSave.Checked)
				parameter.OutputAssembly = _strServiceName + ".dll";// 保存文件，后面直接调用
			else
				parameter.GenerateInMemory = true;
			parameter.ReferencedAssemblies.Add("System.dll");
			parameter.ReferencedAssemblies.Add("System.XML.dll");
			parameter.ReferencedAssemblies.Add("System.Web.Services.dll");
			parameter.ReferencedAssemblies.Add("System.Data.dll");

			CompilerResults result = provider.CompileAssemblyFromDom(parameter, unit);
			Assembly asmFuncs;
			if (result.Errors.HasErrors)
			{
				MessageBox.Show("load ws error");
				return;
			}
			else
			{
				btnInvoke.Enabled = true;
				asmFuncs = result.CompiledAssembly;
			}
			//Assembly asmFuncs = Assembly.LoadFrom(_strServiceName + ".dll"); // 调用前面保存的文件
			// 如果在前面为代理类添加了命名空间，此处需要将命名空间添加到类型前面。
			_asmType = asmFuncs.GetType(_strServiceName);
			if (_asmType == null)
			{
				MessageBox.Show("err service/namespace");
				return;
			}
			_objClient = Activator.CreateInstance(_asmType);
			MethodInfo[] arMethods = _asmType.GetMethods();
			foreach (MethodInfo m in arMethods)
			{
				//if (m.Name == "CancelAsync")
				//	break;
				if (m.Name.EndsWith("Async") || m.Name.EndsWith("Completed"))
					continue;
				cbFunction.Items.Add(m.Name);
			}
			cbFunction.SelectedIndex = 0;
			// set service address
			MethodInfo method = _asmType.GetMethod("get_Url");
			object oret = method.Invoke(_objClient, null);
			if (textAddress.Text != oret.ToString())
			{
				method = _asmType.GetMethod("set_Url");
				object[] objs = { textAddress.Text };
				method.Invoke(_objClient, objs);
			}
		}

		private void cbFunction_SelectedIndexChanged(object sender, EventArgs e)
		{
			MethodInfo method = _asmType.GetMethod(cbFunction.Text);
			_paramInfos = method.GetParameters();
			string strParam = "(";
			foreach (ParameterInfo p in _paramInfos)
			{
				strParam += p.ParameterType.Name + " ";
				strParam += p.Name + ",";
			}
			strParam.TrimEnd(',');
			strParam += ") : ";
			strParam += method.ReturnType.Name + " ";
			strParam += method.ReturnParameter.Name; // null?
			lblParam.Text = strParam;
		}

		private void btnInvoke_Click(object sender, EventArgs e)
		{
			MethodInfo method = _asmType.GetMethod(cbFunction.Text);
			object[] arrObj = null;
			if (_paramInfos.Length > 0)
			{
				string[] strParams = textParams.Text.Split(',');
				if (strParams.Length != _paramInfos.Length)
				{
					MessageBox.Show("params count should be:" + _paramInfos.Length);
					return;
				}
				arrObj = new object[strParams.Length];
				for (int i = 0; i < strParams.Length; i++)
				{
					if (_paramInfos[i].ParameterType.Name == "Int32")
						arrObj[i] = Convert.ToInt32(strParams[i]);
					else if (_paramInfos[i].ParameterType.Name == "Int64")
						arrObj[i] = Convert.ToInt64(strParams[i]);
					else // string
						arrObj[i] = strParams[i];
				}
			}
			object oret = null;
			try
			{
				oret = method.Invoke(_objClient, arrObj);
			}
			catch (Exception ex)
			{
				//MessageBox.Show(ex.Message);
				textRet.Text = ex.Message;
				return;
			}
			if (oret == null)
				textRet.Text = null;
			//else if (oret.GetType().Name == "Data")
			else
				textRet.Text = oret.ToString();
		}

		private void WSCaller_FormClosed(object sender, FormClosedEventArgs e)
		{

		}
	}
}
