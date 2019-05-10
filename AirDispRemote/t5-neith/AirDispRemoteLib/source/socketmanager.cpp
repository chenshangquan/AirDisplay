#include "stdafx.h"
//#include <afxsock.h>
//#include "windows.h"
#include "socketmanager.h"
#include "AirDispRemoteprintctrl.h"

//static UINT     g_nHeartBeatLostCount;                      //心跳包丢失个数
//static bool     g_bHeartBeatKeep;                           //
//#define         TIME_HEARTBEAT_INTERVAL        5000         //时间间隔

bool CSocketManager::m_bIsSocketOpen = false;    //Socket是否开启

CSocketManager* CSocketManager::m_pSocketManager = NULL;

/*
UINT ThreadSendDadaPack(LPVOID lpParam)
{
    while (CSocketManager::m_bIsSocketOpen)
    {
        SOCKETWORK->SendDataPack();
        Sleep(100);
    }
    return 0;
}*/
/*
UINT ThreadRevcDadaPack(LPVOID lpParam)
{
    while (CSocketManager::m_bIsSocketOpen)
    {
        SOCKETWORK->RecvDataPack();
    }
    return 0;
}*/

CSocketManager::CSocketManager()
{
    //g_nHeartBeatLostCount = 0;
    //g_bHeartBeatKeep = false;

    InitializeCriticalSection(&m_csMsgLock);

    memset(m_achIP, 0, 16);
    m_dwPort = 0;
    //m_evWaitMsg = 0;
    m_sServer = INVALID_SOCKET;
    m_sClient = INVALID_SOCKET;

    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    WSAStartup(sockVersion, &data);
}

CSocketManager::~CSocketManager()
{
    DeleteCriticalSection(&m_csMsgLock);
    WSACleanup();
}

CSocketManager* CSocketManager::GetSocketManager()
{
    if (CSocketManager::m_pSocketManager == NULL)
    {
        CSocketManager::m_pSocketManager = new CSocketManager();
    }
    return CSocketManager::m_pSocketManager;
}

void CSocketManager::SetSocketIP(char* pchbuf)
{
    if(pchbuf == NULL)
    {
        return;
    }
    memset(m_achIP, 0, MAX_IP_LENGTH);
    int nlength = (strlen(pchbuf) >= MAX_IP_LENGTH ? MAX_IP_LENGTH: strlen(pchbuf));
    memcpy(m_achIP, pchbuf, nlength);
    m_achIP[nlength] = '\0';
}

void CSocketManager::SetSocketPort(u32 dwPort)
{
    m_dwPort = dwPort;
}

DWORD WINAPI Rcv( LPVOID lpParam )
{
    SOCKET sClient = *(SOCKET*)lpParam;
    int retVal;
    u8 *pRecvbuf = new u8[2000000];
    memset( pRecvbuf, 0, 2000000 );
    while(1)
    {
        retVal = recv( sClient, (char *)pRecvbuf, 2000000, 0 );
        if ( retVal == SOCKET_ERROR ) {
            PrtAirDispRemoteMsg( "recv failed!\r\n" );
            break;
        } else {
            PrtAirDispRemoteMsg( "recv message from touch\r\n" );
        }
    }

    delete pRecvbuf;
    pRecvbuf = NULL;

    return 0;
}
UINT ThreadAccept(LPVOID pParam)
{
    CSocketManager *pThis = (CSocketManager*)pParam;
    if (!pThis)
    {
        return -1;
    }

    sockaddr_in cliAddr;
    SOCKET CliSocket;
    int dwCliAddrLen = sizeof(cliAddr);
    //while (1)
    {
        CliSocket = accept(pThis->GetSocket(), (SOCKADDR FAR*)&cliAddr, &dwCliAddrLen);
        if(CliSocket == INVALID_SOCKET)
        {
            CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg("accept error\n");
            //continue; //继续等待下一次连接
        }
        else
        {
            //HANDLE hThread2;
            DWORD dwThreadId2;

            //hThread1 = ::CreateThread(NULL, NULL, Snd, (LPVOID*)&sClient, 0, &dwThreadId1);
            pThis->m_hRcvThread = ::CreateThread(NULL, NULL, Rcv, (LPVOID*)&CliSocket, 0, &dwThreadId2);

            //::WaitForSingleObject(hThread1, INFINITE);
            ::WaitForSingleObject(pThis->m_hRcvThread, INFINITE);
            //::CloseHandle(hThread1);
            ::CloseHandle(pThis->m_hRcvThread);
        }
    }
}

void CSocketManager::OpenSocket()
{
    m_sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_sServer == INVALID_SOCKET)
    {
        CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg("Socket creation error.\r\n");
        return;
    }
    // 设置发送接受超时
    UINT nNetTimeout = 3000;//超时时间 3s
    setsockopt(m_sServer, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout,sizeof(int));
    setsockopt(m_sServer, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
    // 设置缓冲区长度
    UINT nRcvBuf = 2000000;
    setsockopt(m_sServer, SOL_SOCKET, SO_SNDBUF,(char*)&nRcvBuf, sizeof(UINT));
    // 允许地址重用
    BOOL bReuseaddr=TRUE;
    setsockopt(m_sServer, SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL));

    // 设置为非阻塞的socket  
    /*int iMode = 1;  
    ioctlsocket(m_sServer, FIONBIO, (u_long FAR*)&iMode);*/

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(m_dwPort);
    serAddr.sin_addr.S_un.S_addr = inet_addr(m_achIP);

    // 绑定
    if ( bind(m_sServer, (LPSOCKADDR)&serAddr, sizeof(serAddr)) == SOCKET_ERROR )
    {
        CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg("bind error.\r\n");
        closesocket( m_sServer );
        WSACleanup();
        return;
    }

    // 监听
    if ( listen(m_sServer, 5) == SOCKET_ERROR )
    {
        CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg("listen error.\r\n");
        closesocket( m_sServer );
        WSACleanup();
        return;
    }

    m_bIsSocketOpen = true;

    AfxBeginThread(ThreadAccept, this);

    // 设回为阻塞socket  
    //iMode = 0;  
    //ioctlsocket(m_sServer, FIONBIO, (u_long FAR*)&iMode); //设置为阻塞模式

    return;
}

void CSocketManager::CloseSocket()
{
    closesocket(m_sServer);
    CSocketManager::m_bIsSocketOpen = false;
    //OspPost(MAKEIID(AID_RKC_APP,0), UI_RKC_DISCONNECTED);
    //PRINTMSG( "关闭 Scoket...");
    TerminateThread(m_hRcvThread, 0);
}

bool CSocketManager::IsSocket()
{
    return CSocketManager::m_bIsSocketOpen;
}

SOCKET CSocketManager::GetSocket()
{
    return m_sServer;
}

void CSocketManager::SendDataPack( u8* pchbuf, u32 dwDataLen)
{
    if ( IsSocket() )
    {
        int ret = send(m_sServer, (const char*)pchbuf, dwDataLen, 0);
        if (ret == -1)
        {
            //发送超时
            //PRINTMSG("send data timeout.\r\n");
        }
    }
}
/*
void CSocketManager::SendDataPack()
{
    if (m_evWaitMsg != 0)
    {
        PrtRkcMsg( m_evWaitMsg, emEventTypeScoketSend, "等待回应中,拒绝发送...");
        return;
    }
    EnterCriticalSection(&m_csMsgLock);
    BOOL bIsMsgEmpty = m_RkcMsgQueue.IsEmpty();
    LeaveCriticalSection(&m_csMsgLock);
    if (!bIsMsgEmpty)
    {
        CRkMessage rkmsg;
        EnterCriticalSection(&m_csMsgLock);
        m_RkcMsgQueue.PopMsg(rkmsg);
        LeaveCriticalSection(&m_csMsgLock);
        TRK100MsgHead tRK100MsgHead = *(TRK100MsgHead*)(rkmsg.GetBody());
        //设置等待回复的消息为发送的消息+1 没有回复这不可继续发送消息
        m_evWaitMsg = ntohl(tRK100MsgHead.dwEvent) + 1;
        int ret = send(m_sClient, (const char*)rkmsg.GetBody(), rkmsg.GetBodyLen(), 0);
        if (ret == -1)
        {
            //发送超时
            PrtRkcMsg( tRK100MsgHead.dwEvent, emEventTypeScoketSend, "发送超时！");
        }
        //发送后等待接受消息
        while (m_evWaitMsg != 0)
        {
            RecvDataPack();
        }
    }
}*/
/*
void CSocketManager::RecvDataPack()
{
    char recData[RK_MAXLEN_MESSAGE] = {0};
    int ret = recv(m_sClient, recData, RK_MAXLEN_MESSAGE, 0);
    if(ret>0)
    {
        recData[ret] = 0x00;
        //消息放到OSP回调线程
        CRkMessage rkmsg;
        memset(&rkmsg,0,sizeof(CRkMessage));
        TRK100MsgHead tRK100MsgHead = *(TRK100MsgHead*)(recData);
        tRK100MsgHead.dwEvent = ntohl(tRK100MsgHead.dwEvent);

        //是等待的恢复消息 释放继续发送
        if (m_evWaitMsg == tRK100MsgHead.dwEvent)
        {
            m_evWaitMsg = 0;
        }
        if (RK100_EVT_SET_HEART_BEAT_ACK == tRK100MsgHead.dwEvent)//心跳包
        {
            g_nHeartBeatLostCount = 0;//未断链 重新计数
            PrtRkcMsg( RK100_EVT_SET_HEART_BEAT_ACK, emEventTypeScoketRecv, "收到心跳包...");
        }
        else
        {
            rkmsg.SetBody(recData, sizeof(TRK100MsgHead) + tRK100MsgHead.wMsgLen);
            OspPost(MAKEIID(AID_RKC_APP,0), tRK100MsgHead.dwEvent , rkmsg.GetBody() , sizeof(TRK100MsgHead) + tRK100MsgHead.wMsgLen);
        }
    }
    else if (ret == -1)
    {
        //接受超时
        PrtRkcMsg( m_evWaitMsg, emEventTypeScoketRecv, "接受超时！");

        if (m_evWaitMsg == RK100_EVT_LOGIN_ACK)//登录超时
        {
            TRK100MsgHead tRK100MsgHead;
            memset(&tRK100MsgHead, 0, sizeof(TRK100MsgHead));
            tRK100MsgHead.dwEvent = RK100_EVT_LOGIN_ACK;
            tRK100MsgHead.wOptRtn = RK100_OPT_ERR_UNKNOWN;
            OspPost(MAKEIID(AID_RKC_APP,0), tRK100MsgHead.dwEvent , &tRK100MsgHead , sizeof(TRK100MsgHead));
        }
        m_evWaitMsg = 0;
    }
}*/
/*
void CSocketManager::StartHeartBeat()
{
    g_nHeartBeatLostCount = 0;
    //启动心跳线程
    g_bHeartBeatKeep = true;
    AfxBeginThread(ThreadHeartBeat, NULL);
}
void CSocketManager::StopHeartBeat()
{
    g_bHeartBeatKeep = false;
    g_nHeartBeatLostCount = 0;
}*/