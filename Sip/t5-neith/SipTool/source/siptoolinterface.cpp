#include "StdAfx.h"
#include "siptoolinterface.h"

CSipToolInterface* CSipToolInterface::m_pMySelf = NULL;

CSipToolInterface::CSipToolInterface() :
                 m_pSipToolSession(NULL),
	             m_pSysCtrlIf(NULL)
{
    m_hRecvWnd = ::CreateWindowEx(0, _T("Static"), _T("SipToolCommon"), WS_DISABLED,
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

LRESULT CALLBACK CSipToolInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    NOTIFY_MSG( uMsg, wParam, lParam );
    return 0;
}

CSipToolInterface* CSipToolInterface::GetCommIF()
{
    if ( NULL != m_pMySelf )
    {
        return m_pMySelf ;
    }

    m_pMySelf = new CSipToolInterface;
    return m_pMySelf;
}

void CSipToolInterface::DestroyCommIF()
{   
    if ( NULL != m_pMySelf )
    {
        delete m_pMySelf;
        m_pMySelf = NULL;
    }

    DesdroySession();
}

void CSipToolInterface::CreateSession()
{
    CSipToolLib::CreateSession( &m_pSipToolSession );

    m_pSipToolSession->RkcGetInterface( &m_pSysCtrlIf );
    if (m_pSysCtrlIf)
    {
        m_pSysCtrlIf->SetNotifyWnd(GetRecvWindow());
    }
}

void CSipToolInterface::DesdroySession()
{   	
    CSipToolLib::DestroySession( &m_pSipToolSession );
}