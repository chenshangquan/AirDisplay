// MsgDispatch.cpp: implementation of the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Touch.h"
#include "MsgDispatch.h"
#include <vector>
#include <map>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMsgDispatch* CMsgDispatch::m_pMySelf = NULL;
map< u32, vector<HWND> > CMsgDispatch::m_mapDispatch;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgDispatch::CMsgDispatch()
{

}

CMsgDispatch::~CMsgDispatch()
{

}

BEGIN_MESSAGE_MAP(CMsgDispatch, CWnd)
END_MESSAGE_MAP()

void CMsgDispatch::Init()
{
    if ( NULL != m_pMySelf )
    {
        return;
    }

    m_pMySelf = new CMsgDispatch;

    if ( NULL != m_pMySelf )
    {
        VERIFY( m_pMySelf->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("TouchView"),
		                             WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
    }
}

void CMsgDispatch::Destroy()
{
    if ( NULL != m_pMySelf )
    {
        m_pMySelf->DestroyWindow();

        delete m_pMySelf;
        m_pMySelf = NULL;
    }
}

HWND CMsgDispatch::GetMsgReceiveHandle()
{
    return m_pMySelf->GetSafeHwnd();
}

void CMsgDispatch::RegMsgHandler( u32 nMsgId, HWND hHandleWnd )
{
    map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( nMsgId );

    vector<HWND> vctTemp;
    if ( m_mapDispatch.end() != itr )
    {
        vctTemp = (vector<HWND>)(itr->second);
    }

    vctTemp.push_back( hHandleWnd );

    m_mapDispatch[nMsgId] = vctTemp;
}


void CMsgDispatch::DetachMsgHandler( u32 nMsgId, HWND hHandleWnd )
{
    map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( nMsgId );

    vector<HWND> vctTemp;
    if ( m_mapDispatch.end() != itr )//找到这条消息
    {
        vctTemp = (vector<HWND>)(itr->second);

		vector<HWND>::iterator iter_Hwnd = vctTemp.begin();

		for( ;  iter_Hwnd < vctTemp.end(); iter_Hwnd++ )
		{
			if( *iter_Hwnd == hHandleWnd )
			{
				vctTemp.erase(iter_Hwnd);
				break;
			}
		}

		m_mapDispatch[nMsgId] = vctTemp;
    }
	

}

BOOL CMsgDispatch::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CMsgDispatch::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if ( NULL != m_pMySelf )
    {
        map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( message );

        // TRACE( "[CMsgDispatch] Receive Msg = %d", message );

        if ( m_mapDispatch.end() != itr )
        {
            vector<HWND> &vctWnd = (vector<HWND>)(itr->second);

            for ( u32 nIndex = 0; nIndex < vctWnd.size(); nIndex++ )
            {
                ::SendMessage( vctWnd[nIndex], message, wParam, lParam );
            }
        }
    }

    return CWnd::DefWindowProc(message, wParam, lParam);
}

LRESULT CMsgDispatch::SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != m_pMySelf )
	{
		return ::SendMessage( m_pMySelf->GetSafeHwnd(), dwMessage, wParam, lParam );
	}

	return FALSE;
}

LRESULT CMsgDispatch::PostMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam )
{
	if ( NULL != m_pMySelf )
	{
		return ::PostMessage( m_pMySelf->GetSafeHwnd(), dwMessage, wParam, lParam );
	}
	
	return FALSE;
}