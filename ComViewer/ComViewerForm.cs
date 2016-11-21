using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace ComViewer
{
	public partial class ComViewerForm : Form
	{
		public ComViewerForm()
		{
			InitializeComponent();
		}

		private void btnQuery_Click(object sender, EventArgs e)
		{//AVSIFOFiles.AVSDVDAudioAttributes
			RegistryKey keyMain, keySub;
			tbInfo.Text = "";

			// HKEY_CLASSES_ROOT\AppName.ClassName: CLSID, CurVer
			keyMain = Registry.ClassesRoot.OpenSubKey(tbName.Text + "\\CLSID");
			if (keyMain == null)
			{
				//tbInfo.Text += "cannot find program " + tbName.Text;
				if (DialogResult.No == MessageBox.Show("cannot find program " + tbName.Text + ", Search all?", "Info", MessageBoxButtons.YesNo))
					return;
				bool bFound = false;
				string[] arItem = Registry.ClassesRoot.GetSubKeyNames();
				int nVer = 0;
				foreach (string sItem in arItem)
				{
					if (sItem.IndexOf(tbName.Text) >= 0)
					{
						string sVersion = sItem.Substring(sItem.LastIndexOf('.') + 1);
						bFound = Int32.TryParse(sVersion, out nVer);
						tbName.Text = sItem;
						if (bFound && nVer > 0)
							break;
					}
				}
				if (bFound)
				{
					keyMain = Registry.ClassesRoot.OpenSubKey(tbName.Text + "\\CLSID");
				}
				else
				{
					MessageBox.Show("cannot find program " + tbName.Text);
					return;
				}
			}
			string sClassID = keyMain.GetValue("").ToString(); //{XXXX-XX..}
			keyMain.Close();
			tbInfo.Text += "CLSID: " + sClassID + "\r\n";
			// Appname.ClassName
			keyMain = Registry.ClassesRoot.OpenSubKey(tbName.Text);
			tbInfo.Text += "ClassName: " + keyMain.GetValue("").ToString() + "\r\n";
			keyMain.Close();

			// HKEY_CLASSES_ROOT\CLSID\{XXXX-XX..}: InProcServer32, TypeLib
			keyMain = Registry.ClassesRoot.OpenSubKey("CLSID\\" + sClassID);
			if (keyMain == null)
			{
				tbInfo.Text += "cannot find CLSID " + sClassID;
				return;
			}
			tbInfo.Text += "InProcServer32: ";
			keySub = keyMain.OpenSubKey("InProcServer32");
			if (keySub != null)
			{
				string sFilePath = keySub.GetValue("").ToString();
				tbInfo.Text += sFilePath;
				Object oCodeBase = keySub.GetValue("CodeBase");
				if (oCodeBase != null)
				{
					sFilePath = oCodeBase.ToString();
					if (sFilePath != null)
						tbInfo.Text += "\r\nCodeBase: " + sFilePath;
				}
				keySub.Close();
			}
			tbInfo.Text += "\r\n";
			tbInfo.Text += "LocalServer32: ";
			keySub = keyMain.OpenSubKey("LocalServer32");
			if (keySub != null)
			{
				string sFilePath = keySub.GetValue("").ToString();
				keySub.Close();
				tbInfo.Text += sFilePath;
			}
			tbInfo.Text += "\r\n";

			tbInfo.Text += "AppID: ";
			keySub = keyMain.OpenSubKey("AppID");
			if (keySub != null)
			{
				string sAppID = keySub.GetValue("").ToString(); //{XXXX-XX..}
				keySub.Close();
				tbInfo.Text += sAppID;
			}
			tbInfo.Text += "\r\n";

			string sTypeLib = null, sVer = "1.0";
			tbInfo.Text += "CLSID-TypeLib: ";
			keySub = keyMain.OpenSubKey("TypeLib");
			if (keySub != null)
			{
				sTypeLib = keySub.GetValue("").ToString(); //{XXXX-XX..}
				tbInfo.Text += sTypeLib;
				keySub.Close();
			}
			tbInfo.Text += "\r\n";
			keyMain.Close();

			// HKEY_CLASSES_ROOT\Interface\{XXXX-XX..}: ProxyStubClsid32, TypeLib
			if (tbInterface.Text.Length > 0)
			{
				tbInterface.Text = tbInterface.Text.ToUpper();
				if (!tbInterface.Text.StartsWith("{"))
					tbInterface.Text = tbInterface.Text.Insert(0, "{");
				if (!tbInterface.Text.EndsWith("}"))
					tbInterface.Text += "}";

				keyMain = Registry.ClassesRoot.OpenSubKey("Interface\\" + tbInterface.Text);
				if (keyMain != null)
				{
					string sInterface = keyMain.GetValue("").ToString();
					tbInfo.Text += "Interface: " + sInterface + "\r\n";
					keySub = keyMain.OpenSubKey("TypeLib");
					if (keySub != null)
					{
						sTypeLib = keySub.GetValue("").ToString();
						tbInfo.Text += "Interface-TypeLib: " + sTypeLib + "\r\n";
						sVer = keySub.GetValue("Version").ToString();
						keySub.Close();
					}
					keySub = keyMain.OpenSubKey("ProxyStubClsid32");
					if (keySub != null)
					{
						string sStub = keySub.GetValue("").ToString();
						tbInfo.Text += "ProxyStubClsid32: " + sStub + "\r\n";
						keySub.Close();
					}
					keyMain.Close();
				}
			}
			tbInfo.Text += "Version: " + sVer + "\r\n";

			// HKEY_CLASSES_ROOT\TypeLib\{XXXX-XX..}: InProcServer32, TypeLib
			keyMain = Registry.ClassesRoot.OpenSubKey("TypeLib\\" + sTypeLib + "\\" + sVer + "\\0\\win32");
			if (keyMain != null)
			{
				string sWin32Path = keyMain.GetValue("").ToString();
				keyMain.Close();
				tbInfo.Text += "TypeLib-win32: " + sWin32Path + "\r\n";
			}
			keyMain = Registry.ClassesRoot.OpenSubKey("TypeLib\\" + sTypeLib + "\\" + sVer + "\\0\\win64");
			if (keyMain != null)
			{
				string sWin32Path = keyMain.GetValue("").ToString();
				keyMain.Close();
				tbInfo.Text += "TypeLib-win64: " + sWin32Path + "\r\n";
			}
		}
	}
}
