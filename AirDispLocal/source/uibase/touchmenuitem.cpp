// TouchMenuItem.cpp: implementation of the CTouchMenuItem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "TouchMenuCtrl.h"
#include "TouchMenuItem.h"
#include "TouchMenuSubDlg.h"
// #include <GdiPlus.h>
// using namespace Gdiplus;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTouchMenuItem::CTouchMenuItem()
{
    m_nItemIndex = -1;
    //m_nItemData = -1;
	m_pItemData = NULL;

    m_bSetTimer = FALSE;
    m_emItemHitStatus = emItemHitStatusNormal;
    m_nDrawFrame = -1;
    
    m_emItemType = emItemTypeAddrInfo;

    m_hParent = NULL;

	wcscpy( m_awszFontName, _L("Arial") );
	m_dwFontSize = 18;

	m_pItemData = NULL;

	m_dwStatusImageId = 0;
}

CTouchMenuItem::~CTouchMenuItem()
{

}


BEGIN_MESSAGE_MAP(CTouchMenuItem, CStatic)
    //{{AFX_MSG_MAP(CTouchMenuItem)
    ON_WM_PAINT()
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuItem message handlers

void CTouchMenuItem::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    
    // TODO: Add your message handler code here
    CRect cRect;
    GetClientRect( &cRect );

    //TRACE( "Paint:%d ---m_nDrawFrame = %d\n", m_nItemIndex, m_nDrawFrame );

    int nOffsetX = cRect.Width() / 5;
    int nOffsetY = cRect.Height() / 5;

    CBrush cBrush;
    cBrush.CreateSolidBrush( RGB( m_nItemIndex * 100, m_nItemIndex * 100, 0 * 100 ) );

    dc.FillRect( cRect, &cBrush );
    dc.TextOut( 10, 10, m_strItemText );

    cBrush.DeleteObject();

    // Do not call CStatic::OnPaint() for painting messages
}
// 
// void CTouchMenuItem::RedrawUI( Graphics *pGraphics, HWND hParent )
// {
//     m_hParent = hParent;
// 
//     if ( 0 == m_dwNormalResID )
//     {
//         return;
//     }
// 
//     if ( NULL == m_pImgNormal && 0 != m_dwNormalResID )
//     {
//         m_pImgNormal = CUtility::LoadImage( m_dwNormalResID, "PNG" );
//     }
//     if ( NULL == m_pImgSel && 0 != m_dwSelResID )
//     {
//         m_pImgSel = CUtility::LoadImage( m_dwSelResID, "PNG" );
//     }
// 
//     CRect cRect;
//     GetWindowRect( &cRect );
//     POINT point = cRect.TopLeft();
// 
//     ::ScreenToClient( m_hParent, &point );
// 
//     Image *pImage = NULL;
//     switch ( m_emItemStatus )
//     {
//     case emItemStatusNormal:
//         pImage = m_pImgNormal;
//         break;
//     case emItemStatusSel:
//     case emItemStatusLBtnDown:
//         pImage = m_pImgSel;
//         break;
//     }
// 
//     if ( NULL != pImage )
//     {
//         pGraphics->DrawImage( pImage, point.x, point.y, pImage->GetWidth(), pImage->GetHeight() );
//     }
// 
//     if ( cRect.Width() != m_pImgNormal->GetWidth()
//         || cRect.Height() != m_pImgNormal->GetHeight() )
//     {
//         SetWindowPos( NULL, 0, 0, m_pImgNormal->GetWidth(), m_pImgNormal->GetHeight(), SWP_NOMOVE );
//     }
// }

LRESULT CTouchMenuItem::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    m_hParent = (HWND)lParam;

	Graphics *pGraphics = (Graphics*)wParam;

	Draw(pGraphics);

    return S_OK;
}

void CTouchMenuItem::Draw(Graphics* pGraphics)
{
	Image *pImgNormal = m_pcTouchMenuSubDlg->m_pImgNormal;
    Image *pImgSel = m_pcTouchMenuSubDlg->m_pImgSel;
	Image *pImgHover = m_pcTouchMenuSubDlg->m_pImgHover;

    if ( NULL == pImgNormal || NULL == pImgSel || pImgHover == NULL )
    {
        return ;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( m_hParent, &point );

    Image *pImage = NULL;
    switch ( m_emItemHitStatus )
    {
    case emItemHitStatusNormal:
        pImage = pImgNormal;
        break;
    case emItemHitStatusSel:
    case emItemHitStatusLBtnDown:
        pImage = pImgSel;
		break;
	case emItemHitStatusHover:
		pImage = pImgHover;
        break;
    }

    if ( NULL != pImage )
    {
        //HWND hCtrlWnd = ::GetParent( m_hParent );
        CRect cCtrlRect;
        ::GetWindowRect( m_pcTouchMenuSubDlg->GetParent()->GetSafeHwnd(), &cCtrlRect );
        ::ScreenToClient( m_hParent, (LPPOINT)&cCtrlRect );
	    ::ScreenToClient( m_hParent, ((LPPOINT)&cCtrlRect) + 1 );

        BOOL32 bDrawText = FALSE;
        s32 nPosY = 0;
        u32 dwHeight = pImage->GetHeight();
        if (point.y < - 50 )
        {
            int j = 0;
        }
        if ( (s32)( point.y + pImage->GetHeight() ) < cCtrlRect.top || point.y > cCtrlRect.bottom )
        {
            return ;
        }
        else
        {
            if ( point.y < cCtrlRect.top )
            {
                nPosY = cCtrlRect.top;
                dwHeight = point.y + pImage->GetHeight() - cCtrlRect.top;
            }
            else if ( point.y + pImage->GetHeight() > cCtrlRect.bottom )
            {
                nPosY = point.y;
                dwHeight = cCtrlRect.bottom - point.y;
            }
            else
            {
                bDrawText = TRUE;
                nPosY = point.y;
                dwHeight = pImage->GetHeight();
            }
        }
        pGraphics->DrawImage( pImage, point.x, nPosY, pImage->GetWidth(), dwHeight );

        if ( TRUE == bDrawText )
        {
//             FontFamily fontFamily(L"Arial"); // 创建字体族对象
//             Font font(&fontFamily, 10); // 创建字体

			FontFamily fontFamily( m_awszFontName );
			Font font( &fontFamily, m_dwFontSize );
            SolidBrush brush( Color( 255, 255, 255 ) ); // 创建白色的实心刷（写字符串用）

            pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));

            WCHAR *pwszText = NULL;
            pwszText = new WCHAR[ m_strItemText.GetLength() + 1];
            ZeroMemory( pwszText, (m_strItemText.GetLength() + 1) * 2 );
            //ASNI TO UNICODE
            MultiByteToWideChar( CP_ACP, 0, (LPCSTR)m_strItemText, -1, (WCHAR*)(pwszText), m_strItemText.GetLength());

            StringFormat sf;
            sf.SetLineAlignment( StringAlignmentCenter );
            sf.SetAlignment( StringAlignmentCenter );
            pGraphics->DrawString( pwszText, -1, &font, RectF( (float)point.x, (float)point.y, pImgNormal->GetWidth(), pImgNormal->GetHeight() ), &sf, &brush );

            delete []pwszText;
        }
    }

    if ( cRect.Width() != pImgNormal->GetWidth()
         || cRect.Height() != pImgNormal->GetHeight() )
    {
        SetWindowPos( NULL, 0, 0, pImgNormal->GetWidth(), pImgNormal->GetHeight(), SWP_NOMOVE );

        // 更新区域大小
        m_cClientRect.right = m_cClientRect.left + pImgNormal->GetWidth();
        m_cClientRect.bottom = m_cClientRect.top + pImgNormal->GetHeight();
    }

}
// 
// BOOL CTouchMenuItem::OnPaint( CDC *pDC )
// {
//     BOOL bReleaseDC = FALSE;
//     if ( pDC == NULL )
//     {
//         bReleaseDC = TRUE;
//         pDC = m_pcTouchMenuSubDlg->GetDC();
//     }
// 
//     int nOffsetX = m_cClientRect.left;
//     int nOffsetY = m_cClientRect.top;
// 
//     if ( -1 == m_nDrawFrame )
//     {
//         Graphics graph(pDC->m_hDC);
//         Pen pen(Color::Black, 8); // 创建宽8个像素的黑色笔（画虚线用）
//         REAL dashVals[4] = {5.0f, 2.0f, 15.0f, 4.0f}; // 线5、空2、线15、空4（像素）
//         FontFamily fontFamily(L"黑体"); // 创建字体族对象
//         Font font(&fontFamily, 35); // 创建5号字大小的Times New Roman字体
//         SolidBrush brush(Color(0, 128, 0)); // 创建绿色的实心刷（写字符串用）
// 
//         graph.DrawRectangle( &pen, m_cClientRect.left, m_cClientRect.top, m_cClientRect.Width(), m_cClientRect.Height() );
// 
//         wchar_t awTemp[10] = { 0 };
//         _itow( m_nItemIndex, awTemp, 10 );
// 
//         graph.SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
//         graph.DrawString(awTemp, -1, &font, PointF(10 + nOffsetX, 10 + nOffsetY), &brush);
//     }
//     else
//     {
//         float fScale = m_nDrawFrame * 0.01;
//         int nScaleWidth = m_cClientRect.Width() * fScale;
//         int nScaleHeight = m_cClientRect.Height() * fScale;
// 
//         Graphics graph(pDC->m_hDC);
//         Pen pen(Color::Black, 8); // 创建宽8个像素的黑色笔（画虚线用）
//         REAL dashVals[4] = {5.0f, 2.0f, 15.0f, 4.0f}; // 线5、空2、线15、空4（像素）
//         FontFamily fontFamily(L"黑体"); // 创建字体族对象
//         Font font(&fontFamily, 35 /** m_nDrawFrame / 100*/ ); // 创建5号字大小的Times New Roman字体
//         SolidBrush brush(Color(0, 128, 0)); // 创建绿色的实心刷（写字符串用）
//         
//         graph.DrawRectangle( &pen, m_cClientRect.left - nScaleWidth, m_cClientRect.top - nScaleHeight, m_cClientRect.Width() + 2 * nScaleWidth, m_cClientRect.Height() + 2 * nScaleHeight );
//         
//         wchar_t awTemp[10] = { 0 };
//         _itow( m_nItemIndex, awTemp, 10 );
//         
//         graph.SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
//         graph.DrawString(awTemp, -1, &font, PointF(10 + nOffsetX, 10 + nOffsetY), &brush);
// 
//         if ( m_nDrawFrame == 10 )
//         {
//             //m_nDrawFrame = -1;
//             // remove timer
//         }
//         else
//         {
//             m_nDrawFrame++;
//         }
//     }
// 
//     if ( TRUE == bReleaseDC )
//     {
//         m_pcTouchMenuSubDlg->ReleaseDC( pDC );
//     }
// 
//     return TRUE;
// }

BOOL CTouchMenuItem::OnMouseMove(UINT nFlags, CPoint point )
{
    return FALSE;
}

BOOL CTouchMenuItem::OnLButtonDown(UINT nFlags, CPoint point )
{
    if ( m_cClientRect.PtInRect( point ) == TRUE )
    {

        SetTimer( 1, 20, NULL );

        m_emItemHitStatus = emItemHitStatusLBtnDown;
        m_nDrawFrame = 0;
    }
    else
    {
        m_emItemHitStatus = emItemHitStatusNormal;
        m_nDrawFrame = -1;

        KillTimer( 1 );
    }

    Invalidate();

    return FALSE;
}

BOOL CTouchMenuItem::OnLButtonUp(UINT nFlags, CPoint point )
{
    BOOL bRet = FALSE;

    if ( m_cClientRect.PtInRect( point ) == TRUE
         && m_emItemHitStatus == emItemHitStatusLBtnDown )
    {
        bRet = OnBtnClick();
    }

    //Invalidate();

    return bRet;
} 

void CTouchMenuItem::OnTimer(UINT nIDEvent) 
{
    Invalidate();

    CStatic::OnTimer(nIDEvent);
}

BOOL CTouchMenuItem::OnBtnClick()
{
	/*m_nItemData = m_nItemData & 0xFFFFF;
	u16 wGrpIndex = m_nItemData >> 12;
	u16 wAddrIndex = m_nItemData & 0xFFF;
	
	//高12位条目在数组中的index， 中间8位存该条目在哪个组内的组在地址簿中的， 末尾12位存item的id
	WPARAM wParam = (m_nItemIndex<<20) |((wGrpIndex << 12) & 0xFF000)  | (wAddrIndex & 0xFFF);
	
    GetParent()->SendMessage( WM_MENU_ITEM_CLICK, wParam, m_emItemType );*/

	GetParent()->SendMessage( WM_MENU_ITEM_CLICK, (WPARAM)this, 0 );

    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

    return FALSE;    
}

void CTouchMenuItem::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_cClientRect.PtInRect( point ) == FALSE )
    {
        return;
    }

/*	m_nItemData = m_nItemData & 0xFFFFF;
	u16 wGrpIndex = m_nItemData >> 12;
	u16 wAddrIndex = m_nItemData & 0xFFF;
	
	WPARAM wParam = (m_nItemIndex<<20) |((wGrpIndex << 12) & 0xFF000)  | (wAddrIndex & 0xFFF);
	
    GetParent()->SendMessage( WM_MENU_ITEM_DBCLICK, wParam, m_emItemType );*/

	// ----------------------------------------------
	// muxingmao
	GetParent()->SendMessage( WM_MENU_ITEM_DBCLICK, (WPARAM)this, 0 );
	// ----------------------------------------------
    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

	// CStatic::OnLButtonDblClk(nFlags, point);
}

// ---------------------------------------
// muxingmao
void CTouchMenuItem::SetItemHitStauts( EmItemHitStatus emItemStatus, BOOL32 bInvalidate /* = TRUE */ )
{
	m_emItemHitStatus = emItemStatus;
	if (bInvalidate)
	{
		::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
	}
}