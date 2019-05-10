// TransparentEdit.cpp : implementation file
//

#include "stdafx.h"
#include "AirDispLocal.h"
#include "TransparentEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentEdit

CTransparentEdit::CTransparentEdit()
{
    m_emStatus = emStatusNormal;
    m_emTextAlign = emAlignmentRight;

    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    m_pImgFocusLeft = NULL;
    m_pImgFocusMiddle = NULL;
    m_pImgFocusRight = NULL;
    m_pImgIcon = NULL;

    m_cNormalColor = Color( 255, 255, 255 );
    m_cFocusColor = Color( 255, 255, 255 );
//    SetImage( IDR_NORMAL_LEFT, IDR_NORMAL_MIDDLE, IDR_NORMAL_RIGHT,
//              IDR_FOCUS_LEFT, IDR_FOCUS_MIDDLE, IDR_FOCUS_RIGHT );
    //SetImage( 0, 0, 0,
    //          IDR_SETTING_EDIT_FOCUS_LEFT, IDR_SETTING_EDIT_FOCUS_MIDDLE, IDR_SETTING_EDIT_FOCUS_RIGHT );
    SetImage( 0, 0, 0, 0, 0, 0 );

    m_dwIcon = 0;

    wcscpy( m_awszFontName, _T("Arial") );
    m_dwFontSize = 18;

    m_strTip = _T("");	
    m_bFocus = FALSE;
    m_bShowCursor = FALSE;
}

CTransparentEdit::~CTransparentEdit()
{
}


BEGIN_MESSAGE_MAP(CTransparentEdit, CEdit)
    //{{AFX_MSG_MAP(CTransparentEdit)
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    ON_WM_SHOWWINDOW()
    ON_WM_CHAR()
    ON_WM_LBUTTONDOWN()
    ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
    ON_WM_LBUTTONUP()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentEdit message handlers

LRESULT CTransparentEdit::OnRedrawUI( WPARAM wParam, LPARAM lParam )
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

    Image *pImgLeft = NULL;
    Image *pImgMiddle = NULL;
    Image *pImgRight = NULL;
    Color colorText;
    if ( m_emStatus == emStatusSetFocus )
    {
        pImgLeft = m_pImgFocusLeft;
        pImgMiddle = m_pImgFocusMiddle;
        pImgRight = m_pImgFocusRight;

        colorText = m_cFocusColor;
    }
    else
    {
        pImgLeft = m_pImgNormalLeft;
        pImgMiddle = m_pImgNormalMiddle;
        pImgRight = m_pImgNormalRight;

        colorText = m_cNormalColor;
    }

    if ( pImgLeft != NULL && pImgMiddle != NULL && pImgRight != NULL )
    {
        u32 nPosX = point.x + pImgLeft->GetWidth();
        u32 dwMiddleWidth = cRect.Width() - pImgLeft->GetWidth() - pImgRight->GetWidth();
        // 左
        pGraphics->DrawImage( pImgLeft, point.x, point.y, pImgLeft->GetWidth(), pImgLeft->GetHeight() );
        // 右
        pGraphics->DrawImage( pImgRight, point.x + cRect.Width() - pImgRight->GetWidth(), point.y, pImgRight->GetWidth(), pImgRight->GetHeight() );

        // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
        for ( u32 nIndex = 0; nIndex < ( dwMiddleWidth / pImgMiddle->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( pImgMiddle, nPosX, point.y, pImgMiddle->GetWidth(), pImgMiddle->GetHeight() );
            nPosX += pImgMiddle->GetWidth();
        }
        pGraphics->DrawImage( pImgMiddle, nPosX, point.y, dwMiddleWidth % pImgMiddle->GetWidth() /*dwMiddleWidth - 5*/, pImgMiddle->GetHeight() );

        // 调整高度和图片一致，宽度可以任意拉伸
        if ( cRect.Height() != m_pImgFocusLeft->GetHeight() )
        {
            SetWindowPos( NULL, 0, 0, cRect.Width(), m_pImgFocusLeft->GetHeight(), SWP_NOMOVE );
        }
    }

    // 绘制光标
    if ( m_bShowCursor == TRUE )
    {
        pGraphics->DrawLine( &Pen( m_cFocusColor, 2 ), Point( point.x + cRect.Width() - 5, point.y + 5 ), Point( point.x + cRect.Width() - 5, point.y + cRect.Height() - 5 ) );
    }

    // 绘制Icon
    if ( m_pImgIcon != NULL && m_emStatus == emStatusNormal )
    {
        s32 nPosX = point.x + 10, nPosY = point.y + ( cRect.Height() - m_pImgIcon->GetHeight() ) / 2;
        pGraphics->DrawImage( m_pImgIcon, nPosX, nPosY, m_pImgIcon->GetWidth(), m_pImgIcon->GetHeight() );
    }

    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));

    CString strText = GetShowText();

    if ( strText.GetLength() > 0 )
    {
        DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
        DWORD dwExStyle = GetWindowLong( m_hWnd, GWL_EXSTYLE );

        // 判断是否显示Tip
        BOOL32 bShowTip = FALSE;
        CString strWindowText;
        GetWindowText( strWindowText );
        if ( m_bFocus == FALSE && strWindowText == "" )
        {
            bShowTip = TRUE;
        }

        if ( ( dwStyle & ES_PASSWORD ) && bShowTip == FALSE )
        {
            CString strTemp;
            for ( u32 nIndex = 0; nIndex < strText.GetLength(); nIndex++ )
            {
                strTemp += "*";
            }
            strText = strTemp;
        }

        WCHAR *pwszText = NULL;
        pwszText = new WCHAR[strText.GetLength() + 1];
        ZeroMemory( pwszText, (strText.GetLength() + 1) * 2 );
        //ASNI TO UNICODE
        MultiByteToWideChar( CP_ACP, 0, (CT2A)strText, -1, (WCHAR*)(pwszText), strText.GetLength());

        StringFormat sf;
        sf.SetLineAlignment( StringAlignmentCenter );
        switch ( m_emTextAlign )
        {
        case emAlignmentLeft:
            sf.SetAlignment( StringAlignmentNear );
            break;
        case emAlignmentCenter:
            sf.SetAlignment( StringAlignmentCenter );
            break;
        case emAlignmentRight:
        default:
            sf.SetAlignment( StringAlignmentFar );
            break;
        }

        // 如果进行了图标的绘制，则文字的现实位置必须偏移
        if ( m_pImgIcon != NULL && m_emStatus == emStatusNormal )
        {
            point.x = point.x + 15 + m_pImgIcon->GetWidth();
            cRect.left = cRect.left + 15 + m_pImgIcon->GetWidth();
        }

        //对于tip和真正的文字进行不同的绘制
        u32 dwTextLen = wcslen( pwszText );
        RectF rectString;

        if ( TRUE == bShowTip )
        {
            colorText = Color( 157, 168, 174 );
            SolidBrush brush( colorText );

            //FontFamily fontFamily( m_awszFontName );
            //Font font( &fontFamily, 13 );
           FontFamily fontFamily(m_awszFontName); // 创建字体族对象
           Gdiplus::Font font(&fontFamily, m_dwFontSize); // 创建字体

            // 计算显示的字符数
            pGraphics->MeasureString( pwszText, -1, &font, PointF( (float)0, (float)0 ), &sf, &rectString );
            float fCharaterWidth = rectString.Width / dwTextLen;
            u32 dwCharaterNum = cRect.Width() / fCharaterWidth;
            if ( dwTextLen <= dwCharaterNum )
            {
                dwTextLen = 0;
            }
            else
            {
                dwTextLen -= dwCharaterNum;
            }

            pGraphics->DrawString( pwszText + dwTextLen, -1, &font, RectF( (float)point.x, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, 
                                   cRect.Width(), ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 5 ), &sf, &brush );
        } 
        else
        {
            SolidBrush brush( colorText ); // 创建白色的实心刷（写字符串用）

            //FontFamily fontFamily( m_awszFontName );
            //Font font( &fontFamily, m_dwFontSize );
           FontFamily fontFamily(m_awszFontName); // 创建字体族对象
           Gdiplus::Font font(&fontFamily, m_dwFontSize); // 创建字体

            // 计算显示的字符数
            pGraphics->MeasureString( pwszText, -1, &font, PointF( (float)0, (float)0 ), &sf, &rectString );
            float fCharaterWidth = rectString.Width / dwTextLen;
            u32 dwCharaterNum = cRect.Width() / fCharaterWidth;
            if ( dwTextLen <= dwCharaterNum )
            {
                dwTextLen = 0;
            }
            else
            {
                dwTextLen -= dwCharaterNum;
            }

            pGraphics->DrawString( pwszText + dwTextLen, -1, &font, RectF( (float)point.x, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, 
                               cRect.Width(), ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 5 ), &sf, &brush );

        }

        delete []pwszText;
    }

    return S_OK;
}

void CTransparentEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusSetFocus;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    // 将光标置到文本框的最后
    CString strWindowText;
    GetWindowText( strWindowText );
    SetSel( strWindowText.GetLength(), strWindowText.GetLength() );

    CEdit::OnLButtonDown(nFlags, point);
}

void CTransparentEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
    // 将光标置到文本框的最后
    CString strWindowText;
    GetWindowText( strWindowText );
    SetSel( strWindowText.GetLength(), strWindowText.GetLength() );

    CEdit::OnLButtonUp(nFlags, point);
}

void CTransparentEdit::OnSetFocus(CWnd* pOldWnd) 
{
    CEdit::OnSetFocus(pOldWnd);
    m_bFocus = TRUE;

    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusSetFocus;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CWnd *pParent = GetParent();
    if ( NULL != pParent && IsWindow( pParent->GetSafeHwnd() ) == TRUE )
    {
        pParent->PostMessage( WM_EDIT_SETFOCUS, 0, 0 );
    }

    SetTimer( 100, 600, NULL );
    m_bShowCursor = FALSE;
}

void CTransparentEdit::OnKillFocus(CWnd* pNewWnd) 
{
    CEdit::OnKillFocus(pNewWnd);
    m_bFocus = FALSE;
    m_bShowCursor = FALSE;

    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusNormal;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    KillTimer( 100 );
}

void CTransparentEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CEdit::OnShowWindow(bShow, nStatus);

    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusNormal;
        
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
}

void CTransparentEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    CEdit::OnChar(nChar, nRepCnt, nFlags);

    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusSetFocus;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
}

void CTransparentEdit::OnChange() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CEdit::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    if ( m_hParent != NULL )
    {
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CWnd *pParent = GetParent();
    if ( NULL != pParent && IsWindow( pParent->GetSafeHwnd() ) == TRUE )
    {
        pParent->PostMessage( WM_EDIT_CHANGED, 0, 0 );
    }
}

void CTransparentEdit::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    if ( m_hParent != NULL && IsWindowVisible() == TRUE )
    {
        m_bShowCursor = !m_bShowCursor;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CEdit::OnTimer(nIDEvent);
}


/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic

CTransparentStatic::CTransparentStatic()
{
    m_hParent = NULL;
    m_dwBkResID = NULL;
    m_pImgBk = NULL;
	m_cNormalColor = Color( 255, 255, 255 );
    
    m_emTextAlign = emAlignmentLeft;//emAlignmentCenter

	wcscpy( m_awszFontName, _T("Arial") );
	m_dwFontSize = 18;

	m_bOverShow = false;
	m_stOverShowType = StringTrimmingNone;
}

CTransparentStatic::~CTransparentStatic()
{
}


BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
//{{AFX_MSG_MAP(CTransparentStatic)
//}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic message handlers

LRESULT CTransparentStatic::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    Graphics *pGraphics = (Graphics*)wParam;
    m_hParent = (HWND)lParam;

    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }

    CRect cRect;
	Color colorText;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( m_hParent, &point );

    if ( NULL != m_pImgBk )
    {
        pGraphics->DrawImage( m_pImgBk, point.x, point.y, cRect.Width(), cRect.Height() );
    }

//     FontFamily fontFamily(L"Arial"); // 创建字体族对象
//     Font font(&fontFamily, 15); // 创建字体

	FontFamily fontFamily(m_awszFontName); // 创建字体族对象
    Gdiplus::Font font(&fontFamily, m_dwFontSize); // 创建字体
	colorText = m_cNormalColor;
    SolidBrush brush( colorText  ); // 创建白色的实心刷（写字符串用）

    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));

    CString strText;
    GetWindowText( strText );
//     WCHAR awszText[512];
//     ZeroMemory( awszText, sizeof( awszText ) );
//     //ASNI TO UNICODE
//     MultiByteToWideChar( CP_ACP, 0, (LPCSTR)strText, -1, (WCHAR*)(awszText), strText.GetLength() );

    StringFormat sf;
    sf.SetLineAlignment( StringAlignmentCenter );
	if (m_bOverShow)
	{
		sf.SetTrimming(m_stOverShowType); 
	}

    if ( emAlignmentLeft == m_emTextAlign )
    {
        sf.SetAlignment( StringAlignmentNear );
    }
    else if ( emAlignmentCenter == m_emTextAlign )
    {
        sf.SetAlignment( StringAlignmentCenter );
    }
    else
    {
        sf.SetAlignment( StringAlignmentFar );
    }

    pGraphics->DrawString( strText, -1, &font, RectF( (float)point.x, (float)point.y, cRect.Width(), cRect.Height() ), &sf, &brush );

    return S_OK;    
}


/////////////////////////////////////////////////////////////////////////////
// CTransparentIPAddrCtrl

CTransparentIPAddrCtrl::CTransparentIPAddrCtrl()
{
    m_emStatus = emStatusNormal;

    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    m_pImgFocusLeft = NULL;
    m_pImgFocusMiddle = NULL;
    m_pImgFocusRight = NULL;

    m_hParent = NULL;
    m_hChild1 = NULL;
    m_hChild2 = NULL;
    m_hChild3 = NULL;
    m_hChild4 = NULL;
    m_hFocusWnd = NULL;

    m_bShowCursor = FALSE;
    m_bShowCursorInChild1 = FALSE;
    m_bShowCursorInChild2 = FALSE;
    m_bShowCursorInChild3 = FALSE;
    m_bShowCursorInChild4 = FALSE;

    m_cNormalColor = Color( 255, 255, 255 );
    m_cFocusColor = Color( 30, 41, 47 );

	//ip控件暂时不用
//     SetImage( IDR_NORMAL_LEFT, IDR_NORMAL_MIDDLE, IDR_NORMAL_RIGHT,
//               IDR_FOCUS_LEFT, IDR_FOCUS_MIDDLE, IDR_FOCUS_RIGHT );

	wcscpy( m_awszFontName, _T("Arial") );
	m_dwFontSize = 14;
}

CTransparentIPAddrCtrl::~CTransparentIPAddrCtrl()
{
}


BEGIN_MESSAGE_MAP(CTransparentIPAddrCtrl, CIPAddressCtrl)
    //{{AFX_MSG_MAP(CTransparentIPAddrCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE( WM_PARENTNOTIFY, OnParentNotify )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentIPAddrCtrl message handlers


LRESULT CTransparentIPAddrCtrl::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    Graphics *pGraphics = (Graphics*)wParam;
    m_hParent = (HWND)lParam;

    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }

    if ( m_hChild1 == NULL
         || m_hChild2 == NULL
         || m_hChild3 == NULL
         || m_hChild4 == NULL )
    {
        m_hChild1 = ::GetWindow( m_hWnd, GW_CHILD );
        m_hChild2 = ::GetWindow( m_hChild1, GW_HWNDNEXT );
        m_hChild3 = ::GetWindow( m_hChild2, GW_HWNDNEXT );
        m_hChild4 = ::GetWindow( m_hChild3, GW_HWNDNEXT );
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( m_hParent, &point );

    Image *pImgLeft = NULL;
    Image *pImgMiddle = NULL;
    Image *pImgRight = NULL;
    Color colorText;
    if ( m_emStatus == emStatusSetFocus )
    {
        pImgLeft = m_pImgFocusLeft;
        pImgMiddle = m_pImgFocusMiddle;
        pImgRight = m_pImgFocusRight;

        colorText = m_cFocusColor;
    }
    else
    {
        pImgLeft = m_pImgNormalLeft;
        pImgMiddle = m_pImgNormalMiddle;
        pImgRight = m_pImgNormalRight;

        colorText = m_cNormalColor;
    }

    if ( pImgLeft != NULL && pImgMiddle != NULL && pImgRight != NULL )
    {
        u32 nPosX = point.x + pImgLeft->GetWidth();
        u32 dwMiddleWidth = cRect.Width() - pImgLeft->GetWidth() - pImgRight->GetWidth();
        // 左
        pGraphics->DrawImage( pImgLeft, point.x, point.y, pImgLeft->GetWidth(), pImgLeft->GetHeight() );
        // 右
        pGraphics->DrawImage( pImgRight, point.x + cRect.Width() - pImgRight->GetWidth(), point.y, pImgRight->GetWidth(), pImgRight->GetHeight() );
        
        // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
        for ( u32 nIndex = 0; nIndex < ( dwMiddleWidth / pImgMiddle->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( pImgMiddle, nPosX, point.y, pImgMiddle->GetWidth(), pImgMiddle->GetHeight() );
            nPosX += pImgMiddle->GetWidth();
        }
        pGraphics->DrawImage( pImgMiddle, nPosX, point.y, dwMiddleWidth % pImgMiddle->GetWidth() /*dwMiddleWidth - 5*/, pImgMiddle->GetHeight() );
        
        // 调整高度和图片一致，宽度可以任意拉伸
        if ( cRect.Height() != pImgLeft->GetHeight() )
        {
            SetWindowPos( NULL, 0, 0, cRect.Width(), pImgLeft->GetHeight(), SWP_NOMOVE );
        }
    }
    
//     FontFamily fontFamily(L"Arial"); // 创建字体族对象
//     Font font(&fontFamily, 14); // 创建字体
	FontFamily fontFamily(m_awszFontName); // 创建字体族对象
    Gdiplus::Font font(&fontFamily, m_dwFontSize); // 创建字体
    SolidBrush brush( colorText ); // 创建白色的实心刷（写字符串用）

    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
    StringFormat sf;
    sf.SetLineAlignment( StringAlignmentCenter );
    sf.SetAlignment( StringAlignmentCenter );

    u32 nCtrlHeight = cRect.Height();
    if ( m_emStatus == emStatusSetFocus )
    {
        if ( m_hChild1 != NULL )
        {
            CString strText;
            TCHAR abyText[10] = { 0 };
            ::GetWindowText( m_hChild1, abyText, 10 );
//             WCHAR awszText[20];
//             ZeroMemory( awszText, sizeof( awszText ) );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, abyText, -1, (WCHAR*)(awszText), strlen( abyText ) );

            ::GetWindowRect( m_hChild1, &cRect );
            POINT point = cRect.TopLeft();
            ::ScreenToClient( m_hParent, &point );
            pGraphics->DrawString( abyText, -1, &font, RectF( (float)point.x - 5, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, cRect.Width() + 10, ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 4 ), &sf, &brush );

            if ( m_bShowCursorInChild1 == TRUE && m_bShowCursor == TRUE )
            {
                pGraphics->DrawLine( &Pen( colorText, 2 ), Point( point.x + cRect.Width() - 3, point.y + 3 ), Point( point.x + cRect.Width() - 3, point.y + nCtrlHeight - 12 ) );
            }
        }
        if ( m_hChild2 != NULL )
        {
            CString strText;
            TCHAR abyText[10] = { 0 };
            ::GetWindowText( m_hChild2, abyText, 10 );
//             WCHAR awszText[20];
//             ZeroMemory( awszText, sizeof( awszText ) );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, abyText, -1, (WCHAR*)(awszText), strlen( abyText ) );

            ::GetWindowRect( m_hChild2, &cRect );
            POINT point = cRect.TopLeft();
            ::ScreenToClient( m_hParent, &point );
            pGraphics->DrawString( abyText, -1, &font, RectF( (float)point.x - 5, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, cRect.Width() + 10, ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 4 ), &sf, &brush );

            pGraphics->DrawEllipse( &Pen( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );
            pGraphics->FillEllipse( &SolidBrush( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );

            if ( m_bShowCursorInChild2 == TRUE && m_bShowCursor == TRUE )
            {
                pGraphics->DrawLine( &Pen( colorText, 2 ), Point( point.x + cRect.Width() - 3, point.y + 3 ), Point( point.x + cRect.Width() - 3, point.y + nCtrlHeight - 12 ) );
            }
        }
        if ( m_hChild3 != NULL )
        {
            CString strText;
            TCHAR abyText[10] = { 0 };
            ::GetWindowText( m_hChild3, abyText, 10 );
//             WCHAR awszText[20];
//             ZeroMemory( awszText, sizeof( awszText ) );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, abyText, -1, (WCHAR*)(awszText), strlen( abyText ) );

            ::GetWindowRect( m_hChild3, &cRect );
            POINT point = cRect.TopLeft();
            ::ScreenToClient( m_hParent, &point );
            pGraphics->DrawString( abyText, -1, &font, RectF( (float)point.x - 5, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, cRect.Width() + 10, ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 4 ), &sf, &brush );

            pGraphics->DrawEllipse( &Pen( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );
            pGraphics->FillEllipse( &SolidBrush( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );
            
            if ( m_bShowCursorInChild3 == TRUE && m_bShowCursor == TRUE )
            {
                pGraphics->DrawLine( &Pen( colorText, 2 ), Point( point.x + cRect.Width() - 3, point.y + 3 ), Point( point.x + cRect.Width() - 3, point.y + nCtrlHeight - 12 ) );
            }
        }
        if ( m_hChild4 != NULL )
        {
            CString strText;
            TCHAR abyText[10] = { 0 };
            ::GetWindowText( m_hChild4, abyText, 10 );
//             WCHAR awszText[20];
//             ZeroMemory( awszText, sizeof( awszText ) );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, abyText, -1, (WCHAR*)(awszText), strlen( abyText ) );

            ::GetWindowRect( m_hChild4, &cRect );
            POINT point = cRect.TopLeft();
            ::ScreenToClient( m_hParent, &point );
            pGraphics->DrawString( abyText, -1, &font, RectF( (float)point.x - 5, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, cRect.Width() + 10, ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 4 ), &sf, &brush );

            pGraphics->DrawEllipse( &Pen( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );
            pGraphics->FillEllipse( &SolidBrush( Color( 11, 154, 215 ) ), point.x + cRect.Width(), point.y + cRect.Height() / 2 + 3, 3, 3 );
            
            if ( m_bShowCursorInChild4 == TRUE && m_bShowCursor == TRUE )
            {
                pGraphics->DrawLine( &Pen( colorText, 2 ), Point( point.x + cRect.Width() - 3, point.y + 3 ), Point( point.x + cRect.Width() - 3, point.y + nCtrlHeight - 12 ) );
            }
        }
    }
    else
    {
//         DWORD dwAddress;
//         GetAddress( dwAddress );
// 
//         if ( dwAddress != 0 )
//         {
//             CString strIP = CCallAddr::GetIpStr( dwAddress );
// 
//             sf.SetLineAlignment( StringAlignmentCenter );
//             sf.SetAlignment( StringAlignmentNear );
// 
//             GetWindowRect( &cRect );
//             POINT point = cRect.TopLeft();
// 
//             ::ScreenToClient( m_hParent, &point );
// 
//             WCHAR awszText[20];
//             ZeroMemory( awszText, sizeof( awszText ) );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, (s8*)(LPCTSTR)strIP, -1, (WCHAR*)(awszText), strIP.GetLength() );
// 
//             pGraphics->DrawString( awszText, -1, &font, RectF( (float)point.x, (float)point.y + m_pImgFocusLeft->GetHeight() / 7, cRect.Width(), ( ((double)m_pImgFocusLeft->GetHeight()) / 7 ) * 4 ), &sf, &brush );
//         }
    }

    return S_OK;   
}

void CTransparentIPAddrCtrl::OnTimer(UINT nIDEvent) 
{
    if ( m_hParent != NULL && IsWindowVisible() == TRUE )
    {
        m_bShowCursor = !m_bShowCursor;

        m_bShowCursorInChild1 = FALSE;
        m_bShowCursorInChild2 = FALSE;
        m_bShowCursorInChild3 = FALSE;
        m_bShowCursorInChild4 = FALSE;

        CWnd *pWnd = NULL;
        pWnd = GetFocus();
        if ( pWnd != NULL )
        {
            HWND hWnd = pWnd->m_hWnd;
            if ( hWnd == m_hChild1 )
            {
                m_bShowCursorInChild1 = TRUE;
            }
            if ( hWnd == m_hChild2 )
            {
                m_bShowCursorInChild2 = TRUE;
            }
            if ( hWnd == m_hChild3 )
            {
                m_bShowCursorInChild3 = TRUE;
            }
            if ( hWnd == m_hChild4 )
            {
                m_bShowCursorInChild4 = TRUE;
            }
        }

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CIPAddressCtrl::OnTimer(nIDEvent);
}

LRESULT CTransparentIPAddrCtrl::OnParentNotify( UINT message, LPARAM lParam )
{
    if ( message == WM_LBUTTONDOWN )
	{
        m_emStatus = emStatusSetFocus;

        m_bShowCursor = FALSE;
        SetTimer( 101, 600, NULL );

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

        if ( m_hChild1 == NULL
             || m_hChild2 == NULL
             || m_hChild3 == NULL
             || m_hChild4 == NULL )
        {
            m_hChild1 = ::GetWindow( m_hWnd, GW_CHILD );
            m_hChild2 = ::GetWindow( m_hChild1, GW_HWNDNEXT );
            m_hChild3 = ::GetWindow( m_hChild2, GW_HWNDNEXT );
            m_hChild4 = ::GetWindow( m_hChild3, GW_HWNDNEXT );
        }
    }

    return S_OK;
}

void CTransparentIPAddrCtrl::OnKillFocus(CWnd* pNewWnd) 
{
    CIPAddressCtrl::OnKillFocus(pNewWnd);

    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusNormal;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
}

BOOL CTransparentIPAddrCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    if ( EN_SETFOCUS == HIWORD( wParam ) )
    {
        m_emStatus = emStatusSetFocus;
        m_hFocusWnd = (HWND)lParam;

        m_bShowCursor = FALSE;
        m_bShowCursorInChild1 = FALSE;
        m_bShowCursorInChild2 = FALSE;
        m_bShowCursorInChild3 = FALSE;
        m_bShowCursorInChild4 = FALSE;
        SetTimer( 101, 600, NULL );

//         CEdit *pcEdit = (CEdit*)CWnd::FromHandle( m_hFocusWnd );
//         CString strText;
//         pcEdit->GetWindowText( strText );
//         pcEdit->SetSel( strText.GetLength(), strText.GetLength() );

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
    if ( EN_KILLFOCUS == HIWORD( wParam ) )
    {
        m_emStatus = emStatusNormal;
        m_hFocusWnd = NULL;

        m_bShowCursor = FALSE;
        m_bShowCursorInChild1 = FALSE;
        m_bShowCursorInChild2 = FALSE;
        m_bShowCursorInChild3 = FALSE;
        m_bShowCursorInChild4 = FALSE;
        KillTimer( 101 );

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
    if ( EN_CHANGE == HIWORD( wParam ) )
    {
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
    if ( EN_UPDATE == HIWORD( wParam ) )
    {
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    return CIPAddressCtrl::OnCommand(wParam, lParam);
}

void CTransparentIPAddrCtrl::MoveWindow( LPCRECT lpRect, BOOL bRepaint /*= TRUE*/ )
{
    // IP地址控件不能改变宽度和高度
    CRect cCtrlRect;
    GetWindowRect( &cCtrlRect );

    u32 dwWidth = cCtrlRect.Width();
    u32 dwHeight = cCtrlRect.Height();
    cCtrlRect.left = lpRect->left;
    cCtrlRect.top = lpRect->top;
    cCtrlRect.right = cCtrlRect.left + dwWidth;
    cCtrlRect.bottom = cCtrlRect.top + dwHeight;

    CWnd::MoveWindow( &cCtrlRect, bRepaint );
}

/////////////////////////////////////////////////////////////////////////////
// CTransparentSliderCtrl

CTransparentSliderCtrl::CTransparentSliderCtrl()
{
    m_emStatus = emStatusNormal;

    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    
    m_pImgHighLightLeft = NULL;
    m_pImgHighLightMiddle = NULL;
    m_pImgHighLightRight = NULL;
    
    m_pImgThumbNormal = NULL;
    m_pImgThumbPress = NULL;

    SetImage( IDR_SLIDER_NORMAL_LEFT, IDR_SLIDER_NORMAL_MIDDLE, IDR_SLIDER_NORMAL_RIGHT,
              IDR_SLIDER_HIGHLIGHT_LEFT, IDR_SLIDER_HIGHLIGHT_MIDDLE, IDR_SLIDER_HIGHLIGHT_RIGHT,
              IDR_SLIDER_THUMB_NORMAL, IDR_SLIDER_THUMB_PRESS );
}

CTransparentSliderCtrl::~CTransparentSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CTransparentSliderCtrl, CSliderCtrl)
    //{{AFX_MSG_MAP(CTransparentSliderCtrl)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_CAPTURECHANGED()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentSliderCtrl message handlers

void CTransparentSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    m_emStatus = emStatusSetFocus;

    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

    CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CTransparentSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CTransparentSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
    if ( m_emStatus == emStatusSetFocus )
    {
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CSliderCtrl::OnMouseMove(nFlags, point);
}

void CTransparentSliderCtrl::OnCaptureChanged(CWnd *pWnd) 
{
    m_emStatus = emStatusNormal;

    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

    CSliderCtrl::OnCaptureChanged(pWnd);
}

LRESULT CTransparentSliderCtrl::OnRedrawUI( WPARAM wParam, LPARAM lParam )
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

    Image *pImgThumb = NULL;

    if ( m_emStatus == emStatusSetFocus )
    {
        pImgThumb = m_pImgThumbPress;
    }
    else
    {
        pImgThumb = m_pImgThumbNormal;
    }

    // 绘制底图
    s32 nPosX = point.x + m_pImgNormalLeft->GetWidth();
    s32 nPosY = point.y + ( cRect.Height() - m_pImgNormalLeft->GetHeight() ) / 2;
    s32 nMiddleWidth = cRect.Width() - m_pImgNormalLeft->GetWidth() - m_pImgNormalLeft->GetWidth();
    // 左
    pGraphics->DrawImage( m_pImgNormalLeft, point.x, nPosY, m_pImgNormalLeft->GetWidth(), m_pImgNormalLeft->GetHeight() );
    // 右
    pGraphics->DrawImage( m_pImgNormalRight, point.x + cRect.Width() - m_pImgNormalRight->GetWidth(), nPosY, m_pImgNormalRight->GetWidth(), m_pImgNormalRight->GetHeight() );

    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for ( u32 nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetWidth() ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgNormalMiddle, nPosX, nPosY, m_pImgNormalMiddle->GetWidth(), m_pImgNormalMiddle->GetHeight() );
        nPosX += m_pImgNormalMiddle->GetWidth();
    }
    pGraphics->DrawImage( m_pImgNormalMiddle, nPosX, nPosY, nMiddleWidth % m_pImgNormalMiddle->GetWidth(), m_pImgNormalMiddle->GetHeight() );

    // 绘制高亮的地方
    CRect cRectThumb;
    GetThumbRect( &cRectThumb );
    // 左
    pGraphics->DrawImage( m_pImgHighLightLeft, point.x, nPosY, m_pImgHighLightLeft->GetWidth(), m_pImgHighLightLeft->GetHeight() );
    // 右
    pGraphics->DrawImage( m_pImgHighLightRight, point.x + cRectThumb.right - m_pImgHighLightRight->GetWidth(), nPosY, m_pImgHighLightRight->GetWidth(), m_pImgHighLightRight->GetHeight() );

    nPosX = point.x + m_pImgHighLightLeft->GetWidth();
    nMiddleWidth = cRectThumb.right - m_pImgHighLightLeft->GetWidth() - m_pImgHighLightRight->GetWidth();
    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for (u32 nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / m_pImgHighLightMiddle->GetWidth() ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgHighLightMiddle, nPosX, nPosY, m_pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
        nPosX += m_pImgHighLightMiddle->GetWidth();
    }
    if ( nMiddleWidth > 0 )
    {
        pGraphics->DrawImage( m_pImgHighLightMiddle, nPosX, nPosY, nMiddleWidth % m_pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
    }

    // 绘制Thumb
    pGraphics->DrawImage( pImgThumb, point.x + cRectThumb.left - 15, point.y - 5, pImgThumb->GetWidth(), pImgThumb->GetHeight() );
    //pGraphics->DrawImage( pImgThumb, point.x + cRectThumb.left - 15, point.y - 5, cRectThumb.Width(), cRectThumb.Height() );


//     // 调整高度和图片一致，宽度可以任意拉伸
//     if ( cRect.Height() != pImgLeft->GetHeight() )
//     {
//         SetWindowPos( NULL, 0, 0, cRect.Width(), pImgLeft->GetHeight(), SWP_NOMOVE );
//     }

    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CTransparentCheckButton

CTransparentCheckButton::CTransparentCheckButton()
{
    m_emStatus = emStatusNormal;

    m_dwCheckNormal = 0;
    m_dwCheckPress = 0;
    m_dwCheckDiable = 0;
    
    m_dwUnCheckNormal = 0;
    m_dwUnCheckPress = 0;
    m_dwUnCheckDiable = 0;

    m_pImgCheckNormal = NULL;
    m_pImgCheckPress = NULL;
    m_pImgCheckDiable = NULL;

    m_pImgUnCheckNormal = NULL;
    m_pImgUnCheckPress = NULL;
    m_pImgUnCheckDiable = NULL;
}

CTransparentCheckButton::~CTransparentCheckButton()
{
}


BEGIN_MESSAGE_MAP(CTransparentCheckButton, CButton)
    //{{AFX_MSG_MAP(CTransparentCheckButton)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentCheckButton message handlers

LRESULT CTransparentCheckButton::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    if ( m_hParent != (HWND)lParam && m_hParent != 0 )
    {
        int i = 0;
    }
    m_hParent = (HWND)lParam;

    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }

#ifdef _DEBUG
    CString strWindowText;
    GetWindowText( strWindowText );
#endif // _DEBUG

    if ( 0 == m_dwCheckNormal )
    {
        return S_FALSE;
    }

    Graphics *pGraphics = (Graphics*)wParam;

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( m_hParent, &point );

    Image *pImage = NULL;
    switch ( m_emStatus )
    {
    case emStatusNormal:
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckNormal : m_pImgUnCheckNormal;
        break;
    case emStatusPress:
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckPress : m_pImgUnCheckPress;
        break;
    }

    if ( FALSE == IsWindowEnabled() )
    {
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckDiable : m_pImgUnCheckDiable;
    }

    if ( NULL != pImage )
    {
        pGraphics->DrawImage( pImage, point.x, point.y, pImage->GetWidth(), pImage->GetHeight() );

//         if ( TRUE == m_bShowText )
//         {
//             FontFamily fontFamily(L"黑体"); // 创建字体族对象
//             Font font(&fontFamily, 35); // 创建5号字大小的Times New Roman字体
//             SolidBrush brush(Color(0, 128, 0)); // 创建绿色的实心刷（写字符串用）
//             pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
// 
//             CString strText;
//             GetWindowText( strText );
//             WCHAR *pwszText = NULL;
//             pwszText = new WCHAR[strText.GetLength() + 1];
//             ZeroMemory( pwszText, (strText.GetLength() + 1) * 2 );
//             //ASNI TO UNICODE
//             MultiByteToWideChar( CP_ACP, 0, (LPCSTR)strText, -1, (WCHAR*)(pwszText), strText.GetLength());
// 
//             pGraphics->DrawString( pwszText, -1, &font, PointF( (float)point.x, (float)point.y ), &brush );
//         }
    }

    if ( cRect.Width() != m_pImgCheckNormal->GetWidth()
         || cRect.Height() != m_pImgCheckNormal->GetHeight() )
    {
        SetWindowPos( NULL, 0, 0, m_pImgCheckNormal->GetWidth(), m_pImgCheckNormal->GetHeight(), SWP_NOMOVE );
    }

    return S_OK;  
}

LRESULT CTransparentCheckButton::OnBMSetCheck(WPARAM wparam, LPARAM lParam)
{
    DefWindowProc( BM_SETCHECK, wparam, lParam );

    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

    return 0;
}

void CTransparentCheckButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusPress;

        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CButton::OnLButtonDown(nFlags, point);
}

void CTransparentCheckButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if ( m_hParent != NULL )
    {
        m_emStatus = emStatusNormal;
        
        ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }

    CButton::OnLButtonUp(nFlags, point);
}

CString CTransparentEdit::GetShowText()
{
    CString strText;
    GetWindowText(strText);

    if ( FALSE == m_bFocus && strText == "" )
    {
        return m_strTip;
    } 

    return strText;
}
