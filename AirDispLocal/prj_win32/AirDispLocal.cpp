
// AirDispLocal.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AirDispLocal.h"
#include "AirDispLocalDlg.h"
#include "msgdispatch.h"
#include "progress.h"
#include <imagehlp.h>

#pragma comment(lib, "DbgHelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern bool g_bHwEncStatus;
extern bool g_bHwEncSupport;
extern EMLangID g_emLanType;
CAirDispLocalDlg * g_dlg = NULL;
// CAirDispLocalApp

BEGIN_MESSAGE_MAP(CAirDispLocalApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAirDispLocalApp 构造

CAirDispLocalApp::CAirDispLocalApp()
{
	// 支持重新启动管理器
	// 需禁用重启管理器，避免未插入投屏器系统启动时自启AirDispLocal程序情形：即，
	// 重启或关机时，AirDispLocal程序未关闭，若启用快速启动功能，则AirDispLocal程序会在下次系统启动时自启
	//m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_bInstallYHFont = false;
}


// 唯一的一个 CAirDispLocalApp 对象

CAirDispLocalApp theApp;

//抓捕异常信息
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// 创建Dump文件
	HANDLE hDumpFile = CreateFileW(L"AirDispLocalException.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// 写入Dump文件内容
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;  
}

int CALLBACK EnumFontFamProc (ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam)
{
	CAirDispLocalApp* pApp = (CAirDispLocalApp*) lParam;
	
	if ( 0 == lstrcmp(lpelf->elfLogFont.lfFaceName, _T("微软雅黑"))
		|| 0 == lstrcmp(lpelf->elfLogFont.lfFaceName, _T("Microsoft YaHei")))
	{
		pApp->m_bInstallYHFont = true;
	}

	return 1;
}

// CAirDispLocalApp 初始化

BOOL CAirDispLocalApp::InitInstance()
{
	//只开启一个程序实例
	if ( !OnlyStartOne() )
	{
		TerminateProcess(GetCurrentProcess(), 0);
		return FALSE;		
	}

	//判断是否有权限调用拷屏库AVCollection.dll
	if (!IsAvAuthPassed())
	{
		::MessageBox(NULL, _T("无权限调用AVCollection.dll!"), NULL, MB_OK|MB_ICONERROR );
		TerminateProcess(GetCurrentProcess(), 0);
		return FALSE;	
	}

	//////////////////////注册新类名///////////////////////////
	// 获取窗口类信息。MFC默认的所有对话框的窗口类名为 #32770
	WNDCLASS wc;
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);
	// 改变窗口类名
	wc.lpszClassName = _T("NexTransmitterClass");
	// 注册新窗口类
	AfxRegisterClass(&wc);


	//关闭windows自动播放窗口
	CloseAutoPlayWindow();

	//设置系统重启、关闭时程序关闭顺序
	SetProcessShutdownParameters(0x100, SHUTDOWN_NORETRY);

	//设置进程优先级为最高
	SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);

	//获取winodws控制面板中“放大或缩小文本和其他项目”的值
	GetZoomScaleValue();

	//设置默认字体
	SetDefaultFont();

	//使用COM
	CoInitialize(NULL);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//抓捕异常文件
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash代码

	if( !IsOspInitd() )
	{

		BOOL bTelnet  = FALSE ;

#ifdef _DEBUG
		bTelnet = TRUE;
#endif

		OspInit( bTelnet, 2600);
		OspSetPrompt(DEF_TELNET_NAME);

#ifndef _DEBUG
		//OspTelAuthor("admin", "KedaKdv123");
#endif
		
	}

	CMsgDispatch::Init();

	CAirDispLocalDlg dlg;
	m_pMainWnd = &dlg;
	g_dlg = &dlg;
	::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );
	return FALSE;
}

int CAirDispLocalApp::ExitInstance()
{
	if ( TRUE == IsOspInitd())
	{
		OspQuit();
	}

	::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );

	return CWinApp::ExitInstance();
}

bool CAirDispLocalApp::IsAvAuthPassed()
{
	bool bRst = false;

	char szIn[Av_CheckAuth_MAX_LEN] = {0x01, 0x04, 0x08, 0x03, 0x01, 0x04, 0x08, 0x03, 0xff, 0x01, 0x04, 0x48, 0x04, 0x48, 0x04, 0x48, 
		0x04, 0x48, 0xff, 0x01, 0x04, 0x48, 0x01, 0x04, 0x08, 0x03, 0xff, 0x01, 0x04, 0x48, 0x04, 0x00};

	char szOut[Av_CheckAuth_MAX_LEN+1] = {0};

	AvMd5Encode(szOut, szIn);

	bRst = AvCheckAuth(szOut, Av_CheckAuth_MAX_LEN);

	return bRst;

}

void CAirDispLocalApp::GetZoomScaleValue()
{
	float dbZoomScaleWidth = 1.0;
	float dbZoomScaleHeight = 1.0;


	HDC desktopDc = CreateDC(_T("display"), NULL, NULL, NULL);
	// Get native resolution
	if (desktopDc != NULL)
	{
		int horizontalDPI = GetDeviceCaps( desktopDc, LOGPIXELSX );
		dbZoomScaleWidth = horizontalDPI / 96.0f;

		int verticalDPI = GetDeviceCaps( desktopDc, LOGPIXELSY );
		dbZoomScaleHeight = verticalDPI / 96.0f;

		DeleteDC(desktopDc);
	}

	if (dbZoomScaleWidth > 1.0)
	{
		g_fScaleWidth = dbZoomScaleWidth;
	}
	
	if (dbZoomScaleHeight > 1.0)
	{
		g_fScaleHeight = dbZoomScaleHeight;
	}
}

void CAirDispLocalApp::CloseAutoPlayWindow()
{
	//判断是否是win7系统，不是就返回
	OSVERSIONINFO osvi;    
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));    
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);    
	if (!GetVersionEx(&osvi))  
	{    
		return ;    
	} 
	if (osvi.dwMajorVersion != 6 || osvi.dwMinorVersion != 1)
	{
		return;
	}

	//win7系统关闭自动播放弹窗
	HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
	while (::IsWindow(hWndPrevious))   
	{   
		CString strTmp;
		CWnd *pWnd = CWnd::FromHandle(hWndPrevious);
		if (pWnd)
		{
			pWnd->GetWindowText(strTmp);
			if (strTmp == _T("自动播放") || strTmp == _T("AutoPlay"))
			{
				HWND hChildWndPrevious = ::GetWindow(hWndPrevious,GW_CHILD); 
				while (::IsWindow(hChildWndPrevious))   
				{   
					CWnd *pChildWnd = CWnd::FromHandle(hChildWndPrevious);
					if (pChildWnd)
					{
						pChildWnd->GetWindowText(strTmp);
						if (strTmp.Find(_T(DEF_TELNET_NAME)) != -1)
						{
							SendMessage(hWndPrevious, WM_CLOSE, NULL, NULL);
							return;
						}
					}
					//   继续寻找下一个窗口   
					hChildWndPrevious  = ::GetWindow(hChildWndPrevious,GW_HWNDNEXT); 
				}   
			}
		}
		//   继续寻找下一个窗口   
		hWndPrevious  = ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
	}   
}

void CAirDispLocalApp::SetDefaultFont()
{
	HDC hdc=::GetDC(NULL);
	int nSt = ::EnumFontFamilies (hdc, NULL, (FONTENUMPROC) EnumFontFamProc,
		(LPARAM)this);

	if ( !m_bInstallYHFont )
	{
		sprintf(g_achDefaultFont, "宋体");
	}
	else
	{
		LANGID langID = GetSystemDefaultLangID();
		if ( langID != 0x0804 )//非中文系统
		{
			sprintf(g_achDefaultFont, "Microsoft YaHei");
		}
	}
}


BOOL OnlyStartOne()
{
	HANDLE  hSem = CreateSemaphore(NULL, 1, 1, AfxGetApp()->m_pszAppName);   

	//信号量存在，则程序已有一个实例运行   
	if (GetLastError() == ERROR_ALREADY_EXISTS)   
	{  		
		//关闭信号量句柄   
		CloseHandle(hSem);  

		LPCWSTR className = _T("NexTransmitterClass");
		LPCWSTR windName = NULL;

		HWND hWnd = ::FindWindow( className, windName );
		if ( IsWindow( hWnd ) )
		{
			::ShowWindow( hWnd, SW_SHOW );
			::SetForegroundWindow(hWnd);   
		}
		
		// 寻找先前实例的主窗口   
		/*HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
		while (::IsWindow(hWndPrevious))   
		{   
			//   检查窗口是否有预设的标记?   
			//   有，则是我们寻找的主窗   
			if (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
			{    		 
				//BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
				//(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 

				//   主窗口已最小化，则恢复其大小   
				if (::IsIconic(hWndPrevious)) 				
					::ShowWindow(hWndPrevious,SW_RESTORE);   

				HWND hdl = GetForegroundWindow();
				if (hWndPrevious !=  hdl )
				{   					
					::ShowWindow(hWndPrevious,SW_RESTORE); 
					::SetForegroundWindow(hWndPrevious);
				}

				return  FALSE;   
			}   
			//   继续寻找下一个窗口   
			hWndPrevious  = ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
		}  */
		//   前一实例已存在，但找不到其主窗   
		//   退出本实例   
		return   FALSE;   
	} 
	return TRUE;
}


/*
API void help()
{
	 OspPrintf(TRUE,FALSE,"\nprt nLevel:打印级别为nLevel的消息；消息级别 0-4，\n \
	 0为关闭打印，默认输入prt即为关闭打印\n \
	 1为打印命令消息\n \
	 2为打印发送视频码流消息\n \
	 3为打印发送音频码流消息\n \
	 4为打印所有消息");
	 OspPrintf(TRUE,FALSE,"\nshowdev:显示hid设备信息");
	 OspPrintf(TRUE,FALSE,"\nshowsize:显示Datalist大小");
	 OspPrintf(TRUE,FALSE,"\nshowver:显示版本号");
	 OspPrintf(TRUE,FALSE,"\nmdver:显示媒控库版本号");
	 OspPrintf(TRUE,FALSE,"\ndatastatus:显示数据是否阻塞");
	 OspPrintf(TRUE,FALSE,"\ncpuadjust:是否启用CPU动态调整");
	 OspPrintf(TRUE,FALSE,"\nscreen byScreen:选择屏幕,从1开始\n");
     OspPrintf(TRUE,FALSE,"\sethwenc:开启(1)|关闭(0) 硬编\n");
     OspPrintf(TRUE,FALSE,"\setlang:自动(0)|中文(1)|英文(2) 设置界面语言\n");
}

API void prt( u8 byLevel )
{
	CPrint::Print( byLevel );
	OspPrintf(TRUE,FALSE,"\nbyLevel:%d", byLevel);
}

API void showdev()
{
	if (g_dlg)
	{
		THidDevice tHidDeviceTmp = g_dlg->GetHidDevie(HID_TYPE_VIDEO);
		if (!tHidDeviceTmp.hndHidDevice)
		{
			OspPrintf(TRUE,FALSE,"\n未找到HID设备");
			return;
		}

		for (int i=HID_TYPE_VIDEO; i<HID_TYPE_NUM; i++)
		{
			THidDevice tHidDevice = g_dlg->GetHidDevie((HID_TYPE)i);
			OspPrintf(TRUE,FALSE,"\nHID device info:hndHidDevice:%d,nOverlapped:%d,uGetReportTimeout:%d,uSetReportTimeout:%d,wInReportBufferLength:%d,wOutReportBufferLength:%d\n",
				tHidDevice.hndHidDevice,tHidDevice.nOverlapped,tHidDevice.uGetReportTimeout,tHidDevice.uSetReportTimeout,
				tHidDevice.wInReportBufferLength,tHidDevice.wOutReportBufferLength);
		
		}
	}
}

API void showsize()
{
	OspPrintf(TRUE,FALSE,"Video:DataList size:%d\n", g_dlg->GetVideoDataList()->Size() );
	OspPrintf(TRUE,FALSE,"Audio:DataList size:%d\n", g_dlg->GetAudioDataList()->Size() );
}

API void mdver()
{
	if (g_dlg)
	{
		char achMdVer[MAX_PATH] = {0};
		g_dlg->GetEncode().GetMeidaLibVersion(achMdVer);
		OspPrintf(TRUE,FALSE,"媒控库版本:%s\n", achMdVer );
	}
}

API void showver()
{
	s8 achVersion[MAX_VER_LEN] = {0};
	CAboutDlg::GetBuildVersion(achVersion);
	OspPrintf(TRUE,FALSE,"Current version:V%s\n", achVersion );
}

API void datastatus()
{
	if (g_dlg)
	{
		OspPrintf(TRUE,FALSE,"是否数据阻塞:%d\n", g_dlg->m_bDataBlock );
	}
}

API void cpuadjust()
{
	if (g_dlg)
	{
		BOOL32 bStatus = TRUE;
		bool bRst = g_dlg->GetEncode().GetCpuAdjustStatus(bStatus);
		if ( bRst )
		{
			OspPrintf(TRUE,FALSE,"启用CPU动态调整(默认1,低电量0):%d\n", bStatus );
		}
	}
}

API void screen( u32 byScreen )
{
	if (g_dlg)
	{
		g_dlg->GetEncode().SelectCaptureScreen( byScreen );
	}
}*/

//API void sethwenc( BOOL32 bEnable )
//{
//    if (g_dlg)
//    {
//        // 硬编码码率为4M，软编码码率为2M
//        // 是否支持硬编码
//        if (g_bHwEncSupport)
//        {
//            g_dlg->GetEncode().SetEnableHwEnc( bEnable );
//
//            if (bEnable)
//            {
//                if (g_bHwEncStatus)
//                {
//                    return;
//                }
//                else
//                {
//                    TVideoEncParam tVideoEncParam;
//                    memset(&tVideoEncParam, 0, sizeof(TVideoEncParam));
//                    g_dlg->GetEncode().GetVideoEncParam(tVideoEncParam);
//                    tVideoEncParam.m_wBitRate = /*1536*/4096;
//                    tVideoEncParam.m_wMinBitRate = 4096;
//                    g_dlg->GetEncode().SetVideoEncParam(tVideoEncParam);
//                    g_bHwEncStatus = true;
//                    OspPrintf(TRUE, FALSE, "切换至硬编码状态\n");
//                }
//            }
//            else
//            {
//                if (g_bHwEncStatus)
//                {
//                    TVideoEncParam tVideoEncParam;
//                    memset(&tVideoEncParam, 0, sizeof(TVideoEncParam));
//                    g_dlg->GetEncode().GetVideoEncParam(tVideoEncParam);
//                    tVideoEncParam.m_wBitRate = /*1536*/2048;
//                    tVideoEncParam.m_wMinBitRate = 2048;
//                    g_dlg->GetEncode().SetVideoEncParam(tVideoEncParam);
//                    g_bHwEncStatus = false;
//                    OspPrintf(TRUE, FALSE, "切换至软编码状态\n");
//                }
//                else
//                {
//                    return;
//                }
//            }
//        }
//        else
//        {
//            //不支持硬编硬解
//            OspPrintf(TRUE, FALSE, "不支持硬编硬解\n");
//            return;
//        }
//    }
//}
//
//API void setlang(u32 byLangID)
//{
//    if (g_dlg)
//    {
//        CString strIniFilePath = g_dlg->GetIniFilePath();
//        if (strIniFilePath.IsEmpty())
//        {
//            return;
//        }
//
//        if (byLangID >= 0)
//        {
//            switch (byLangID)
//            {
//            case enumUILangAUTO:
//                {
//                    WritePrivateProfileString(_T("UILangInfo"), _T("Language"), _T("AUTO"), strIniFilePath);
//                    OspPrintf(TRUE, FALSE, "界面语言为自动模式，需重新插拔投屏器\n");
//                }
//                break;
//            case enumUILangCHN:
//                {
//                    WritePrivateProfileString(_T("UILangInfo"), _T("Language"), _T("CHN"), strIniFilePath);
//                    OspPrintf(TRUE, FALSE, "界面语言为中文模式，需重新插拔投屏器\n");
//                }
//                break;
//            case enumUILangENG:
//                {
//                    WritePrivateProfileString(_T("UILangInfo"), _T("Language"), _T("ENG"), strIniFilePath);
//                    OspPrintf(TRUE, FALSE, "界面语言为英文模式，需重新插拔投屏器\n");
//                }
//                break;
//            default:   
//                break;
//            }
//        }
//    }
//}
