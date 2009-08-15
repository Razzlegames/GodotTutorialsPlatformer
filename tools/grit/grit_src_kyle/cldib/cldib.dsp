# Microsoft Developer Studio Project File - Name="cldib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cldib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cldib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cldib.mak" CFG="cldib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cldib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cldib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cldib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"cldib.lib"

!ELSEIF  "$(CFG)" == "cldib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"cldibd.lib"

!ENDIF 

# Begin Target

# Name "cldib - Win32 Release"
# Name "cldib - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cldib_adjust.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_conv.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_core.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_test.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_tmap.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_wu.cpp
# End Source File
# End Group
# Begin Group "hdr"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\cldib.h
# End Source File
# Begin Source File

SOURCE=.\cldib_core.h
# End Source File
# Begin Source File

SOURCE=.\cldib_quant.h
# End Source File
# Begin Source File

SOURCE=.\cldib_tmap.h
# End Source File
# Begin Source File

SOURCE=.\cldib_tools.h
# End Source File
# Begin Source File

SOURCE=.\winglue.h
# End Source File
# End Group
# Begin Group "file"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cldib_bmp.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_files.h
# End Source File
# Begin Source File

SOURCE=.\cldib_img.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_pal.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_pcx.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_png.cpp
# End Source File
# Begin Source File

SOURCE=.\cldib_tga.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cldib.chm
# End Source File
# Begin Source File

SOURCE=.\cldib.dox
# End Source File
# End Target
# End Project
