; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CThellierDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Thellier.h"
LastPage=0

ClassCount=8
Class1=CThellierApp
Class2=CThellierDoc
Class3=CThellierView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=RangeDlg
Class7=CRangeForm
Class8=CRangeDlg
Resource3=IDD_RANGE_DIALOG

[CLS:CThellierApp]
Type=0
HeaderFile=Thellier.h
ImplementationFile=Thellier.cpp
Filter=N

[CLS:CThellierDoc]
Type=0
HeaderFile=ThellierDoc.h
ImplementationFile=ThellierDoc.cpp
Filter=N
LastObject=CThellierDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CThellierView]
Type=0
HeaderFile=ThellierView.h
ImplementationFile=ThellierView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_EDIT1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Thellier.cpp
ImplementationFile=Thellier.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VEKTOR_FKOMP
Command17=ID_VEKTOR_ZKOMP
Command18=ID_OPTIONEN_RANGE
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_VEKTOR_FKOMP
Command9=ID_VEKTOR_ZKOMP
Command10=ID_OPTIONEN_RANGE
Command11=ID_APP_ABOUT
CommandCount=11

[CLS:RangeDlg]
Type=0
HeaderFile=RangeDlg.h
ImplementationFile=RangeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[CLS:CRangeForm]
Type=0
HeaderFile=RangeForm.h
ImplementationFile=RangeForm.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TEMPMIN_EDIT
VirtualFilter=dWC

[DLG:IDD_RANGE_DIALOG]
Type=1
Class=CRangeDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEMPMIN_EDIT,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552

[CLS:CRangeDlg]
Type=0
HeaderFile=RangeDlg1.h
ImplementationFile=RangeDlg1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRangeDlg

