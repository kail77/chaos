; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBatchDownDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BatchDown.h"

ClassCount=3
Class1=CBatchDownApp
Class2=CBatchDownDlg

ResourceCount=3
Resource2=IDD_BATCHDOWN
Resource1=IDR_MAINFRAME
Class3=CNewTaskDlg
Resource3=IDD_NEWTASK

[CLS:CBatchDownApp]
Type=0
HeaderFile=BatchDown.h
ImplementationFile=BatchDown.cpp
Filter=N

[CLS:CBatchDownDlg]
Type=0
HeaderFile=BatchDownDlg.h
ImplementationFile=BatchDownDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DELETE



[DLG:IDD_BATCHDOWN]
Type=1
Class=CBatchDownDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_LISTTASK,SysListView32,1350631433
Control4=IDC_CLEAR,button,1342242816
Control5=IDC_ADDTASK,button,1342242816
Control6=IDC_INFO,static,1342308352

[DLG:IDD_NEWTASK]
Type=1
Class=CNewTaskDlg
ControlCount=16
Control1=IDC_URL,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_RANGE1,edit,1350631552
Control4=IDC_SPINRANGE1,msctls_updown32,1342177334
Control5=IDC_STATIC,static,1342308352
Control6=IDC_RANGE2,edit,1350631552
Control7=IDC_SPINRANGE2,msctls_updown32,1342177334
Control8=IDC_STATIC,static,1342308352
Control9=IDC_WILDNUM,edit,1350631552
Control10=IDC_SPINWILD,msctls_updown32,1342177334
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_EXAMPLE,static,1073872896
Control14=IDC_MATCH,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SUBFOLDER,edit,1350631552

[CLS:CNewTaskDlg]
Type=0
HeaderFile=NewTaskDlg.h
ImplementationFile=NewTaskDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNewTaskDlg

