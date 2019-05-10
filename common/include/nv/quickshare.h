#ifndef _QUICKSHARE_H_
#define _QUICKSHARE_H_
///////////////////////////相关hid通信消息定义/////////////////////////////////////////////
//和pc通信相关
#define Ev_NV_StartProjecting_Ntf   		0x00  	/*开始投屏*/
#define Ev_NV_StopProjecting_Cmd    		0x01  	/*停止投屏*/
#define Ev_NV_NetConnectStatus_Ntf  		0x03  	/*网络连接状态，参见em_NET_STATUS枚举*/
#define Ev_NV_UserInfo_Cmd         			0x04   	/*发送PC用户名，参见tagUserInfo结构体*/
#define Ev_NV_UserInfo_Nty         			0x09	/*投屏器收到用户名的回复 */
#define Ev_NV_KeepWidthHeight_Cmd   		0x05   	/*保持宽高比，1:保持,0:不保持，默认保持*/
#define Ev_NV_ImaxRequstKeyFrame_Ntf		0x06	/*Imax请求关键帧*/
#define Ev_NV_ImaxStopPic_Ntf				0x07	/*Imax主动停止投屏*/
#define Ev_NV_WidthHeightFrame_Cmd			0x13	/*分辨率和帧率*/
#define Ev_NV_RequestTerminalType_Ntf		0x15	/*quickshare请求对端类型(pc or imix)*/
#define Ev_NV_TerminalType_PC_Cmd			0x16	/*对端类型是PC*/
#define Ev_NV_REQUSTPCNAME_Ntf				0x17	/*请求用户名*/
#define Ev_NV_WidthHeightFrame_Ntf			0x19	/*回复邋PC分辨率和帧率*/
#define Ev_NV_PCDisconnet_Cmd				0x20	/*PC休眠时通知投屏器消息*/
#define Ev_NV_PCDisconnet_Ntf				0x21	/*PC休眠时回复PC消息*/
#define Ev_NV_BroadCastPPT_Cmd				0x22	/*PC播放PPT消息通知*/
#define Ev_NV_BroadCastPPT_Ntf				0x23	/*PC播放PPT回复PC消息*/
//#define Ev_NV_PCStopBroadCastPPT_Cmd		0x24	/*PC停止播放PPT消息通知*/
#define Ev_NV_UpgradeQuickShare_Ntf			0x25	/*通知PC界面升级投屏器*/
#define Ev_NV_SendPCHeatMsg_Ntf				0x26	/*发送心跳消息给PC*/
#define Ev_NV_SendPCHeatMsg_Cmd				0x27	/*PC回复心跳消息*/
#define Ev_NV_PCSendBusiness_Cmd			0x28	/*PC发送业务消息*/
#define Ev_NV_PCSendBusiness_Ntf			0x29	/*业务回复PC消息*/
#define Ev_NV_SendPCTerName_Ntf			    0x30	/*通知PC界面终端别名*/
#define Ev_Nv_NeedCodeConsult_Ntf           0x31    /*通知PC界面需要编码协商*/
#define Ev_Nv_CodeFormat_Cmd                0x32    /*通知PC界面音视频编码类型*/
#define Ev_Nv_CodeResolution_Cmd            0x33    /*通知PC界面编码分辨率*/
#define Ev_Nv_CodeFrameRate_Cmd             0x34    /*通知PC界面编码帧率*/
#define Ev_Nv_CodeRate_Cmd                  0x35    /*通知PC界面编码率*/
#define Ev_Nv_QKPidType_Cmd                 0x36    /*通知PC界面当前投屏器类型*/
#define Ev_Nv_QKNotView_Cmd                 0x37    /*通知PC界面当前投屏器不能投屏（商密终端会议中不能投屏）*/

//和Imax配对相关
#define Ev_NV_RequstIPAndSSID_Req			0x08	/*quichshare请求Imax发送ip和ssid*/
#define Ev_NV_ImaxSendIP_Ntf				0x39	/*Imax发送ip给quickshare*/
#define Ev_NV_ImaxSendSSID_Ntf				0x10	/*Imax发送连接路由器信息给quickshare*/
#define Ev_NV_RequstOpenWps_Req				0x11	/*quickshare请求开启WPS功能*/
#define Ev_NV_NotifyImaxWifiConnect_Req		0x12	/*quickshare发送wifi连接成功消息*/
#define Ev_NV_NotifyImaxWifiDisConnect_Ntf	0x14	/*quickshare发送wifi连接失败消息*/
#define Ev_NV_TerminalType_IMIX_Cmd			0x61	/*对端类型是IMIX*/
#define Ev_NV_RequestUpdata_Req				0x18	/*quickshare请求升级*/
#define Ev_NV_StartUpdata_Ntf				0x62	/*quickshare开始升级*/
#define Ev_NV_NoNeedUpdata_Ntf				0x63	/*quickshare不需要升级*/
#define EV_NV_ImixSendWpsConnect_Rsp        0x64    /*imix收到配对成功或失败后的回应消息*/
#define Ev_NV_SendDevLog_Req				0x65	/*quickshare请求发送驱动log*/

////////////////////////////////////////////end/////////////////////////////////////////////

#define DEV_NAME                    "/dev/hidg0"  //设备名称
#define HID_MAX_READLENTH			2048
#define USERNAME_MAX_LENGTH         64
#define PC_SENDDATA_LENGTH			496
#define IMIX_CONTROLMSG_LENGTH		15

//#define SEND_TYPE_IMAX			4
#define SEND_TYPE_VIDEO 			8
#define SEND_TYPE_AUDIO				7
#define SEND_TYPE_CMD				6
#define SEND_TYPE_CMD_CHAR		    '6'

typedef enum em_NET_STATUS
{
	NET_STATUS_CONNECTING = 0x00,   //正在登录imix
	NET_STATUS_CONNECTED,           //已连接
	NET_STATUS_PROJECTING,          //正在投屏
	NET_STATUS_DISCONNECTED,        //网络断开
	NET_STATUS_NO_NETWORK,          //无网络
	NET_STATUS_NO_MATCH,            //未配对
	NET_STATUS_ENOUGHNUM,           //Imix投屏量满
	NET_STATUS_RESETQUICKSHARE,     //重新插拔投屏器
	NET_STATUS_RESETWIFI,           //网络重连中
	NET_STATUS_FIND_SSID_FAIL,      //查找热点失败
}NET_STATUS;

typedef enum em_PPT_STATUS
{
	PPT_STATUS_START = 0x01,   		//开始播放ppt
	PPT_STATUS_START_NTF,         	//回复PC开始播放ppt
	PPT_STATUS_STOP,           		//停止播放ppt
	PPT_STATUS_STOP_NTF,			//回复PC停止播放ppt
	PPT_STATUS_NEXTPAGE,         	//ppt播放下一页
	PPT_STATUS_RPEVIOUSPAGE,        //ppt播放上一页
}PPT_STATUS;

//视频格式
typedef enum em_CodeVid_Format
{
	em_VID_FORMAT_H265 = 0x01,   		
	em_VID_FORMAT_H264,         	    
	em_VID_FORMAT_PROFILE,              
	em_VID_FORMAT_MPEG,			        
	em_VID_FORMAT_H263,         	
	em_VID_FORMAT_H263PLUS,       
	em_VID_FORMAT_H261,
}EmCodeVidFormat;

//音频格式
typedef enum em_CodeAud_Format
{
	em_AUD_FORMAT_OPUS = 0x01,   		
	em_AUD_FORMAT_G711A,         	    
	em_AUD_FORMAT_G711U,              
	em_AUD_FORMAT_G719,			        
	em_AUD_FORMAT_G722,
	em_AUD_FORMAT_G7221,
	em_AUD_FORMAT_G728,     
	em_AUD_FORMAT_G729,
	em_AUD_FORMAT_MPEGAACLC,
	em_AUD_FORMAT_MPEGAACLD,
	em_AUD_FORMAT_MP3,
}EmCodeAudFormat;

//编码分辨率
typedef enum em_CodeRes_Type
{
	em_RES_TYPE_1080P1920x1080 = 0x01,   		
	em_RES_TYPE_WSXGA1440x900,         	    
	em_RES_TYPE_SXGA1280x1024,              
	em_RES_TYPE_1280x960,			        
	em_RES_TYPE_WXGA1366x768,
	em_RES_TYPE_WXGA1360x768,
	em_RES_TYPE_WXGA1280x800,     
	em_RES_TYPE_WXGA1280x768,
	em_RES_TYPE_720P1280x720,
	em_RES_TYPE_1280x600,
	em_RES_TYPE_XGA1024x768,
	em_RES_TYPE_SVGA800x600,
	em_RES_TYPE_CIF352x288,
}EmCodeResType;

typedef enum em_QK_Pid_Type
{
	em_NT30_Type = 0x01,
	em_NT30_MT_Type,
	em_Unknow_Type,
}EmQKPidType;

typedef enum em_QK_NotView_Reason
{
	em_MtEncryptConf_Reason = 0x01,   //终端加密会议
	em_UnkownReason,

}EmQkNotViewReason;


typedef struct tagUserInfo
{
	s8 abyUserName[USERNAME_MAX_LENGTH];
	tagUserInfo()
	{
		memset(abyUserName, 0, USERNAME_MAX_LENGTH);
	}

}TUserInfo,*PTUserInfo;

typedef struct tagTimeInfo
{
	u16    m_dwYear;
	u16    m_dwMonth;
	u16	   m_dwDay;
	u16    m_dwHour;
	u16    m_dwMinute;
	u16    m_dwSecond;
}TTimeInfo;/*在Ev_NV_TerminalType_PC_Cmd或者Ev_NV_TerminalType_IMIX_Cmd后发送*/

typedef struct tagFrameInfo
{
	u32    m_dwPCWidth;
	u32    m_dwPCHeight;
	u32    m_dwFrame;
	u16	   m_dwBitRate;
}TFrameInfo;

typedef struct tagTUSBData{
	u32      m_dwSeqID; //循环累加id

	u16      m_wSliceID;//每帧数据开始=0 每曾一包累加
	u16      m_wSliceNum;//分为多少包

	u32		 m_byDataSize;//有效数据长度
	u8       m_abyData[ PC_SENDDATA_LENGTH ];	//音视频数据
	
	//u32      m_dwCheckSum;//校验
}TUSBData;



#define STRUCT_FRAMEHDR_LENGTH sizeof(FRAMEHDR)
#define RECVVIDEOBUF_LENGTH 2000000
#define RECVAUDIOBUF_LENGTH 1000000
#define READBUF_LENGTH  64*1024

#endif
