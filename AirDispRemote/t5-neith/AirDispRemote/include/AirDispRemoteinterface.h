/** @defgroup AirDispRemote调用AirDispRemotelib的公共接口 
 *  @version V1.0.0
 *  @author  叶良平
 *  @date    2019.4.10
 */
#pragma once

#include "AirDispRemotelib.h"

class CAirDispRemoteInterface
{
public:
    /** 获取接口指针 */
    static CAirDispRemoteInterface* GetCommIF();
    /** 销毁接口指针 */
    void DestroyCommIF();

public:
    /** 获取内嵌的窗口句柄
	*   @return HWND 返回窗口句柄 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/** 创建会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void CreateSession();

	/** 销毁会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void DesdroySession();

    /**
	*   登录Sip
	*/ 
    u16 SocketConnect( u32 dwIp, s8* szUser , s8* szPwd);
    /**
	*   开始连接
	*/ 
    u16 LinkSipServer();
    /**
	*   连接断开
	*/ 
    u16 CloseLink();
    /**
	*   发送本地网络媒体码流端口
	*/ 
    u16 SendLocalMediaPort(u32 dwLocalVidPort, u32 dwLocalAudPort); 

    

private:
    static  CAirDispRemoteInterface*  m_pMySelf;
    CAirDispRemoteInterface(void);
    HWND                 m_hRecvWnd;         // 内嵌接收消息的窗口
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    WNDPROC              m_wndprocOld;       // 系统窗口过程

    CAirDispRemoteSessionCtrlIF   *m_pAirDispRemoteSession;       //url会话

    CAirDispRemoteSysCtrlIF  *m_pSysCtrlIf;

    TLoginInfo           m_tLoginInfo;//保存登录的IP 端口 用户名 密码
};

#define CAirDispRemoteComInterface  CAirDispRemoteInterface::GetCommIF()
