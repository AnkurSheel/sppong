############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "MyPong"
!define COMP_NAME "BGI"
!define WEB_SITE "http://www.gamedev.net/blog/1369-speedruns-journal/"
!define VERSION "00.00.00.07"
!define COPYRIGHT "AnkurSheel© 2011"
!define DESCRIPTION "Application"
!define INSTALLER_NAME "C:\Users\SpeedRun\Projects\sppong\Setup\setup.exe"
!define MAIN_APP_EXE "Main.exe"
!define INSTALL_TYPE "SetShellVarContext all"
!define REG_ROOT "HKLM"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

!define REG_START_MENU "Start Menu Folder"

var SM_Folder

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\MyPong"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!insertmacro MUI_PAGE_DIRECTORY

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "MyPong"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################

Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
SetOutPath "$INSTDIR"
File "C:\Users\SpeedRun\Projects\sppong\Retail\AI.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Base.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\BasicXSLT.xsl"
File "C:\Users\SpeedRun\Projects\sppong\Retail\fmodex.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\fmodexL.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Game.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\GameBase.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\GraphicsEngine.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\InternetExplorerJavascriptViewer.html"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Log.txt"
File "C:\Users\SpeedRun\Projects\sppong\Retail\log.xml"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Main.exe"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Sound.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\Utilities.dll"
File "C:\Users\SpeedRun\Projects\sppong\Retail\zlibwapi.dll"
SetOutPath "$INSTDIR\resources"
File "C:\Users\SpeedRun\Projects\sppong\Retail\resources\resources.zip"
SetOutPath "$INSTDIR\resources\Sounds\SFX"
File "C:\Users\SpeedRun\Projects\sppong\Retail\resources\Sounds\SFX\collision1.wav"
File "C:\Users\SpeedRun\Projects\sppong\Retail\resources\Sounds\SFX\collision2.wav"
File "C:\Users\SpeedRun\Projects\sppong\Retail\resources\Sounds\SFX\win.wav"
SetOutPath "$INSTDIR\resources\Sounds\Music"
File "C:\Users\SpeedRun\Projects\sppong\Retail\resources\Sounds\Music\mainmenu.mid"
SectionEnd

######################################################################

!define NEVER_UNINSTALL
!include FontRegAdv.nsh
!include FontName.nsh
!include ZipDll.nsh

#!define FontBackup Reg\key\To\Backup\Fonts\entries\To

Section - "Fonts"
StrCpy $FONT_DIR $FONTS
!insertmacro InstallTTF "C:\Users\SpeedRun\Projects\sppong\Media\Fonts\VLADIMIR.TTF"
SendMessage ${HWND_BROADCAST} ${WM_FONTCHANGE} 0 0 /TIMEOUT=5000
SectionEnd

######################################################################

Section -Icons_Reg
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
CreateDirectory "$SMPROGRAMS\$SM_Folder"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!insertmacro MUI_STARTMENU_WRITE_END
!endif

!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\MyPong"
CreateShortCut "$SMPROGRAMS\MyPong\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\MyPong\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\MyPong\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
${INSTALL_TYPE}
Delete "$INSTDIR\AI.dll"
Delete "$INSTDIR\Base.dll"
Delete "$INSTDIR\BasicXSLT.xsl"
Delete "$INSTDIR\fmodex.dll"
Delete "$INSTDIR\fmodexL.dll"
Delete "$INSTDIR\Game.dll"
Delete "$INSTDIR\GameBase.dll"
Delete "$INSTDIR\GraphicsEngine.dll"
Delete "$INSTDIR\InternetExplorerJavascriptViewer.html"
Delete "$INSTDIR\Log.txt"
Delete "$INSTDIR\log.xml"
Delete "$INSTDIR\Main.exe"
Delete "$INSTDIR\Sound.dll"
Delete "$INSTDIR\Utilities.dll"
Delete "$INSTDIR\zlibwapi.dll"
Delete "$INSTDIR\resources\resources.zip"
Delete "$INSTDIR\resources\Sounds\SFX\collision1.wav"
Delete "$INSTDIR\resources\Sounds\SFX\collision2.wav"
Delete "$INSTDIR\resources\Sounds\SFX\win.wav"
Delete "$INSTDIR\resources\Sounds\Music\mainmenu.mid"
 
RmDir "$INSTDIR\resources\Sounds\Music"
RmDir "$INSTDIR\resources\Sounds\SFX"
RmDir "$INSTDIR\resources\Sounds\"
RmDir "$INSTDIR\resources"
 
Delete "$INSTDIR\uninstall.exe"
!ifdef WEB_SITE
Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR"

!ifndef NEVER_UNINSTALL
Delete "$FONTS\VLADIMIR.TTF"
 
!endif

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\$SM_Folder"
!endif

!ifndef REG_START_MENU
Delete "$SMPROGRAMS\MyPong\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\MyPong\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\MyPong\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\MyPong"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

