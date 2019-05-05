#pragma once

#ifndef _EVSIPLIB_20180920_H_
#define _EVSIPLIB_20180920_H_



//rkcLib中消息定义
enum EmUiRkcMsg
{

#define UI_SIPTOOL_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** 连接 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISipToolConnect	= UI_SIPTOOL_MSG_BEGIN,
#define	UI_SIPTOOL_CONNECTED  ev_UISipToolConnect
	
	/************************************************************************/
	/** 已断开
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISipToolDisconnected,
#define UI_SIPTOOL_DISCONNECTED	 ev_UISipToolDisconnected

    

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

// osp event
enum EMNvmpAppMsgSegs
{
    EV_NVMPAPP_REGISTER_REQ = 61012,        //注册请求
    EV_NVMPAPP_REGISTER_RSP,                //注册回复
    EV_NVMPAPP_VIEWQKSHARE_Cmd,             //投屏请求  BOOL32
    EV_NVMPAPP_VIEWQKSHARE_Ntf,             //投屏结果通知 BOOL32
    EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf,      //socket 监听结点通知 u32
    EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf,      //socket accept通知
    EV_NVMPAPP_ASKKEYFRAME,                 //关键帧请求
};
#endif 
