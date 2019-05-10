/*=======================================================================
模块名      : RCK实例App类
文件名      : msgrecver.h
相关文件    : 
文件实现功能: 声明接收OSP消息所需的CInstance派生类
作者        : 叶良平
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/8/29   3.0         叶良平        创建
=======================================================================*/

#include "AirDispRemotemsgrecver.h"
#include "AirDispRemotemsgdriver.h"
//////////////////////////////////////////////////////////////////////////
//  COspAppBase
//

CAirDispRemoteAppBase::CAirDispRemoteAppBase()
{
    m_dwNodeId = INVALID_NODE;
}

CAirDispRemoteAppBase::~CAirDispRemoteAppBase()
{
}

void CAirDispRemoteAppBase::ClearOspMsg()
{
    CAirDispRemoteMsgHandler *pHandler = CAirDispRemoteMsgHandler::GetMsgHandler();
    if (pHandler) 
    {
        pHandler->ClearQueue();
    }
}

//////////////////////////////////////////////////////////////////////////
// CMsgQueue
// 
CAirDispRemoteMsgQueue::CAirDispRemoteMsgQueue()
{
}
CAirDispRemoteMsgQueue::~CAirDispRemoteMsgQueue()
{
    Clear();
}

void CAirDispRemoteMsgQueue::PushMsg(CMessage* const pMsg)
{
    CMessage cMsg;
    cMsg = *pMsg;
    cMsg.content = new u8[pMsg->length];
    memcpy(cMsg.content, pMsg->content, pMsg->length);
    m_queMsg.push(cMsg);
}

void CAirDispRemoteMsgQueue::PopMsg(CAirDispRemoteMsgQueue &cOutQue)
{
    CMessage *pMsg = &m_queMsg.front(); 
    cOutQue.PushMsg(pMsg);
    delete []pMsg->content;
    m_queMsg.pop();
}

void CAirDispRemoteMsgQueue::Clear()
{
    while (!m_queMsg.empty()) 
    {
        CMessage *pMsg = &m_queMsg.front();
        delete []pMsg->content;
        m_queMsg.pop();
    }
}

BOOL CAirDispRemoteMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}

////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象
zTemplate<CAirDispRemoteMsgHandler, RKC_INSTANCE_COUNT, CAirDispRemoteAppBase> g_AirDispRemoteApp;

////////////////////////////////////////////////////////////////////////////////
// CMsgHandler

CAirDispRemoteMsgHandler* CAirDispRemoteMsgHandler::s_pMsgHandler = NULL;

CAirDispRemoteMsgHandler::CAirDispRemoteMsgHandler()
{
    InitializeCriticalSection(&m_csQueueOspMsg);
    s_pMsgHandler = this;
}

CAirDispRemoteMsgHandler::~CAirDispRemoteMsgHandler()
{
    s_pMsgHandler = NULL;
    DeleteCriticalSection(&m_csQueueOspMsg);
}

void CAirDispRemoteMsgHandler::InstanceEntry(CMessage *const pMsg)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    if(m_cMsgQue.Size() == 0)
    {
        m_cMsgQue.PushMsg(pMsg);
        CAirDispRemoteMsgDriver::s_pMsgDriver->OnOspMessageComing( 0, 0 );
    }
    else
    {
        m_cMsgQue.PushMsg(pMsg);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

void CAirDispRemoteMsgHandler::PopAllMsg(CAirDispRemoteMsgQueue &cMsgQue)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

void CAirDispRemoteMsgHandler::ClearQueue()
{
    EnterCriticalSection(&m_csQueueOspMsg);
    m_cMsgQue.Clear();
    LeaveCriticalSection(&m_csQueueOspMsg);
}
