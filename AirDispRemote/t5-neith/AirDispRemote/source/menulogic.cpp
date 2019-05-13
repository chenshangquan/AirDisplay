#include "stdafx.h"
#include "menulogic.h"
#include "networksetuplogic.h"
#include "videologic.h"
#include "AirDispRemotecommonop.h"

#define TIMER_LENGTH  4000
#define TIMER_SHOWTIP 200

APP_BEGIN_MSG_MAP(CMenuLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("login"), OnCreate)
    MSG_INIWINDOW(_T("login"), OnInit)
    MSG_WINDOWDESTORY(_T("login"), OnDestroy)
    MSG_WINDOWSIZE(_T("login"), OnSize)

    MSG_CLICK(_T("minbtn"), OnMinBtnClicked)
    MSG_CLICK(_T("closebtn"), OnCloseBtnClicked)
    MSG_CLICK(_T("LoginBtn"), OnLoginBtnClicked)

    MSG_TIMER(_T("LoginTipLeb"), OnShowTipTimer)

    //USER_MSG(UI_AIRDISPREMOTE_CONNECTED , OnAirDispRemoteConnected)
    //USER_MSG(UI_RKC_DISCONNECTED , OnAirDispRemoteDisconnected)
APP_END_MSG_MAP()

CMenuLogic::CMenuLogic()
{
}

CMenuLogic::~CMenuLogic()
{
}

bool CMenuLogic::OnCreate( TNotifyUI& msg )
{
    s32 nTop = 0;
    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);
    SetWindowPos( m_pm->GetPaintWindow(), HWND_TOP, rcParent.left, rcParent.top, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE );

    HWND hWnd = m_pm->GetPaintWindow();
    LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
    styleValue &= ~(WS_EX_APPWINDOW);
    ::SetWindowLong(hWnd, GWL_STYLE, styleValue|WS_SIZEBOX|WS_CAPTION|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    return false;
}


bool CMenuLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());

    //IAirDispRemoteCommonOp::ShowControl( true, m_pm, _T("PageVideo") );
    WINDOW_MGR_PTR->ShowWindow( g_stcStrVideoDlg.c_str(), true );
    return true;
}

bool CMenuLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CMenuLogic::OnSize( TNotifyUI& msg )
{
    RECT rcParent;
    GetWindowRect(m_pm->GetPaintWindow(),&rcParent);

    if (WINDOW_MGR_PTR->GetWindow( g_stcStrVideoDlg.c_str()))
        WINDOW_MGR_PTR->GetWindow( g_stcStrVideoDlg.c_str())->ResizeClient(rcParent.right-rcParent.left, rcParent.bottom-rcParent.top-60);
    return true;
}

bool CMenuLogic::OnMinBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindowMinsize(g_stcStrMainDlg.c_str());  
    return true;
}

bool CMenuLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->CloseWindow(g_stcStrMainDlg.c_str());  
    TerminateProcess(GetCurrentProcess(), 0); 
    return false;
}

bool CMenuLogic::OnLoginBtnClicked(TNotifyUI& msg)
{
    NOTIFY_MSG( UI_AIRDISPREMOTE_SHOWVIDEO, (WPARAM)TRUE , 0 );
    return true;
}

bool CMenuLogic::OnShowTipTimer(TNotifyUI& msg)
{
    m_pm->DoCase(_T("caseCloseTip"));
    m_pm->KillTimer(msg.pSender, TIMER_SHOWTIP);
    return true;
}

bool CMenuLogic::OnCheckAutoLoginSel(TNotifyUI& msg)
{
    COptionUI *pCheckRemPassWord = (COptionUI*)IAirDispRemoteCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)IAirDispRemoteCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    if (pCheckRemPassWord && pCheckAutoLogin)
    {
        if (pCheckAutoLogin->IsSelected())
        {
            pCheckRemPassWord->Selected(true);
        }
    }
    return true;
}

bool CMenuLogic::OnCheckRemPassWordSel(TNotifyUI& msg)
{
    COptionUI *pCheckRemPassWord = (COptionUI*)IAirDispRemoteCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)IAirDispRemoteCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    if (pCheckRemPassWord && pCheckAutoLogin)
    {
        if (pCheckRemPassWord->IsSelected() == false)
        {
            pCheckAutoLogin->Selected(false);
        }
    }
    return true;
}

bool CMenuLogic::OnAirDispRemoteConnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    //m_pm->DoCase(_T("caseNormal"));

    u32 dwRemoteVidPort = (u32)wparam;
	u32 dwRemoteAudPort = (u32)lparam;
    
    return true;
}

bool CMenuLogic::OnAirDispRemoteDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_pm->DoCase(_T("caseNormal"));
    return true;
}

void CMenuLogic::ShowTip(CString strTip)
{
    m_pm->DoCase(_T("caseShowTip"));
    CLabelUI *pControl = (CLabelUI*)IAirDispRemoteCommonOp::FindControl( m_pm, _T("LoginTipLeb") );
    if (pControl)
    {
        pControl->SetText(strTip);
        m_pm->KillTimer(pControl, TIMER_SHOWTIP);
        m_pm->SetTimer(pControl, TIMER_SHOWTIP, TIMER_LENGTH);
    }
}

CString CMenuLogic::GetIniFilePath()
{
    TCHAR tchPath[MAX_PATH] = {0};
    CString strIniFilePath;
    if (S_OK == SHGetFolderPathW(NULL,CSIDL_APPDATA,NULL,0,tchPath))
    {
        CString strIniFileDir(tchPath);
        strIniFileDir = strIniFileDir + _T("\\AirDispRemote");		
        if(!PathFileExists(strIniFileDir))
        {
            CreateDirectory(strIniFileDir, NULL);
        }
        strIniFilePath = strIniFileDir + _T("\\conf.ini");
    }

    return strIniFilePath;
}

