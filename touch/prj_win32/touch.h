
// touch.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


#include "setupapi.h"
#include "dbt.h"
extern "C"
{
//#include "hidsdi.h"
}

//#pragma comment(lib, "hid.lib")
#pragma comment(lib, "SetupAPI.lib")

#include "AVCollect.h"
#pragma comment(lib, "AVCollection.lib")
// CtouchApp:
// 有关此类的实现，请参阅 touch.cpp
//

class CtouchApp : public CWinApp
{
public:
	CtouchApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	bool IsAvAuthPassed();     //是否有权限调用拷屏库AVCollection.dll
	void GetZoomScaleValue();  //获取winodws控制面板中“放大或缩小文本和其他项目”的值
	void CloseAutoPlayWindow();//关闭windows自动播放窗口
	void SetDefaultFont();     //设置默认字体

	DECLARE_MESSAGE_MAP()

public:
	bool m_bInstallYHFont;     //是否安装了微软雅黑
};

BOOL OnlyStartOne();

extern CtouchApp theApp;

/*
//打印信息
API void help();

API void prt( u8 byLevel );

API void showdev();

API void showsize();

API void mdver();

API void showver();

API void datastatus();

API void cpuadjust();

API void screen( u32 byScreen );

API void sethwenc( BOOL32 bEnable );

API void setlang( u32 byLangID );
*/