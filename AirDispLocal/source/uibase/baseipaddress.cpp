// BaseIPAddress.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "baseipaddress.h"
#include "softkeyboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseIPAddress
extern CSoftKeyboardDlg *g_pdlg;
CBaseIPAddress::CBaseIPAddress()
{
	
}

CBaseIPAddress::~CBaseIPAddress()
{

}

BEGIN_MESSAGE_MAP(CBaseIPAddress, CTransparentIPAddrCtrl)
	//{{AFX_MSG_MAP(CBaseIPAddress)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	//ON_COMMAND( WM_SETFOCUS, OnSetFocus )
	ON_MESSAGE( WM_PARENTNOTIFY, OnParentNotify )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseIPAddress message handlers

LRESULT CBaseIPAddress::OnParentNotify(UINT message, LPARAM lParam)
{
	
	//SetFocus();
	if ( message == WM_LBUTTONDOWN )
	{
		OspPrintf( TRUE, FALSE, "[OnParentNotify]: WM_LBUTTONDOWN SUCCEED!\n");
		CRect crect;
		CRect crectdlg;
		GetWindowRect( crect );
		// 获取桌面分辨率
		int nDesktopWidth = ::GetSystemMetrics( SM_CXSCREEN );
		int nDesktopHeight = ::GetSystemMetrics( SM_CYSCREEN );
		g_pdlg->GetWindowRect( crectdlg );
		
		int ndiff = (crect.left + crectdlg.Width()) - nDesktopWidth;
		int ndiffy = (crect.top + crectdlg.Height()) - nDesktopHeight;
		
		if ( crect.left + crectdlg.Width() > nDesktopWidth && crect.top + crectdlg.Height() > nDesktopHeight ) //宽和高都超出范围
		{	
			g_pdlg->MoveWindow( crect.left - ndiff, crect.top - crectdlg.Height() - /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
		}
		else if ( crect.left + crectdlg.Width() > nDesktopWidth ) //宽度
		{
			g_pdlg->MoveWindow( crect.left - ndiff, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
		}
		else if ( crect.top + crectdlg.Height() > nDesktopHeight ) //高度
		{	
			g_pdlg->MoveWindow( crect.left , crect.top - crectdlg.Height() - /*2 **/ crect.Height() , crectdlg.Width(),crectdlg.Height() );
		}
		else //正常
		{
			g_pdlg->MoveWindow( crect.left, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
		}

		if ( IsWindowVisible() == FALSE )
		{
			g_pdlg->ShowWindow( SW_HIDE );
			g_pdlg->m_bIsIPkeyFlag = FALSE;
		}
		else
        {
            g_pdlg->m_bIsvisibleFlag = TRUE;
            g_pdlg->m_bIsIPkeyFlag = TRUE;
            g_pdlg->m_bSetIpCtrlFocus = TRUE;
            g_pdlg->m_pBaseIpAddress = this;
//  			g_pdlg->ShowWindow(SW_SHOW);
//  			SetFocus();
			g_pdlg->DrawKeyboard();
            g_pdlg->SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW );
			
		}

		::PostMessage( GetParent()->GetSafeHwnd(), WM_CLICKIPCTRL, 0, 0);
	}
	else
	{
		g_pdlg->m_bIsIPkeyFlag = FALSE;
	}

    return CTransparentIPAddrCtrl::OnParentNotify( message, lParam );
}

LRESULT CBaseIPAddress::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch( message )
	{
	case WM_COMMAND:
		{
			if ( HIWORD(wParam) == EN_KILLFOCUS )
			{
				g_pdlg->m_bIsvisibleFlag = FALSE;
				//g_pdlg->m_bIsIPkeyFlag = FALSE;

                g_pdlg->m_pBaseIpAddress = NULL;
			}
			else
			{
				g_pdlg->m_bIsvisibleFlag = TRUE;
                //g_pdlg->m_bIsIPkeyFlag = TRUE;
                g_pdlg->m_pBaseIpAddress = this;
			}
		}
		
		break;
	default:
		//g_pdlg->m_bIsIPkeyFlag = FALSE;
	    break;
	}
	
	return CTransparentIPAddrCtrl::DefWindowProc(message, wParam, lParam);
}


void CBaseIPAddress::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	OspPrintf( TRUE, FALSE, "WM_LBUTTONDOWN SUCCEED!\n");
	CRect crect;
	CRect crectdlg;
	GetWindowRect( crect );
	// 获取桌面分辨率
	int nDesktopWidth = ::GetSystemMetrics( SM_CXSCREEN );
	int nDesktopHeight = ::GetSystemMetrics( SM_CYSCREEN );
	g_pdlg->GetWindowRect( crectdlg );
	
	int ndiff = (crect.left + crectdlg.Width()) - nDesktopWidth;
	int ndiffy = (crect.top + crectdlg.Height()) - nDesktopHeight;
	
	if ( crect.left + crectdlg.Width() > nDesktopWidth && crect.top + crectdlg.Height() > nDesktopHeight ) //宽和高都超出范围
	{	
		g_pdlg->MoveWindow( crect.left - ndiff, crect.top - crectdlg.Height() - /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	else if ( crect.left + crectdlg.Width() > nDesktopWidth ) //宽度
	{
		g_pdlg->MoveWindow( crect.left - ndiff, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	else if ( crect.top + crectdlg.Height() > nDesktopHeight ) //高度
	{	
		g_pdlg->MoveWindow( crect.left , crect.top - crectdlg.Height() - /*2 **/ crect.Height() , crectdlg.Width(),crectdlg.Height() );
	}
	else //正常
	{
		g_pdlg->MoveWindow( crect.left, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	
	if ( IsWindowVisible() == FALSE )
	{
		g_pdlg->ShowWindow( SW_HIDE );
		g_pdlg->m_bIsIPkeyFlag = FALSE;
	}
	else
	{
		g_pdlg->m_bIsvisibleFlag = TRUE;
		g_pdlg->m_bIsIPkeyFlag = TRUE;
		g_pdlg->m_bSetIpCtrlFocus = TRUE;
		g_pdlg->m_pBaseIpAddress = this;
		// g_pdlg->ShowWindow(SW_SHOW);
		// SetFocus();
		g_pdlg->DrawKeyboard();
		g_pdlg->SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW );
		
	}
	
	::PostMessage( GetParent()->GetSafeHwnd(), WM_CLICKIPCTRL, 0, 0);
	
	CTransparentIPAddrCtrl::OnLButtonDown(nFlags, point);
}

