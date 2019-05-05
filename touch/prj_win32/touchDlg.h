
// touchDlg.h : 头文件
//

#pragma once
#include "MainDlg.h"
#include "BannerDlg.h"
#include "Encoder.h"
#include "AboutDlg.h"
#include "datalistclass.h"
#include "logo.h"
#include "ppt.h"

//typedef enum em_Send_Data_Mode
//{
//    em_To_HID = 0x01,    //发送码流到设备
//    em_To_Server,        //发送码流到服务器
//}EmSendDataMode;

// CtouchDlg 对话框
class CtouchDlg : public CDialogEx
{
// 构造
public:
	CtouchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOUCH_DIALOG };
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// 实现
protected:
	// 生成的消息映射函数
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNotifyIcon(WPARAM, LPARAM);
	//重载默认的消息处理函数
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	
	afx_msg void OnExit();
	afx_msg void OnShow();
	
	afx_msg void OnBannerClose();
	afx_msg void OnBannerShow();
	afx_msg void OnClickMenuKeepWidthHeight();
	afx_msg void OnClickMenuAbout();
	afx_msg void OnBnClickedOk();
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnOpenHidDevSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVolumeCtrlChanged( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnPCSleepMsg( WPARAM wParam, LPARAM lParam );   //PC休眠、睡眠消息处理
	afx_msg LRESULT OnPCSleepResume( WPARAM wParam, LPARAM lParam );//PC休眠、睡眠恢复消息处理
	afx_msg LRESULT OnPCRebootClose( WPARAM wParam, LPARAM lParam );//PC重启、关机消息处理

	afx_msg LRESULT OnPptPlay( WPARAM wParam, LPARAM lParam );      //ppt消息处理
	afx_msg LRESULT OnPowerStatus( WPARAM wParam, LPARAM lParam );      //ppt消息处理
	
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMini();
	afx_msg void OnAbout();
	afx_msg void OnHide();
	void SetBannerAutoHide();
	
	void UdiskOut();

	void InitEncoderParam();
	void InitVideoEncoderParam(u8 byVideoType);
	void InitAudioEncoderParam(u8 byAudioMode, u16 wAudioDuration = 0);
	void OnStartScreenCatch();
	void OnStopScreenCatch();

	//获取设备句柄
	//HANDLE GetHidHandle(HID_TYPE emType);
	//THidDevice &GetHidDevie(HID_TYPE emType);

	CDataListClass* GetVideoDataList();
	CDataListClass* GetAudioDataList();

	//void SendCmdToHid( int nCmd );//发送命令给usb_hid设备
	void SolveReadInfo(BYTE* readBuffer);//处理读到的信息

	void StartProjectScreen(); //开始投屏
	void StopProjectScreen(bool bNotifyHid);  //停止投屏

	void SolveNetStatusNty(NET_STATUS emStatus);

	void StartTrayIconChange();//开始托盘图标变化
	void StopTrayIconChange(); //停止托盘图标变化

	CEncoder &GetEncode();//获取编码对象

	void SetLogo();    //设置台标
	void GetResolution(int &nWidth, int &nHeight);//获取要进行编码的分辨率
    void CheckResolution();  //检测当前系统分辨率是否超出限制分辨率（3840*2160）

	//默认音频设备设置
	HRESULT SetDefaultAudioPlaybackDevice(LPCWSTR devID);
	void InitDefaultAudioDevice();
	void UnInitDedaultAudioDevice();
	void CheckDedaultAudioDevice();

	//音量控制
	void InitVolumeCtrl();
	void UninitVolumeCtrl();

	void SolvePCNty();      //处理系统睡眠、休眠,重启、关闭的通知

	bool GetSysUserName( CString &strName );  //获取操作系统用户名

    CString GetIniFilePath();  //ini文件路径

	//ppt函数
	void SendPptCmdToHid( EnumPptStatus emStatus );//发送ppt消息到hid
	void SolvePptNty( PPT_STATUS emPptStatus );

	//检测笔记本电量状态
	void CheckBatteryStatus();

	//设置编码协商参数
	void SetConsultVideoParam(u8 byVideoType);
    //是否编码协商
    bool NeedCodeConsult();

private:
	void InitUI();

    // 模拟鼠标消息
    void SetMouseMessage( WORD wMM,CPoint MousePosition,UINT nFlags,short zDelta );
    void SetMouseKB( INPUT & KeyBoardInput,WORD wVk,bool bDown );

	//音频类型转音频模式
	void MediaTypeToAudioMode( u8 byMediatype, u8& byRatio );

public:
	CMainDlg  *m_pcMainDlg;
	CBannerDlg  *m_pcBannerDlg;
	CAboutDlg *m_pcVerDlg;

	bool m_bIsProjecting;      //是否正在投屏
	bool m_bAVExit;            //是否退出音视频线程
	bool m_bReadExit;          //是否退出读线程
	bool m_bPptExit;           //是否退出ppt线程

	bool m_bKeepWidthHeight;  //是否保持宽高比
	BOOL bFirstKeyFrame;      //是否是关键帧
	HDEVNOTIFY m_hDevNotiy;   //设备状态改变通知
	bool m_bHidOpen;          //hid设备是否已经打开
	bool m_bSetDefAudoDev;    //是否设置了默认音频设备
	LPWSTR m_wstrSysAudioID;  //系统未插入投屏器前使用的音频设备

	CString m_strLogoPath;    //台标路径

	bool m_bVideoThreadRun;   //判断视频线程是否运行
	bool m_bAudioThreadRun;   //判断音频线程是否运行

	bool m_bDataBlock;        //是否数据阻塞

	bool m_bIsSleep;          //是否收到系统睡眠、休眠消息
	bool m_bIsRebootClose;    //是否收到系统重启、关闭消息
	int m_nSendPCDisconnetCount;//发送PC断开消息次数

	CString m_strSysUserName; //系统用户名

	int m_nStartPptCount;      //发送ppt播放命令次数
	int m_nStopPptCount;       //发送ppt未播放命令次数
    int m_nSendBusinessCount;  //发送业务命令次数
    int m_nThreadExitCount;    //音视频发送线程退出次数

	bool m_bCapOverEncode;   //判断采集分辨率是否大于编码分辨率
	bool m_bStretch;         //判断是否不等比拉伸，即采集分辨率比例大于等于1.5时
    bool m_bOverResLimit;    //判断是否超出限制分辨率

	bool m_bBusinessStaus;   //是否需要判断业务状态

	NET_STATUS m_bCurConnetStatus;    //当前连接状态
    EmQKPidType m_emQKPidType;        //当前投屏器类型
    //EmSendDataMode m_emSendDateMode;  //发送码流方式

protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_ntIcon;
	HICON m_hTrayIcon[4];//用于变化的icon;

private:
	bool m_bMin;
	CEncoder m_cEncoder;
	TVideoEncParam  m_tVideoEncParam;  //终端协商的编码参数
	BOOL     m_bNeedCodeConsult;       //是否协商编码参数

	//THidDevice m_HidDevice[HID_TYPE_NUM];
	CDataListClass m_cVideoDataList;
	CDataListClass m_cAudioDataList;
	CWinThread * m_pcVideoThread;
	CWinThread * m_pcAudioThread;
	CWinThread * m_pcReadThread;//读取数据线程
};