/** @defgroup ˫����ʾ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016.8.9
 */
#pragma once
#include "Decoder.h"

class CVideoLogic : public CNotifyUIImpl, public Singleton<CVideoLogic>
{
public:
	CVideoLogic(void);
	~CVideoLogic(void);

    //�˳�Ԥ��
    bool OnHideVideo(TNotifyUI& msg);
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
	
	/** ���� 
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
	//BOOL32 m_bIsClkBtn;          //���ڱ�־�Ƿ��ǵ���tpad�տ���ʾ��ť���յ��Ļظ���Ϣ
	TTpEncryptKey m_tTpEncryptKey;

};