// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SwitchCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchCtrl

void CSwitchCtrl::ZeroMember()
{
	SAFEDEL( m_pcBtnLeft );
	SAFEDEL( m_pcBtnRight );
	SAFEDEL( m_pcSt );
	m_nCurInd = -1;
	m_vctIndVal.clear();
}



CSwitchCtrl::CSwitchCtrl()
{
	m_pcBtnLeft = NULL;
	m_pcBtnRight = NULL;
	m_pcSt = NULL;
	m_nCurInd = -1;
	m_vctIndVal.clear();
}

CSwitchCtrl::~CSwitchCtrl()
{
	ZeroMember();
}


BEGIN_MESSAGE_MAP(CSwitchCtrl, CStatic)
	//{{AFX_MSG_MAP(CSwitchCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BTN_CLICKME, OnClickBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchCtrl message handlers
BOOL CSwitchCtrl::Create( CRect &rect, UINT TxtBoxLen, CWnd *pwnd )
{
	ASSERT( pwnd != NULL );
	ASSERT( rect.right - rect.left > TxtBoxLen);
	
	CStatic::Create(_T(""), WS_CHILD, rect, pwnd );

//	HWND hwnd = this->GetSafeHwnd();
	m_hParent = pwnd->GetSafeHwnd();

	m_cRectLeft =  rect;
	m_cRectRight = rect;
	m_cRectST    = rect;
	
	m_cRectLeft.right = rect.left + (rect.right - rect.left - TxtBoxLen)/2;
//	m_pcBtnLeft = new CControlButton();
	m_pcBtnLeft = new CTransparentBtn();
	BOOL bRes = m_pcBtnLeft->Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, m_cRectLeft, pwnd, NULL);
	if( !bRes )
	{

		return FALSE;
	}
	m_pcBtnLeft->SetTargetHwnd( this->GetSafeHwnd() );
	
	m_cRectRight.left = m_cRectLeft.right + TxtBoxLen;		
	m_pcBtnRight = new CTransparentBtn();

	bRes = m_pcBtnRight->Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, m_cRectRight, pwnd, NULL/*m_sdwBtnID++*/);
	if( !bRes )
	{

		return FALSE;
	}
	m_pcBtnRight->SetTargetHwnd( this->GetSafeHwnd() );
	

	m_cRectST.left = m_cRectLeft.right;
	m_cRectST.right = m_cRectST.left + TxtBoxLen;
	
	m_pcSt = new CTransparentStatic/*CCenterST*/();
	bRes = m_pcSt->Create(_T(""), WS_CHILD|WS_VISIBLE| SS_CENTER | SS_CENTERIMAGE , m_cRectST, pwnd, NULL);
	if( !bRes )
	{

		return FALSE;
	}	

// 	CFont   font;   
// 	LOGFONT   lf;   
// 	memset(&lf,   0,   sizeof(LOGFONT));               //   zero   out   structure   
// 	lf.lfHeight   =   8;                                             //   request   a   12-pixel-height   font   
// 	strcpy(lf.lfFaceName,   "Arial");                 //   request   a   face   name   "Arial"   
// 	VERIFY(font.CreateFontIndirect(&lf));     //   create   the   font   
//     
// 	m_pcSt->SetFont(&font);
	
	SetBMP();
	return TRUE;
}

// void CSwitchCtrl::SetColors(COLORREF  rolloverclr, COLORREF  downclr, 
// 						   COLORREF  normalclr ,  COLORREF  focusclr)
// {
// 	ASSERT( m_pcBtnLeft != NULL );
// 	ASSERT( m_pcBtnRight != NULL);
// 	
// 	m_pcBtnLeft->SetColors( rolloverclr, downclr, normalclr ,  focusclr );
// 	m_pcBtnRight->SetColors( rolloverclr, downclr, normalclr ,  focusclr );
// 	
// 	
// }

void CSwitchCtrl::SetBMP()
{
// 	m_pcBtnLeft->SetRgnMask(IDB_TBtn_MASK_L, TRUE);        //设置响应区域,TRUE表示使用掩码
// 	m_pcBtnLeft->SetMaskBitmapId(IDB_TBtn_MASK_L, TRUE);   //设置掩码图片
// 	m_pcBtnLeft->SetBitmapId(IDB_TBtn_OVER_L, IDB_TBtn_Normal_L,
// 							IDB_TBtn_Press_L, IDB_TBtn_Normal_L); //设置按钮的四种状态图
// 
// 	m_pcBtnRight->SetRgnMask(IDB_TBtn_MASK_R , TRUE);
// 	m_pcBtnRight->SetMaskBitmapId(IDB_TBtn_MASK_R, TRUE);
// 	m_pcBtnRight->SetBitmapId(IDB_TBtn_OVER_R, IDB_TBtn_Normal_R, 
// 							IDB_TBtn_Press_R, IDB_TBtn_Normal_R);

	m_pcBtnLeft->SetImage ( IDR_CFG_SWC_LBTN_NORMAL, IDR_CFG_SWC_LBTN_PRESS, IDR_CFG_SWC_LBTN_NORMAL );
	m_pcBtnRight->SetImage( IDR_CFG_SWC_RBTN_NORMAL, IDR_CFG_SWC_RBTN_PRESS, IDR_CFG_SWC_RBTN_NORMAL );
}

void CSwitchCtrl::SetText(CString &str , BOOL bShowNothing)
{
	if( bShowNothing )
	{
		CString strTmp = "";
		//m_pcSt->SetText(strTmp);
		m_pcSt->SetWindowText( strTmp );
	}
	else
	{
		//m_pcSt->SetText(str);
		m_pcSt->SetWindowText( str );
	}
	m_pcSt->SetFont( 15 );
	m_pcSt->SetTextAlign( CTransparentStatic::emAlignmentCenter );
//	::SendMessage( GetParent()->GetParent()->GetSafeHwnd(), WM_REDRAW_UI,  0, 0);
//	m_pcSt->ShowWindow( SW_SHOW );
}


LRESULT CSwitchCtrl::OnClickBtn(WPARAM wParam, LPARAM lParam)
{
	u32	dwMsg = 0;
	s32 nCount = m_vctIndVal.size();
	if( nCount <=0 )
		return 0;
	if( wParam == (UINT)m_pcBtnLeft )
	{
		dwMsg = WM_BTN_CLICK_LEFT;
		m_nCurInd--;
	}
	if( wParam == (UINT)m_pcBtnRight )
	{
		dwMsg = WM_BTN_CLICK_RIGHT;
		m_nCurInd++;
	}

	if( m_nCurInd > nCount - 1  )
	{
		m_nCurInd = 0;
	}
	if( m_nCurInd < 0 )
	{
		m_nCurInd = nCount - 1;
	}
	SetText(  ( (tIndVal)(m_vctIndVal[m_nCurInd]) ).cstrVal );
	

	::SendMessage( m_hParent/*GetParent()->GetSafeHwnd()*/, dwMsg,  (WPARAM) this, 0);
	return 0;
}


s32  CSwitchCtrl::GetCurSel()
{
	return m_nCurInd;
}

u32 CSwitchCtrl::GetDataItem( s32 index )
{
	if( index < 0)
		return 0;
	return ( (tIndVal)(m_vctIndVal[index]) ).dwVal;
}
	
s32	 CSwitchCtrl::SetCurSel( s32 pos)
{
	s32 nCount = m_vctIndVal.size();
	if( pos < 0 || nCount == pos)
	{
		CString str ="";
		SetText( str , TRUE);
		m_nCurInd = -1;
		return -1;
	}
	if( nCount > pos )
	{
		m_nCurInd = pos;
		SetText( ( (tIndVal)(m_vctIndVal[m_nCurInd]) ).cstrVal , FALSE);
		return 1;
	}
	return 0;
}


void CSwitchCtrl::EnableUse(BOOL bUse)
{
		m_pcBtnLeft ->EnableWindow( bUse );
		m_pcBtnRight ->EnableWindow( bUse );
		m_pcSt->EnableWindow( bUse );

}

s32  CSwitchCtrl::GetCountItem()
{
	return m_vctIndVal.size();
}