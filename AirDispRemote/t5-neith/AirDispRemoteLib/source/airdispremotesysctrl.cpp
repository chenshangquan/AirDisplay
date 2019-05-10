#include "stdafx.h"
#include "AirDispRemotesysctrl.h"
#include "AirDispRemoteevent.h"
//#include "socketmanager.h"
#include "AirDispRemoteprintctrl.h"
#include ""

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
    REG_PFUN(EV_NVMPAPP_REGISTER_REQ, CAirDispRemoteSysCtrl::OnRegister);
    REG_PFUN(EV_NVMPAPP_VIEWQKSHARE_Cmd, CAirDispRemoteSysCtrl::OnStartViewShare);
}

void CAirDispRemoteSysCtrl::OnRegister(const CMessage& cMsg)
{
    if ( NULL == cMsg.content )
    {
        return;
    }

    NetSendMediaPort tRemoteMediaPort = *(NetSendMediaPort*)(cMsg.content);
    
    PostEvent( UI_AIRDISPREMOTE_MEDIAPORT, tRemoteMediaPort.m_dwVidPort, tRemoteMediaPort.m_dwAudPort );
    PrtAirDispRemoteMsg("Rec NetSend Media TransPoart.\r\n");
    CAirDispRemoteMsgDriver::s_pMsgDriver->SetNodeId(cMsg.srcnode);

}

void CAirDispRemoteSysCtrl::OnStartViewShare(const CMessage& cMsg)
{
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