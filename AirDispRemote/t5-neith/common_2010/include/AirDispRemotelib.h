#pragma once

#include "AirDispRemoteSessionCtrlIF.h"

class CAirDispRemoteLib  
{

public:
	CAirDispRemoteLib();
	virtual ~CAirDispRemoteLib();

	/*����	����ʵ���˽ӿ�SessionCtrlIF�Ķ���
	����	ppICnt	[out]�ɹ�����SessionCtrlIF�ӿ�,ʧ�ܷ���NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	�ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���*/
	static u16 CreateSession(CAirDispRemoteSessionCtrlIF **ppICnt);
	/*����	����ʵ���˽ӿ�SessionCtrlIF�Ķ���
	����	ppICnt	[in, out]�ӿ�SessionCtrlIF,�ɹ��󷵻�NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	ֻ��������CreateInstance���������Ķ���*/
	static u16 DestroySession(CAirDispRemoteSessionCtrlIF **ppICnt);

};

