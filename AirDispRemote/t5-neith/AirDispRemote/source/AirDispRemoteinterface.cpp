#include "StdAfx.h"
#include "AirDispRemoteinterface.h"

CAirDispRemoteInterface* CAirDispRemoteInterface::m_pMySelf = NULL;

CAirDispRemoteInterface::CAirDispRemoteInterface() :
                 m_pAirDispRemoteSession(NULL),
	             m_pSysCtrlIf(NULL)
{
    m_hRecvWnd = ::CreateWindowEx(0, _T("Static"), _T("AirDispRemoteCommon"), WS_DISABLED,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, 0, 0);

    if ( m_hRecvWnd != NULL )
    {
        m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hRecvWnd, GWL_WNDPROC));
        SetWindowLong(m_hRecvWnd, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
    } 
    else
    {
        m_wndprocOld = NULL;
    }
}

LRESULT CALLBACK CAirDispRemoteInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    NOTIFY_MSG( uMsg, wParam, lParam );
    return 0;
}

CAirDispRemoteInterface* CAirDispRemoteInterface::GetCommIF()
{
    if ( NULL != m_pMySelf )
    {
        return m_pMySelf ;
    }

    m_pMySelf = new CAirDispRemoteInterface;
    return m_pMySelf;
}

void CAirDispRemoteInterface::DestroyCommIF()
{   
    if ( NULL != m_pMySelf )
    {
        delete m_pMySelf;
        m_pMySelf = NULL;
    }

    DesdroySession();
}

void CAirDispRemoteInterface::CreateSession()
{
    CAirDispRemoteLib::CreateSession( &m_pAirDispRemoteSession );

    m_pAirDispRemoteSession->RkcGetInterface( &m_pSysCtrlIf );
    if (m_pSysCtrlIf)
    {
        m_pSysCtrlIf->SetNotifyWnd(GetRecvWindow());
    }
}

void CAirDispRemoteInterface::DesdroySession()
{   	
    CAirDispRemoteLib::DestroySession( &m_pAirDispRemoteSession );
}