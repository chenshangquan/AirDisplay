/** @defgroup ������ʾ����
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2015.1.5
 */
#pragma once

class CMessageBoxLogic : public CNotifyUIImpl
{
public:
	CMessageBoxLogic(void);
	~CMessageBoxLogic(void);
protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	bool OnDestroy(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** �˳�
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnUmsGrabLogin( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����
	bool OnUpdateSysCmd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()

};

bool showMessageBox(LPCTSTR lpstrText, bool bIsShowCancel = false);
#define ShowMessageBox showMessageBox
