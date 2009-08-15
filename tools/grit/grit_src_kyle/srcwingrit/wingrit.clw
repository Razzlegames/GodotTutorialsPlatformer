; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CxpGbaDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wingrit.h"
LastPage=0

ClassCount=9
Class1=CxpGbaDlg
Class2=CMainFrame
Class3=CModelessDlg
Class4=CPalViewDlg
Class5=CWinrgitApp
Class6=CAboutDlg
Class7=CWingritDoc
Class8=CWingritView

ResourceCount=5
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))
Resource3=IDD_XP_GBA (English (U.S.))
Resource4=IDD_PAL_VIEW (English (U.S.))
Class9=CLogDlg
Resource5=IDD_XPLOG

[CLS:CxpGbaDlg]
Type=0
HeaderFile=gritdlg.h
ImplementationFile=gritdlg.cpp
BaseClass=CDialog
LastObject=CxpGbaDlg
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CModelessDlg]
Type=0
BaseClass=CDialog
HeaderFile=ModelessDlg.h
ImplementationFile=ModelessDlg.cpp

[CLS:CPalViewDlg]
Type=0
BaseClass=CModelessDlg
HeaderFile=PalViewDlg.h
ImplementationFile=PalViewDlg.cpp

[CLS:CWingritApp]
Type=0
BaseClass=CWinApp
HeaderFile=wingrit.h
ImplementationFile=wingrit.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=wingrit.cpp
ImplementationFile=wingrit.cpp
LastObject=CAboutDlg

[CLS:CWingritDoc]
Type=0
BaseClass=CDocument
HeaderFile=wingritDoc.h
ImplementationFile=wingritDoc.cpp

[CLS:CWingritView]
Type=0
BaseClass=CView
HeaderFile=wingritView.h
ImplementationFile=wingritView.cpp

[DLG:IDD_XP_GBA]
Type=1
Class=CxpGbaDlg

[DLG:IDD_PAL_VIEW]
Type=1
Class=CPalViewDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_VIEW_GBAEXPORT
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
CommandCount=7

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_QUANT_WU
Command12=ID_EDIT_QUANT_NN
Command13=ID_EDIT_CONVERTTO555
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VIEW_PAL
Command17=ID_VIEW_GBAEXPORT
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_VIEW_PAL
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_GBAEXPORT
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_XP_GBA (English (U.S.))]
Type=1
Class=CxpGbaDlg
ControlCount=76
Control1=IDC_STATIC,button,1342177287
Control2=IDC_IMG_CHK,button,1342242819
Control3=IDC_IMG_MODE,combobox,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_IMG_BPP,combobox,1342373891
Control6=IDC_STATIC,static,1342308352
Control7=IDC_IMG_CPRS,combobox,1342373891
Control8=IDC_STATIC,static,1342308352
Control9=IDC_IMG_TRANS,edit,1350631554
Control10=IDC_STATIC,button,1342177287
Control11=IDC_MAP_CHK,button,1342242819
Control12=IDC_MAP_FLAT,button,1342373897
Control13=IDC_MAP_SBB,button,1342177289
Control14=IDC_MAP_AFF,button,1342177289
Control15=IDC_STATIC,button,1342308359
Control16=IDC_MAP_RDX,button,1342373891
Control17=IDC_MAP_RDX_PAL,button,1342242851
Control18=IDC_MAP_RDX_FLIP,button,1342242819
Control19=IDC_META_PAL,button,1342373891
Control20=IDC_STATIC,static,1342308352
Control21=IDC_MAP_CPRS,combobox,1342373891
Control22=IDC_MAP_OFS,edit,1350770818
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,button,1342177287
Control25=IDC_OBJ_SQR,button,1342377993
Control26=IDC_OBJ_WIDE,button,1342181385
Control27=IDC_OBJ_TALL,button,1342189577
Control28=IDC_OBJ_8,button,1342377993
Control29=IDC_OBJ_16,button,1342181385
Control30=IDC_OBJ_32,button,1342181385
Control31=IDC_OBJ_64,button,1342181385
Control32=IDC_OBJ_CUSTOM,button,1342373891
Control33=IDC_STATIC,static,1342308352
Control34=IDC_OBJ_HORZ,edit,1350770818
Control35=IDC_STATIC,static,1342308352
Control36=IDC_OBJ_VERT,edit,1350639746
Control37=IDC_STATIC,button,1342177287
Control38=IDC_PAL_CHK,button,1342242819
Control39=IDC_STATIC,static,1342308352
Control40=IDC_START,edit,1350639746
Control41=IDC_STATIC,static,1342308352
Control42=IDC_COUNT,edit,1350639746
Control43=IDC_STATIC,static,1342308352
Control44=IDC_PAL_TRANS,edit,1350639746
Control45=IDC_STATIC,button,1342177287
Control46=IDC_AREA_CSM,button,1342373897
Control47=IDC_AREA_IMG,button,1342177289
Control48=IDC_AREA_SEL,button,1476395017
Control49=IDC_STATIC,static,1342308352
Control50=IDC_LEFT,edit,1350770818
Control51=IDC_STATIC,static,1342308352
Control52=IDC_TOP,edit,1350639746
Control53=IDC_STATIC,static,1342308352
Control54=IDC_WIDTH,edit,1350639746
Control55=IDC_STATIC,static,1342308352
Control56=IDC_HEIGHT,edit,1350639746
Control57=IDC_STATIC,button,1342177287
Control58=IDC_FILE_PATH,edit,1350762624
Control59=IDC_FILE_BROWSE,button,1342242816
Control60=IDC_STATIC,static,1342308352
Control61=IDC_FILE_TYPE,combobox,1344471043
Control62=IDC_VAR_8,button,1342378761
Control63=IDC_VAR_16,button,1342182153
Control64=IDC_VAR_32,button,1342182153
Control65=IDC_FILE_HDR,button,1342374403
Control66=IDC_FILE_CAT,button,1342373891
Control67=IDC_RIFF_CHK,button,1342242819
Control68=IDC_VAR_CHK,button,1342373891
Control69=IDC_VAR_NAME,edit,1350631552
Control70=IDC_SUMMARY,edit,1344473156
Control71=IDOK,button,1342242817
Control72=IDCANCEL,button,1342242816
Control73=ID_APPLY_NOW,button,1342242816
Control74=IDC_TILESET_PATH,edit,1350762624
Control75=IDC_TILESET_BROWSE,button,1342242816
Control76=IDC_TILESET_CHK,button,1342373891

[DLG:IDD_PAL_VIEW (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=ID_APPLY_NOW,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_PAL_VIEW,static,1342312459
Control4=IDC_PAL_VAL,static,1342312460
Control5=IDC_PAL_ID,static,1342312460

[DLG:IDD_XPLOG]
Type=1
Class=CLogDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SUMMARY,edit,1350633668

[CLS:CLogDlg]
Type=0
HeaderFile=LogDlg.h
ImplementationFile=LogDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SUMMARY
VirtualFilter=dWC

