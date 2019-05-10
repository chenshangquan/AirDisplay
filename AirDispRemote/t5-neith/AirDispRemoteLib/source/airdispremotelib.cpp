#include "stdafx.h"
#include "AirDispRemotelib.h"
#include "AirDispRemotesession.h"
#include "AirDispRemoteConst.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAirDispRemoteLib::CAirDispRemoteLib()
{

}

CAirDispRemoteLib::~CAirDispRemoteLib()
{

}

/*=============================================================================
  �� �� ���� CreateSession
  ��    �ܣ� ����ʵ���˽ӿ�SessionCtrlIF�Ķ���
  �㷨ʵ�֣� �ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���
  ȫ�ֱ����� 
  ��    ���� SessionCtrlIF **ppICnt �ɹ�����SessionCtrlIF�ӿ�,ʧ�ܷ���NULL
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��        �汾        �޸���        �߶���    �޸�����
 2018.02.26     1.0             ylp                     ����
=============================================================================*/
u16 CAirDispRemoteLib::CreateSession(CAirDispRemoteSessionCtrlIF **ppICnt)
{
    CAirDispRemoteSession *pConnect = new CAirDispRemoteSession();
    if(pConnect == NULL)
    {
        *ppICnt = NULL;
        return ERR_AirDispRemote_CREATINSTANCE;
    }
    else
    {
        *ppICnt = pConnect;
        return NO_ERROR;
    }
}

/*=============================================================================
  �� �� ���� DestroySession
  ��    �ܣ� ����ʵ���˽ӿ�SessionCtrlIF�Ķ���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� SessionCtrlIF **ppICnt ����ӿ�SessionCtrlIF,�ɹ��󷵻�NULL
  �� �� ֵ�� u16 
  ˵    ���� ֻ��������CreateInstance���������Ķ���
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��        �汾        �޸���        �߶���    �޸�����
 2018.02.26     1.0              ylp                    ����
=============================================================================*/
u16 CAirDispRemoteLib::DestroySession(CAirDispRemoteSessionCtrlIF **ppICnt)
{
    CAirDispRemoteSession *pConnect = dynamic_cast<CAirDispRemoteSession*>(*ppICnt);
    if(pConnect == NULL)
    {
        return ERR_AirDispRemote_INTERFACE;
    }
    delete pConnect;
    *ppICnt = NULL;
    return NO_ERROR;
}