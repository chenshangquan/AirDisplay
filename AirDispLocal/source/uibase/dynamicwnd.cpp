// DynamicWnd.cpp : implementation file
//

#include "stdafx.h"
#include "touch.h"
#include "DynamicWnd.h"
#include "msgdispatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIME_ELAPSE     20

/////////////////////////////////////////////////////////////////////////////
// CDynamicWnd dialog


CDynamicWnd::CDynamicWnd(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CDynamicWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_cNormalRect = CRect( 0, 0, 1280, 200 );
    m_cShrinkRect = CRect( 0, 0, 1280, 50 );
    m_cEnlargeRect = CRect( 0, 0, 1280, 210 );
    m_cCurrentRect = CRect( 0, 0, 1280, 200 );

    m_cWindowPos = CPoint( 0, 1024 );

    m_emAction = emShowed;
    m_emMoveDirction = emDirUpAndDown;
    m_bTowordEnlarge = FALSE;

    m_pcParentWnd = NULL;
}


void CDynamicWnd::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDynamicWnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDynamicWnd, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CDynamicWnd)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	//ON_BN_CLICKED(IDC_BTN_HIDE, OnBtnHide)
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynamicWnd message handlers

BOOL CDynamicWnd::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();

	// TODO: Add extra initialization here

// 	u32 dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
// 	dwStyle &= ~WS_POPUP;
// 	dwStyle |= WS_CHILD;
// 	SetWindowLong( m_hWnd, GWL_STYLE, dwStyle );


    m_pcParentWnd = new CBaseDlg( CBaseDlg::IDD, GetParent() );
    m_pcParentWnd->m_bTransparentWithoutBK = TRUE;
    m_pcParentWnd->Create( CBaseDlg::IDD, GetParent() );
    //m_pcParentWnd->UpdateWindow();

	//ShowWindow( SW_SHOW );

    SetParent( m_pcParentWnd );

    MoveWindow( &m_cNormalRect );

    AjustWindow();

    m_pcParentWnd->SendMessage( WM_REDRAW_UI, NULL, NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDynamicWnd::AjustWindow()
{
    int nHeight = m_cCurrentRect.Height();
    int nWidth = m_cCurrentRect.Width();

    if ( emDirLeftAndRight == m_emMoveDirction )
    {
        int nPosX = m_cCurrentRect.right - m_cNormalRect.right;

        CRect cWindowRect = m_cNormalRect;
        cWindowRect.left += nPosX;
        cWindowRect.right += nPosX;

        MoveWindow( &cWindowRect );
    }
    else if ( emDirUpAndDown == m_emMoveDirction )
    {
        int nPosY = m_cCurrentRect.bottom - m_cEnlargeRect.bottom;

        CRect cWindowRect = m_cNormalRect;
        cWindowRect.top -= nPosY;
        cWindowRect.bottom -= nPosY;

        MoveWindow( &cWindowRect );
    }
	else if ( emDirRightAndLeft == m_emMoveDirction )
    {
        int nPosX = m_cCurrentRect.left - m_cNormalRect.left;

        CRect cWindowRect = m_cNormalRect;
        cWindowRect.left += nPosX;
        cWindowRect.right += nPosX;

        MoveWindow( &cWindowRect );

    }

	if ( emDirLeftAndRight == m_emMoveDirction || emDirUpAndDown == m_emMoveDirction )
	{
		CRect cRect;
		cRect.left = m_cWindowPos.x;
		cRect.bottom = m_cWindowPos.y;
		cRect.right = cRect.left + m_cEnlargeRect.Width();
		cRect.top = cRect.bottom - m_cEnlargeRect.Height();
		
		m_pcParentWnd->MoveWindow( &cRect );
	}
	else
	{
		CRect cRect;
		cRect.left = m_cWindowPos.x - m_cEnlargeRect.Width();
		cRect.bottom = m_cWindowPos.y;
		cRect.right = m_cWindowPos.x;
		cRect.top = cRect.bottom - m_cEnlargeRect.Height();
		
		m_pcParentWnd->MoveWindow( &cRect );
	}
   

    if ( m_emAction == emHided )
    {
        m_pcParentWnd->ShowWindow( SW_HIDE );
    }
    else
    {
        if ( m_pcParentWnd->IsWindowVisible() == FALSE )
        {
            m_pcParentWnd->ShowWindow( SW_SHOW );
        }
    }
}

void CDynamicWnd::OnClose() 
{
    DoHide();

	//CBaseDlg::OnClose();
}

void CDynamicWnd::DoShow()
{
    if ( m_emAction == emHiding || m_emAction == emShowed )
    {
        return;
    }
    else if ( m_emAction == emHided )
    {
        m_emAction = emShowing;
        m_bTowordEnlarge = TRUE;

        SetTimer( 2, TIME_ELAPSE, NULL );
    }

    // 开始移动
    if ( emDirUpAndDown == m_emMoveDirction )
    {
        s32 nStep;
        s32 nTowordsHeight = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsHeight = m_cEnlargeRect.Height();
        }
        else
        {
            nTowordsHeight = m_cNormalRect.Height();
        }

        nStep = (float)( nTowordsHeight - m_cCurrentRect.Height() ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( nTowordsHeight > m_cCurrentRect.Height() ) ? 1 : -1;
        }

        if ( TRUE == m_bTowordEnlarge )
        {
            if ( m_cCurrentRect.Height() + nStep < nTowordsHeight )
            {
                m_cCurrentRect.bottom += nStep;
            }
            else
            {
                m_cCurrentRect.bottom = nTowordsHeight;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
            if ( m_cCurrentRect.Height() + nStep > nTowordsHeight )
            {
                m_cCurrentRect.bottom += nStep;
            }
            else
            {
                m_cCurrentRect = m_cNormalRect;

                m_emAction = emShowed;
                KillTimer( 2 );

                // 显示完后调回调函数
                Showed();
            }
        }
    }
    else if ( emDirLeftAndRight == m_emMoveDirction )
    {
        s32 nStep;
        s32 nTowordsWidth = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsWidth = m_cEnlargeRect.Width();
        }
        else
        {
            nTowordsWidth = m_cNormalRect.Width();
        }

        nStep = (float)( nTowordsWidth - m_cCurrentRect.Width() ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( nTowordsWidth > m_cCurrentRect.Width() ) ? 1 : -1;
        }

        if ( TRUE == m_bTowordEnlarge )
        {
            if ( m_cCurrentRect.Width() + nStep < nTowordsWidth )
            {
                m_cCurrentRect.right += nStep;
            }
            else
            {
                m_cCurrentRect.right = nTowordsWidth;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
            if ( m_cCurrentRect.Width() + nStep > nTowordsWidth )
            {
                m_cCurrentRect.right += nStep;
            }
            else
            {
                m_cCurrentRect = m_cNormalRect;

                m_emAction = emShowed;
                KillTimer( 2 );

                // 显示完后调回调函数
                Showed();
            }
        }
    }
	else if ( emDirRightAndLeft == m_emMoveDirction )
    {
        s32 nStep;

        s32 nTowordsWidth = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsWidth = m_cEnlargeRect.Width();
        }
        else
        {
            nTowordsWidth = m_cNormalRect.Width();
        }
		
        nStep = (float)( nTowordsWidth - abs(m_cCurrentRect.Width()) ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( nTowordsWidth > abs(m_cCurrentRect.Width()) ) ? 1 : -1;
        }
		
        if ( TRUE == m_bTowordEnlarge )
        {
            if ( abs(m_cCurrentRect.Width()) + nStep < nTowordsWidth )
            {
                m_cCurrentRect.left -= nStep;
            }
            else
            {
                m_cCurrentRect.left = 0;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
            if ( abs(m_cCurrentRect.Width()) + nStep >= nTowordsWidth )
            {
                m_cCurrentRect.left -= nStep;
            }
            else
            {
                m_cCurrentRect = m_cNormalRect;
				
                m_emAction = emShowed;
                KillTimer( 2 );
				
                // 显示完后调回调函数
                Showed();
            }
        }
    }

    AjustWindow();
}

void CDynamicWnd::DoHide()
{
    if ( m_emAction == emShowing || m_emAction == emHided )
    {
        return;
    }
    else if ( m_emAction == emShowed )
    {
        m_emAction = emHiding;
        m_bTowordEnlarge = TRUE;
        //GetWindowRect( &m_cRectWindow );

        SetTimer( 1, TIME_ELAPSE, NULL );
    }

    // 开始移动
    if ( emDirUpAndDown == m_emMoveDirction )
    {
        s32 nStep;
        s32 nTowordsHeight = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsHeight = m_cEnlargeRect.Height();
        }
        else
        {
            nTowordsHeight = m_cShrinkRect.Height();
        }

        nStep = ( m_cCurrentRect.Height() - nTowordsHeight ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( m_cCurrentRect.Height() > nTowordsHeight ) ? 1 : -1;
        }

        if ( TRUE == m_bTowordEnlarge )
        {
            if ( m_cCurrentRect.Height() - nStep < nTowordsHeight )
            {
                m_cCurrentRect.bottom -= nStep;
            }
            else
            {
                m_cCurrentRect.bottom = nTowordsHeight;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
            if ( m_cCurrentRect.Height() - nStep > nTowordsHeight )
            {
                m_cCurrentRect.bottom -= nStep;
            }
            else
            {
                m_cCurrentRect = m_cShrinkRect;

                m_emAction = emHided;
                KillTimer( 1 );

                // 隐藏完后调回调函数
                Hided();
            }
        }
    }
    else if ( emDirLeftAndRight == m_emMoveDirction )
    {
        s32 nStep;
        s32 nTowordsWidth = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsWidth = m_cEnlargeRect.Width();
        }
        else
        {
            nTowordsWidth = m_cShrinkRect.Width();
        }

        nStep = ( m_cCurrentRect.Width() - nTowordsWidth ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( m_cCurrentRect.Width() > nTowordsWidth ) ? 1 : -1;
        }

        if ( TRUE == m_bTowordEnlarge )
        {
            if ( m_cCurrentRect.Width() - nStep < nTowordsWidth )
            {
                m_cCurrentRect.right -= nStep;
            }
            else
            {
                m_cCurrentRect.right = nTowordsWidth;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
            if ( m_cCurrentRect.Width() - nStep > nTowordsWidth )
            {
                m_cCurrentRect.right -= nStep;
            }
            else
            {
                m_cCurrentRect = m_cShrinkRect;

                m_emAction = emHided;
                KillTimer( 1 );

                // 隐藏完后调回调函数
                Hided();
            }
        }
    }
	else if ( emDirRightAndLeft == m_emMoveDirction )
    {
        s32 nStep;
        s32 nTowordsWidth = 0;
        if ( TRUE == m_bTowordEnlarge )
        {
            nTowordsWidth = m_cEnlargeRect.Width();
        }
        else
        {
            nTowordsWidth = m_cShrinkRect.Width();
        }
		
        nStep = ( nTowordsWidth  - abs(m_cCurrentRect.Width()) ) / 2;
        if ( nStep == 0 )
        {
            nStep = ( abs(m_cCurrentRect.Width()) > nTowordsWidth ) ? 1 : -1;
        }
		
        if ( TRUE == m_bTowordEnlarge )
        {
            if ( abs(m_cCurrentRect.Width()) - nStep < nTowordsWidth )
            {
                m_cCurrentRect.left += nStep;
            }
            else
            {
                m_cCurrentRect.left += nTowordsWidth;
                m_bTowordEnlarge = FALSE;
            }
        }
        else
        {
           /* if ( abs(m_cCurrentRect.Width()) - nStep > nTowordsWidth )
            {
                m_cCurrentRect.left += nStep;
            }
            else*/
            {
                m_cCurrentRect = m_cShrinkRect;
				
                m_emAction = emHided;
                KillTimer( 1 );
				
                // 隐藏完后调回调函数
                Hided();
            }
        }
    }
    AjustWindow();
}

void CDynamicWnd::OnTimer(UINT nIDEvent) 
{
    if ( nIDEvent == 1 || nIDEvent == 2 )
    {
        if ( m_emAction == emHided || m_emAction == emShowed )
        {
            KillTimer( nIDEvent );

            m_pcParentWnd->SendMessage( WM_REDRAW_UI, NULL, NULL );

            return;
        }

        if ( 1 == nIDEvent )
        {
            DoHide();
        }
        else if ( 2 == nIDEvent )
        {
            DoShow();
        }
    }

    m_pcParentWnd->SendMessage( WM_REDRAW_UI, NULL, NULL );

	//CTransparentBaseDlg::OnTimer(nIDEvent);
}

void CDynamicWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    DoShow();

	CTransparentBaseDlg::OnLButtonDblClk(nFlags, point);
}

void CDynamicWnd::OnBtnHide() 
{
    OnClose();
}

BOOL CDynamicWnd::PreTranslateMessage(MSG* pMsg) 
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if ( pMsg->wParam == VK_RETURN )
        {
            return TRUE;
        }
        else if ( pMsg->wParam == VK_ESCAPE )
        {
            DoHide();

            return TRUE;
        }
    }

	return CTransparentBaseDlg::PreTranslateMessage(pMsg);
}

void CDynamicWnd::SetWindowTopMost()
{
//#ifndef _DEBUG
    m_pcParentWnd->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW  );
//#endif
}

LRESULT CDynamicWnd::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    Graphics *pGraphics = (Graphics*)wParam;

    if ( pGraphics == NULL )
    {
        // 为空的话，则是由子控件发来的，需要再向父窗口转发
        GetParent()->SendMessage( WM_REDRAW_UI, NULL, NULL );

        return S_FALSE;
    }

    if ( 0 != m_pImageBK )
    {
        CRect cRect;
        GetWindowRect( &cRect );
        POINT point = cRect.TopLeft();

        ::ScreenToClient( m_pcParentWnd->GetSafeHwnd(), &point );

       /* if ( m_bScale == TRUE )
        {
            pGraphics->DrawImage( m_pImageBK, point.x, point.y, 
				CUtility::GetScreenScaleWidth( m_pImageBK->GetWidth() ), CUtility::GetScreenScaleHeight( m_pImageBK->GetHeight() ) );
        }
        else
        {*/
            pGraphics->DrawImage( m_pImageBK, point.x, point.y, m_pImageBK->GetWidth(), m_pImageBK->GetHeight() );
        //}
    }

    return S_OK;
}

void CDynamicWnd::Hided()
{
	CMsgDispatch::SendMessage( WM_HIDE_FINISH_NOTIFY, 0, (LPARAM)this );
}

void CDynamicWnd::Showed()
{
	CMsgDispatch::SendMessage( WM_SHOW_FINISH_NOTIFY, 0, (LPARAM)this );
}