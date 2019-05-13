
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

typedef struct tagNetSendMediaPort
{
    u32 m_dwVidPort;
    u32 m_dwAudPort;

    tagNetSendMediaPort()
    {
        m_dwVidPort = 0;
        m_dwAudPort = 0;
    }
}NetSendMediaPort;

typedef struct tagNetSendPara
{
	u32 m_dwLocalIP;
	u32 m_dwRemoteIP;
    u32 m_dwLocalVidPort;
    u32 m_dwLocalAudPort;	
	u32 m_dwRemoteVidPort;
	u32 m_dwRemoteAudPort;	

    void clear()
    {
        m_dwLocalIP  = 0;
        m_dwRemoteIP = 0;
		m_dwLocalVidPort = 0;
		m_dwLocalAudPort = 0;
		m_dwRemoteVidPort = 0;
		m_dwRemoteAudPort = 0;
    }
    tagNetSendPara()
    {
        clear();
    }
    /*tagNetSendMediaPort& operator = (const tagNetSendMediaPort& tRhs)
    {
        if (this == &tRhs)
        {
            return *this;
        }

        this->m_dwVidPort = tRhs.m_dwVidPort;
        this->m_dwAudPort = tRhs.m_dwAudPort;
        return *this;
    }*/
}NetSendPara;
