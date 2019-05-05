#pragma once

#ifndef _EVSIPLIB_20180920_H_
#define _EVSIPLIB_20180920_H_



//rkcLib����Ϣ����
enum EmUiRkcMsg
{

#define UI_SIPTOOL_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISipToolConnect	= UI_SIPTOOL_MSG_BEGIN,
#define	UI_SIPTOOL_CONNECTED  ev_UISipToolConnect
	
	/************************************************************************/
	/** �ѶϿ�
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
    EV_NVMPAPP_REGISTER_REQ = 61012,        //ע������
    EV_NVMPAPP_REGISTER_RSP,                //ע��ظ�
    EV_NVMPAPP_VIEWQKSHARE_Cmd,             //Ͷ������  BOOL32
    EV_NVMPAPP_VIEWQKSHARE_Ntf,             //Ͷ�����֪ͨ BOOL32
    EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf,      //socket �������֪ͨ u32
    EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf,      //socket accept֪ͨ
    EV_NVMPAPP_ASKKEYFRAME,                 //�ؼ�֡����
};
#endif 
