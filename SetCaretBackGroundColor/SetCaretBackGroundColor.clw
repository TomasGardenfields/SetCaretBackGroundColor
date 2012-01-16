; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CIgnoreDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SetCaretBackGroundColor.h"

ClassCount=4
Class1=CSetCaretBackGroundColorApp
Class2=CSetCaretBackGroundColorDlg

ResourceCount=5
Resource2=IDD_DIALOG_IGNORE
Resource3=IDD_CONFIGDIALOG
Resource1=IDR_MAINFRAME
Class3=CConfigDialog
Resource4=IDD_SETCARETBACKGROUNDCOLOR_DIALOG
Class4=CIgnoreDialog
Resource5=IDR_TRAYMENU

[CLS:CSetCaretBackGroundColorApp]
Type=0
HeaderFile=SetCaretBackGroundColor.h
ImplementationFile=SetCaretBackGroundColor.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CSetCaretBackGroundColorApp

[CLS:CSetCaretBackGroundColorDlg]
Type=0
HeaderFile=SetCaretBackGroundColorDlg.h
ImplementationFile=SetCaretBackGroundColorDlg.cpp
Filter=W
LastObject=CSetCaretBackGroundColorDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SETCARETBACKGROUNDCOLOR_DIALOG]
Type=1
Class=CSetCaretBackGroundColorDlg
ControlCount=0

[MNU:IDR_TRAYMENU]
Type=1
Class=?
Command1=ID_MENUITEM_TRAY_EXIT
Command2=ID_MENUITEM_TRAY_RESTART
Command3=ID_MENUITEM_TRAY_CONFIG
Command4=ID_MENUITEM_TRAY_IGNORE
Command5=ID_MENUITEM_TRAY_CANCEL
CommandCount=5

[DLG:IDD_CONFIGDIALOG]
Type=1
Class=CConfigDialog
ControlCount=20
Control1=IDC_SLIDER_TRANSPARENT_OPEN,msctls_trackbar32,1342242840
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_BUTTON_COLOR_OPEN,button,1342242816
Control5=IDC_BUTTON_COLOR_CLOSE,button,1342242816
Control6=IDC_SLIDER_TRANSPARENT_CLOSE,msctls_trackbar32,1342242840
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,button,1342177287
Control10=IDC_SLIDER_BLINK_COUNT,msctls_trackbar32,1342242840
Control11=IDC_STATIC_PICTURE_COLOR_OPEN,static,1342181376
Control12=IDC_STATIC_PICTURE_COLOR_CLOSE,static,1342181376
Control13=IDC_STATIC,static,1342308864
Control14=IDC_SLIDER_BLINK_FADE_LENGTH,msctls_trackbar32,1342242840
Control15=IDC_STATIC,static,1342308864
Control16=IDC_EDIT_BLINK_FRAMELENGTH,edit,1350641792
Control17=IDC_EDIT_BLINK_COUNT,edit,1350641792
Control18=IDC_EDIT_COLOR_OPEN,edit,1350641792
Control19=IDC_EDIT_COLOR_CLOSE,edit,1350641792
Control20=IDC_BUTTON_CONFIG_CLOSE,button,1342242816

[CLS:CConfigDialog]
Type=0
HeaderFile=ConfigDialog.h
ImplementationFile=ConfigDialog.cpp
BaseClass=CDialog
Filter=W
LastObject=CConfigDialog
VirtualFilter=dWC

[DLG:IDD_DIALOG_IGNORE]
Type=1
Class=CIgnoreDialog
ControlCount=8
Control1=IDC_LIST_IGNORE_CLASSNAME,listbox,1353777411
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON_CLASSNAME_ADD,button,1342242816
Control4=IDC_EDIT_IGNORE_CLASSNAME,edit,1350631552
Control5=IDC_LIST_IGNORE_CLASSNAME_HISTORY,listbox,1352728835
Control6=IDC_STATIC,static,1342308864
Control7=IDC_BUTTON_CLASSNAME_REMOVE,button,1342242816
Control8=IDC_BUTTON_IGNORE_CLOSE,button,1342242816

[CLS:CIgnoreDialog]
Type=0
HeaderFile=IgnoreDialog.h
ImplementationFile=IgnoreDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CIgnoreDialog
VirtualFilter=dWC

