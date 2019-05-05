#include "stdafx.h"
#include "siptoollib.h"
#include "siptoolsession.h"
#include "siptoolConst.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSipToolLib::CSipToolLib()
{

}

CSipToolLib::~CSipToolLib()
{

}

/*=============================================================================
  函 数 名： CreateSession
  功    能： 创建实现了接口SessionCtrlIF的对象
  算法实现： 接口使用完成后,调用DestroyInstance方法销毁对象
  全局变量： 
  参    数： SessionCtrlIF **ppICnt 成功返回SessionCtrlIF接口,失败返回NULL
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期        版本        修改人        走读人    修改内容
 2018.02.26     1.0             ylp                     创建
=============================================================================*/
u16 CSipToolLib::CreateSession(CSipToolSessionCtrlIF **ppICnt)
{
    CSipToolSession *pConnect = new CSipToolSession();
    if(pConnect == NULL)
    {
        *ppICnt = NULL;
        return ERR_SIPTOOL_CREATINSTANCE;
    }
    else
    {
        *ppICnt = pConnect;
        return NO_ERROR;
    }
}

/*=============================================================================
  函 数 名： DestroySession
  功    能： 销毁实现了接口SessionCtrlIF的对象
  算法实现： 
  全局变量： 
  参    数： SessionCtrlIF **ppICnt 输入接口SessionCtrlIF,成功后返回NULL
  返 回 值： u16 
  说    明： 只能销毁由CreateInstance方法创建的对象
  -----------------------------------------------------------------------------
  修改记录：
  日  期        版本        修改人        走读人    修改内容
 2018.02.26     1.0              ylp                    创建
=============================================================================*/
u16 CSipToolLib::DestroySession(CSipToolSessionCtrlIF **ppICnt)
{
    CSipToolSession *pConnect = dynamic_cast<CSipToolSession*>(*ppICnt);
    if(pConnect == NULL)
    {
        return ERR_SIPTOOL_INTERFACE;
    }
    delete pConnect;
    *ppICnt = NULL;
    return NO_ERROR;
}