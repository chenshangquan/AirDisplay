#include "StdAfx.h"
#include "AirDispRemotecommonop.h"
#include "networksetuplogic.h"
#include "videologic.h"
#include "messageboxlogic.h"

#include "menulogic.h"

IAirDispRemoteCommonOp::IAirDispRemoteCommonOp(void)
{
}


IAirDispRemoteCommonOp::~IAirDispRemoteCommonOp(void)
{
}


void IAirDispRemoteCommonOp::RegLogics()
{
    REG_LOGIC(CMenuLogic);
	REG_LOGIC(CNetworkSetupLogic);
    REG_LOGIC(CVideoLogic);
    REG_LOGIC(CMessageBoxLogic);

	return ;
}

bool IAirDispRemoteCommonOp::NotifyMsg(u16 wMsgId, void *pData)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)pData;
	IAirDispRemoteMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}

bool IAirDispRemoteCommonOp::NotifyMsg(u16 wMsgId, WPARAM wParam, LPARAM lParam)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)wParam;
	Msg.lParam = lParam;
	IAirDispRemoteMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}


MbString IAirDispRemoteCommonOp::StringFormat(const char *format, ... )
{
	char str[1024] = { 0 };
	va_list pvlist;
	va_start(pvlist, format);
	vsnprintf((char *)str, 1024, format, pvlist);
	va_end(pvlist);
	return str;
}
