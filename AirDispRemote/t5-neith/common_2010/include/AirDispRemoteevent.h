#pragma once

#ifndef _EVSIPLIB_20180920_H_
#define _EVSIPLIB_20180920_H_



//rkcLib����Ϣ����
enum EmUiRkcMsg
{

#define UI_AIRDISPREMOTE_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAirDispRemoteConnect	= UI_AIRDISPREMOTE_MSG_BEGIN,
#define	UI_AIRDISPREMOTE_CONNECTED  ev_UIAirDispRemoteConnect
	
	/************************************************************************/
	/** �ѶϿ�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAirDispRemoteDisconnected,
#define UI_AIRDISPREMOTE_DISCONNECTED	 ev_UIAirDispRemoteDisconnected

    /************************************************************************/
	/** ��ʾ��Ƶ
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAirDispRemoteShowVideo,
#define UI_AIRDISPREMOTE_SHOWVIDEO	 ev_UIAirDispRemoteShowVideo

    /************************************************************************/
	/** ����Ƶ�˿�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAirDispRemoteMediaPort,
#define UI_AIRDISPREMOTE_MEDIAPORT	 ev_UIAirDispRemoteMediaPort

    /************************************************************************/
	/** ����video����λ��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAirDispRemoteResetVideoPos,
#define UI_AIRDISPREMOTE_RESETVIDEOPOS	 ev_UIAirDispRemoteResetVideoPos
    

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

// osp event
enum EMNvmpAppMsgSegs
{
    EV_NVMPAPP_CONNECT_REQ = 61012,        //ע������
    EV_NVMPAPP_CONNECT_RSP,                //ע��ظ�
    EV_NVMPAPP_VIEWQKSHARE_Cmd,             //Ͷ������  BOOL32
    EV_NVMPAPP_VIEWQKSHARE_Ntf,             //Ͷ�����֪ͨ BOOL32
    EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf,      //socket �������֪ͨ u32
    EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf,      //socket accept֪ͨ
    EV_NVMPAPP_ASKKEYFRAME,                 //�ؼ�֡����
};
#endif 
