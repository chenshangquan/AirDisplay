
#define TP_MAXLEN_ENCRYPTKEY			128

// 媒体类型
enum EmTpMediaType
{
	emTPMediaVideo = 1, //视频
	emTPMediaAudio = 2, //音频
	emTPMediaAV    = 3, //音频和视频
	emTPMediaMerge = 4 //画面合成
};

//关键帧检测
enum EmTpIFrameCheckType
{
	TP_IFrameCheck_Speaker,				//检测发言人
	TP_IFrameCheck_SingleSpeaker,		//
	TP_IFrameCheck_Poll,				//轮询监测点
	TP_IFrameCheck_ChairWait,			//主席发言时，切换到其他发言人，主席的监测
};

