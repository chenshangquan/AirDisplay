
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#define WM_TRAY_NOTIFYICON      (WM_USER+1001)
#define WM_OPENHIDDEV_SUCCESS   (WM_USER+1002)
#define WM_VOLUMECTRL_CHANGE    (WM_USER+1003)
#define WM_PCSLEEP_MSG          (WM_USER+1004)
#define WM_PCSLEEPRESUME_MSG    (WM_USER+1005)
#define WM_PCREBOOTCLOSE_MSG    (WM_USER+1006)
#define WM_PPT_PLAY_MSG         (WM_USER+1007)
#define WM_POWER_STATUS_MSG     (WM_USER+1008)

//CMainDlg Message
enum EMWMCMainDlgSegs
{
    WM_REGISTER_SUCCEED = WM_USER+1020,
    WM_VIEW_QK_SHARE_QUIT,
    WM_RECV_IMIX_SOCKET,
    WM_VIEW_QK_SHARE_START,
};
//#define WM_REGISTER_SUCCEED     (WM_USER+1020)
//#define WM_VIEW_QK_SHARE_OK     (WM_USER+1021)
//#define WM_RECV_IMIX_SOCKET     (WM_USER+1022)
//#define WM_VIEW_QK_SHARE_START  (WM_USER+1023)

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include "kdvtype.h"

#include "TransparentBaseDlg.h"
#include "TransparentBtn.h"
#include "TransparentEdit.h"
#include "transparentprogressctrl.h"
#include "uicommon.h"
#include "print.h"

#define _WIN32_WINNT 0x0600

//telnet默认提示名称
#define  DEF_TELNET_NAME "NexTransmitter"

//设置默认音频播放设备
#define  DEF_AUDIO_NAME _T("NexTransmitter")

#define TOUCH_VERSION_ID	   "6.0.0.1.0."
#define MAX_VER_LEN            38

#define MAX_NAME_LEN           32  //最大的名字长度
#define AID_AIRDIS_APP         62
#define AID_SIPTOOL_APP        53

//全局定义
extern s8 g_achDefaultFont[MAX_PATH];
#define DEFAULT_FONT_COLOR Color(76,76,76)
#define TIP_DES_FONT_COLOR Color(163,163,163)
#define UPGRADE_FONT_COLOR Color(0,127,192)

//winodws控制面板中“放大或缩小文本和其他项目”的值
extern float g_fScaleWidth; //水平方向
extern float g_fScaleHeight;//竖直方向
#define MULX(x) (int)((x) * g_fScaleWidth)
#define MULY(y) (int)((y) * g_fScaleHeight)

#define HID_MODE_SYNC  0  //hid打开方式，同步
#define HID_MODE_ASYNC 1  //hid打开方式，异步

typedef enum _EnumPptStatus
{
	EM_PPT_NO_PLAY  = 0,         // ppt未播放状态
	EM_PPT_PLAYING		         // ppt播放状态	
}EnumPptStatus;

enum EMLangID
{
    enumLangIdCHN   = (u8)0,    //简体中文
    enumLangIdENG   = (u8)1     //English
};

enum EMUILangID
{
    enumUILangAUTO   = (u8)0,    //自动识别
    enumUILangCHN    = (u8)1,    //中文界面
    enumUILangENG    = (u8)2     //英文界面
};
