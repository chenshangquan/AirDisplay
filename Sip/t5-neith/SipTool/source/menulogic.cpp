#include "stdafx.h"
#include "menulogic.h"
#include "networksetuplogic.h"

#define TIMER_LENGTH  4000
#define TIMER_SHOWTIP 200

APP_BEGIN_MSG_MAP(CMenuLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("login"), OnCreate)
    MSG_INIWINDOW(_T("login"), OnInit)
    MSG_WINDOWDESTORY(_T("login"), OnDestroy)

    MSG_CLICK(_T("minbtn"), OnMinBtnClicked)
    MSG_CLICK(_T("closebtn"), OnCloseBtnClicked)
    MSG_CLICK(_T("LoginBtn"), OnLoginBtnClicked)

    //MSG_SELECTCHANGE(_T("CheckAutoLogin"), OnCheckAutoLoginSel)
    //MSG_SELECTCHANGE(_T("CheckRemPassWord"), OnCheckRemPassWordSel)

    MSG_TIMER(_T("LoginTipLeb"), OnShowTipTimer)

    //USER_MSG(UI_SIPTOOL_CONNECTED , OnSipToolConnected)
    //USER_MSG(UI_RKC_DISCONNECTED , OnSipToolDisconnected)
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
    SetWindowPos( m_pm->GetPaintWindow(), HWND_TOP, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

    HWND hWnd = m_pm->GetPaintWindow();
    LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
    styleValue &= ~(WS_EX_APPWINDOW);
    ::SetWindowLong(hWnd, GWL_STYLE, styleValue);

    return false;
}


bool CMenuLogic::OnInit( TNotifyUI& msg )
{
    REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CMenuLogic::OnDestroy( TNotifyUI& msg )
{
    UNREG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    return true;
}

bool CMenuLogic::OnMinBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindowMinsize(g_stcStrLoginDlg.c_str());  
    return true;
}

bool CMenuLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->CloseWindow(g_stcStrLoginDlg.c_str());  
    TerminateProcess(GetCurrentProcess(), 0); 
    return false;
}

bool CMenuLogic::OnLoginBtnClicked(TNotifyUI& msg)
{
    CString strIP =(ISipToolCommonOp::GetControlText( m_pm ,_T("edtIP"))).c_str();
    CString strUserName = (ISipToolCommonOp::GetControlText( m_pm ,_T("edtUserName"))).c_str();
    CString strPassWord = (ISipToolCommonOp::GetControlText( m_pm ,_T("edtPassWord"))).c_str();

    /*if( !IsIpFormatRight(strIP) )
    {
        ShowTip(_T("服务器地址非法"));
        return false;
    }
    if (strUserName.IsEmpty())
    {
        ShowTip(_T("请输入账号、密码"));
        return false;
    }
    if(strPassWord.IsEmpty())
    {
        ShowTip(_T("请输入账号、密码"));
        return false;
    }*/

    u32 dwIp = ntohl( inet_addr( CT2A(strIP) ) );
    /*m_pm->DoCase(_T("caseIsLogining"));
    CSipToolComInterface->SocketConnect( dwIp, CT2A(strUserName), CT2A(strPassWord));*/

    CNetworkSetupLogic::GetSingletonPtr()->OnSipToolConnected(1);
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
    COptionUI *pCheckRemPassWord = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
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
    COptionUI *pCheckRemPassWord = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    COptionUI *pCheckAutoLogin = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    if (pCheckRemPassWord && pCheckAutoLogin)
    {
        if (pCheckRemPassWord->IsSelected() == false)
        {
            pCheckAutoLogin->Selected(false);
        }
    }
    return true;
}

bool CMenuLogic::OnSipToolConnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_pm->DoCase(_T("caseNormal"));

    bool bIsLogin = (bool)wparam;
    if (bIsLogin == false )
    {
        ShowTip(_T("连接到主机失败"));
    }
    else
    {
        CString strIniPath = GetIniFilePath();
        CString strLoginIP = _T("172.0.0.1");
        CString strUserName = (ISipToolCommonOp::GetControlText( m_pm ,_T("edtUserName"))).c_str();
        CString strPassWord = (ISipToolCommonOp::GetControlText( m_pm ,_T("edtPassWord"))).c_str();
        WritePrivateProfileString(_T("LoginInfo"),_T("LoginIP"),strLoginIP,strIniPath);
        WritePrivateProfileString(_T("LoginInfo"),_T("UserName"),strUserName,strIniPath);
        COptionUI *pCheckRemPassWord = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
        COptionUI *pCheckAutoLogin = (COptionUI*)ISipToolCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
        if (pCheckRemPassWord)
        {
            if (pCheckRemPassWord->IsSelected())
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassWord,strIniPath);
                WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("1"),strIniPath);
            }
            else
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),_T(""),strIniPath);
                WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("0"),strIniPath);
            }
        }
        if (pCheckAutoLogin)
        {
            if (pCheckAutoLogin->IsSelected())
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("1"),strIniPath);
            }
            else
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("0"),strIniPath);
            }
        }
    }
    return true;
}

bool CMenuLogic::OnSipToolDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    m_pm->DoCase(_T("caseNormal"));
    return true;
}

void CMenuLogic::ShowTip(CString strTip)
{
    m_pm->DoCase(_T("caseShowTip"));
    CLabelUI *pControl = (CLabelUI*)ISipToolCommonOp::FindControl( m_pm, _T("LoginTipLeb") );
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
        strIniFileDir = strIniFileDir + _T("\\SipTool");		
        if(!PathFileExists(strIniFileDir))
        {
            CreateDirectory(strIniFileDir, NULL);
        }
        strIniFilePath = strIniFileDir + _T("\\conf.ini");
    }

    return strIniFilePath;
}

