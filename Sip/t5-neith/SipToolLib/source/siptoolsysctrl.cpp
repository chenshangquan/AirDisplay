#include "stdafx.h"
#include "siptoolsysctrl.h"
#include "siptoolevent.h"
#include "socketmanager.h"
#include "siptoolprintctrl.h"

CSipToolSysCtrl::CSipToolSysCtrl(CSipToolSession &cSession) : CSipToolSysCtrlIF()
{
    m_pSession = &cSession;
    BuildEventsMap();
}

CSipToolSysCtrl::~CSipToolSysCtrl()
{

}

u16 CSipToolSysCtrl::SocketConnect(s8* pchIP, u32 dwPort)
{
   
    return NO_ERROR;
}

u16 CSipToolSysCtrl::CloseSocket()
{
    return NO_ERROR;
}

void CSipToolSysCtrl::BuildEventsMap()
{
    REG_PFUN(EV_NVMPAPP_REGISTER_REQ, CSipToolSysCtrl::OnRegister);
    REG_PFUN(EV_NVMPAPP_VIEWQKSHARE_Cmd, CSipToolSysCtrl::OnStartViewShare);
}

void CSipToolSysCtrl::OnRegister(const CMessage& cMsg)
{
    // socket create
    SOCKETWORK->SetSocketIP(_T("172.16.160.113"));
    SOCKETWORK->SetSocketPort((u32)6684);

    //SOCKETWORK->OpenSocket();
    PrtSipToolMsg("set socket ip&port success.\r\n");
    CSipToolMsgDriver::s_pMsgDriver->SetNodeId(cMsg.srcnode);
    CSipToolMsgDriver::s_pMsgDriver->PostCMsg(EV_NVMPAPP_REGISTER_RSP, NULL, 0);

}

void CSipToolSysCtrl::OnStartViewShare(const CMessage& cMsg)
{
    BOOL32 bTPStart = *(BOOL32*)(cMsg.content);
    PrtSipToolMsg("bTPStart:%d\r\n", bTPStart);

    if (bTPStart)
    {
        PrtSipToolMsg("start view share.\r\n");
        SOCKETWORK->OpenSocket();
        u32 dwSerPort = SOCKETWORK->GetSocket();
        PrtSipToolMsg("Socket listen:%d.\r\n", dwSerPort);
        CSipToolMsgDriver::s_pMsgDriver->PostCMsg(EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf, &dwSerPort, sizeof(u32));
    }
    else
    {
        if ( SOCKETWORK->IsSocket() )
        {
            PrtSipToolMsg("stop view share.\r\n");
            SOCKETWORK->CloseSocket();
        }
    }
}

void CSipToolSysCtrl::OnDicconnected(const CMessage& cMsg)
{
    //发送界面提醒
    
}

void CSipToolSysCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CSipToolSysCtrl, cMsg);
}

void CSipToolSysCtrl::OnTimeOut(u16 wEvent)
{ 
}