#pragma once
#ifdef CAPTURE_EXPORTS
#define CAPTURE_API __declspec(dllexport)
#else
#define CAPTURE_API __declspec(dllimport)
#endif


/*拷屏库密码校验接口
  用法： 密码先调用AvMd5Encode加密，再传入AvCheckAuth中校验 
  ****/
#define Av_CheckAuth_MAX_LEN  32
CAPTURE_API bool AvCheckAuth(char* pcBuf, int dwLen );
CAPTURE_API void AvMd5Encode(char* szOut, char* szIn);


//音频返回nwidth为声道，nheight为采样率，视频是宽度与高度
typedef void (*PAVCALLBACK)(unsigned char *pBuf, int nSize, int nParam1, int nParam2, void* dwContext,int nTimeTap);


class CAPTURE_API CAudioCollect
{
public:
	CAudioCollect(void);
	~CAudioCollect(void);

/*开始采集数据
******/
	int StartAudCapture(bool bAudio);
	/*停止采集数据
    *******/
	int StopAudCapture(void);
	/*初始化数据
    *******/
	int InitAudCap();

    /*设置音频回调函数
    *******/
	bool SetAudioCallBack(PAVCALLBACK pAudioCallBack, 
		void* dwContext);

    /*清理数据
    *******/
	int Destroy(void);

	 /*返回当前使用的版本信息
    *******/
	void GetCurrentVer(char*chVersion);
};

/*屏幕信息
******/
typedef struct
{
	char chName[32];
	int nWidth;
	int nHeight;
}TMonitorInfo;

class CAPTURE_API CVideoCollect
{
public:
	CVideoCollect(void);
	~CVideoCollect(void);

	/*开始采集数据
	******/
	int StartVidCapture(bool bVedio);
	/*停止采集数据
    *******/
	int StopVidCapture(void);
	/*设置视频采集帧率
    *******/
	int SetFrameRate(int nRate);
	/*初始化数据
    *******/
	int InitVideoCap();
    /*设置视频回调函数
    *******/
	bool SetVideoCallBack(PAVCALLBACK pVedioCallBack, 
									void* dwContext);

    /*清理数据
    *******/
	int Destroy(void);

	 /*返回当前使用的版本信息
    *******/
	void GetCurrentVer(char*chVersion);

	/*返回当前系统的屏的信息
	TMonitorInfo*ptMonitor 需要预先申请空间，在系统中不初始化，只是赋值
    *******/
	int GetAllDisplay(TMonitorInfo*ptMonitor);

	/*选择截取的屏幕
	**/
	bool SelectCaptureScreen(int nNum);


	
};
