// BaseEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "baseedit.h"
//#include "softkeyboardDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseEdit
extern CSoftKeyboardDlg *g_pdlg;
CBaseEdit::CBaseEdit()
{

}

CBaseEdit::~CBaseEdit()
{

}

BEGIN_MESSAGE_MAP(CBaseEdit, CTransparentEdit)
	//{{AFX_MSG_MAP(CBaseEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseEdit message handlers

void CBaseEdit::OnSetFocus(CWnd* pOldWnd) 
{
    CTransparentEdit::OnSetFocus(pOldWnd);

	//g_pdlg->m_bIsIPkeyFlag = FALSE;
	CRect crect;
	CRect crectdlg;
	GetWindowRect( crect );
	// 获取桌面分辨率
    int nDesktopWidth = ::GetSystemMetrics( SM_CXSCREEN );
    int nDesktopHeight = ::GetSystemMetrics( SM_CYSCREEN );
	g_pdlg->GetWindowRect( crectdlg );

	int ndiff = (crect.left + crectdlg.Width()) - nDesktopWidth;
	int ndiffy = (crect.top + crectdlg.Height()) - nDesktopHeight;

	int i = 0;
	if ( crect.left + crectdlg.Width() > nDesktopWidth && crect.top + crectdlg.Height() > nDesktopHeight ) //宽和高都超出范围
	{
		i = 1; 
		g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top - crectdlg.Height() - /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	else if ( crect.left + crectdlg.Width() > nDesktopWidth ) //宽度
	{
		i = 2;
		g_pdlg->MoveWindow( crect.left - ndiff * 5, crect.top + /*2**/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	else if ( crect.top + crectdlg.Height() > nDesktopHeight ) //高度
	{	
		i = 3;
		g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top - crectdlg.Height() - /*2 **/ crect.Height() , crectdlg.Width(),crectdlg.Height() );
	}
	else //正常
	{
		i = 4;
		g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
	}
	OspPrintf( 1, 0, "当前是%d\n", i );

	if ( IsWindowVisible() == FALSE )
	{
		g_pdlg->ShowWindow( SW_HIDE );
	}
	else
	{
		g_pdlg->m_bIsIPkeyFlag = FALSE;
		//g_pdlg->ShowWindow( SW_SHOW );
		//SetFocus();
		g_pdlg->DrawKeyboard();
        g_pdlg->SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW );
		
	}

	g_pdlg->m_bIsvisibleFlag = TRUE;
}

void CBaseEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CTransparentEdit::OnKillFocus(pNewWnd);
	g_pdlg->m_bIsvisibleFlag = FALSE;
 	if ( NULL == g_pdlg->GetFocus() && IsWindowVisible() )
 	{
 		g_pdlg->ShowWindow( SW_HIDE );
	}
}

void CBaseEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	g_pdlg->m_bIsIPkeyFlag = FALSE;
    if ( GetParent()->GetFocus() != this )
    {
        CTransparentEdit::OnLButtonDown(nFlags, point);
        return;
    }

    CRect crect;
    CRect crectdlg;
    GetWindowRect( crect );
    // 获取桌面分辨率
    int nDesktopWidth = ::GetSystemMetrics( SM_CXSCREEN );
    int nDesktopHeight = ::GetSystemMetrics( SM_CYSCREEN );
    g_pdlg->GetWindowRect( crectdlg );
    
    int ndiff = (crect.left + crectdlg.Width()) - nDesktopWidth;
    int ndiffy = (crect.top + crectdlg.Height()) - nDesktopHeight;
    
	int i = 0;
    if ( crect.left + crectdlg.Width() > nDesktopWidth && crect.top + crectdlg.Height() > nDesktopHeight ) //宽和高都超出范围
    {	
		i = 1;
        g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top - crectdlg.Height() -/* 2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
    }
    else if ( crect.left + crectdlg.Width() > nDesktopWidth ) //宽度
    {
		i = 2;
        g_pdlg->MoveWindow( crect.left - ndiff * 5, crect.top + /*2**/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
    }
    else if ( crect.top + crectdlg.Height() > nDesktopHeight ) //高度
    {	
		i = 3;
        g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top - crectdlg.Height() - /*2 **/ crect.Height() , crectdlg.Width(),crectdlg.Height() );
    }
    else //正常
    {
		i = 4;
        g_pdlg->MoveWindow( crect.left + ndiff / 2, crect.top + /*2 **/ crect.Height(), crectdlg.Width(),crectdlg.Height() );
    }
	OspPrintf( 1, 0, "当前是%d\n", i );

    if ( IsWindowVisible() == FALSE )
    {
        g_pdlg->ShowWindow( SW_HIDE );
    }
    else
    {
		g_pdlg->m_bIsvisibleFlag = TRUE;
        g_pdlg->m_bIsIPkeyFlag = FALSE;
		//g_pdlg->ShowWindow(SW_SHOW);
		g_pdlg->DrawKeyboard();
        g_pdlg->SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW );
    }

	CTransparentEdit::OnLButtonDown(nFlags, point);
}
