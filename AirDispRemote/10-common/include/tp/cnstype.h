#ifndef _h_cnstype_h__
#define _h_cnstype_h__
#include "osp.h"

enum EmTpMcuSelView
{
	emTpMcuSelView_Idle,
		emTpMcuSelView_Req,
		emTpMcuSelView_Success
};

enum EmTpColor
{
	emRed,
	emBlue,
	emYellow,
	emBlack,
	emGreen
};

enum EmTpSize
{
	emBig,
	emMid,
	emlittle
};

enum EmTpLogoStyle
{
	emLeftUp,
	emLeftDown,
	emMidUp,
	emMidDown,
	emRightUp,
	emRightDown
};

enum EmTpStyle
{
	emStyleOne,
	emStyleTwo,
	emStyleThree,
	emStyleFour,
	emStyleFive
};

enum emTpTransparency
{
	emTransparent,
	emTranslucent,
	Opaque
};

//cndeviceģ��ö������ --add by zhangapei
//��ʾ���ͺţ�Sharp 70LCD-LX640A��sharp 70LX550A��Ĭ��sharp 70LX550A,B4 fix��ӿ��ڵ��ӻ�
enum EmTVModle
{
	emSharp70LCD_LX640A,
	emSharp70LX550A,
	emSharp70LX565A,
	emKangGuan70B17,
	emKeShi70GMO1A,
};

enum EmPanCamBright
{
	emBrightUp = 0x02,
	emBrightDown,
};

//add end

enum EmTpWorkMode 
{
    emTpIdle = 0,          //��ǰ���ڿ���״̬
	emTpSingleVideo = 1,   //���ڵ���״̬
	emTpMiniVideoSend = 2,  //����С����״̬
	emTpMergeVideoSnd =3    //����ϳ�״̬
};

enum EmTpVEncCodecType 
{
	emTpVEncCodec1 = 1,  //������1
	emTpVEncCodec2 = 2  //������2
};

//channel handle
enum EmTpChannelHandle
{
	emTp_ChanHandle_Begin,
	emTp_ChanHandle_Pri_VidSnd_0,
	emTp_ChanHandle_Pri_VidSnd_1,
	emTp_ChanHandle_Pri_VidSnd_2,	

	emTp_ChanHandle_Pri_VidRcv_0,
	emTp_ChanHandle_Pri_VidRcv_1,
	emTp_ChanHandle_Pri_VidRcv_2,
	
	emTp_ChanHandle_Pri_AudSnd_0,
	emTp_ChanHandle_Pri_AudSnd_1,
	emTp_ChanHandle_Pri_AudSnd_2,
	
	emTp_ChanHandle_Pri_AudRcv_0,
	emTp_ChanHandle_Pri_AudRcv_1,
	emTp_ChanHandle_Pri_AudRcv_2,	

	emTp_ChanHandle_Mix_Snd,
	emTp_ChanHandle_Mix_Rcv,
	
	emTp_ChanHandle_Snd_VidSnd,	
	emTp_ChanHandle_Snd_VidRcv,
	emTp_ChanHandle_Snd_AudSnd,	
	emTp_ChanHandle_Snd_AudRcv,
		
	emTp_Channel_Handle_End	 =	300,
};

enum EmTpVideoLoopTest
{
    emTp_All_Loop = 0, //��·�Ի�
		emTp_Single_Loop = 1,//��·�Ի�
		emTp_Mini_Loop = 2,//С�����Ի�  
		emTp_Merge_Loop =3  //����ϳ��Ի�  
};

enum EmTpDualIdleReason
{
	emTpNoSource, //������ʾʧ�ܣ�����ƵԴ
	emTpBussyNow, //������ʾʧ�ܣ��᳡æ���ڻ�����
	emTpSuccess   //������ʾ�ɹ�
};

enum EmTpPadMaxCap //�����PAD���������
{
	emTp_PadMaxCap_720p30 = 0,
	emTp_PadMaxCap_1080p5 = 1,
	emTp_PadMaxCap_4Cif30 = 2
};

enum EmTpIpNameNatSyn
{
	emSynInvalid,
	emTpIpAndName,
	emTpIpAndNat,
	emTpNameAndNat,
	emTpAll
};


// begin add for hdu
enum EmCnsHduRunStatus
{
	emCnsHdu_Idle,		//����״̬
	emCnsHdu_Waiting,		//�ȴ�
	emCnsHdu_Playing,		//����״̬
	emCnsHdu_Unknow		//δ֪״̬
};  

enum EmCnsHduPlayNackReason
{
	em_Cnshdu_play_success,
	em_CnsHdu_Invalid_Index,	//��Ч��λ������
	em_CnsHdu_Invalid_ID,		//��Ч��ID
	em_CnsHdu_No_Reged,		//HDUδע��
		
	em_CnsHdu_Illegal,			//��Ч��hdu
	em_CnsAlias_Illegal,		//��Ч�ı���
	em_CnsMonitor_Fail,		//��ǽʧ��
	em_CnsHdu_PlayNack,		//����ǽ�������ܾ�
	em_CnsSame_Alias,			//����
	em_CnsSame_Info,			//��ͬ����Ϣ
	em_Cnsunknown				//δ֪�Ĵ���		
};

enum EmCnsHduSetVolRes
{
	em_Cnshdu_SetVol_Success,
	em_Cnshdu_SetVol_Invalid_Index,
	em_Cnshdu_SetVol_UnReg,    
	em_Cnshdu_SetVol_VmpChan  // �໭��ϳ�ģʽ���ܵ�������
};

enum EmCnsHduChangeChanModeRes
{
	em_Cnshdu_change_mode_success = 0,
	em_Cnshdu_change_mode_error_index, // ��Ч��ͨ��
	em_Cnshdu_change_mode_error_param, // vmp mode��������
	em_Cnshdu_change_mode_error_regstate, // ͨ��δע��
	em_Cnshdu_change_mode_error_onlyoneVmp, // ����ǽ����ͨ��ֻ����һ����vmpģʽ
	em_Cnshdu_change_mode_error_workingstate, // ͨ�����ڷ�æ״̬
	em_Cnshdu_change_mode_error_fromhdu   // hdu�����л�ģʽ����
		
};

enum EmEthState
{
	em_BackMode,
	em_DoubleMode
};
// end add for hdu


#endif // _h_cnstype_h__

