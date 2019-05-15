/** @defgroup 双流显示
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016.8.9
 */
#pragma once
#include "Decoder.h"

class CVideoLogic : public CNotifyUIImpl, public Singleton<CVideoLogic>
{
public:
	CVideoLogic(void);
	~CVideoLogic(void);

    //退出预览
    bool OnHideVideo(TNotifyUI& msg);
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
	
	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	bool OnAirDispRemoteConnected( WPARAM wparam, LPARAM lparam, bool& bHandle );
    bool OnAirDispRemoteMediaPort( WPARAM wparam, LPARAM lparam, bool& bHandle );
	bool OnAirDispRemoteResetVideoPos( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnShowVideo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool HideDualView();
	void RestoreVedioWnd();
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	bool OnDualCodeEnCryptKeyNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	void AskKeyFrame( BOOL32 bForce );

	void SetDecVol( u8 abyVol );

	u8 GetDecVol();
	APP_DECLARE_MSG_MAP()
private:
	void InitParam();

private:
	CDecoder  m_cDecoder;

    //BOOL32 m_bRecvStream;
    //BOOL32 m_bDecod;

    //BOOL32 m_bFullScreen;
	//BOOL32 m_bIsClkBtn;          //用于标志是否是点了tpad收看演示按钮才收到的回复消息
	TTpEncryptKey m_tTpEncryptKey;

};