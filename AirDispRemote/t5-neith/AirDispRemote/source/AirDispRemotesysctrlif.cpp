#include "stdafx.h"
#include "AirDispRemoteinterface.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT ThreadConnectAirDispRemote(LPVOID lpParam)
{
    u16 re  = CAirDispRemoteComInterface->LinkSipServer();

    if ( re != NO_ERROR )
    {
        
        return re;
    }

    return re;
}

u16 CAirDispRemoteInterface::SocketConnect( u32 dwIp, s8* szUser , s8* szPwd)
{
    if( NULL == m_pAirDispRemoteSession )
    {
        return ERR_AirDispRemote;
    } 

    m_tLoginInfo.m_dwIp = dwIp;
    m_tLoginInfo.m_wPort = CONNETCT_SIPSERVER_PORT;

    strncpy(m_tLoginInfo.m_achName, szUser, sizeof(m_tLoginInfo.m_achName));
    strncpy(m_tLoginInfo.m_achPswd, szPwd, sizeof(m_tLoginInfo.m_achPswd));

    //Á¬½Órkc100
    AfxBeginThread( ThreadConnectAirDispRemote , NULL );

    return NO_ERROR;
}

u16 CAirDispRemoteInterface::LinkSipServer()
{
    u16 re =  ERR_AirDispRemote;
    if ( m_pAirDispRemoteSession != NULL )
    {
        re = m_pAirDispRemoteSession->ConnectSip( m_tLoginInfo.m_dwIp,  m_tLoginInfo.m_wPort, m_tLoginInfo.m_achName, m_tLoginInfo.m_achPswd );
    }
    return re;
}

u16 CAirDispRemoteInterface::CloseLink()
{
    return m_pSysCtrlIf->CloseSocket();
}