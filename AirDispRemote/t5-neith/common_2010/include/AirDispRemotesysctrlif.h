/*****************************************************************************
ģ����      : rkclib�ӿ�
�ļ���      : rkcsysctrlif.h
����ļ�    : 
�ļ�ʵ�ֹ���: rkc����
����        : Ҷ��ƽ
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2018/8/30   1.0         Ҷ��ƽ        ����
******************************************************************************/
#ifndef __RKCSYSCTRLIF_H__
#define __RKCSYSCTRLIF_H__

#include "kdvdispevent.h"

class CAirDispRemoteSysCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   Socket����
	*/ 
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort) = 0;
    /**
	*   Socket�Ͽ�
	*/ 
    virtual u16 CloseSocket() = 0;
    /**
	*   ���ͱ�������ý�������˿�
	*/ 
	virtual u16 SendLocalMediaPort(u32 dwLocalVidPort, u32 dwLocalAudPort) = 0;
};

#endif __RKCSYSCTRLIF_H__