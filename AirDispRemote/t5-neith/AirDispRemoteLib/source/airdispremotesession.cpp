#include "stdafx.h"
#include <string>
#include "AirDispRemotesession.h"
#include "AirDispRemotemsgrecver.h"
#include "AirDispRemotesysctrl.h"
#include "AirDispRemoteprintctrl.h"

//线程函数
DWORD WINAPI GetConfTempThread(LPVOID pParam);

CAirDispRemoteSession::CAirDispRemoteSession():m_bInitOsp(FALSE)
{
    InitializeOsp();
    SetAppId( AID_AirDispRemote_APP );

    m_pSysCtrlIf = NULL;
   
    //在该类中，new出所有的功能类，外部通过接口GetInterface()获取
    #define NEW_REG(pCtrlIF, clsName)         \
    pCtrlIF = new clsName(*this);     \
    RegHandler(pCtrlIF);

    NEW_REG( m_pSysCtrlIf, CAirDispRemoteSysCtrl );
}

CAirDispRemoteSession::~CAirDispRemoteSession()
{

}

u16 CAirDispRemoteSession::InitializeOsp()
{
    // 初始化OSP
    const u32 dwTelnetPort = 60012;
    if( !IsOspInitd() )
    {

        BOOL bTelnet  = FALSE ;

#ifdef _DEBUG
        bTelnet = TRUE;
#endif

        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return ERR_OSP_INIT;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }

    char szOspApp[] = "RkcLib";
    const u32 dwPrior = 80;
    int nRet = g_AirDispRemoteApp.CreateApp(&szOspApp[0], AID_AirDispRemote_APP, dwPrior, 300, 200);
    ASSERT(nRet == 0);

    PrtAirDispRemoteMsg( "AirDispRemote osp启动成功\n" );

    //创建本地监听节点
    nRet = ::OspCreateTcpNode( 0, 60011, TRUE );
    PrtAirDispRemoteMsg( "监听端口返回值%d \n", nRet );
    if (INVALID_SOCKET == nRet)
    {
        return ERR_OSP_CREATE_TCP_NODE;
    }

    return NO_ERROR;
}

/*获取接口指针*/
u16 CAirDispRemoteSession::RkcGetInterface(CAirDispRemoteSysCtrlIF **ppCtrl)
{
    if( m_pSysCtrlIf != NULL)
    {
        *ppCtrl = m_pSysCtrlIf;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_AirDispRemote;
    }
}


/*功    能： 是否已和CNS建立了连接*/
BOOL CAirDispRemoteSession::IsConnectedSip()
{
	return g_AirDispRemoteApp.GetNodeId() != INVALID_NODE;
}

/*功    能： 连接*/
u16 CAirDispRemoteSession::ConnectSip(u32 dwIP, u32 dwPort, char* strUser, char* strPwd, BOOL32 bConnect /* = TRUE */)
{
    // 建立TCP连接
    if( IsConnectedSip() )
    { 
        //如何已经登录了该IP，则直接返回，否则断开重连
		if ( dwIP == m_dwSipIp )
		{
			return ERR_AirDispRemote_ACTIVE_CONNECT;
		}
		else
		{
			DisconnectSip();
			return ERR_AirDispRemote_ACTIVE_CONNECT;
		}
        
    }
    
    //ClearDisp();
    // 重构消息分发表
    //BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), 5 , 3, 5000 );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_AirDispRemote_TCPCONNECT;
		}		
	}
	else
	{
		dwCnNodeId = 0;
	}

    g_AirDispRemoteApp.SetNodeId( dwCnNodeId );
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, AID_AirDispRemote_APP, 1);

	return NO_ERROR;
}

/*功    能： 断开Sip连接*/
u16 CAirDispRemoteSession::DisconnectSip()
{
    if( !IsConnectedSip() )
    {
        return NO_ERROR;
    }

    OspDisconnectTcpNode(g_AirDispRemoteApp.GetNodeId()); 
	m_dwSipIp = 0;
    
    return NO_ERROR;
}

void CAirDispRemoteSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CAirDispRemoteSession, cMsg);
}

void CAirDispRemoteSession::OnTimeOut(u16 wEvent)
{ 
}


