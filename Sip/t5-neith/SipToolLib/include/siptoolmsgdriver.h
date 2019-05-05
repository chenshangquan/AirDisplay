/*=======================================================================
模块名      : RKC控制台
文件名      : rckmsgdriver.h
相关文件    : 
文件实现功能: RCK消息驱动器
作者        : 叶良平
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容

=======================================================================*/
#ifndef SIPTOOLMSGDRIVER_H
#define SIPTOOLMSGDRIVER_H

#include <vector>
#include "kdvdispevent.h"
#include "ospmsg.h"
//#include "eventoutrkcentre.h"
#include "siptoolmessage.h"

#define     AID_SIPTOOL_APP     53
#define     AID_AIRDIS_APP      62

class CSipToolMsgDriver
{
public:
    CSipToolMsgDriver();
    ~CSipToolMsgDriver();

    // 得到发送消息的指针
    COspMsg* GetOspMsgPtr(BOOL32 bClear = TRUE);
    // 注册一个处理消息的类的指针
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // 发送CMessage osp消息
    virtual void PostCMsg(u16 wEvenId, void* pConent, u16 wLen);
    // 发送osp消息
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

    // 设置当前连接节点
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    u32 GetNodeId(){ return m_dwNodeId;}

    // 设置使用的APPID号
    void SetAppId( u16 wAppID ){ m_wAppID = wAppID; } 
    u16  GetAppId(){ return m_wAppID; }

public:
    static CSipToolMsgDriver *s_pMsgDriver;

    // 响应WM_OSPMESSAGECOMING消息
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:
    COspMsg     m_tOspMsg;              //osp传送消息
    CMessage    m_cMsg;			        //用于发送其他消息的消息结构
private:
    void MappingEventName();

    vector<CKdvDispEvent*> m_vpDispEvent;   // 消息分发表

    u32  m_dwNodeId;        // 当前连接的节点
    u16  m_wAppID;			// 连接的APPID号
};


#endif //SIPTOOLMSGDRIVER_H
