!define APP_NAME "SpBreakOut"
!define PRODUCT_VERSION "1.0"
!define VERSION "00.00.01.0"
!define WEB_SITE "http://www.ankursheel.com/"
!define DESCRIPTION "Application"
!define INSTALLER_NAME "setup_v${PRODUCT_VERSION}.exe"
!define MAIN_APP_EXE "BreakoutMain.exe"
!define INSTALL_TYPE "SetShellVarContext all"
!define REG_ROOT "HKLM"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
!define REG_START_MENU "Start Menu Folder"

######################################################################
VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${PRODUCT_VERSION}"

######################################################################

SetCompressor ZLIB
;Request application privileges for Windows Vista, 7, 8
RequestExecutionLevel admin 
######################################################################

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!define MUI_WELCOMEPAGE_TITLE "This Will Install ${APP_NAME} (v${PRODUCT_VERSION}) on your computer"
!insertmacro MUI_PAGE_WELCOME
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY

var SM_Folder

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${APP_NAME}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

; Instfiles page
!insertmacro MUI_PAGE_INSTFILES

; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
!insertmacro MUI_LANGUAGE "English"
; MUI end ------

######################################################################

Name "${APP_NAME} v${PRODUCT_VERSION}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "C:\Games\SpBreakout"

######################################################################

AutoCloseWindow false
ShowInstDetails hide
ShowUnInstDetails show

Section "Main (Required)" SEC01
	${INSTALL_TYPE}
	SectionIn RO
	SetOverwrite ifnewer
	SetOutPath "$INSTDIR"
	File /r /x log.* "..\Retail\*"
	; File "..\Retail\AI.dll"
	; File "..\Retail\Base.dll"
	; File "..\Retail\GameBase.dll"
	; File "..\Retail\GraphicsEngine.dll"
	; File "..\Retail\Physics.dll"
	; File "..\Retail\Sound.dll"
	; File "..\Retail\Utilities.dll"
	; File "..\Retail\zlibwapi.dll"
	; File "..\Retail\Options.ini"
	; File "..\Retail\Breakout.dll"
	; File "..\Retail\BreakoutMain.exe"
	; SetOutPath "$INSTDIR\Media"
	; File "..\Retail\Media\PlayerOptions.xml"
	; File "..\Retail\Media\Assets.zip"
SectionEnd

######################################################################

; Shortcuts
Section -Icons_Reg
	!ifdef REG_START_MENU
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateDirectory "$SMPROGRAMS\$SM_Folder"
	CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
	CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
	!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Var Error

!include x64.nsh

Section "Visual Studio 2010 Re-distributable (Recommended)" SEC02
  ${INSTALL_TYPE}
  
	${If} ${RunningX64}
        ReadRegStr $0 HKLM "SOFTWARE\Microsoft\VisualStudio\10.0\VC\VCRedist\x64" "Installed"
        ${If} $0 == 0
			SetOutPath "$TEMP"
			File /oname=vcredist.exe "vcredist_x64.exe"
			StrCpy $1 1
		${EndIf}
	${Else}
        ReadRegStr $0 HKLM "SOFTWARE\Microsoft\VisualStudio\10.0\VC\VCRedist\x86" "Installed"
        ${If} $0 == 0
			SetOutPath "$TEMP"
			File /oname=vcredist.exe "vcredist_x86.exe"
			StrCpy $1 1
		${EndIf}
	${EndIf}

	${IF} $1 == 1
		DetailPrint "Installing Visual Studio 2010 Re-distributable..."
		ExecWait '"$TEMP\vcredist.exe" /Q' $Error
		DetailPrint "Finished Installing Visual Studio 2010 Re-distributable"

		Delete "$TEMP\vcredist.exe"
		SetOutPath "$INSTDIR"
	${EndIf}
SectionEnd
 
Section "DirectX (Recommended)" SEC03
	${INSTALL_TYPE}
	; SectionIn RO
	# NSISdl::download http://download.microsoft.com/download/1/7/1/1718CCC4-6315-4D8E-9543-8E28A4E18C4C/dxwebsetup.exe $TEMP\dxwebsetup.exe
	SetOutPath "$TEMP"
	File "dxwebsetup.exe"
	DetailPrint "Running DirectX Setup..."
	ExecWait '"$TEMP\dxwebsetup.exe" /Q' $Error
	DetailPrint "Finished DirectX Setup"

	Delete "$TEMP\dxwebsetup.exe"
	SetOutPath "$INSTDIR"

	; Shortcuts
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
	SetOutPath "$INSTDIR"
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

	!ifdef WEB_SITE
		WriteIniStr "$INSTDIR\Ankur Sheel's Website.url" "InternetShortcut" "URL" "${WEB_SITE}"
		CreateShortCut "$SMPROGRAMS\$SM_Folder\Ankur Sheel's Website.lnk" "$INSTDIR\Ankur Sheel's Website.url"
	!endif
	!insertmacro MUI_STARTMENU_WRITE_END
	!endif
SectionEnd

Section -Post
	WriteUninstaller "$INSTDIR\uninstall.exe"
	WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
	; WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

	!ifdef WEB_SITE
		WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
	!endif
SectionEnd

######################################################################
; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "Main"
!insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "Checks And Installs Visual Studio 2010 Re-distributable.\
(Do not uncheck unless you are sure you have the Visual Studio 2010 Re-distributable installed)\"
!insertmacro MUI_DESCRIPTION_TEXT ${SEC03} "Checks And Installs the latest Directx runtime.\
Please make sure you have internet access.\
(Do not uncheck unless you are sure you have the latest DirectX installed)\"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

######################################################################

Section Uninstall
${INSTALL_TYPE}
	Delete "$INSTDIR\*.*"
	Rmdir /r "$INSTDIR\Media"

	Delete "$INSTDIR\uninstall.exe"
	!ifdef WEB_SITE
	Delete "Ankur Sheel's Website.url"
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
	Delete "$SMPROGRAMS\$SM_Folder\Ankur Sheel's Website.lnk"
	!endif
	Delete "$DESKTOP\${APP_NAME}.lnk"

	RmDir "$SMPROGRAMS\$SM_Folder"
	!endif

	DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
	DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
	SetAutoClose true
SectionEnd

######################################################################
Function UninstallMe
	Delete "$INSTDIR\*.*"
	Rmdir /r "$INSTDIR\Media"

	Delete "$INSTDIR\uninstall.exe"
	!ifdef WEB_SITE
	Delete "Ankur Sheel's Website.url"
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
	Delete "$SMPROGRAMS\$SM_Folder\Ankur Sheel's Website.lnk"
	!endif
	Delete "$DESKTOP\${APP_NAME}.lnk"

	RmDir "$SMPROGRAMS\$SM_Folder"
	!endif

	DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
	DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
FunctionEnd

Function .onInit

	ReadRegStr $R0 HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
	"UninstallString"
	StrCmp $R0 "" done

	MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
	"${APP_NAME} is already installed. $\n$\nClick `OK` to remove the \
	previous version or `Cancel` to cancel this upgrade." \
	IDOK uninst
	Abort

	;Run the uninstaller
	uninst:
	ClearErrors
	Call UninstallMe

	done:

FunctionEnd

Function un.onUninstSuccess
	HideWindow
	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
	Abort
FunctionEnd

