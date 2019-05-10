/*****************************************************************************
模块名      : rkclib接口
文件名      : rkcsysctrlif.h
相关文件    : 
文件实现功能: rkc配置
作者        : 叶良平
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/8/30   1.0         叶良平        创建
******************************************************************************/
#ifndef __RKCSYSCTRLIF_H__
#define __RKCSYSCTRLIF_H__

#include "kdvdispevent.h"

class CAirDispRemoteSysCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   Socket连接
	*/ 
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort) = 0;
    /**
	*   Socket断开
	*/ 
    virtual u16 CloseSocket() = 0;
	
};

#endif __RKCSYSCTRLIF_H__