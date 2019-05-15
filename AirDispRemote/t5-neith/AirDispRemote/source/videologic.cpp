#include "StdAfx.h"
#include <Shlobj.h>
#include <shlwapi.h>
#include "videologic.h"
//#include "codeclib_vs2010.h"
#include "messageboxlogic.h"
//#include "mainframelogic.h"
//#include "airdispremotemsgdriver.h"

template<> CVideoLogic* Singleton<CVideoLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CVideoLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("VideoLayout"), OnCreate)
	MSG_INIWINDOW(_T("VideoLayout"), OnInit)
	//MSG_DBCLICK(_T("VideoLayout"), OnHideVideo)

    /*USER_MSG(WM_CMS_SHOWVIDEO,OnShowVideo)
    USER_MSG(UI_CNS_RECV_DUAL_NOTIFY,OnDualRecvStateNotify)
    USER_MSG(UI_CNSINS_START_DUALCODESTREAM_RSP,OnStartRsp)
    USER_MSG(UI_CNS_DUAL_KEY_NOTIFY,OnDualCodeEnCryptKeyNty)
    USER_MSG(UI_CNS_DISCONNECTED,OnDisconnect)*/
    //USER_MSG(UI_AIRDISPREMOTE_SHOWVIDEO, OnShowVideo)
	USER_MSG(UI_AIRDISPREMOTE_CONNECTED , OnAirDispRemoteConnected)
    USER_MSG(UI_AIRDISPREMOTE_MEDIAPORT , OnAirDispRemoteMediaPort)
	USER_MSG(UI_AIRDISPREMOTE_RESETVIDEOPOS , OnAirDispRemoteResetVideoPos)
APP_END_MSG_MAP()


CVideoLogic::CVideoLogic(void)
{
	//m_bRecvStream = FALSE;
	//m_bDecod = FALSE;
	//m_bFullScreen = FALSE;
	//m_bIsClkBtn = FALSE;
	m_cDecoder.SetAudioVolume( 255 );
}

CVideoLogic::~CVideoLogic(void)
{
}

bool CVideoLogic::OnCreate(TNotifyUI& msg)
{
	REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
	return false;
}

bool CVideoLogic::OnInit(TNotifyUI& msg)
{
    s32 nTop = 30;
    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        nTop = s32(nTop * fAdpY);
    }
	SetWindowPos( m_pm->GetPaintWindow(), NULL, 1, nTop, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE);

	return NO_ERROR;
}

bool CVideoLogic::OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	//m_bRecvStream = FALSE;
	//m_bDecod = FALSE;

	TNotifyUI msg;
	OnHideVideo(msg);
	return true;
}

bool CVideoLogic::OnHideVideo(TNotifyUI& msg)
{
	//ComInterface->SetReceiveDual( FALSE );

	bool bVis = WINDOW_MGR_PTR->IsWindowVisible(g_stcStrVideoDlg.c_str());
	if ( !bVis )
	{
		return true;
	}

	m_cDecoder.StopPlay();
	//m_bDecod = FALSE;
	WINDOW_MGR_PTR->ShowWindow( g_stcStrVideoDlg.c_str(), false );
	return true;
}

bool CVideoLogic::OnAirDispRemoteConnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	//m_pm->DoCase(_T("caseNormal"));

	u32 dwRemoteIP = (u32)wparam;
	u32 dwLocalIP = (u32)lparam;
	m_cDecoder.SetNetSendIP(dwLocalIP, dwRemoteIP);

	return true;
}

bool CVideoLogic::OnAirDispRemoteMediaPort( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	u32 dwRemoteVidPort = (u32)wparam;
	u32 dwRemoteAudPort = (u32)lparam;
    m_cDecoder.SetRemoteMediaSendPort(dwRemoteVidPort, dwRemoteAudPort);
    //m_cDecoder.SetNetSendPara();

    NetSendMediaPort tNetSendMediaPort;
    m_cDecoder.GetLocalMediSendPort(tNetSendMediaPort);
    CAirDispRemoteComInterface->SendLocalMediaPort(tNetSendMediaPort.m_dwVidPort, tNetSendMediaPort.m_dwAudPort);

    bool bHdle = true;
    OnShowVideo(1,0,bHdle);

	return true;
}

bool CVideoLogic::OnAirDispRemoteResetVideoPos( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    s32 nTop = 30;
    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        nTop = s32(nTop * fAdpY);
    }
    SetWindowPos( m_pm->GetPaintWindow(), NULL, 1, nTop, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE);

    return true;
}

bool CVideoLogic::OnShowVideo(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    InitParam();
    RestoreVedioWnd( );
    m_cDecoder.StartPlay(); 

	return S_OK;
}

bool CVideoLogic::HideDualView()
{      
	bool bVis = WINDOW_MGR_PTR->IsWindowVisible(g_stcStrVideoDlg.c_str());
	if ( bVis )
	{   
		WINDOW_MGR_PTR->ShowWindow(g_stcStrVideoDlg.c_str(), false);
	}

	//m_cDecoder.SetWnd(NULL);
	m_cDecoder.StopPlay();
	//m_bDecod = FALSE;
	////ComInterface->SetReceiveDual( FALSE );

	return true;
}

void CVideoLogic::RestoreVedioWnd()
{
	Window *pVideo = WINDOW_MGR_PTR->GetWindow(g_stcStrVideoDlg.c_str());

	if ( pVideo != NULL )
	{   
		m_cDecoder.SetWnd( pVideo->GetHWND() ); 
		//pVideo->Invalidate();//2012-7-26 解决窗口还原后人残留大窗口图像       
	} 

	//切换大小时请求关键帧，防止白屏 -2014.3.4 xcr
	m_cDecoder.AskKeyFrame( TRUE );

	WINDOW_MGR_PTR->ShowWindow(g_stcStrVideoDlg.c_str());
}

LRESULT CVideoLogic::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if ( uMsg == WM_INPUT )
	{
		INT nData;
		UINT cbSize = 0;
		nData = GetRawInputData(   
			(HRAWINPUT)lParam,
			(UINT)RID_INPUT,
			(LPVOID)NULL,
			(PUINT) &cbSize,
			(UINT)sizeof(RAWINPUTHEADER)
			);

		LPBYTE lpbBuffer = new BYTE[cbSize];
		nData = GetRawInputData(   
			(HRAWINPUT)lParam,
			(UINT)RID_INPUT,
			(LPVOID)lpbBuffer,
			(PUINT)&cbSize,
			(UINT)sizeof(RAWINPUTHEADER)
			);

		RAWINPUT * pRawInput = (RAWINPUT *) lpbBuffer;

		/*CString strTemp;
		strTemp.Format( _T("CVideoLogic msg:%d  Type %d,Flags %d,MakeCode %d VKey:%d ExtraInformation:%d Message:%d Reserved:%d\n"),
			uMsg, pRawInput->header.dwType, pRawInput->data.keyboard.Flags, pRawInput->data.keyboard.MakeCode, 
			pRawInput->data.keyboard.VKey, pRawInput->data.keyboard.ExtraInformation, pRawInput->data.keyboard.Message,pRawInput->data.keyboard.Reserved);
		AfxOutputDebugString( strTemp );*/
		if (pRawInput->header.dwType == RIM_TYPEKEYBOARD) 
		{
			if( pRawInput->data.keyboard.Message == WM_KEYUP)
			{
				if (pRawInput->data.keyboard.VKey == VK_VOLUME_DOWN)
				{     
					////CMainFrameLogic::GetSingletonPtr()->OnThinkpadVolumeLow(5);
				}
				else if ( pRawInput->data.keyboard.VKey == VK_VOLUME_UP )
				{
					////CMainFrameLogic::GetSingletonPtr()->OnThinkpadVolumeAdd(5);
				}

			}
		}

		delete[] lpbBuffer;
	}
	
	return CNotifyUIImpl::MessageHandler( uMsg, wParam, lParam, bHandled);
}

bool CVideoLogic::OnDualCodeEnCryptKeyNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_tTpEncryptKey = *(TTpEncryptKey*)wParam;

	return NO_ERROR;
}

void CVideoLogic::AskKeyFrame(BOOL32 bForce)
{
	////ComInterface->ReqKeyFrame( bForce );
}

void CVideoLogic::SetDecVol(u8 abyVol)
{
	m_cDecoder.SetAudioVolume(abyVol);
}

u8 CVideoLogic::GetDecVol()
{
	u8 abyVol = 0;
	m_cDecoder.GetAudioVolume( abyVol );
	return abyVol;
}

void CVideoLogic::InitParam()
{
	//SET_ASK_MAIN_FRAME_FUN( &CVideoLogic::AskKeyFrame, CVideoLogic::GetSingletonPtr(), CVideoLogic )

    m_cDecoder.SetVidDecZoomPolicy(EN_ZOOM_SCALE); //EN_ZOOM_CUT是全屏显示

	TNetRSParam tNetRSParam;
	tNetRSParam.m_wFirstTimeSpan = 40;
	tNetRSParam.m_wSecondTimeSpan = 0 /*80*/;  //第二个重传检测点
	tNetRSParam.m_wThirdTimeSpan = 0 /*120*/;   //第三个重传检测点
	tNetRSParam.m_wRejectTimeSpan = 2000;  //过期丢弃的时间跨度
	m_cDecoder.SetNetFeedbackVideoParam( /*tNetRSParam,*/ TRUE );
	m_cDecoder.SetNetFeedbackAudioParam( /*tNetRSParam,*/ TRUE );

	//设置视频接受的端口和Ip地址
    m_cDecoder.SetNetSendPara();
	TMediaParam  tMonitorParam;
	tMonitorParam.abyDynamicPayLoad[0] = MEDIA_TYPE_H264;
	tMonitorParam.abyDynamicPayLoad[1] = MEDIA_TYPE_RED;  //MEDIA_TYPE_AACLC

	tMonitorParam.abyRealType[0] = MEDIA_TYPE_H264;
	tMonitorParam.abyRealType[1] = MEDIA_TYPE_RED;  //MEDIA_TYPE_AACLC

	tMonitorParam.atEncryptKey[0].byLen = 0;
	tMonitorParam.atEncryptKey[1].byLen = 0;

	m_cDecoder.SetVideoParam(tMonitorParam);

    // 音频解码参数
	TAudAACParam tAACParam;
	tAACParam.dwChannel = 1;
	tAACParam.dwSamplePerSecond = 32000;
	m_cDecoder.SetAACParam(tAACParam);

	m_cDecoder.SetNetRcvParam();        //设置音视频网络接收参数

	//if ( 0 != m_tTpEncryptKey.byLen )
	//{
	//	m_cDecoder.SetDecryptKey( (char*)m_tTpEncryptKey.byKey, m_tTpEncryptKey.byLen, AES_ENCRYPT_MODE/*m_tTpEncryptKey.emEncryType*/ );
	//}
}