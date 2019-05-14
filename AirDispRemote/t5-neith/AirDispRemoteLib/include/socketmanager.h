#pragma once
//#include "kdvtype.h"
//#include "rkconst.h"
//#include <stdio.h>  
#include <winsock2.h>
//#include <queue>

//#pragma comment(lib,"ws2_32.lib")

#define MAX_IP_LENGTH 16

class CSocketManager
{
public:

    CSocketManager();
    ~CSocketManager();

    //得到全局的Manager变量
    static CSocketManager* m_pSocketManager; 
    static CSocketManager* GetSocketManager(); 

    void SetSocketIP(char* pchbuf);

    void SetSocketPort(u32 dwPort);

    void OpenSocket();

    void CloseSocket();

    bool IsSocket();
    //获取Socket
    SOCKET GetSocket();

    void SendDataPack( u8* pchbuf, u32 dwDataLen );

    //void SendDataPack();

    //void RecvDataPack();

    //心跳包相关
    //void StartHeartBeat();//启动心跳
    //void StopHeartBeat();//停止心跳

public:
    //CRkcScoketMsgQueue          m_RkcMsgQueue;  //等待发送的消息队列
    //u32                         m_evWaitMsg;    //等待回复的消息

    static bool                 m_bIsSocketOpen;
    HANDLE  m_hRcvThread;      //接收线程句柄
protected:
    CRITICAL_SECTION            m_csMsgLock;    //消息发送临界锁
private:

    SOCKET  m_sServer;
    SOCKET  m_sClient;
    s8      m_achIP[MAX_IP_LENGTH];
    u32     m_dwPort;
};

#define SOCKETWORK CSocketManager::GetSocketManager()