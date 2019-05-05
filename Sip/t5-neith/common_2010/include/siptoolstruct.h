// rkcstruct.h: interface for the cmsstruct class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _h_siptoolstruct_h__
#define _h_siptoolstruct_h__

#include "siptoolconst.h"
#include "siptoolmessage.h"

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


#endif 
