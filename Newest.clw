; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProfileForm
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "newest.h"
LastPage=0

ClassCount=22
Class1=CChildFrame
Class2=CDialog_BandSelect
Class3=CDisplayOptions_dlg
Class4=CDisplayscale_dialog
Class5=CFileParams_Dialog
Class6=CFitres_dlg
Class7=CFrameWnd_Child
Class8=CMainFrame
Class9=CNewestApp
Class10=CAboutDlg
Class11=CNewestDoc
Class12=CNewestView
Class13=CPlotWin
Class14=CRGB_Dialog
Class15=CSelectBand_dlg
Class16=CTopoParams_dlg
Class17=ZoomWindow

ResourceCount=16
Resource1=IDR_MAINFRAME
Resource2=IDR_NEWESTTYPE
Resource3=IDD_DIALOG3
Resource4=IDD_ABOUTBOX
Resource5=IDD_CFV_FORM
Resource6=IDD_DIALOG1
Resource7=IDD_CRATER_ID
Resource8=IDD_DIALOG2
Resource9=IDD_DIALOG6
Resource10=IDR_PROFILEFORM_TMPL
Class18=CResults_dlg
Resource11=IDD_DIALOG4
Class19=CCraterID_Dlg
Resource12=IDD_FITRES_DLG
Class20=CResFormView
Resource13=IDD_DIALOG5
Class21=CFileSelectDlg
Resource14=IDD_DIALOG7
Resource15=IDD_FILESELECT_DLG
Class22=CProfileForm
Resource16=IDD_PROFILEFORM_FORM

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDialog_BandSelect]
Type=0
BaseClass=CDialog
HeaderFile=Dialog_BandSelect.h
ImplementationFile=Dialog_BandSelect.cpp

[CLS:CDisplayOptions_dlg]
Type=0
BaseClass=CDialog
HeaderFile=DisplayOptions_dlg.h
ImplementationFile=DisplayOptions_dlg.cpp

[CLS:CDisplayscale_dialog]
Type=0
BaseClass=CDialog
HeaderFile=Displayscale_dialog.h
ImplementationFile=Displayscale_dialog.cpp

[CLS:CFileParams_Dialog]
Type=0
BaseClass=CDialog
HeaderFile=FileParams_Dialog.h
ImplementationFile=FileParams_Dialog.cpp

[CLS:CFitres_dlg]
Type=0
BaseClass=CDialog
HeaderFile=Fitres_dlg.h
ImplementationFile=Fitres_dlg.cpp

[CLS:CFrameWnd_Child]
Type=0
BaseClass=CFrameWnd
HeaderFile=FrameWnd_Child.h
ImplementationFile=FrameWnd_Child.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CNewestApp]
Type=0
BaseClass=CWinApp
HeaderFile=Newest.h
ImplementationFile=Newest.cpp
Filter=N
VirtualFilter=AC
LastObject=CNewestApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Newest.cpp
ImplementationFile=Newest.cpp
LastObject=CAboutDlg

[CLS:CNewestDoc]
Type=0
BaseClass=CDocument
HeaderFile=NewestDoc.h
ImplementationFile=NewestDoc.cpp
LastObject=CNewestDoc

[CLS:CNewestView]
Type=0
BaseClass=CScrollView
HeaderFile=NewestView.h
ImplementationFile=NewestView.cpp
LastObject=CNewestView
Filter=C
VirtualFilter=VWC

[CLS:CPlotWin]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=PlotWin.h
ImplementationFile=PlotWin.cpp

[CLS:CRGB_Dialog]
Type=0
BaseClass=CDialog
HeaderFile=RGB_Dialog.h
ImplementationFile=RGB_Dialog.cpp

[CLS:CSelectBand_dlg]
Type=0
BaseClass=CDialog
HeaderFile=SelectBand_dlg.h
ImplementationFile=SelectBand_dlg.cpp

[CLS:CTopoParams_dlg]
Type=0
BaseClass=CDialog
HeaderFile=TopoParams_dlg.h
ImplementationFile=TopoParams_dlg.cpp

[CLS:ZoomWindow]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ZoomWindow.h
ImplementationFile=ZoomWindow.cpp
LastObject=ID_APP_ABOUT
Filter=M
VirtualFilter=mfWC

[DLG:IDD_DIALOG5]
Type=1
Class=CDialog_BandSelect
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[DLG:IDD_DIALOG4]
Type=1
Class=CDisplayOptions_dlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_VAL_MIN,edit,1350631552
Control6=IDC_VAL_MAX,edit,1350631552

[DLG:IDD_DIALOG3]
Type=1
Class=CDisplayscale_dialog
ControlCount=14
Control1=IDC_USER_MNMX,button,1342373897
Control2=IDC_RADIO7,button,1342242825
Control3=IDC_VAL,button,1342373897
Control4=IDC_RADIO9,button,1342242825
Control5=IDC_MINVAL,edit,1350631552
Control6=IDC_MAXVAL,edit,1350631552
Control7=IDC_BANDS,edit,1350631552
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=CFileParams_Dialog
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_FILENAME,edit,1350631552
Control10=IDC_SAMPS,edit,1350631552
Control11=IDC_LINES,edit,1350631552
Control12=IDC_BANDS,edit,1350631552
Control13=IDC_DTYPE,combobox,1344339970
Control14=IDC_BFORM,combobox,1344339970

[DLG:IDD_FITRES_DLG]
Type=1
Class=CFitres_dlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_FITRESULTS,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG2]
Type=1
Class=CRGB_Dialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_RBAND,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GBAND,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IDC_BBAND,edit,1350631552

[DLG:IDD_DIALOG6]
Type=1
Class=CTopoParams_dlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PIXDIM,edit,1350631552
Control9=IDC_MINVAL,edit,1350631552
Control10=IDC_MAXVAL,edit,1350631552
Control11=IDC_SUNELEV,edit,1350631552
Control12=IDC_SUNAZ,edit,1350631552
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_NEWESTTYPE]
Type=1
Class=?
Command1=ID_DEF_SHADE
Command2=ID_DEF_ALTSHADEFILE
Command3=ID_DEF_DEM
Command4=ID_DEFINE_HITFILE
Command5=ID_APP_EXIT
Command6=ID_DISP_SHADE
Command7=ID_SHOW_ALT_SHADE
Command8=ID_TOGGLE_ALT
Command9=ID_SHOW_HITS
Command10=IDC_DEFCRATERCTR
Command11=ID_DEF_UNAFFECT
Command12=IDC_DEF_RIM
Command13=ID_DEF_INNERPRIMARY
Command14=ID_DEFINEPRIMARYSECONDARYBOUNDARY
Command15=ID_DEF_SECONDARY
Command16=IDC_DEFLOBES
Command17=IDC_NEWCRATER
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_VIEW_STATUS_BAR
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

[DLG:IDD_DIALOG7]
Type=1
Class=CResults_dlg
ControlCount=14
Control1=IDWRITEFILE,button,1342242816
Control2=IDC_RIM_PROF,static,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_YMAX,static,1342308352
Control5=IDC_YMIN,static,1342308352
Control6=IDC_XMIN,static,1342308352
Control7=IDC_XMAX,static,1342308352
Control8=IDC_RIMTEXT,static,1342177280
Control9=IDC_Cratervol,static,1342308352
Control10=IDC_Rimvol,static,1342308352
Control11=IDC_Primvol,static,1342308352
Control12=IDC_Secvol,static,1342308352
Control13=IDC_EDIT_OUTFILE,edit,1350631552
Control14=IDC_BROWSE_OUTPUT,button,1342242816

[CLS:CResults_dlg]
Type=0
HeaderFile=Results_dlg.h
ImplementationFile=Results_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CResults_dlg

[DLG:IDD_CRATER_ID]
Type=1
Class=CCraterID_Dlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CRATERID_EDIT,edit,1350631552

[CLS:CCraterID_Dlg]
Type=0
HeaderFile=CraterID_Dlg.h
ImplementationFile=CraterID_Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CRATERID_EDIT
VirtualFilter=dWC

[DLG:IDD_CFV_FORM]
Type=1
Class=CResFormView
ControlCount=12
Control1=IDC_RIMPROF,static,1342177287
Control2=IDC_LOCATION,static,1342308352
Control3=IDC_SURFTEXT,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CratRimText,static,1342308352
Control6=IDC_InnerLobe,static,1342308352
Control7=IDC_Outer,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_YMAX,static,1342308352
Control10=IDC_YMIN,static,1342308352
Control11=IDC_XMIN,static,1342308352
Control12=IDC_XMAX,static,1342308352

[CLS:CResFormView]
Type=0
HeaderFile=ResFormView1.h
ImplementationFile=ResFormView1.cpp
BaseClass=CFormView
Filter=D
LastObject=ID_DEF_ALTSHADEFILE
VirtualFilter=VWC

[DLG:IDD_FILESELECT_DLG]
Type=1
Class=CFileSelectDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SURFACEFILE,edit,1350631552
Control5=IDC_BUTTON_STATSELECT,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_FEATUREFILE,edit,1350631552
Control8=IDC_BUTTON_FEATURESELECT,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON_ANALYSISSELECT,button,1342242816
Control11=IDC_ANALYSISFILE,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TABFILE,edit,1350631552
Control14=IDC_BROWSE_TABFILE,button,1342242816

[CLS:CFileSelectDlg]
Type=0
HeaderFile=FileSelectDlg.h
ImplementationFile=FileSelectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DEFCRATERCTR

[DLG:IDD_PROFILEFORM_FORM]
Type=1
Class=CProfileForm
ControlCount=20
Control1=IDC_PROFWINDOW,static,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ORIENTATION,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LENGTH,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MAXHEIGHT,edit,1350631552
Control9=IDC_MINHEIGHT,edit,1350631552
Control10=IDC_BUTTON1,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CENTSAMP,edit,1350631552
Control13=IDC_CENTLINE,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_AUTOSTATE,button,1342242819
Control16=IDC_XMAXLAB,static,1342308352
Control17=IDC_XMINLAB,static,1342308352
Control18=IDC_YMINLAB,static,1342308352
Control19=IDC_YMAXLAB,static,1342308352
Control20=IDC_YMID,static,1342308352

[CLS:CProfileForm]
Type=0
HeaderFile=ProfileForm.h
ImplementationFile=ProfileForm.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_YMAXLAB

[MNU:IDR_PROFILEFORM_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21
