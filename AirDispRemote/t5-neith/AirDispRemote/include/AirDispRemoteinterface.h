/** @defgroup AirDispRemote����AirDispRemotelib�Ĺ����ӿ� 
 *  @version V1.0.0
 *  @author  Ҷ��ƽ
 *  @date    2019.4.10
 */
#pragma once

#include "AirDispRemotelib.h"

class CAirDispRemoteInterface
{
public:
    /** ��ȡ�ӿ�ָ�� */
    static CAirDispRemoteInterface* GetCommIF();
    /** ���ٽӿ�ָ�� */
    void DestroyCommIF();

public:
    /** ��ȡ��Ƕ�Ĵ��ھ��
	*   @return HWND ���ش��ھ�� 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/** �����Ự
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void CreateSession();

	/** ���ٻỰ
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void DesdroySession();

    /**
	*   ��¼Sip
	*/ 
    u16 SocketConnect( u32 dwIp, s8* szUser , s8* szPwd);
    /**
	*   ��ʼ����
	*/ 
    u16 LinkSipServer();
    /**
	*   ���ӶϿ�
	*/ 
    u16 CloseLink();
    /**
	*   ���ͱ�������ý�������˿�
	*/ 
    u16 SendLocalMediaPort(u32 dwLocalVidPort, u32 dwLocalAudPort); 

    

private:
    static  CAirDispRemoteInterface*  m_pMySelf;
    CAirDispRemoteInterface(void);
    HWND                 m_hRecvWnd;         // ��Ƕ������Ϣ�Ĵ���
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    WNDPROC              m_wndprocOld;       // ϵͳ���ڹ���

    CAirDispRemoteSessionCtrlIF   *m_pAirDispRemoteSession;       //url�Ự

    CAirDispRemoteSysCtrlIF  *m_pSysCtrlIf;

    TLoginInfo           m_tLoginInfo;//�����¼��IP �˿� �û��� ����
};

#define CAirDispRemoteComInterface  CAirDispRemoteInterface::GetCommIF()
