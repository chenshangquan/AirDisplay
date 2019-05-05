/** @defgroup 网络设置逻辑单元 
 *  @version V1.0.0
 *  @author  csq
 *  @date    2019.4.25
 */
#if !defined(AFX_NETWORKSETUP_H_)
#define AFX_NETWORKSETUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNetworkSetupLogic : public CNotifyUIImpl, public Singleton<CNetworkSetupLogic> 
{
public:
	CNetworkSetupLogic();
	~CNetworkSetupLogic();

    bool OnSipToolConnected(WPARAM wparam);

protected:
    /** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    /** 关闭消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestroy(TNotifyUI& msg);

    //点击最小化按钮
    bool OnMinBtnClicked(TNotifyUI& msg);
    //点击关闭按钮
    bool OnCloseBtnClicked(TNotifyUI& msg);

    //Siptool connected
    bool OnSipToolConnected(WPARAM wparam, LPARAM lparam, bool& bHandle);

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_NETWORKSETUP_H_)