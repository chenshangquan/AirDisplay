#pragma once

#include "AirDispRemoteSessionCtrlIF.h"

class CAirDispRemoteLib  
{

public:
	CAirDispRemoteLib();
	virtual ~CAirDispRemoteLib();

	/*功能	创建实现了接口SessionCtrlIF的对象
	参数	ppICnt	[out]成功返回SessionCtrlIF接口,失败返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	接口使用完成后,调用DestroyInstance方法销毁对象*/
	static u16 CreateSession(CAirDispRemoteSessionCtrlIF **ppICnt);
	/*功能	销毁实现了接口SessionCtrlIF的对象
	参数	ppICnt	[in, out]接口SessionCtrlIF,成功后返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	只能销毁由CreateInstance方法创建的对象*/
	static u16 DestroySession(CAirDispRemoteSessionCtrlIF **ppICnt);

};

