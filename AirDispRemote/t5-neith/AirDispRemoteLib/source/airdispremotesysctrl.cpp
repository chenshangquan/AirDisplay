#include "stdafx.h"
#include "AirDispRemotesysctrl.h"
#include "AirDispRemoteevent.h"
//#include "socketmanager.h"
#include "AirDispRemoteprintctrl.h"

CAirDispRemoteSysCtrl::CAirDispRemoteSysCtrl(CAirDispRemoteSession &cSession) : CAirDispRemoteSysCtrlIF()
{
    m_pSession = &cSession;
    BuildEventsMap();
}

CAirDispRemoteSysCtrl::~CAirDispRemoteSysCtrl()
{

}

u16 CAirDispRemoteSysCtrl::SocketConnect(s8* pchIP, u32 dwPort)
{
   
    return NO_ERROR;
}

u16 CAirDispRemoteSysCtrl::CloseSocket()
{
    return NO_ERROR;
}

void CAirDispRemoteSysCtrl::BuildEventsMap()
{
    REG_PFUN(EV_NVMPAPP_CONNECT_REQ, CAirDispRemoteSysCtrl::OnConnected);
    REG_PFUN(EV_NVMPAPP_VIEWQKSHARE_Cmd, CAirDispRemoteSysCtrl::OnStartViewShare);
}

void CAirDispRemoteSysCtrl::OnConnected(const CMessage& cMsg)
{
    if ( NULL == cMsg.content )
    {
        return;
    }

    NetSendPara tNetSendPara = *(NetSendPara*)(cMsg.content);
    
	PostEvent( UI_AIRDISPREMOTE_CONNECTED, tNetSendPara.m_dwLocalIP, tNetSendPara.m_dwRemoteIP );
    PostEvent( UI_AIRDISPREMOTE_MEDIAPORT, tNetSendPara.m_dwRemoteVidPort, tNetSendPara.m_dwRemoteAudPort );
    PrtAirDispRemoteMsg("Rec NetSend Media Trans IP Address.\r\n");
    CAirDispRemoteMsgDriver::s_pMsgDriver->SetNodeId(cMsg.srcnode);

}

void CAirDispRemoteSysCtrl::OnStartViewShare(const CMessage& cMsg)
{
#if 0
    BOOL32 bTPStart = *(BOOL32*)(cMsg.content);
    PrtAirDispRemoteMsg("bTPStart:%d\r\n", bTPStart);

    if (bTPStart)
    {
        PrtAirDispRemoteMsg("start view share.\r\n");
        SOCKETWORK->OpenSocket();
        u32 dwSerPort = SOCKETWORK->GetSocket();
        PrtAirDispRemoteMsg("Socket listen:%d.\r\n", dwSerPort);
        CAirDispRemoteMsgDriver::s_pMsgDriver->PostCMsg(EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf, &dwSerPort, sizeof(u32));
    }
    else
    {
        if ( SOCKETWORK->IsSocket() )
        {
            PrtAirDispRemoteMsg("stop view share.\r\n");
            SOCKETWORK->CloseSocket();
        }
    }
#endif
}

void CAirDispRemoteSysCtrl::OnDicconnected(const CMessage& cMsg)
{
    //发送界面提醒
    
}

void CAirDispRemoteSysCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CAirDispRemoteSysCtrl, cMsg);
}

void CAirDispRemoteSysCtrl::OnTimeOut(u16 wEvent)
{ 
}