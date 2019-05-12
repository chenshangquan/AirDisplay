#pragma once
#include "osp.h"

#define INSTANCE_NUM	1	// 接收消息的实例的数目

enum EMNvmpAppMsgSegs
{
    EV_NVMPAPP_CONNECT_REQ = 61012,        //注册请求
    EV_NVMPAPP_REGISTER_RSP,                //注册回复
    EV_NVMPAPP_VIEWQKSHARE_Cmd,             //投屏请求  BOOL32
    EV_NVMPAPP_VIEWQKSHARE_Ntf,             //投屏结果通知 BOOL32
    EV_NVMPAPP_IMIX_SOCKET_LISTEN_Ntf,      //socket 监听结点通知 u32
    EV_NVMPAPP_IMIX_SOCKET_ACCEPT_Ntf,      //socket accept通知
    EV_NVMPAPP_ASKKEYFRAME,                 //关键帧请求
};

/************************************************************************/
/*                        OSP实例定义                                  */
/************************************************************************/
class CMsgHandler : public CInstance  
{
public:
    CMsgHandler();
    ~CMsgHandler();
    virtual void InstanceEntry(CMessage *const pMsg);

private:
    // 注册回复消息处理
    void RegisterRspHandle(CMessage *const pMsg);
    // 投屏结果通知处理
    void ViewQKShareNtfHandle(CMessage *const pMsg);
    // socket 监听结点通知处理
    void SocketListenNtf(CMessage *const pMsg);
    // socket accept通知处理
    void SocketAcceptNtf(CMessage *const pMsg);

public:
    static CMsgHandler* GetMsgHandler() { return s_pMsgHandler; }
private:
    static CMsgHandler *s_pMsgHandler;
};

class CAppBase
{
public:
    CAppBase();
    ~CAppBase();
    // 获取当前连接节点的标识(线程安全)
    u32 GetNodeId(){ return m_dwNodeId;}
    // 设置当前连接节点的标识(线程安全)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
protected:
    u32                     m_dwNodeId;     // 当前建立连接的节点标识
};

extern zTemplate<CMsgHandler, INSTANCE_NUM, CAppBase> g_AirDisApp;