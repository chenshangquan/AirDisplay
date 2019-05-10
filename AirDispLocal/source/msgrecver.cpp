#include "stdafx.h"
#include "AirDispLocal.h"
#include "msgrecver.h"
#include "AirDispLocalDlg.h"

extern CAirDispLocalDlg * g_dlg;

//////////////////////////////////////////////////////////////////////////
//  COspAppBase
//

CAppBase::CAppBase()
{
    m_dwNodeId = INVALID_NODE;
}

CAppBase::~CAppBase()
{
}

////////////////////////////////////////////////////////////////////////////////
// ȫ��OspӦ�ó������
zTemplate<CMsgHandler, INSTANCE_NUM, CAppBase> g_AirDisApp;

////////////////////////////////////////////////////////////////////////////////
// CMsgHandler

CMsgHandler* CMsgHandler::s_pMsgHandler = NULL;

CMsgHandler::CMsgHandler()
{
    s_pMsgHandler = this;
}

CMsgHandler::~CMsgHandler()
{
    s_pMsgHandler = NULL;
}

void CMsgHandler::RegisterRspHandle(CMessage *const pMsg)
{
    PRINTMSG_TIME("EV_NVMPAPP_REGISTER_RSP, SUCCESSFUL.\r\n");
    SendMessage(g_dlg->m_pcMainDlg->GetSafeHwnd(), WM_REGISTER_SUCCEED, 0, 0);
    return;
}

void CMsgHandler::ViewQKShareNtfHandle(CMessage *const pMsg)
{
    BOOL32 bViewQKShare  = *(BOOL32*)(pMsg->content);
    PRINTMSG_TIME("EV_NVMPAPP_VIEWQKSHARE_Ntf, bViewQKShare:%d\r\n", bViewQKShare);
    if (bViewQKShare)
    {
        PRINTMSG_TIME("View Quick Share Start.\r\n");
    }
    else
    {
        PRINTMSG_TIME("View Quick Share Stop.\r\n");
        SendMessage(g_dlg->m_pcMainDlg->GetSafeHwnd(), WM_VIEW_QK_SHARE_QUIT, (WPARAM)bViewQKShare, sizeof(BOOL32));
    }
    return;
}

void CMsgHandler::SocketListenNtf(CMessage *const pMsg)
{
    SOCKET sServerListen = *(u32*)(pMsg->content);
    PRINTMSG_TIME("EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf, sServerListen:%d\r\n", sServerListen);
    if (sServerListen != INVALID_SOCKET)
    {
        SendMessage(g_dlg->m_pcMainDlg->GetSafeHwnd(), WM_RECV_IMIX_SOCKET, (WPARAM)sServerListen, 0);
    }

    return;
}

void CMsgHandler::SocketAcceptNtf(CMessage *const pMsg)
{
    PRINTMSG_TIME("EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf\r\n");
    SendMessage(g_dlg->m_pcMainDlg->GetSafeHwnd(), WM_VIEW_QK_SHARE_START, 0, 0);
    return;
}

void CMsgHandler::InstanceEntry(CMessage *const pMsg)
{
    /*�õ���ǰ��Ϣ������;*/
    u16 wCurEvent = pMsg->event;

    // ���ݲ�ͬ����Ϣ���ͽ��д���;
    switch (wCurEvent)
    {
    case EV_NVMPAPP_REGISTER_RSP:
        //ע��ظ�
        RegisterRspHandle(pMsg);
        break;
    case EV_NVMPAPP_VIEWQKSHARE_Ntf:
        //Ͷ�����֪ͨ BOOL32
        ViewQKShareNtfHandle(pMsg);
        break;
    case EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf:
        //socket �������֪ͨ u32
        SocketListenNtf(pMsg);
        break;
    case EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf:
        //socket accept֪ͨ
        SocketAcceptNtf(pMsg);
        break;
    default:

        break;
    }

    return;
}
