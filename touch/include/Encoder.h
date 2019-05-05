// Decoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
#define AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "cncstruct.h" 

//编解码
#define SOFT_CODEC 
#pragma comment(lib, "osplib.lib")

#include "codecwrapper_win32.h"
#pragma comment(lib, "mediasdkvc10.lib")


#include "kdvmedianet.h"
#pragma comment(lib, "kdvmedianetdll.lib")

#include "commonstruct.h"

typedef struct tagAudAACParam
{
    u32 dwSamplePerSecond;
    u32 dwChannel;
}TAudAACParam;



class CCallBackBase
{ 
public:
    //定义回调函数的格式
    virtual void operator() (BOOL32) = 0;
};

template<class T> class CClsCallBackFun:public  CCallBackBase
{
public:
    //定义回调函数的格式
    typedef void (T::*MemberFunctionType)(BOOL32);
    
    // 构造的时候需要为函数赋值
    CClsCallBackFun ( MemberFunctionType pFunc, T* pObject )
    {
        m_pObject = pObject;
        m_pFuc = pFunc ;
    }

    
    virtual void operator()(BOOL32 bValue )
    {
         (m_pObject->*m_pFuc)( bValue );
    }
    
private:
    T* m_pObject;
    MemberFunctionType m_pFuc;	
};


#define LOW_POWER_FRAME      10
#define NORMAL_POWER_FRAME   30


class CEncoder  
{
public:
	CEncoder();
	virtual ~CEncoder();

public:
    CKdvEncoder* GetEncoder();
    void SnapShot();
    BOOL IsPlayed();
   
    void StartPlay();
    void StopPlay();
    void StartEnc();
    void StopEnc(); 


    u16  SetAudioVolume(u8 byVolume );  /*设置输出声音音量*/	
    u16  GetAudioVolume(u8 &pbyVolume );/*得到输出声音音量*/ 

	u16	SetAudZoominVol(float fZoominVol);//设置音频采集信号放大倍数（如：1.0f就是不放大，2.0f就是放大1倍）
     
    void SetVidDecZoomPolicy( enZoomMode emZoomMode );
	 
	void SetVideoEncParam(TVideoEncParam tVideoEncParam);          //设置视频编码参数
	void GetVideoEncParam(TVideoEncParam &tVideoEncParam );        //得到视频编码参数
	void SetAudioEncParam(u8 byAudioMode, u16 wAudioDuration = 0); //设置音频编码参数


	u16 SetDeskSharedAudCallback(PDESKSHARECALLBACK pAudCallback, u32 dwContext);
	u16	SetDeskSharedVidCallback(PDESKSHARECALLBACK pVidCallback, u32 dwContext);
	u16 SetVideoCapStdCB(PVIDEOCAPSTDCALLBACK pVidCapStdCallBack, u32 dwContext);

	void SetAskKeyFrm(BOOL32 bIsNeedProtect = TRUE);//请求关键帧

	void SetAddLogoIntoEncStream(TFullLogoParam *ptLogoSetting);//设置台标
	void GetMeidaLibVersion(s8 *pszVersion);//获取采集库版本号

	void SetLowPowerMode();     //设置节电模式
	void SetNormalPowerMode();  //设置正常电量模式

	bool GetCpuAdjustStatus(BOOL32 &bStatus);

	void SelectCaptureScreen(u32 dwScreenIndex, BOOL32 bStartCap = TRUE);//选择采集屏幕，从1开始，1是主屏

    u16	 SetEnableHwEnc(BOOL32 bEnable);//开启|关闭 硬编
    u16  GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);//获取编码器状态
private:
	void InitEncoder();
	void PlayVideo();
    void StopVideo();
    void PlayAudio();
    void StopAudio();
	void SendError();
	void SetWnd(HWND hwndPlay );
private:
    BOOL m_bPlayed;
    CKdvEncoder     *m_pcEncoder;

    EmTpMediaType   m_emMediaMode;
    BOOL            m_bAudio;
    
	HWND m_hMonitor;

    s16             m_hTimerAskKeyFrm;
    s16             m_hTimerAskKeyFrmForce;// //强制请求关键帧，一般用于刚开启解码器，连续请求3次关键帧 PS:由于解码器还未稳定是否需要关键帧状态还不准确
};
#endif // !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
