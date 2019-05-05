// vidstatic.cpp : implementation file
//

#include "stdafx.h"
#include "touch.h"
#include "transtatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVidStatic

CTranStatic::CTranStatic()
{
	m_chVidType = -1; 
	m_bSwap = FALSE;

    m_pImgBk = NULL;
}

CTranStatic::~CTranStatic()
{
}


BEGIN_MESSAGE_MAP(CTranStatic, CStatic)
	//{{AFX_MSG_MAP(CVidStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVidStatic message handlers

void CTranStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    //RedrawUI( &dc );


// 	CRect rc;
// 	GetClientRect( rc );
// 	switch ( m_chVidType)
// 	{
// 	case emLocalVid:
// 		dc.TextOut( rc.left+30, rc.top+30, "LocalVid");
// 		break;
// 	case emRemoteVid:
// 		dc.TextOut( rc.left+30, rc.top+30, "RemoteVid");
// 		break;
// 	case emDualStreamVid:
// 		dc.TextOut( rc.left+30, rc.top+30, "DualStreamVid");
// 		break;
// 	default:
// 		dc.TextOut( rc.left+30, rc.top+30, "UnKonwnVid");
// 		break;
// 	}
	// Do not call CStatic::OnPaint() for painting messages
}

int CTranStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	return 0;
}

void CTranStatic::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CTranStatic::MoveWindow( LPCRECT lpRect, BOOL bRepaint )
{
    if ( CStatic::GetSafeHwnd() == NULL )
    {
        return;
    }

    CStatic::MoveWindow( lpRect, bRepaint );
}

void CTranStatic::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint /*= TRUE */ )
{
    if ( CStatic::GetSafeHwnd() == NULL )
    {
        return;
    }

    CStatic::MoveWindow( x, y, nWidth, nHeight, bRepaint );
}

void CTranStatic::DrawBk( HWND hWnd, Graphics *pGraphics )
{
// 	if ( IsWindowVisible() == FALSE )
// 	{
// 		return;
// 	}

	RECT rc;
	::GetWindowRect( m_hWnd, &rc );
	::ScreenToClient( hWnd, (LPPOINT)&rc );
	::ScreenToClient( hWnd, ((LPPOINT)&rc) + 1 );

	POINT ptSrc = { rc.left, rc.top };
	POINT ptWinPos = { rc.left, rc.top };
	SIZE szWin;
	szWin.cx = rc.right - rc.left;
	szWin.cy = rc.bottom - rc.top;

	pGraphics->SetSmoothingMode( SmoothingModeHighQuality );

	// ±³¾°
	CRect cRectBK;
	cRectBK.left = ptSrc.x;
	cRectBK.right = cRectBK.left + szWin.cx;
	cRectBK.top = ptSrc.y;
	cRectBK.bottom = cRectBK.top + szWin.cy;
	if ( m_pImgBk != NULL )
	{
		pGraphics->DrawImage( m_pImgBk, cRectBK.left - 1, cRectBK.top - 1, cRectBK.Width() + 1, cRectBK.Height() + 1 );
	}
	else
	{
		SolidBrush brush( Color( 0, 0, 0 ) );
		pGraphics->FillRectangle( &brush, cRectBK.left - 1, cRectBK.top -1, cRectBK.Width() + 1, cRectBK.Height() + 1 );
	}
}