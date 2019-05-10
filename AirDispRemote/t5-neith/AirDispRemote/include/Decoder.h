// Decoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
#define AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AirDispRemotestruct.h" 

//编解码
#define SOFT_CODEC
//#include "codeclib_vs2010.h"
//#include "codeclib.h"
//#pragma comment(lib, "kdvencoder.lib")  
//#pragma comment(lib, "KdvDecoder.lib")

// #pragma comment(lib, "kdvdecoder_vs2010_u.lib")
// #pragma comment(lib, "kdvmedianet.lib")
// #pragma comment(lib, "kdvencrypt.lib")
// #pragma comment(lib, "kdimg.lib")
#include "medianet_win\kdvmedianet.h"
#include "codecwrapper_win32.h"

#pragma comment(lib, "kdvmedianetdll.lib")
#pragma comment(lib, "mediasdkvc10.lib")

#define RTP_LOCALVIDEO_PORT 10000       // Local video trans port

typedef struct tagMediaParam
{
    u8 abyRealType[2];			        //第一路视频和音频的载荷类型
    u8 abyDynamicPayLoad[2];			//第一路视频和音频的动态载荷类型
    TTpEncryptKey  atEncryptKey[2];		//第一路视频和音频的密钥
//    EmSite emSite;
public:
    tagMediaParam()
    {
        memset(this, 0 ,sizeof(struct tagMediaParam));
    }
}TMediaParam; 


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





class CDecoder  
{
public:
	CDecoder();
	virtual ~CDecoder();

public:
    CKdvDecoder* GetDecoder();
    void SnapShot();
    u16  SetOnlyKeyFrame(BOOL bKeyFrame);
    BOOL IsPlayed();
    BOOL IsKeyFrame() { return m_bKeyFrame;}
   
    
    //  dwRTPAddr和dwRTCPAddr值是一样的，都是本地地址 
    void SetWnd(HWND hwndPlay);
    void SetInfo(u16 wVRTPPort, u16 wARTPPort, u32 dwRTPAddr, u32 dwRTCPAddr);
    void GetLocalMediaTransPort(NetSendMediaPort &tNetSendMediaPort);
    void SetVideoBackParam( u16 wRTPVedioPort, u32 dwRTPVedioAddr );
    void SetAudioBackParam(  u16 wRTPAudioPort, u32 dwRTPAudioAddr  );
    void StartPlay();
    void StopPlay();
    void StartDec();
    void StopDec(); 
    BOOL32 IsWaitKeyFrame();  //是否在等待关键帧


    u16 SetNetFeedbackVideoParam(/*TNetRSParam tNetRSParam,*/ BOOL32 bRepeatSnd = FALSE);
	u16 SetNetFeedbackAudioParam(/*TNetRSParam tNetRSParam,*/ BOOL32 bRepeatSnd = FALSE);
     
    void SetVideoParam(const TMediaParam& tMonitorParam);
    void SetAACParam(const TAudAACParam & tAACParam);
    void SetG7221cReverse(BOOL bReverse);


    u16    SetAudioVolume(u8 byVolume );  /*设置输出声音音量*/	
    u16    GetAudioVolume(u8 &pbyVolume );/*得到输出声音音量*/ 
    
    void AskKeyFrame( BOOL32 bForce ); // 连续3次请求关键帧


    //通过宏定义来调用该函数
    static void SetAskFrameFun( CCallBackBase *pAskKeyFrame )
    { m_pCBAskKeyFrame = pAskKeyFrame; }
     

    void OAskKeyFrame(  UINT timerID );

    //以后换文件只要小于分辨率1920*1080，并且宽高是2的整数倍就可以了
    //BOOL32 SetStaticPicturePath( CString strImgPath );
	void SetDecryptKey( s8 *pszKeyBuf, u16 wKeySize, u8 byDecryptMode );
	void SetNetRcvParam();

    void SetVidDecZoomPolicy( enZoomMode emZoomMode );
private:
    void InitDecoder();
    void PlayVideo();
    void StopVideo();
    void PlayAudio();
    void StopAudio();
    void SendError();
private:
    BOOL m_bInited;
    BOOL m_bPlayed;
    BOOL m_bKeyFrame;         //是否抽帧播放
    CKdvDecoder     *m_pcDecoder;
    HWND            m_hMonitor;
    HWND            m_hFullScreenDlg;

     
    TMnetNetParam  m_tVideoNetParam;//TLocalNetParam
    TMnetNetParam  m_tAudioNetParam;//TLocalNetParam
    EmTpMediaType   m_emMediaMode;
    BOOL            m_bAudio;
    
    TAudAACParam    m_tAudioAACParam;
	BOOL			m_bG7221cReserve;
   
    TKdvDecStatis   m_tSVDecStatis;
    static CCallBackBase*   m_pCBAskKeyFrame;
    

    u16             m_nAskKeyFrameCnt;
    s16             m_hTimerAskKeyFrm;
    s16             m_hTimerAskKeyFrmForce;// //强制请求关键帧，一般用于刚开启解码器，连续请求3次关键帧 PS:由于解码器还未稳定是否需要关键帧状态还不准确

    // 网络发送参数
    NetSendMediaPort m_tLocalMediaPort;
    NetSendMediaPort m_tRemoteMediaPort;
};


/*
* 注册全局函数、以类成员函数作为函数指针 \n
* dwMsgID 函数ID func 函数名 obj 类指针 objType 类类型
*/
 
#define SET_ASK_MAIN_FRAME_FUN(func, obj, objType ) \
CDecoder::SetAskFrameFun( new CClsCallBackFun<objType>( func, obj ) );
 

#endif // !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
