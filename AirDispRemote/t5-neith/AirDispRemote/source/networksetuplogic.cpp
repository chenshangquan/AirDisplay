#include "stdafx.h"
#include "networksetuplogic.h"

template<> CNetworkSetupLogic* Singleton<CNetworkSetupLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CNetworkSetupLogic, CNotifyUIImpl)
    USER_MSG(UI_AIRDISPREMOTE_CONNECTED , OnAirDispRemoteConnected)
APP_END_MSG_MAP()

    CNetworkSetupLogic::CNetworkSetupLogic()
{
}

CNetworkSetupLogic::~CNetworkSetupLogic()
{
}

bool CNetworkSetupLogic::OnCreate( TNotifyUI& msg )
{
    //HWND hWnd = m_pm->GetPaintWindow();
    //LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
    //styleValue |= (WS_EX_APPWINDOW);//当窗口可见时将一个顶层窗口放置在任务栏上
    //styleValue &= ~(WS_EX_TOOLWINDOW); //去掉工具栏窗口属性，使其在任务栏可见
    //::SetWindowLong(hWnd, GWL_STYLE, styleValue);

    s32 nTop = 0;
    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);
    SetWindowPos( m_pm->GetPaintWindow(), HWND_TOP, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
    return false;
}


bool CNetworkSetupLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CNetworkSetupLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CNetworkSetupLogic::OnMinBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindowMinsize(g_stcStrNetworkSetupDlg.c_str());  
    return true;
}

bool CNetworkSetupLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->CloseWindow(g_stcStrNetworkSetupDlg.c_str());  
    TerminateProcess(GetCurrentProcess(), 0); 
    return false;
}

bool CNetworkSetupLogic::OnAirDispRemoteConnected(WPARAM wparam)
{
    bool bIsLogin = (bool)wparam;
    //int emErr = lparam;
    if (bIsLogin)
    {
        //SetTimerOutTimer(true);
        //界面变更
        //m_pm->DoCase(_T("caseIsLogin"));

        //窗口变更
        WINDOW_MGR_PTR->ShowWindow(g_stcStrMainDlg.c_str(), false); 
        WINDOW_MGR_PTR->ShowWindowCenter(g_stcStrNetworkSetupDlg.c_str());
    }
    else
    {
        m_pm->DoCase(_T("caseIsnotLogin"));
    }
    return true;
}

bool CNetworkSetupLogic::OnAirDispRemoteConnected(WPARAM wparam, LPARAM lparam, bool& bHandle)
{
    bool bIsLogin = (bool)wparam;
    //int emErr = lparam;
    if (bIsLogin)
    {
        //SetTimerOutTimer(true);
        //界面变更
        m_pm->DoCase(_T("caseIsLogin"));

        //窗口变更
        WINDOW_MGR_PTR->HideWindow(g_stcStrMainDlg.c_str());
        WINDOW_MGR_PTR->ShowWindowCenter(g_stcStrNetworkSetupDlg.c_str());
    }
    else
    {
        m_pm->DoCase(_T("caseIsnotLogin"));
    }
    return true;
}
