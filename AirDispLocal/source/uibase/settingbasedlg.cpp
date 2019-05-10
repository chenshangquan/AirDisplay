// settingbase.cpp : implementation file
//

#include "stdafx.h"
#include "settingbasedlg.h"
#include "touchpcmtdlg.h"
#include "CfgMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTouchPcmtDlg *g_pcTouchPcmtDlg;
extern CCfgMainDlg	 *g_pcCfgMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CSettingBase dialog


// CSettingBaseDlg::CSettingBaseDlg(CWnd* pParent /*=NULL*/)
// 	: CDialog(CSettingBaseDlg::IDD, pParent)
// {
// 	//{{AFX_DATA_INIT(CSettingBase)
// 		// NOTE: the ClassWizard will add member initialization here
// 	//}}AFX_DATA_INIT
// }
CSettingBaseDlg::CSettingBaseDlg(UINT uResourceID, CWnd* pParent /*=NULL*/)
: CDialog(uResourceID, pParent)
{
	m_bNeedUpdate = FALSE;
	m_vctCtrls.clear();
	memset( &m_cRectDSC, 0 , sizeof(m_cRectDSC));
	memset( &m_cRectST, 0 , sizeof(m_cRectST));
				
	m_emEvent = emCfgEvtBegin;
}


void CSettingBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingBaseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingBaseDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP

// 	ON_MESSAGE( MTC_UI_P2P_ENDED,		UpdateUI )		
// 	ON_MESSAGE( MTC_UI_CONF_LEAVE,		UpdateUI )

	

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingBaseDlg message handlers


void CSettingBaseDlg::RegMsgFun()
{
// 	CMsgDispatch::RegMsgHandler( MTC_UI_P2P_STARTED,	GetSafeHwnd() );
// 	CMsgDispatch::RegMsgHandler( MTC_UI_CONF_STARTED,	GetSafeHwnd() );
// 	CMsgDispatch::RegMsgHandler( MTC_UI_P2P_ENDED,		GetSafeHwnd() );
// 	CMsgDispatch::RegMsgHandler( MTC_UI_CONF_LEAVE,		GetSafeHwnd() );	
}

VOID CSettingBaseDlg::InitCfg()
{

}

void CSettingBaseDlg::MoveConfigDlg()
{
	CRect cRect;
	GetParent()->GetClientRect( &cRect );		
	MoveWindow( cRect );
}

BOOL CSettingBaseDlg::IsCtrlsValid()
{
    vector<CCfgControl *>::iterator iter;
    for (iter = m_vctCtrls.begin(); iter < m_vctCtrls.end(); iter++)
    {
        if ((*iter)->IsValid() == FALSE) 
		{
			return FALSE;
        }
    }
	return TRUE;
}

void CSettingBaseDlg::UpdateInfo()
{
    vector<CCfgControl *>::iterator iter;
    for (iter = m_vctCtrls.begin(); iter < m_vctCtrls.end(); iter++)
    {
		(*iter)->UpdateInfo();
    }

}

BOOL CSettingBaseDlg::SaveChange()
{

	return TRUE;
}

void CSettingBaseDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	m_vctCtrls.clear();
	// TODO: Add your message handler code here
	
}

BOOL CSettingBaseDlg::PreTranslateMessage(MSG* pMsg) 
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if ( pMsg->wParam == VK_RETURN )
        {
            return TRUE;
        }
        else if ( pMsg->wParam == VK_ESCAPE )
        {
            return TRUE;
        }
    }
	
    return CDialog::PreTranslateMessage(pMsg);
}


void CSettingBaseDlg::SetUpdateFlag(EmCfgTimerEvent dwIDEvent, EmCfgTime dwMillSecond)
{ 
	if( FALSE == m_bNeedUpdate ) 
	{
		m_bNeedUpdate = TRUE;
		m_emEvent = dwIDEvent;
		SetTimer(dwIDEvent, dwMillSecond, NULL);
	}
}

void CSettingBaseDlg::OnTimer(UINT nIDEvent) 
{
    //和CPU消耗率的大时间类型号冲突先注掉
// 	if( m_emEvent <= emCfgEvtBegin || m_emEvent >= emCfgEvtEnd/* && m_emEvent != ((u32)WM_TIMER + 40) */)
// 	{
// 		return;
// 	}

	if( nIDEvent == m_emEvent )
	{
		KillTimer( m_emEvent );
		::SendMessage(GetParent()->GetSafeHwnd(), WM_REDRAW_UI , 0, 0);
	}
	m_bNeedUpdate = FALSE;

 	CDialog::OnTimer(nIDEvent);
}

LRESULT CSettingBaseDlg::UpdateUI(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

BOOL CSettingBaseDlg::IsInConf()
{
	return g_pcTouchPcmtDlg->IsInconf();
}

