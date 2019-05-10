// rkcstruct.h: interface for the cmsstruct class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _h_AirDispRemotestruct_h__
#define _h_AirDispRemotestruct_h__

#include "AirDispRemoteconst.h"
#include "AirDispRemotemessage.h"
#include "tpcommonstruct.h"

//µÇÂ¼ÐÅÏ¢
typedef struct tagLoginInfo
{
	u32     m_dwIp;
	u16     m_wPort;
	s8      m_achName[MAX_ALIAS_LENGTH+1];
	s8      m_achPswd[MAX_ALIAS_LENGTH+1];

	tagLoginInfo()
	{
		memset( this, 0, sizeof(tagLoginInfo) );
	}
}TLoginInfo;

typedef struct tagNetSendMediaPort
{
    u32 m_dwVidPort;
    u32 m_dwAudPort;	

    void clear()
    {
        m_dwVidPort = 0;
        m_dwAudPort = 0;
    }
    tagNetSendMediaPort()
    {
        clear();
    }
    tagNetSendMediaPort& operator = (const tagNetSendMediaPort& tRhs)
    {
        if (this == &tRhs)
        {
            return *this;
        }

        this->m_dwVidPort = tRhs.m_dwVidPort;
        this->m_dwAudPort = tRhs.m_dwAudPort;
        return *this;
    }
}NetSendMediaPort;

#endif 
