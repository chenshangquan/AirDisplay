#pragma once
#include "StdAfx.h"
#include "AirDispRemoteSessionCtrlIF.h"
#include "AirDispRemotemsgdriver.h"

class CAirDispRemoteSession : public CAirDispRemoteSessionCtrlIF,
                        public CAirDispRemoteMsgDriver
{
public:
    CAirDispRemoteSession();
    ~CAirDispRemoteSession();

    //��ȡ�ӿ� 
    virtual u16 RkcGetInterface(CAirDispRemoteSysCtrlIF **ppCtrl);

    virtual u16 ConnectSip(u32 dwIP, u32 dwPort, LPSTR strUser, LPSTR strPwd, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectSip();
    virtual BOOL IsConnectedSip();

protected:
    // ��ʼ��OSP 
    u16 InitializeOsp();

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    BOOL32 m_bInitOsp;
    u32	   m_dwSipIp;	  //����Sip��IP

    // ����������ӿ���
    CAirDispRemoteSysCtrlIF  *m_pSysCtrlIf;

};

