
;---------------------------全局编译脚本预定义的常量-----------------------------------------------------
!define OUTFILE_NAME "NexTransmitter.exe"
 ;安装图标的路径名字
!define MUI_ICON "touch.ico"
!define PRODUCT_DIR_REGKEY "Software\Kedacom\NexTransmitter"
!define PRODUCT_DIR_REGDLL "Software\Microsoft\Windows NT\CurrentVersion\Drivers32"

;tservice.exe实现开机运行的注册表位置及填入的值
!define PRODUCT_DIR_REGSERVER "Software\Microsoft\Windows\CurrentVersion\Run"
!define TSERVICE_AUTO_RUN "$\"$LOCALAPPDATA\NexTransmitter\tservice.exe$\" hide"

;版本号,注意与touch版本号保持一致
!define PRODUCT_VER 6.0.0.1.0
!define /date PRODUCT_DATE %Y%m%d
!define PRODUCT_VERSION "${PRODUCT_VER}.${PRODUCT_DATE}"

;dll信息
!define VIDC_TPH4        "vidc.tph4"
!define MSACM_KDMP3      "msacm.kdmp3"
!define MSACM_KDMP3_ACM  "msacm.kdmp3.acm"

!define TPH4_DLL         "tph4.dll"
!define KDMP3_ACM        "kdmp3.acm"

 
;---------------------------设置软件压缩类型（也可以通过外面编译脚本控制）------------------------------------
SetCompressor lzma
SetCompress force
XPStyle on

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "nsWindows.nsh"
!include "MUI.nsh"
!include "WordFunc.nsh"

!define MUI_CUSTOMFUNCTION_GUIINIT onGUIInit

;自定义页面
Page custom WelcomePage
; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese" ;注释此举就会有边框 保留就会无边框

;-------------------------公司信息-----------------------------------------------------

!define PRODUCT_PUBLISHER "苏州科达科技股份有限公司"
!define PRODUCT_NAME "NexTransmitter"
!define PRODUCT_DESC "NexTransmitter Setup"

VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey /LANG=2052 "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey /LANG=2052 "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey /LANG=2052 "FileDescription" "${PRODUCT_DESC}"
VIAddVersionKey /LANG=2052 "FileVersion" "${PRODUCT_VERSION}"
VIAddVersionKey /LANG=2052 "ProductVersion" "${PRODUCT_VERSION}"
VIAddVersionKey /LANG=2052 "LegalCopyright" "版权所有 (C) 2017 ${PRODUCT_PUBLISHER}"
;------------------------------------------------------MUI 现代界面定义以及函数结束------------------------

;应用程序显示名字
Name "NexTransmitter"
;应用程序输出路径
OutFile "${OUTFILE_NAME}"
InstallDir "$LOCALAPPDATA\NexTransmitter"
;获得管理员权限
RequestExecutionLevel user
;去掉安装包自身的CRC校验，默认开启
CRCCheck off

Var old_ver
Var new_ver
Var info

Function .onInit
    Call onOnlyStartOne
	ClearErrors
	;读取版本号,没有读到认为未安装
	ReadRegStr $old_ver HKCU "${PRODUCT_DIR_REGKEY}" "Version"
	IfErrors 0 +2
	  Return
    StrCpy $new_ver ${PRODUCT_VERSION}
	;版本比较,有新版本则升级
	${VersionCompare} $new_ver $old_ver $0
	;MessageBox MB_OK "比较结果:$0"
	${if} $0 == 0
	    Call isFileNoLack
	    Pop $0
	    ${If} $0 == "true"  
		   ;注册dll  解决系统升级导致dll值被删的情况
	       Call RegisterDll
           Call OpenTouch
		   Call OpenService
           Call onClose
		   Abort
        ${Else}  
           Call CloseService
		   sleep 100
	       Delete "$INSTDIR\*.*"
		   Return
        ${EndIf}  
	${Else}
	    Call CloseService
		sleep 100
	    Delete "$INSTDIR\*.*"
		Return
	${EndIf}
FunctionEnd

Function onGUIInit
    ;消除边框
    System::Call `user32::SetWindowLong(i$HWNDPARENT,i${GWL_STYLE},0x9480084C)i.R0`
    ;隐藏一些既有控件
    GetDlgItem $0 $HWNDPARENT 1034
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1035
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1036
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1037
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1038
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1039
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1256
    ShowWindow $0 ${SW_HIDE}
    GetDlgItem $0 $HWNDPARENT 1028
    ShowWindow $0 ${SW_HIDE}
FunctionEnd

Function isFileNoLack
    ${If} ${FileExists} "$INSTDIR\touch.exe"
    ${AndIf} ${FileExists} "$INSTDIR\tservice.exe"
    ${AndIf} ${FileExists} "$INSTDIR\AVCollection.dll"
    ${AndIf} ${FileExists} "$INSTDIR\asflib.dll"
    ${AndIf} ${FileExists} "$INSTDIR\h264enc_x.dll"
    ${AndIf} ${FileExists} "$INSTDIR\kdvmedianetdll.dll"
	${AndIf} ${FileExists} "$INSTDIR\libkdcrypto-1_1.dll"
	${AndIf} ${FileExists} "$INSTDIR\libkdvsrtp.dll"
	${AndIf} ${FileExists} "$INSTDIR\mediasdkvc10.dll"
	${AndIf} ${FileExists} "$INSTDIR\mediawrapper.dll"
	${AndIf} ${FileExists} "$INSTDIR\ospdll.dll"
	${AndIf} ${FileExists} "$INSTDIR\kdimg.dll"
	${AndIf} ${FileExists} "$INSTDIR\tph4.dll"
	${AndIf} ${FileExists} "$INSTDIR\kdmp3.acm"
	${AndIf} ${FileExists} "$INSTDIR\kdaudproc.dll"
	${AndIf} ${FileExists} "$INSTDIR\mfc100u.dll"
	${AndIf} ${FileExists} "$INSTDIR\msvcp100.dll"
	${AndIf} ${FileExists} "$INSTDIR\msvcr100.dll"
	;硬编码新增库
	${AndIf} ${FileExists} "$INSTDIR\kdaudcodec.dll"
	${AndIf} ${FileExists} "$INSTDIR\HwCodecWrapper.dll"
	${AndIf} ${FileExists} "$INSTDIR\IntelHwWrapper.dll"
	;touch配置文件
	${AndIf} ${FileExists} "$INSTDIR\touch.ini"
	    Push "true"
	${Else}
	    Push "false"
	${EndIf}
FunctionEnd

Function OpenTouch
    ;双击投屏器盘符，可以启动touch程序，显示已隐藏的窗口
    ;FindProcDLL::FindProc "touch.exe"
    ;Pop $R0
    ;${If} $R0 == 0
		ExecShell open "$INSTDIR\touch.exe"
    ;${EndIf}
FunctionEnd

Function OpenService
    FindProcDLL::FindProc "tservice.exe"
    Pop $R0
    ${If} $R0 == 0
		ExecShell open "$INSTDIR\tservice.exe"
    ${EndIf}
FunctionEnd

Function CloseService
   FindProcDLL::FindProc "tservice.exe"
   Pop $R0
   ${If} $R0 != 0
	    KillProcDLL::KillProc "tservice.exe"
   ${Endif}
FunctionEnd

;音视频编码的dll注册函数
Function RegisterDll
    ReadRegStr $info HKCU "${PRODUCT_DIR_REGDLL}" "${VIDC_TPH4}"
	IfErrors 0 +2
	  WriteRegStr HKCU "${PRODUCT_DIR_REGDLL}" "${VIDC_TPH4}" "${TPH4_DLL}"
	ReadRegStr $info HKCU "${PRODUCT_DIR_REGDLL}" "${MSACM_KDMP3}" 
	IfErrors 0 +2
	  WriteRegStr HKCU "${PRODUCT_DIR_REGDLL}" "${MSACM_KDMP3}" "${KDMP3_ACM}"
	ReadRegStr $info HKCU "${PRODUCT_DIR_REGDLL}" "${MSACM_KDMP3_ACM}" 
	IfErrors 0 +2
	  WriteRegStr HKCU "${PRODUCT_DIR_REGDLL}" "${MSACM_KDMP3_ACM}" "${KDMP3_ACM}"
    Return 
FunctionEnd

Function MAINInstall32
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "touch.exe"
  File "tservice.exe"
  File "AVCollection.dll"
  File "asflib.dll"
  File "h264enc_x.dll"
  File "kdvmedianetdll.dll"
  File "libkdcrypto-1_1.dll"
  File "libkdvsrtp.dll"
  File "mediasdkvc10.dll"
  File "mediawrapper.dll"
  File "ospdll.dll"
  File "kdimg.dll"
  File "tph4.dll"
  File "kdmp3.acm"
  File "kdaudproc.dll"
  File "mfc100u.dll"
  File "msvcp100.dll"
  File "msvcr100.dll"
  ;硬编码新增库
  File "kdaudcodec.dll"
  File "HwCodecWrapper.dll"
  File "IntelHwWrapper.dll"
  ;touch配置文件
  File "touch.ini"
  
  Call onComplete
FunctionEnd

;关闭窗口
Function onClose
    FindProcDLL::FindProc "${OUTFILE_NAME}"
    Pop $R0
    ${If} $R0 != 0
    KillProcDLL::KillProc "${OUTFILE_NAME}"
    ${EndIf}
FunctionEnd

;只能启动一个
Function onOnlyStartOne
    ;创建互斥防止重复运行  
     System::Call 'kernel32::CreateMutexA(i 0, i 0, t"Winsnap_installer") i .r1 ?e'  
     Pop $R0  
     StrCmp $R0 0 +2  
     Abort  
FunctionEnd

;点击最后完成
Function onComplete
      ;注册版本号
      WriteRegStr HKCU "${PRODUCT_DIR_REGKEY}" "Version" "${PRODUCT_VERSION}"
	  ;实现tservice.exe开机运行
	  ReadRegStr $info HKCU "${PRODUCT_DIR_REGSERVER}" "NexTransmitter"
	  IfErrors 0 +2
	    WriteRegStr HKCU "${PRODUCT_DIR_REGSERVER}" "NexTransmitter" "${TSERVICE_AUTO_RUN}"
      ;注册dll
	  Call RegisterDll
	  ;去掉防火墙弹窗
	  nsExec::Exec '"cmd.exe" /c netsh advfirewall firewall Delete rule name="allow touch"'
      nsExec::Exec '"cmd.exe" /c netsh advfirewall firewall add rule name="allow touch" dir=in action=allow program="$INSTDIR\touch.exe"'
	  ;运行程序
      ExecShell open "$INSTDIR\touch.exe"
	  sleep 1000
      ExecShell open "$INSTDIR\tservice.exe"
FunctionEnd

Function WelcomePage
    GetFunctionAddress $0 MAINInstall32
    BgWorker::CallAndWait
FunctionEnd

Section SEC
SectionEnd

Section -Post
SectionEnd
