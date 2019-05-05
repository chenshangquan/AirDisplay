// transparentprogressctrl.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "transparentprogressctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentProgressCtrl

CTransparentProgressCtrl::CTransparentProgressCtrl()
{
    m_hParent = NULL;

    m_dwLeftResID = 0;
	m_dwLeftBKResID = 0;
    m_dwMidResID = 0;
    m_dwMidBKResID = 0;
    m_dwRightBKResID = 0;
    m_dwRightResID = 0;

    m_pImgFront = NULL;
    m_pImgFrontBK = NULL;
	m_pImgMid = NULL;
	m_pImgMidBK = NULL;
    m_pImgTail = NULL;
    m_pImgTailBK = NULL;

	m_nWidth = -1;
}

CTransparentProgressCtrl::~CTransparentProgressCtrl()
{
	/*if ( NULL != m_pImgFront )
    {
        delete m_pImgFront;
    }
    if ( NULL != m_pImgMid )
    {
        delete m_pImgMid;
    }
    if ( NULL != m_pImgTail )
    {
        delete m_pImgTail;
    }
	if ( NULL != m_pImgFrontBK )
    {
        delete m_pImgFrontBK;
    }
    if ( NULL != m_pImgMidBK )
    {
        delete m_pImgMidBK;
    }
    if ( NULL != m_pImgTailBK )
    {
        delete m_pImgTailBK;
    }
*/
	m_emStatus = emStatusOrigin;

	m_nWidth = -1;
}


BEGIN_MESSAGE_MAP(CTransparentProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CTransparentProgressCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentProgressCtrl message handlers


int CTransparentProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CProgressCtrl::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	return 0;
}

LRESULT CTransparentProgressCtrl::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
    m_hParent = (HWND)lParam;

    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( m_hParent, &point );

    // 绘制底图
    s32 nPosX = point.x + m_pImgFrontBK->GetWidth();
    s32 nPosY = point.y + ( cRect.Height() - m_pImgFrontBK->GetHeight() ) / 2;
    s32 nMiddleWidth = cRect.Width() - m_pImgFrontBK->GetWidth() - m_pImgFrontBK->GetWidth();
    // 左
    pGraphics->DrawImage( m_pImgFrontBK, point.x, nPosY, m_pImgFrontBK->GetWidth(), m_pImgFrontBK->GetHeight() );
    // 右
    pGraphics->DrawImage( m_pImgTailBK, point.x + cRect.Width() - m_pImgTailBK->GetWidth(), nPosY, m_pImgTailBK->GetWidth(), m_pImgTailBK->GetHeight() );
    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for ( u32 nIndex = 0; nIndex < ( nMiddleWidth / m_pImgMidBK->GetWidth() ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgMidBK, nPosX - 1, nPosY, m_pImgMidBK->GetWidth(), m_pImgMidBK->GetHeight() );
        nPosX += m_pImgMidBK->GetWidth();
    }
    pGraphics->DrawImage( m_pImgMidBK, nPosX - 1, nPosY, nMiddleWidth % m_pImgMidBK->GetWidth() + 2, m_pImgMidBK->GetHeight() );

	
	//活动条绘制
	s32 nEndX = cRect.Width();
	if ( m_nWidth < 6 && m_nWidth > 0 )
	{
		m_nWidth = 6;
	}
	s32 nLightWidth = ( ( (DOUBLE)m_nWidth / 100.00 ) * (DOUBLE)nEndX );	
	
	
	if ( nLightWidth > 0 )
	{
		// 左
		pGraphics->DrawImage( m_pImgFront, point.x, nPosY, m_pImgFront->GetWidth(), m_pImgFront->GetHeight() );
		//右
		pGraphics->DrawImage( m_pImgTail, point.x + nLightWidth - m_pImgTail->GetWidth(), nPosY, m_pImgTail->GetWidth(), m_pImgTail->GetHeight() );
	}
	else
	{
		
		//右
		//pGraphics->DrawImage( m_pImgTail, point.x /*+ nLightWidth*/ + m_pImgTail->GetWidth(), nPosY, m_pImgTail->GetWidth(), m_pImgTail->GetHeight() );
	}	
	
	//中
	nPosX = point.x + m_pImgFront->GetWidth();
	nMiddleWidth =  nLightWidth - m_pImgFront->GetWidth() - m_pImgTail->GetWidth();
	
	for ( u32 nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / m_pImgMidBK->GetWidth() ); nIndex++ )
	{
		pGraphics->DrawImage( m_pImgMid, nPosX, nPosY, m_pImgMid->GetWidth(), m_pImgMid->GetHeight() );
		nPosX += m_pImgMid->GetWidth();
	}
	
	if ( nMiddleWidth > 0 )
	{
		pGraphics->DrawImage( m_pImgMid, nPosX, nPosY, nMiddleWidth % m_pImgMid->GetWidth() , m_pImgMid->GetHeight() );
	}
    
    return S_OK;
}

void CTransparentProgressCtrl::SetPos( s32 dwPos )
{
	if ( m_hParent != NULL )
	{
		m_emStatus = emStatusModify;

		m_nWidth = dwPos;


		::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
	}
	
	CProgressCtrl::SetPos(dwPos);
}
