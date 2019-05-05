#pragma once
#include "StdAfx.h"
#include "siptoolSessionCtrlIF.h"
#include "siptoolmsgdriver.h"

class CSipToolSession : public CSipToolSessionCtrlIF,
                        public CSipToolMsgDriver
{
public:
    CSipToolSession();
    ~CSipToolSession();

    //获取接口 
    virtual u16 RkcGetInterface(CSipToolSysCtrlIF **ppCtrl);

    virtual u16 ConnectSip(u32 dwIP, u32 dwPort, LPSTR strUser, LPSTR strPwd, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectSip();
    virtual BOOL IsConnectedSip();

protected:
    // 初始化OSP 
    u16 InitializeOsp();

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    BOOL32 m_bInitOsp;
    u32	   m_dwSipIp;	  //连接Sip的IP

    // 各个功能类接口类
    CSipToolSysCtrlIF  *m_pSysCtrlIf;

};

