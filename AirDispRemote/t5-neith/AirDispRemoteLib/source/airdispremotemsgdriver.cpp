#include "stdafx.h"
#include "AirDispRemotemsgdriver.h"
#include "AirDispRemotemsgrecver.h"
#include "AirDispRemoteprintctrl.h"

CAirDispRemoteMsgDriver* CAirDispRemoteMsgDriver::s_pMsgDriver = NULL;

CAirDispRemoteMsgDriver::CAirDispRemoteMsgDriver()
{
    // 构造事件名称表
    MappingEventName();
    s_pMsgDriver = this;
}

CAirDispRemoteMsgDriver::~CAirDispRemoteMsgDriver()
{
    s_pMsgDriver = NULL;
}

COspMsg* CAirDispRemoteMsgDriver::GetOspMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_tOspMsg, sizeof(COspMsg));
    }

    return &m_tOspMsg;
}
//注册一个处理消息的类的指针
void CAirDispRemoteMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

void CAirDispRemoteMsgDriver::MappingEventName()
{
    
}
void CAirDispRemoteMsgDriver::PostCMsg(u16 wEvenId, void* pConent, u16 wLen)
{
    ZeroMemory(&m_cMsg, sizeof(CMessage));

    m_cMsg.event = wEvenId;
    if (pConent == NULL)
    {
        m_cMsg.content = NULL;
        m_cMsg.length = 0;
    }
    else
    {
        m_cMsg.content = (u8*)pConent;
        m_cMsg.length = wLen;
    }

    PostMsg(TYPE_CMESSAGE);
}

u16 CAirDispRemoteMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = MAKEIID(AID_AIRDIS_APP, 0);	 //目的
    u32 dwSrcIID = MAKEIID(GetAppId());	         //源 

    u16 wRet = NO_ERROR;
    u16 wEvent = 0;
    if (TYPE_TPMSG == dwType) 
    {  
        wRet = OspPost(MAKEIID(AID_AirDispRemote_APP,0), m_tOspMsg.GetEvent(),m_tOspMsg.GetBody(),m_tOspMsg.GetBodyLen());
    }
    else
    {
        //发送Osp CMessage消息
        /*if(m_cMsg.dstid != INVALID_NODE)
        {
            dwDesIID = m_cMsg.dstid;
        }
        if(m_cMsg.srcid != INVALID_NODE)
        {
            dwSrcIID = m_cMsg.srcid;
        }*/

        wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
            GetNodeId(), dwSrcIID);

        //wEvent = m_cMsg.event;
    }

    return wRet;
}

void CAirDispRemoteMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CAirDispRemoteMsgHandler *pHandler = CAirDispRemoteMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CAirDispRemoteMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

        //打印输出
        CString strEvent = CAirDispRemotePrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event); 

        PrtAirDispRemoteMsg(cMsg.event, "\n[RkcLib]: 收到消息:%s(%u).", strEvent,cMsg.event);

        // 检索消息分发表
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
            PrtAirDispRemoteMsg( "[RkcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

