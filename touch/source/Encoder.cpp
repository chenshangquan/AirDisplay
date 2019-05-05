// Decoder.cpp: implementation of the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Encoder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEC_CHECK_KEY_FRSME_ELAPS  1000  
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncoder *g_pDecoder = NULL;

CEncoder::CEncoder() 
{   
    m_hTimerAskKeyFrm = 0;
    m_hTimerAskKeyFrmForce = 0;

    g_pDecoder = this;
    
    m_bAudio = TRUE;
    m_emMediaMode = emTPMediaAV;
    
    m_bPlayed = FALSE;
    m_pcEncoder = NULL;

	MediaSDKInitial();
	InitEncoder();
}

CEncoder::~CEncoder()
{   
    StopPlay();

    if (m_pcEncoder != NULL) 
    {
        delete m_pcEncoder;
        m_pcEncoder = NULL;
    }
    
 
}

void CEncoder::StartPlay()
{
	StartEnc(); 
	m_bPlayed = TRUE;
}

void CEncoder::StartEnc()
{
	ASSERT(m_pcEncoder != NULL);

	if(m_emMediaMode == emTPMediaAV)
	{
		PlayVideo();
        if (m_bAudio) 
        {
            PlayAudio();
        }
	}
	else if(m_emMediaMode == emTPMediaVideo)
	{
		PlayVideo();
	}
	else if(m_emMediaMode == emTPMediaAudio && m_bAudio)
	{
		PlayAudio();
	}
}
void CEncoder::StopPlay()
{   
    KillTimer( NULL, m_hTimerAskKeyFrm );
    KillTimer( NULL, m_hTimerAskKeyFrmForce );

	StopEnc();
	m_bPlayed = FALSE;
}

void CEncoder::StopEnc()
{
	if (m_pcEncoder == NULL) 
    {
        return;
    }
    
	if(m_emMediaMode == emTPMediaAV)
	{
		StopVideo();
        if (m_bAudio) 
        {
            StopAudio();
        }
	}
	else if(m_emMediaMode == emTPMediaVideo)
	{
		StopVideo();
	}
	else if(m_emMediaMode == emTPMediaAudio && m_bAudio)
	{
		StopAudio();
	}
}

void CEncoder::PlayVideo()
{
    StopVideo();

	if(CODEC_NO_ERROR != m_pcEncoder->StartVideoEnc())//开始图象编码
	{
        SendError();
    }

	if (CODEC_NO_ERROR != m_pcEncoder->StartVideoCap())//开始视频采集
	{
		 SendError();
	}

}

void CEncoder::StopVideo()
{
	m_pcEncoder->StopVideoCap();
	m_pcEncoder->StopVideoEnc();
}

void CEncoder::PlayAudio()
{
    StopAudio();

	if(CODEC_NO_ERROR != m_pcEncoder->StartAudioEnc())//开始声音解码
	{
        SendError();
	}

	if(CODEC_NO_ERROR != m_pcEncoder->StartDeskSharedAud())//开始桌面音频共享
	{
        SendError();
	}
}

void CEncoder::StopAudio()
{
	m_pcEncoder->StopDeskSharedAud();
	m_pcEncoder->StopAudioEnc();
}

void CEncoder::SetWnd(HWND hwndPlay)
{
	m_hMonitor = hwndPlay;
}

BOOL CEncoder::IsPlayed()
{
    return m_bPlayed;
}

void CEncoder::SetVideoEncParam(TVideoEncParam tVideoEncParam)
{
	if(!m_pcEncoder)
	{
		return;
	}

	m_pcEncoder->SetVideoEncParam(&tVideoEncParam);
}

void CEncoder::GetVideoEncParam(TVideoEncParam &tVideoEncParam )
{
	if(!m_pcEncoder)
	{
		return;
	}

	m_pcEncoder->GetVideoEncParam(tVideoEncParam);
}

void CEncoder::SetAudioEncParam(u8 byAudioMode, u16 wAudioDuration)
{
	if(!m_pcEncoder)
	{
		return;
	}

	m_pcEncoder->SetAudioEncParam(byAudioMode, wAudioDuration);
}

u16 CEncoder::SetDeskSharedAudCallback(PDESKSHARECALLBACK pAudCallback, u32 dwContext)
{
	return m_pcEncoder->SetDeskSharedAudCallback(pAudCallback, dwContext);
}
	

u16 CEncoder::SetDeskSharedVidCallback(PDESKSHARECALLBACK pVidCallback, u32 dwContext)
{
	return m_pcEncoder->SetDeskSharedVidCallback(pVidCallback, dwContext);
}

u16 CEncoder::SetVideoCapStdCB(PVIDEOCAPSTDCALLBACK pVidCapStdCallBack, u32 dwContext)
{
	return m_pcEncoder->SetVideoCapStdCB(pVidCapStdCallBack, dwContext);
}

CKdvEncoder* CEncoder::GetEncoder()
{
	if ( m_pcEncoder != NULL )
	{
		return m_pcEncoder;
	}
	else
		return NULL;
}


 
void CEncoder::SendError()
{//还要不要 dyy
//     u32 dwError = 0;
//     m_pcDecoder->GetLastError(dwError);
//     CString csError;
//     csError.Format(_T("解码器出错：%d") , dwError);
//     //::SendMessage(m_hParent, WM_DECODER_ERROR, (WPARAM)(LPCTSTR)csError, 0);
}

u16   CEncoder::SetAudioVolume(u8 byVolume )   /*设置输出声音音量*/	
{
    return m_pcEncoder->SetAudioVolume(byVolume);
}
u16    CEncoder::GetAudioVolume(u8 &pbyVolume ) /*得到输出声音音量*/
{
    return m_pcEncoder->GetAudioVolume(pbyVolume);
}	

void CEncoder::SetVidDecZoomPolicy( enZoomMode emZoomMode )
{
    m_pcEncoder->SetVidCapToEncZoomPolicy(emZoomMode);
}


void CEncoder::InitEncoder()
{
	if(!m_pcEncoder)
	{
		m_pcEncoder = new CKdvEncoder;
	}

	if(!m_pcEncoder)
	{
		return;
	}

	TInitVidEncoder tVidInitParam;
	TInitAudEncoder tAudInitParam;
	memset(&tVidInitParam,0,sizeof(TInitVidEncoder));
	memset(&tAudInitParam,0,sizeof(TInitAudEncoder));

	tVidInitParam.m_dwCapType = CAP_DESKSHARE_ONLY;
	tVidInitParam.m_nCpuID = 0;
	tAudInitParam.m_nCpuID = 0;
	u16 wRet = 0, wRetA = 0;
	wRet = m_pcEncoder->InitialVideoEncoder(tVidInitParam);
	wRetA = m_pcEncoder->InitialAudioEncoder(tAudInitParam);

	if(wRet != CODEC_NO_ERROR || wRetA != CODEC_NO_ERROR)
	{
		BOOL bDel = TRUE;

		CString strError;
		strError.Format( _T("编码器创建错误%d") , wRet);

		if(bDel)
		{
			if (m_pcEncoder) 
			{
				delete m_pcEncoder;
				m_pcEncoder = NULL;
			}
			return;
		}
	}
}

void CEncoder::SetAskKeyFrm( BOOL32 bIsNeedProtect /*= TRUE*/ )
{
	if(!m_pcEncoder)
	{
		return;
	}
	m_pcEncoder->SetFastUpdate(bIsNeedProtect);
}

void CEncoder::SetAddLogoIntoEncStream( TFullLogoParam *ptLogoSetting )
{
	if(!m_pcEncoder)
	{
		return;
	}
	m_pcEncoder->SetAddLogoIntoEncStream(ptLogoSetting);
}

void CEncoder::GetMeidaLibVersion( s8 *pszVersion )
{
	if(!m_pcEncoder)
	{
		return;
	}
	m_pcEncoder->GetDeskShareLibVersion(pszVersion);
}

u16 CEncoder::SetAudZoominVol( float fZoominVol )
{
	return m_pcEncoder->SetAudZoominVol(fZoominVol);
}

void CEncoder::SetLowPowerMode()
{
	BOOL32 bSatus = FALSE;
	m_pcEncoder->GetCpuAdjustStatus( bSatus );
	if (  TRUE == bSatus )
	{
		m_pcEncoder->EnableCpuAdjust(FALSE);
		m_pcEncoder->SetDeskSharedVidFrame( LOW_POWER_FRAME );
	}
}

void CEncoder::SetNormalPowerMode()
{
	BOOL32 bSatus = TRUE;
	m_pcEncoder->GetCpuAdjustStatus( bSatus );
	if (  TRUE == bSatus )
	{
		m_pcEncoder->EnableCpuAdjust(FALSE);    //自动调整帧率功能去除
		m_pcEncoder->SetDeskSharedVidFrame( NORMAL_POWER_FRAME );
	}
}

bool CEncoder::GetCpuAdjustStatus( BOOL32 &bStatus )
{
	if ( m_pcEncoder == NULL )
	{
		return false;
	}

	m_pcEncoder->GetCpuAdjustStatus( bStatus );
	return true;
}

void CEncoder::SelectCaptureScreen( u32 dwScreenIndex, BOOL32 bStartCap /*= TRUE*/ )
{
	if ( m_pcEncoder == NULL )
	{
		return;
	}

	m_pcEncoder->SelectCaptureScreen(dwScreenIndex, bStartCap);
}

u16 CEncoder::SetEnableHwEnc(BOOL32 bEnable)
{
    if ( m_pcEncoder == NULL )
    {
        //PRINTMSG("SetEnableHwEnc Failed!\r\n");
        return 0;
    }

    return m_pcEncoder->SetEnableHwEnc(bEnable);
}

u16 CEncoder::GetEncoderStatus(TKdvEncStatus &tKdvEncStatus)
{
    if ( m_pcEncoder == NULL )
    {
        //PRINTMSG("GetEncoderStatus Failed!\r\n");
        return 0;
    }

    return m_pcEncoder->GetEncoderStatus(tKdvEncStatus);
}
