using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace EmfView
{
	public partial class formEmfView : Form
	{
		private BinaryReader binaryReader = null;

		private DevMode _devmode = new DevMode();
		private string _sFileName;
		private int _iViewPage = 1;
		private int _PageCount = 0;
		private int _ImgW = 1024;
		private int _ImgH = 768;
		private float _scale;
		private bool _bPageLoaded = false;
		private Image _img;
		private int _iSplBeginPos;
		private uint _nHeaderSize; // size of header record
		private int _iSplSize;
		private Metafile _metaFile;
		private string _sDocName;
		private int _nPageW, _nPageH; // page size in pixel
		private int _nTmpFont = 0;
		private int _nCutLength = 0;// roller cut length,in priv devmode
		private float _DpiX, _DpiY;
		private Point _ptDown;	// point of mouse down
		private Point _ptOrg = new Point(0, 0);	// org of show image
		private List<string> _lsTmpFonts = new List<string>();

		[DllImport("gdi32")]
		public static extern int CreateScalableFontResource(UInt32 fdwHidden, string lpszFontRes, string lpszFontFile, string lpszCurrentPath);
		[DllImport("gdi32")]
		public static extern int AddFontResource(string lpFileName);
		[DllImport("gdi32")]
		public static extern int RemoveFontResource(string lpFileName);
		[DllImport("user32.dll")]
        public static extern int SendMessage(int hWnd, uint Msg, int wParam, int lParam);

		public formEmfView()
		{
			InitializeComponent();
		}
		private void ParseHeaderInfo()
		{
			while (true)
			{
				//文件名
				byte[] ArrayInfoNameSize = new byte[4];
				UInt32 u32InfoNameSize;
				ArrayInfoNameSize = this.binaryReader.ReadBytes(4);
				u32InfoNameSize = BitConverter.ToUInt32(ArrayInfoNameSize, 0);
				byte[] ArrayInfoName = this.binaryReader.ReadBytes((int)(u32InfoNameSize * 2));

				//文件内容
				byte[] ArrayInfoSize = new byte[4];
				UInt32 u32InfoSize;
				ArrayInfoSize = this.binaryReader.ReadBytes(4);
				u32InfoSize = BitConverter.ToUInt32(ArrayInfoSize, 0);
				byte[] ArrayInfo = this.binaryReader.ReadBytes((int)(u32InfoSize));	// save file
				string sName = System.Text.Encoding.Unicode.GetString(ArrayInfoName);

				int iLen = sName.Length;
				if (sName.EndsWith(".tmp")) // temp font
				{
					if (chkTempFont.Checked)
						AddTempFont(ArrayInfo, sName);
					this._nTmpFont++;
				}
				if (sName.EndsWith(".SHD"))
				{
					GetDevMode(ArrayInfo);
					ArrayInfoNameSize = this.binaryReader.ReadBytes(4);
					u32InfoNameSize = BitConverter.ToUInt32(ArrayInfoNameSize, 0);
					ArrayInfoName = this.binaryReader.ReadBytes((int)(u32InfoNameSize * 2));
					ArrayInfoSize = this.binaryReader.ReadBytes(4);
					u32InfoSize = BitConverter.ToUInt32(ArrayInfoSize, 0);
					sName = System.Text.Encoding.Unicode.GetString(ArrayInfoName); // c:\..\0000x.spl
					_iSplBeginPos = (int)this.binaryReader.BaseStream.Position;
					_iSplSize = (int)u32InfoSize;
					break;
				}
			} // while
		} // ParseHeaderInfo
		private void GetDevMode(byte[] arData)
		{
			int nSize = Marshal.SizeOf(_devmode);//unsafe 
			int nPos = BitConverter.ToInt32(arData, 4);
			IntPtr structPtr = Marshal.AllocHGlobal(nSize);
			Marshal.Copy(arData, nPos, structPtr, nSize);
			_devmode = (DevMode)Marshal.PtrToStructure(structPtr, _devmode.GetType());
			Marshal.FreeHGlobal(structPtr);
			int nShdHead = BitConverter.ToInt32(arData, 4);
			_nCutLength = BitConverter.ToInt32(arData, nShdHead + 1156);
		}
		private bool AddTempFont(byte[] arData, string sFileName)
		{
			int i = this._sFileName.LastIndexOf('\\');
			string sPath = this._sFileName.Substring(0, i + 1) + sFileName;
			if (!File.Exists(sPath))
			{
				FileStream fs = new FileStream(sPath, FileMode.Create);
				fs.Write(arData, 0, arData.Length);
				fs.Flush();
				fs.Close();
			}
			string sFot = sPath + ".fot";
			//if (CreateScalableFontResource(0x11, sFot, sPath, null) <= 0)
			//	return false;
			int nRet = AddFontResource(sPath);//sFot);//
			this._lsTmpFonts.Add(sPath);
			return true;
		}

		private HeaderRecord ParseHeaderRecord()
		{
			var headerRecord = new HeaderRecord();
			headerRecord.dwVersion = this.binaryReader.ReadUInt32();
			headerRecord.cjSize = this.binaryReader.ReadUInt32();
			headerRecord.dpszDocName = this.binaryReader.ReadUInt32();
			headerRecord.dpszOutput = this.binaryReader.ReadUInt32();

			if (headerRecord.dpszDocName != 0)
			{
				this.binaryReader.BaseStream.Seek(headerRecord.dpszDocName + this._iSplBeginPos, SeekOrigin.Begin);
				var docNameStringBuilder = new StringBuilder();
				while (this.binaryReader.PeekChar() != 0)
				{
					docNameStringBuilder.Append(this.binaryReader.ReadChar());
				}
				headerRecord.DocName = docNameStringBuilder.ToString();
				_sDocName = headerRecord.DocName;
			}
			this.Ensure32BitAlignment();
			if (headerRecord.dpszOutput != 0)
			{
				this.binaryReader.BaseStream.Seek(headerRecord.dpszOutput + this._iSplBeginPos, SeekOrigin.Begin);
				var outputDeviceStringBuilder = new StringBuilder();
				while (this.binaryReader.PeekChar() != 0)
				{
					outputDeviceStringBuilder.Append(this.binaryReader.ReadChar());
				}
				headerRecord.OutputDevice = outputDeviceStringBuilder.ToString();
			}
			this.Ensure32BitAlignment();
			this.EnsurePosition(headerRecord.cjSize);
			this._nHeaderSize = headerRecord.cjSize;
			return headerRecord;
		} // ParseHeaderRecord

		private void ParseDataRecords()
		{
			long lSplLen = this.binaryReader.BaseStream.Length;
			while (true)
			{
				long pos = this.binaryReader.BaseStream.Position;
				if (pos >= lSplLen)
					break;

				uint ulID = this.binaryReader.ReadUInt32();
				if (ulID == 0x00000000)
				{
					//Don't know why. Sometimes 0x0 is too early.
					//So we need read it again.
					ulID = this.binaryReader.ReadUInt32();
				}
				var dataRecord = new DataRecord();
				dataRecord.ulID = ulID;
				dataRecord.cjSize = this.binaryReader.ReadUInt32();
				if (dataRecord.cjSize == 0)
					break; // 垃圾数据.
				if (!Enum.IsDefined(typeof(RecordType), dataRecord.ulID))
				{
					this.binaryReader.ReadBytes((int)dataRecord.cjSize); // Read unknown data block
					continue;
				}
				switch (dataRecord.ulID)
				{
					case (uint)RecordType.EMRI_METAFILE:
						{
							var pageContentRecord = new PageContentRecord(dataRecord);
							pageContentRecord.EmfMetaFile = this.binaryReader.ReadBytes((int)pageContentRecord.cjSize);
							SaveImg(pageContentRecord);
						}
						break;
					case (uint)RecordType.EMRI_ENGINE_FONT:
						break;
					case (uint)RecordType.EMRI_DEVMODE:
						{
							var devmodeRecord = new EMRI_DEVMODERecord(dataRecord);
							byte[] buffer = this.binaryReader.ReadBytes((int)dataRecord.cjSize);
							//this.deviceMode = new DeviceMode(new DEVMODE(buffer));
							//devmodeRecord.Devmode = this.deviceMode;
							//dataRecords.Add(devmodeRecord);
							//SaveImg(devmodeRecord);
						}
						break;
					case (uint)RecordType.EMRI_METAFILE_DATA:
						{
							var pageContentRecord = new PageContentRecord(dataRecord);
							pageContentRecord.EmfMetaFile = this.binaryReader.ReadBytes((int)dataRecord.cjSize);
							//dataRecords.Add(pageContentRecord);
							SaveImg(pageContentRecord);
						}
						break;
					case (uint)RecordType.EMRI_METAFILE_EXT:
					case (uint)RecordType.EMRI_BW_METAFILE_EXT:
						{
							var pageOffsetRecord = new PageOffsetRecord(dataRecord);
							var offsets = new ulong[pageOffsetRecord.cjSize / sizeof(ulong)];
							for (int i = 0; i < offsets.Length; i++)
							{
								offsets[i] = this.binaryReader.ReadUInt64();
							}
							//dataRecords.Add(pageOffsetRecord);
							SaveImg(pageOffsetRecord);
						}
						break;
					case (uint)RecordType.EMRI_TYPE1_FONT:
						break;
					case (uint)RecordType.EMRI_PRESTARTPAGE:
						break;
					case (uint)RecordType.EMRI_DESIGNVECTOR:
						break;
					case (uint)RecordType.EMRI_SUBSET_FONT:
						break;
					case (uint)RecordType.EMRI_DELTA_FONT:
						break;
					case (uint)RecordType.EMRI_FORM_METAFILE:
						break;
					case (uint)RecordType.EMRI_BW_METAFILE:
						break;
					case (uint)RecordType.EMRI_BW_FORM_METAFILE:
						break;
					case (uint)RecordType.EMRI_ENGINE_FONT_EXT:
						break;
					case (uint)RecordType.EMRI_TYPE1_FONT_EXT:
						break;
					case (uint)RecordType.EMRI_DESIGNVECTOR_EXT:
						break;
					case (uint)RecordType.EMRI_SUBSET_FONT_EXT:
						break;
					case (uint)RecordType.EMRI_DELTA_FONT_EXT:
						break;
					case (uint)RecordType.EMRI_PS_JOB_DATA:
						break;
					case (uint)RecordType.EMRI_EMBED_FONT_EXT:
						break;
				} // switch
			} // while
		} // ParseDataRecords
		private void EnsurePosition(uint size)
		{
			this.binaryReader.BaseStream.Seek(size + this._iSplBeginPos, SeekOrigin.Begin);
		}

		private void Ensure32BitAlignment()
		{
			long pos = this.binaryReader.BaseStream.Position;
			long currentAlignment = pos % 4;
			if (currentAlignment == 0)
			{
				return;
			}
			this.binaryReader.BaseStream.Seek(currentAlignment, SeekOrigin.Current);
		}
		public void SaveImg(DataRecord datarecord)
		{
			var pageContentRecord = datarecord as PageContentRecord;
			var devmodeRecord = datarecord as EMRI_DEVMODERecord;
			if (pageContentRecord != null)
			{
				this._PageCount++;
				if ((this._PageCount == this._iViewPage) && (this._bPageLoaded) != true)
				{
					var memoryStream = new MemoryStream(pageContentRecord.EmfMetaFile);
					_metaFile = new Metafile(memoryStream);
					float fRatio = (float)_metaFile.Width / (float)_metaFile.Height;
					this._ImgW = (int)(fRatio * this._ImgH);
					this._scale = this._ImgW / (float)_metaFile.Width;
					this._img = _metaFile.GetThumbnailImage(this._ImgW, this._ImgH, null, IntPtr.Zero);
					MetafileHeader metaHead = _metaFile.GetMetafileHeader();
					_nPageW = metaHead.Bounds.Width;
					_nPageH = metaHead.Bounds.Height;
					_DpiX = metaHead.DpiX;
					_DpiY = metaHead.DpiY;
					this._bPageLoaded = true;
				}
			}
			if (devmodeRecord != null)
			{
				//this.deviceMode = devmodeRecord.Devmode;
			}
		}
		private int LoadPage(int iPage)
		{
			_PageCount = 0;
			this._bPageLoaded = false;
			this.EnsurePosition(this._nHeaderSize);
			this.ParseDataRecords();
			txPage.Text = string.Format("{0}/{1}", iPage, _PageCount);
			float fPaperW = _nPageW * 25.4f / (int)_DpiX; // mm
			float fPaperH = _nPageH * 25.4f / (int)_DpiY;
			txInfo.Text = string.Format("DocName:{0}\nPageSize:{1}x{2}pix\nPaperSize:{3:0.#}x{4:0.#}mm\nDPI:{5:0.##}x{6:0.##}\nTempFont:{7}\r\n",
				_sDocName, _nPageW, _nPageH, fPaperW, fPaperH, _DpiX, _DpiY, _nTmpFont);
			if (_devmode.dmSize > 0)
			{
				txInfo.Text += "DevMode:\r\n";
				txInfo.Text += string.Format("orient:{0} papersize:{1},{2}x{3}\nfields:{4:X} scale:{5} copies:{6} source:{7}\r\n",
					_devmode.dmOrientation, _devmode.dmPaperSize, _devmode.dmPaperWidth, _devmode.dmPaperLength,
					_devmode.dmFields, _devmode.dmScale, _devmode.dmCopies, _devmode.dmDefaultSource);
				txInfo.Text += string.Format("Res:{0}x{1} color:{2} duplex:{3} media:{4}\r\n",
					_devmode.dmPrintQuality, _devmode.dmYResolution, _devmode.dmColor, _devmode.dmDuplex, _devmode.dmMediaType);
				char[] arName = new char[32];
				for (int i=0; i<32; i++)
					arName[i] = (char)_devmode.dmFormName[i];
				string sName = new string(arName);
				txInfo.Text += string.Format("formName:{0}\r\n", sName);
				txInfo.Text += string.Format("CutLen:{0}mm\r\n", _nCutLength);
			}
			//picBox.Image = this._img;
			this._ptDown.X = 0;
			Refresh();
			return 0;
		}
		private void btnOpen_Click(object sender, EventArgs e)
		{
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.Filter = "Job File (*.dat)|*.dat|Spl File (*.spl)|*.spl|All Files (*.*)|*.*||";
			if (DialogResult.Cancel == dlg.ShowDialog())
				return;
			this._sFileName = dlg.FileName;
			this.Text = "EmfViewer - " + dlg.FileName;
			this._nTmpFont = 0;
			Stream stream = new FileStream(dlg.FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
			this.binaryReader = new BinaryReader(stream, Encoding.Unicode);
			if (dlg.FileName.EndsWith("dat"))
				this.ParseHeaderInfo();
			Int32.TryParse(txPage.Text, out _iViewPage);
			if (_iViewPage <= 0)
				_iViewPage = 1;
			//if (this._nTmpFont > 0)
			//{
			//    const int WM_FONTCHANGE = 0x001D;
			//    const int HWND_BROADCAST = 0xffff;
			//    int nRet = SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); // why block?
			//}
			HeaderRecord headerRecord = this.ParseHeaderRecord();
			LoadPage(this._iViewPage);
		}

		private void btnZoomIn_Click(object sender, EventArgs e)
		{
			this._scale *= 1.25f;
			this._ImgW = (int)(this._metaFile.Width * this._scale);
			this._ImgH = (int)(this._metaFile.Height * this._scale);
			this._img = _metaFile.GetThumbnailImage(this._ImgW, this._ImgH, null, IntPtr.Zero);
			Refresh();
		}

		private void btnZoomOut_Click(object sender, EventArgs e)
		{
			this._scale /= 1.25f;
			this._ImgW = (int)(this._metaFile.Width * this._scale);
			this._ImgH = (int)(this._metaFile.Height * this._scale);
			this._img = _metaFile.GetThumbnailImage(this._ImgW, this._ImgH, null, IntPtr.Zero);
			Refresh();
		}

		private void btnPrev_Click(object sender, EventArgs e)
		{
			this._iViewPage--;
			if (_iViewPage < 1)
				_iViewPage = 1;
			else
				LoadPage(this._iViewPage);
		}

		private void btnNext_Click(object sender, EventArgs e)
		{
			this._iViewPage++;
			if (_iViewPage > _PageCount)
				_iViewPage = _PageCount;
			else
				LoadPage(this._iViewPage);
		}

		private void btnGo_Click(object sender, EventArgs e)
		{
			int i = txPage.Text.IndexOf('/');
			string sPage = txPage.Text;
			if (i >= 0)
				sPage = txPage.Text.Substring(0, i);
			if (!Int32.TryParse(sPage, out _iViewPage))
				return;
			if (_iViewPage < 1)
				_iViewPage = 1;
			else if (_iViewPage > _PageCount)
				_iViewPage = _PageCount;
			else
				LoadPage(this._iViewPage);
		}

		private void formEmfView_SizeChanged(object sender, EventArgs e)
		{
			int nMargin = 14;
			txInfo.Left = this.ClientSize.Width - txInfo.Width - nMargin;
			txInfo.Height = this.ClientSize.Height - txInfo.Top - nMargin;
			picBox.Width = this.ClientSize.Width - txInfo.Width - nMargin * 3;
			picBox.Height = this.ClientSize.Height - picBox.Top - nMargin;
		}

		private void formEmfView_Paint(object sender, PaintEventArgs e)
		{
			if (this._img == null)
				return;
			Graphics g = picBox.CreateGraphics();
			g.DrawImage(_img, _ptOrg.X, _ptOrg.Y);
			g.DrawRectangle(new Pen(Color.Black), _ptOrg.X, _ptOrg.Y, _img.Width, _img.Height);
		}

		private void picBox_MouseDown(object sender, MouseEventArgs e)
		{
			this._ptDown.X = e.X;
			this._ptDown.Y = e.Y;
		}

		private void picBox_MouseUp(object sender, MouseEventArgs e)
		{
			if (this._ptDown.X == 0)
				return;
			this._ptOrg.X = this._ptOrg.X + e.X - this._ptDown.X;
			this._ptOrg.Y = this._ptOrg.Y + e.Y - this._ptDown.Y;
			//if (this._ptOrg.X < 0)
			//    this._ptOrg.X = 0;
			//if (this._ptOrg.X + _ImgW > picBox.Width)
			//    this._ptOrg.X = picBox.Width - _ImgW;
			//if (this._ptOrg.Y < 0)
			//    this._ptOrg.Y = 0;
			//if (this._ptOrg.Y + _ImgH > picBox.Height)
			//    this._ptOrg.Y = picBox.Height - _ImgH;
			Refresh();
		}

		private void formEmfView_FormClosed(object sender, FormClosedEventArgs e)
		{
			int i, nRet;
			for (i = 0; i < _lsTmpFonts.Count; i++)
			{
				nRet = RemoveFontResource(_lsTmpFonts[i]);
				//File.Delete(_lsTmpFonts[i]); // using by system?
			}
		}

	}
}
