#include "stdafx.h"
#include <string>
#include "AirDispRemotesession.h"
#include "AirDispRemotemsgrecver.h"
#include "AirDispRemotesysctrl.h"
#include "AirDispRemoteprintctrl.h"

//�̺߳���
DWORD WINAPI GetConfTempThread(LPVOID pParam);

CAirDispRemoteSession::CAirDispRemoteSession():m_bInitOsp(FALSE)
{
    InitializeOsp();
    SetAppId( AID_AirDispRemote_APP );

    m_pSysCtrlIf = NULL;
   
    //�ڸ����У�new�����еĹ����࣬�ⲿͨ���ӿ�GetInterface()��ȡ
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
    // ��ʼ��OSP
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

    PrtAirDispRemoteMsg( "AirDispRemote osp�����ɹ�\n" );

    //�������ؼ����ڵ�
    nRet = ::OspCreateTcpNode( 0, 60011, TRUE );
    PrtAirDispRemoteMsg( "�����˿ڷ���ֵ%d \n", nRet );
    if (INVALID_SOCKET == nRet)
    {
        return ERR_OSP_CREATE_TCP_NODE;
    }

    return NO_ERROR;
}

/*��ȡ�ӿ�ָ��*/
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


/*��    �ܣ� �Ƿ��Ѻ�CNS����������*/
BOOL CAirDispRemoteSession::IsConnectedSip()
{
	return g_AirDispRemoteApp.GetNodeId() != INVALID_NODE;
}

/*��    �ܣ� ����*/
u16 CAirDispRemoteSession::ConnectSip(u32 dwIP, u32 dwPort, char* strUser, char* strPwd, BOOL32 bConnect /* = TRUE */)
{
    // ����TCP����
    if( IsConnectedSip() )
    { 
        //����Ѿ���¼�˸�IP����ֱ�ӷ��أ�����Ͽ�����
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
    // �ع���Ϣ�ַ���
    //BuildEventsMap();
    
    //����Osp��TCP����,�õ����ػ�����IP��ַ
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
    //������node�����ж�ʱ��֪ͨ��appid��InstId
    ::OspNodeDiscCBReg( dwCnNodeId, AID_AirDispRemote_APP, 1);

	return NO_ERROR;
}

/*��    �ܣ� �Ͽ�Sip����*/
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


