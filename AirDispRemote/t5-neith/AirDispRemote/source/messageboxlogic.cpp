#include "StdAfx.h"
#include "messageboxlogic.h"


APP_BEGIN_MSG_MAP(CMessageBoxLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("MessageBoxLayout"), OnCreate)
	MSG_INIWINDOW(_T("MessageBoxLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("MessageBoxLayout"), OnDestroy)

	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)
	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	/*USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG( UI_UMS_GRAB_LOGIN_NOTIFY, OnUmsGrabLogin )
	USER_MSG(UI_TPAD_UPDATESYS_CMD,OnUpdateSysCmd)*/

APP_END_MSG_MAP()

static CString m_strText = _T("");
static bool    m_bIsShowCancel = false;

bool showMessageBox(LPCTSTR lpstrText, bool bIsShowCancel)
{
	m_strText = lpstrText;
	m_bIsShowCancel = bIsShowCancel;
	return WINDOW_MGR_PTR->ShowModal(g_strMessageBoxDlg.c_str());
}

CMessageBoxLogic::CMessageBoxLogic( void )
{
}


CMessageBoxLogic::~CMessageBoxLogic(void)
{
}


bool CMessageBoxLogic::OnCreate( TNotifyUI& msg )
{
	REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = 0;
	RECT rcParent;
	HWND hparent = GetParent(m_pm->GetPaintWindow());
	GetWindowRect(hparent,&rcParent);
	SIZE szDlg = m_pm->GetInitSize();
	s32 nLeft = (rcParent.right - rcParent.left - szDlg.cx)/2;
	nTop = (rcParent.bottom - rcParent.top - szDlg.cy)/2;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
		nLeft = s32(nLeft * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CMessageBoxLogic::OnInit(TNotifyUI& msg)
{
	IAirDispRemoteCommonOp::ShowControl( m_bIsShowCancel, m_pm, _T("BtnCancel") );		
	IAirDispRemoteCommonOp::SetControlText( m_strText, m_pm, _T("LabelTip") );
	return true;
}

bool CMessageBoxLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (m_strText == _T("其他客户端抢登") || _tcsstr(m_strText,_T("登录失败")) != NULL || m_strText ==_T("连接超时"))
	{
		return NO_ERROR;
	}

	//WINDOW_MGR_PTR->HideWindow(g_strMessageBoxDlg.c_str());
	m_strText = _T("");
	m_bIsShowCancel = false;
	WINDOW_MGR_PTR->CloseWindow(g_strMessageBoxDlg.c_str(),IDCANCEL);

	return NO_ERROR;
}

bool CMessageBoxLogic::OnUmsGrabLogin( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (WINDOW_MGR_PTR->IsWindowVisible(_T("MessageBoxDlg")))
	{
		m_strText = _T("其他客户端抢登");
		if (m_bIsShowCancel)
		{
			m_bIsShowCancel = false;
			IAirDispRemoteCommonOp::ShowControl( m_bIsShowCancel, m_pm, _T("BtnCancel") );
		}
		IAirDispRemoteCommonOp::SetControlText( m_strText, m_pm, _T("LabelTip") );
	}

	return true;
}



bool CMessageBoxLogic::OnUpdateSysCmd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if (WINDOW_MGR_PTR->IsWindowVisible(_T("MessageBoxDlg")))
	{
		m_strText = _T("");
		m_bIsShowCancel = false;
		WINDOW_MGR_PTR->CloseWindow(g_strMessageBoxDlg.c_str(),IDCANCEL);
	}

	return NO_ERROR;
}

bool CMessageBoxLogic::OnBtnCancel( TNotifyUI& msg )
{
	//WINDOW_MGR_PTR->HideWindow(g_strMessageBoxDlg.c_str());
	m_strText = _T("");
	m_bIsShowCancel = false;
	WINDOW_MGR_PTR->CloseWindow(g_strMessageBoxDlg.c_str(),IDCANCEL);
	return true;
}

bool CMessageBoxLogic::OnBtnOk( TNotifyUI& msg )
{
	//WINDOW_MGR_PTR->HideWindow(g_strMessageBoxDlg.c_str());
	m_strText = _T("");
	m_bIsShowCancel = false;
	WINDOW_MGR_PTR->CloseWindow(g_strMessageBoxDlg.c_str(),IDOK);
	//delete this;
	return true;
}

bool CMessageBoxLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}
