/** @defgroup 会议提示弹窗
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015.1.5
 */
#pragma once

class CMessageBoxLogic : public CNotifyUIImpl
{
public:
	CMessageBoxLogic(void);
	~CMessageBoxLogic(void);
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

	bool OnDestroy(TNotifyUI& msg);

	/** 返回
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** 退出
	*  @param[in] 消息
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//抢登
	bool OnUmsGrabLogin( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//升级
	bool OnUpdateSysCmd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()

};

bool showMessageBox(LPCTSTR lpstrText, bool bIsShowCancel = false);
#define ShowMessageBox showMessageBox
