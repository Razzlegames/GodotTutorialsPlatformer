# Microsoft Developer Studio Project File - Name="wingrit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wingrit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wingrit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wingrit.mak" CFG="wingrit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wingrit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wingrit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wingrit - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../srcwingrit" /I "../extlib" /I "../cldib" /I "../libgrit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 FreeImage.lib /nologo /subsystem:windows /pdb:"wingrit.pdb" /machine:I386 /libpath:"../extlib" /libpath:"../cldib" /libpath:"../libgrit"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "wingrit - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin/"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../srcwingrit" /I "../extlib" /I "../cldib" /I "../libgrit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 FreeImage.lib /nologo /subsystem:windows /pdb:"wingrit.pdb" /debug /machine:I386 /out:"../bin/wingritd.exe" /pdbtype:sept /libpath:"../extlib" /libpath:"../cldib" /libpath:"../libgrit"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "wingrit - Win32 Release"
# Name "wingrit - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\extlib\fi.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\FileFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\gritdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\ModelessDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\PalViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingrit.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingrit.rc
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingritDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingritView.cpp
# End Source File
# End Group
# Begin Group "hdr"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\extlib\fi.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\FileFilter.h
# End Source File
# Begin Source File

SOURCE=..\extlib\FreeImage.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\gritdlg.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\LogDlg.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\ModelessDlg.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\PalViewDlg.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\resource.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingrit.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingritDoc.h
# End Source File
# Begin Source File

SOURCE=..\srcwingrit\wingritView.h
# End Source File
# End Group
# Begin Group "res"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=..\res\wingrit.ico
# End Source File
# Begin Source File

SOURCE=..\res\wingritDoc.ico
# End Source File
# End Group
# Begin Group "doc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\doc\prehtml\grit.htm
# End Source File
# Begin Source File

SOURCE=..\doc\html\tonc.css
# End Source File
# Begin Source File

SOURCE=..\doc\html\tonc.js
# End Source File
# Begin Source File

SOURCE=..\doc\prehtml\wingrit.htm
# End Source File
# End Group
# Begin Source File

SOURCE=..\bin\gxplog.txt
# End Source File
# Begin Source File

SOURCE=..\bin\wingrit.txt
# End Source File
# End Target
# End Project
