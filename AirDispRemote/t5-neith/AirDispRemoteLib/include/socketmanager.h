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

    //�õ�ȫ�ֵ�Manager����
    static CSocketManager* m_pSocketManager; 
    static CSocketManager* GetSocketManager(); 

    void SetSocketIP(char* pchbuf);

    void SetSocketPort(u32 dwPort);

    void OpenSocket();

    void CloseSocket();

    bool IsSocket();
    //��ȡSocket
    SOCKET GetSocket();

    void SendDataPack( u8* pchbuf, u32 dwDataLen );

    //void SendDataPack();

    //void RecvDataPack();

    //���������
    //void StartHeartBeat();//��������
    //void StopHeartBeat();//ֹͣ����

public:
    //CRkcScoketMsgQueue          m_RkcMsgQueue;  //�ȴ����͵���Ϣ����
    //u32                         m_evWaitMsg;    //�ȴ��ظ�����Ϣ

    static bool                 m_bIsSocketOpen;
    HANDLE  m_hRcvThread;      //�����߳̾��
protected:
    CRITICAL_SECTION            m_csMsgLock;    //��Ϣ�����ٽ���
private:

    SOCKET  m_sServer;
    SOCKET  m_sClient;
    s8      m_achIP[MAX_IP_LENGTH];
    u32     m_dwPort;
};

#define SOCKETWORK CSocketManager::GetSocketManager()