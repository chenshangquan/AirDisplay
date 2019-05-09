/** @defgroup 登录逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.27
 */
#if !defined(AFX_LOGINLOGIC_H_)
#define AFX_LOGINLOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMenuLogic : public CNotifyUIImpl
{
public:
	CMenuLogic();
	~CMenuLogic();

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

    /** 窗口大小变化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnSize(TNotifyUI& msg);

    //点击最小化按钮
    bool OnMinBtnClicked(TNotifyUI& msg);
    //点击关闭按钮
    bool OnCloseBtnClicked(TNotifyUI& msg);
    //点击登录按钮
    bool OnLoginBtnClicked(TNotifyUI& msg);

    //自动登录
    bool OnCheckAutoLoginSel(TNotifyUI& msg);
    //记住密码
    bool OnCheckRemPassWordSel(TNotifyUI& msg);

    //显示提示定时器响应
    bool OnShowTipTimer(TNotifyUI& msg);

    bool OnSipToolConnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnSipToolDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    void ShowTip(CString strTip);

    CString GetIniFilePath();

    APP_DECLARE_MSG_MAP()

private:
};

#endif // !defined(AFX_LOGINLOGIC_H_)