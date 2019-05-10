// switchbutton.cpp : implementation file
//

#include "stdafx.h"
#include "switchbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchButton

CSwitchButton::CSwitchButton()
{
	m_pcBtnLeft = NULL;
	m_pcBtnRight = NULL;
	m_bYesNo = FALSE;
	m_HwndParent = NULL;
}

CSwitchButton::~CSwitchButton()
{
// 	m_pcBtnLeft = NULL;
// 	m_pcBtnRight = NULL;
	SAFEDEL(m_pcBtnLeft)
	SAFEDEL(m_pcBtnRight)
}


BEGIN_MESSAGE_MAP(CSwitchButton, CStatic)
	//{{AFX_MSG_MAP(CSwitchButton)
	//}}AFX_MSG_MAP
	ON_MESSAGE(ALTERNATIVEBTN_LEFTCLICK, OnLeftClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchButton message handlers


BOOL CSwitchButton::CreateBtns(CRect &rect,  CWnd *pwnd)
{

	ASSERT( pwnd != NULL );
	
	CStatic::Create(_T(""), WS_CHILD, rect, pwnd );
	
	m_HwndParent = pwnd->GetSafeHwnd();
	m_cRectLeft =  rect;
	m_cRectRight = rect;

	
	m_cRectLeft.right = (rect.right - rect.left )/2 + rect.left;
/*	m_cRectLeft.left = rect.left;*/

	m_pcBtnLeft = new CAlternativeButton();
	BOOL bRes = m_pcBtnLeft->Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, m_cRectLeft, pwnd, NULL);
	if( !bRes )
	{
		
		return FALSE;
	}
	m_pcBtnLeft->SetTargetHwnd( this->GetSafeHwnd() );
	SetBmpButtonLeft( IDB_TBtn_Normal_L, IDB_TBtn_MASK_L);
	m_pcBtnLeft->SetImage(IDR_CFG_SETTINGDLG_SELECTED, IDR_CFG_SETTINGDLG_PRESS, IDR_CFG_SETTINGDLG_UNSELECTED);
	m_pcBtnLeft->SetWindowText(_T("ÊÇ"));
	m_pcBtnLeft->ShowText( TRUE );


	m_cRectRight.left = (rect.right - rect.left )/2  + rect.left;
	m_pcBtnRight  = new CAlternativeButton();
	bRes = m_pcBtnRight->Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, m_cRectRight, pwnd, NULL/*m_sdwBtnID++*/);
	if( !bRes )
	{
		
		return FALSE;
	}
	m_pcBtnRight->SetTargetHwnd( this->GetSafeHwnd() );
	SetBmpButtonRight(IDB_TBtn_Normal_L, IDB_TBtn_MASK_L );	
	m_pcBtnRight->SetImage(IDR_CFG_SETTINGDLG_SELECTED_RIGHT, IDR_CFG_SETTINGDLG_PRESS, IDR_CFG_SETTINGDLG_UNSELECTED);
	m_pcBtnRight->SetWindowText(_T("·ñ"));
	m_pcBtnRight->ShowText( TRUE );
	
//	m_pcBtnLeft->ShowWindow( SW_SHOW );
//	m_pcBtnRight->ShowWindow( SW_SHOW );
	return TRUE;

}

void CSwitchButton::SetBmpButtonLeft(  u32 use, u32 unuse )
{
	m_dwUseLeft	=	use;
	m_dwUnuseLeft = unuse;
	

//	m_pcBtnLeft->SetBitmaps(use, use, use, use);
}

	
void CSwitchButton::SetBmpButtonRight( u32 use, u32 unuse )
{
	m_dwUseRight = use;
	m_dwUnuseRight = unuse;
//	m_pcBtnRight->SetBitmaps(use, use, use, use);
}

void CSwitchButton::ShowButton( BOOL bFlag )
{
	m_pcBtnLeft->ShowWindow( bFlag );
	m_pcBtnRight->ShowWindow( bFlag );
//	UpdateData();
// 	if( m_bYesNo )
// 	{
// 		m_pcBtnLeft->SetBitmaps(m_dwUseLeft, m_dwUseLeft, m_dwUseLeft, m_dwUseLeft);
// 		m_pcBtnRight->SetBitmaps(m_dwUnuseRight, m_dwUnuseRight, m_dwUnuseRight, m_dwUnuseRight);
// 	}
// 	else
// 	{
// 		m_pcBtnLeft->SetBitmaps(m_dwUnuseLeft, m_dwUnuseLeft, m_dwUnuseLeft,  m_dwUnuseLeft);
// 		m_pcBtnRight->SetBitmaps(m_dwUseRight, m_dwUseRight, m_dwUseRight, m_dwUseRight);
// 	}
//	UpdateData( FALSE );
}

void CSwitchButton::EnableBtns()
{
	if( m_bYesNo )
	{
		m_pcBtnLeft->EnableWindow(FALSE);
 		m_pcBtnRight->EnableWindow();
 	}
 	else
 	{
		m_pcBtnLeft->EnableWindow();
 		m_pcBtnRight->EnableWindow(FALSE);
	}
	/*
	CDC *pDC;
	if ( m_bYesNo == TRUE )
	{
		pDC = m_pcBtnLeft->GetDC();
	}
	else
	{
		pDC = m_pcBtnRight->GetDC();
	}
	pDC->SetTextColor(RGB(0, 0, 0));   
	pDC->SetBkMode(TRANSPARENT);   
*/	//pDC->TextOut(x,y,"Caption");
}

LRESULT CSwitchButton::OnLeftClick(WPARAM wParam, LPARAM lParam)
{
	Color color = Color( 63, 68, 72 );
	Color colorDft = Color( 255, 255, 255 );
	if( wParam == (UINT)m_pcBtnLeft )
	{
		m_bYesNo = TRUE;

		m_pcBtnLeft->SetTextColor( color );
		m_pcBtnRight->SetTextColor( colorDft );
	}
	if( wParam == (UINT)m_pcBtnRight )
	{
		m_bYesNo = FALSE;

		m_pcBtnRight->SetTextColor( color );
		m_pcBtnLeft->SetTextColor( colorDft );
	}

	EnableBtns();
	::PostMessage( m_HwndParent, SWITCHBTN_CHANGE,  (WPARAM) this, 0 );
	return 0;
}

