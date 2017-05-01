using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace EmfView
{
	/// <summary>
	/// The RecordType enumeration specifies the types of records allowed in an EMF spool format metafile.
	/// </summary>
	[Serializable]
	//[CLSCompliant(false)]
	public enum RecordType : uint
	{
		EOF_OR_UNKNOWN = 0x00000000,
		EMRI_METAFILE = 0x00000001,
		EMRI_ENGINE_FONT = 0x00000002,
		EMRI_DEVMODE = 0x00000003,
		EMRI_TYPE1_FONT = 0x00000004,
		EMRI_PRESTARTPAGE = 0x00000005,
		EMRI_DESIGNVECTOR = 0x00000006,
		EMRI_SUBSET_FONT = 0x00000007,
		EMRI_DELTA_FONT = 0x00000008,
		EMRI_FORM_METAFILE = 0x00000009,
		EMRI_BW_METAFILE = 0x0000000A,
		EMRI_BW_FORM_METAFILE = 0x0000000B,
		EMRI_METAFILE_DATA = 0x0000000C,
		EMRI_METAFILE_EXT = 0x0000000D,
		EMRI_BW_METAFILE_EXT = 0x0000000E,
		EMRI_ENGINE_FONT_EXT = 0x0000000F,
		EMRI_TYPE1_FONT_EXT = 0x00000010,
		EMRI_DESIGNVECTOR_EXT = 0x00000011,
		EMRI_SUBSET_FONT_EXT = 0x00000012,
		EMRI_DELTA_FONT_EXT = 0x00000013,
		EMRI_PS_JOB_DATA = 0x00000014,
		EMRI_EMBED_FONT_EXT = 0x00000015
	}

	internal struct HeaderRecord
	{
		public uint cjSize;
		public string DocName;
		public uint dpszDocName; //Offset
		public uint dpszOutput; //Offset
		public uint dwVersion;
		public string OutputDevice;
	}
	public class DataRecord
	{
		public uint cjSize;
		public uint ulID;

		public DataRecord() { }
		public DataRecord(DataRecord dataRecord)
		{
			this.ulID = dataRecord.ulID;
			this.cjSize = dataRecord.cjSize;
		}
		public RecordType Type
		{
			get
			{
				if (Enum.IsDefined(typeof(RecordType), this.ulID))
				{
					return (RecordType)this.ulID;
				}
				return RecordType.EOF_OR_UNKNOWN;
			}
		}
	}
	public class PageContentRecord : DataRecord
	{
		public byte[] EmfMetaFile;

		public PageContentRecord(DataRecord dataRecord)
			: base(dataRecord)
		{
		}
	}
	public class EMRI_DEVMODERecord : DataRecord
	{
		//public DeviceMode Devmode;
		public EMRI_DEVMODERecord(DataRecord dataRecord)
			: base(dataRecord)
		{
		}
	}
	public class PageOffsetRecord : DataRecord
	{
		public ulong[] offset;

		public PageOffsetRecord(DataRecord dataRecord)
			: base(dataRecord)
		{
		}
	}
	internal struct DevMode
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
		public UInt16[] dmDeviceName;
		public UInt16 dmSpecVersion;
		public UInt16 dmDriverVersion;
		public UInt16 dmSize;
		public UInt16 dmDriverExtra;
		public UInt32 dmFields;
		public short dmOrientation;
		public short dmPaperSize;
		public short dmPaperLength;
		public short dmPaperWidth;
		public short dmScale;
		public short dmCopies;
		public short dmDefaultSource;
		public short dmPrintQuality;
		public short dmColor;
		public short dmDuplex;
		public short dmYResolution;
		public short dmTTOption;
		public short dmCollate;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
		public UInt16[] dmFormName;
		public UInt16 dmLogPixels;
		public UInt32 dmBitsPerPel;
		public UInt32 dmPelsWidth;
		public UInt32 dmPelsHeight;
		public UInt32 dmNup;
		public UInt32 dmDisplayFrequency;
		public UInt32 dmICMMethod;
		public UInt32 dmICMIntent;
		public UInt32 dmMediaType;
		public UInt32 dmDitherType;
		public UInt32 dmReserved1;
		public UInt32 dmReserved2;
		public UInt32 dmPanningWidth;
		public UInt32 dmPanningHeight;
	}
}
