#pragma once
#include "kdvdispevent.h"
#include "siptoolsysctrlif.h"
#include "siptoolstruct.h"

class CSipToolSessionCtrlIF : public CKdvDispEvent 
{
public:
    //获取接口 
    virtual u16 RkcGetInterface(CSipToolSysCtrlIF **ppCtrl) = 0;

    //连接到Sip
	virtual u16 ConnectSip(u32 dwIP, u32 dwPort,LPSTR strUser,LPSTR strPwd, BOOL32 bConnect = TRUE) = 0;

	//断开CNS连接 
	virtual u16 DisconnectSip() = 0;

	//查询是否已连接
	virtual BOOL IsConnectedSip() = 0;
};
