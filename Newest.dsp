# Microsoft Developer Studio Project File - Name="Newest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Newest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Newest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Newest.mak" CFG="Newest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Newest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Newest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Newest - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /subsystem:windows /machine:I386 /out:"Release/Impact.exe"
# SUBTRACT LINK32 /nologo

!ELSEIF  "$(CFG)" == "Newest - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Impact.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Newest - Win32 Release"
# Name "Newest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Array.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\covsrt.c
# End Source File
# Begin Source File

SOURCE=.\CraterID_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CraterStats.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog_BandSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\DIB.cpp
# End Source File
# Begin Source File

SOURCE=.\DisplayOptions_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Displayscale_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\FileParams_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FileSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Fitres_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\gaussj.c
# End Source File
# Begin Source File

SOURCE=.\ImageFile.cpp
# End Source File
# Begin Source File

SOURCE=.\lfit.c
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Newest.cpp
# End Source File
# Begin Source File

SOURCE=.\Newest.rc
# End Source File
# Begin Source File

SOURCE=.\NewestDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\NewestView.cpp
# End Source File
# Begin Source File

SOURCE=.\nrutil.c
# End Source File
# Begin Source File

SOURCE=.\PlotWin.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileForm.cpp
# End Source File
# Begin Source File

SOURCE=.\ResFormView1.cpp
# End Source File
# Begin Source File

SOURCE=.\Results_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RGB_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\svbksb.c
# End Source File
# Begin Source File

SOURCE=.\svdcmp.c
# End Source File
# Begin Source File

SOURCE=.\svdfit.c
# End Source File
# Begin Source File

SOURCE=.\svdvar.c
# End Source File
# Begin Source File

SOURCE=.\TopoArray.cpp
# End Source File
# Begin Source File

SOURCE=.\TopoParams_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Array.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\constants.h
# End Source File
# Begin Source File

SOURCE=.\CraterID_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\CraterStats.h
# End Source File
# Begin Source File

SOURCE=.\Dialog_BandSelect.h
# End Source File
# Begin Source File

SOURCE=.\DIB.h
# End Source File
# Begin Source File

SOURCE=.\DisplayOptions_dlg.h
# End Source File
# Begin Source File

SOURCE=.\Displayscale_dialog.h
# End Source File
# Begin Source File

SOURCE=.\FileOperations.h
# End Source File
# Begin Source File

SOURCE=.\FileParams_Dialog.h
# End Source File
# Begin Source File

SOURCE=.\FileSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\Fitres_dlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageFile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Newest.h
# End Source File
# Begin Source File

SOURCE=.\NewestDoc.h
# End Source File
# Begin Source File

SOURCE=.\NewestView.h
# End Source File
# Begin Source File

SOURCE=.\nr.h
# End Source File
# Begin Source File

SOURCE=.\nrutil.h
# End Source File
# Begin Source File

SOURCE=.\PlotWin.h
# End Source File
# Begin Source File

SOURCE=.\ProfileForm.h
# End Source File
# Begin Source File

SOURCE=.\ResFormView1.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Results_dlg.h
# End Source File
# Begin Source File

SOURCE=.\RGB_Dialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TopoArray.h
# End Source File
# Begin Source File

SOURCE=.\TopoParams_dlg.h
# End Source File
# Begin Source File

SOURCE=.\ZoomWindow.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Newest.ico
# End Source File
# Begin Source File

SOURCE=.\res\Newest.rc2
# End Source File
# Begin Source File

SOURCE=.\res\NewestDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
