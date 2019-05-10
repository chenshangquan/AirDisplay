#if !defined(AFX_SETTINGBASE_H__C3ACE2D0_C919_434A_8630_C32CA645D59A__INCLUDED_)
#define AFX_SETTINGBASE_H__C3ACE2D0_C919_434A_8630_C32CA645D59A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// settingbase.h : header file
//


enum	EmCfgTimerEvent
{
	emCfgEvtBegin = 0,
	emCallCfgEvt ,
	emScreenShowCfgEvt,
	emAnswerModeCfgEvt,
	emLoginPswCfgEvt,
	emBellCfgEvt,
	emTimeCfgEvt,
	emVideoCfgEvt,
	emAudioCfgEvt,
	emNetParamCfgEvt,
	emNetEnvCfgEvt,
	emNetOptimizeCfgEvt,
	emSysDetailShowEvt,
	emSysStatisShowEvt,
	emShowStatis,
	emShowDetail,
	//cpu_mem_status_timer,
	emCfgEvtEnd,
};
			
enum	EmCfgTime
{

	emCallCfgTime			= 300,
	emScreenShowCfgTime		= 300,
	emAnswerModeCfgTime		= 300,
	emLoginPswCfgTime		= 300,
	emBellCfgTime			= 300,
	emTimeCfgTime			= 300,
	emVideoCfgTime			= 300,
	emAudioCfgTime			= 300,
	emNetParamCfgTime		= 30,
	emNetEnvCfgTime			= 300,
	emNetOptimizeCfgTime	= 300,
	emSysDetailShowTime		= 300,
	emSysStatisShowTime		= 300,

};

#define TCHPCMT_MSG_RETURN			10050

//消息已经报上来，但还没有触发重画问题
#define	UPDATEUI_DIRECT			if( UpdateUIDirect() ) \
								 ::SendMessage(GetParent()->GetSafeHwnd(), WM_REDRAW_UI , 0, 0);
//会议中退出不保存数据
#define RETURN_DIRECT			if( IsInConf() )	\
									return TRUE;
/////////////////////////////////////////////////////////////////////////////
// CSettingBase dialog
#include "DataSwitchCtrl.h"
#include "TransparentBaseDlg.h"
#include "BaseDlg.h"
class CSettingBaseDlg : public CDialog//CTransparentBaseDlg/* CBMPDlg*//*CDialog*/
{
// Construction
public:
//	CSettingBaseDlg(CWnd* pParent = NULL);   // standard constructor
	
	CSettingBaseDlg(UINT uResourceID, CWnd* pParent /*=NULL*/);

	virtual void RegMsgFun();
	virtual void MoveConfigDlg();

	virtual VOID InitCfg();
	virtual BOOL IsCtrlsValid();//控件内的数值是否合法
//	virtual BOOL IsNeedToSave();//是否需要保存
	virtual BOOL SaveChange();
	virtual void UpdateInfo();//更新控件

	virtual LRESULT UpdateUI(WPARAM wParam, LPARAM lParam);
	void SetUpdateFlag(EmCfgTimerEvent dwIDEvent, EmCfgTime dwMillSecond);
	BOOL UpdateUIDirect()
	{
		if( ! m_bNeedUpdate )
		{
			return FALSE;
		}

		if( m_emEvent <= emCfgEvtBegin || m_emEvent >= emCfgEvtEnd )
		{
			return FALSE;
		}
		KillTimer( m_emEvent );
		m_bNeedUpdate = FALSE;
		return TRUE;
	}
	BOOL IsInConf();
// Dialog Data
	//{{AFX_DATA(CSettingBase)
	enum { IDD = IDD_SETTING_BASE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingBase)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect					m_cRectDSC;
	CRect					m_cRectST;
	vector<CCfgControl*>	m_vctCtrls;
	BOOL					m_bNeedUpdate;
	EmCfgTimerEvent			m_emEvent;
	// Generated message map functions
	//{{AFX_MSG(CSettingBase)
		// NOTE: the ClassWizard will add member functions here
		afx_msg void OnDestroy();
		afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGBASE_H__C3ACE2D0_C919_434A_8630_C32CA645D59A__INCLUDED_)
