
#define TP_MAXLEN_ENCRYPTKEY			128

// ý������
enum EmTpMediaType
{
	emTPMediaVideo = 1, //��Ƶ
	emTPMediaAudio = 2, //��Ƶ
	emTPMediaAV    = 3, //��Ƶ����Ƶ
	emTPMediaMerge = 4 //����ϳ�
};

//�ؼ�֡���
enum EmTpIFrameCheckType
{
	TP_IFrameCheck_Speaker,				//��ⷢ����
	TP_IFrameCheck_SingleSpeaker,		//
	TP_IFrameCheck_Poll,				//��ѯ����
	TP_IFrameCheck_ChairWait,			//��ϯ����ʱ���л������������ˣ���ϯ�ļ��
};

typedef struct tagNetSendMediaPort
{
    u32 m_dwVidPort;
    u32 m_dwAudPort;	

    void clear()
    {
        m_dwVidPort = 0;
        m_dwAudPort = 0;
    }
    tagNetSendMediaPort()
    {
        clear();
    }
    tagNetSendMediaPort& operator = (const tagNetSendMediaPort& tRhs)
    {
        if (this == &tRhs)
        {
            return *this;
        }

        this->m_dwVidPort = tRhs.m_dwVidPort;
        this->m_dwAudPort = tRhs.m_dwAudPort;
        return *this;
    }
}NetSendMediaPort;
