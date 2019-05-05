#include "stdafx.h"
#include "siptoolinterface.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT ThreadConnectSipTool(LPVOID lpParam)
{
    u16 re  = CSipToolComInterface->LinkSipServer();

    if ( re != NO_ERROR )
    {
        
        return re;
    }

    return re;
}

u16 CSipToolInterface::SocketConnect( u32 dwIp, s8* szUser , s8* szPwd)
{
    if( NULL == m_pSipToolSession )
    {
        return ERR_SIPTOOL;
    } 

    m_tLoginInfo.m_dwIp = dwIp;
    m_tLoginInfo.m_wPort = CONNETCT_SIPSERVER_PORT;

    strncpy(m_tLoginInfo.m_achName, szUser, sizeof(m_tLoginInfo.m_achName));
    strncpy(m_tLoginInfo.m_achPswd, szPwd, sizeof(m_tLoginInfo.m_achPswd));

    //Á¬½Órkc100
    AfxBeginThread( ThreadConnectSipTool , NULL );

    return NO_ERROR;
}

u16 CSipToolInterface::LinkSipServer()
{
    u16 re =  ERR_SIPTOOL;
    if ( m_pSipToolSession != NULL )
    {
        re = m_pSipToolSession->ConnectSip( m_tLoginInfo.m_dwIp,  m_tLoginInfo.m_wPort, m_tLoginInfo.m_achName, m_tLoginInfo.m_achPswd );
    }
    return re;
}

u16 CSipToolInterface::CloseLink()
{
    return m_pSysCtrlIf->CloseSocket();
}