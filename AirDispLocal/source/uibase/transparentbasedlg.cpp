// TransparentBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentBaseDlg.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog

PFN_SetLayeredWindowAttributes CTransparentBaseDlg::m_s_pfnSetLayeredWindowAttributes = NULL;
PFN_UpdateLayeredWindow CTransparentBaseDlg::m_s_pfnUpdateLayeredWindow = NULL;

UINT ReDrawThread(LPVOID pParam)
{
	//Sleep(20);
	CTransparentBaseDlg *pThis =(CTransparentBaseDlg*)pParam;
	pThis->RedrawUIAll();
	pThis->SetReadyToRedrawUI(FALSE);
	return 0;
}

CTransparentBaseDlg::CTransparentBaseDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CTransparentBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_dwBkResourceID = 0;
    m_pImageBK = NULL;
    m_bTransparentWithoutBK = FALSE;
    m_bReadyToRedrawUI = FALSE;
    m_bRedrawUIImediately = FALSE;
	m_byteSourceConstantAlpha = 255;
	m_bAjustSize = FALSE;
    m_bScale = FALSE;
}


void CTransparentBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentBaseDlg)
	//}}AFX_DATA_MAP
}

CTransparentBaseDlg::~CTransparentBaseDlg()
{
	if ( m_bScale == TRUE && m_pImageBK != NULL )
	{
		delete m_pImageBK;
	}
}

BEGIN_MESSAGE_MAP(CTransparentBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CTransparentBaseDlg)
    ON_WM_TIMER()
    ON_WM_SHOWWINDOW()
    ON_WM_ERASEBKGND()
	//ON_WM_PAINT()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg message handlers

BOOL CTransparentBaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    HMODULE hUser32Dll = ::GetModuleHandle( _T("user32.dll") );
    ASSERT(hUser32Dll);

    if( NULL == m_s_pfnSetLayeredWindowAttributes )
    {
        m_s_pfnSetLayeredWindowAttributes = (PFN_SetLayeredWindowAttributes)::GetProcAddress( hUser32Dll, "SetLayeredWindowAttributes" );
        ASSERT(m_s_pfnSetLayeredWindowAttributes);
    }

    if( NULL == m_s_pfnUpdateLayeredWindow )
    {
        m_s_pfnUpdateLayeredWindow = (PFN_UpdateLayeredWindow)::GetProcAddress( hUser32Dll, "UpdateLayeredWindow" );
        ASSERT(m_s_pfnUpdateLayeredWindow);
	}

	::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong( m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED );
    if ( 0 != m_dwBkResourceID || TRUE == m_bTransparentWithoutBK )
    {
        if ( 0 != m_dwBkResourceID )
        {
            m_pImageBK = CUtility::GetImage( m_dwBkResourceID, _T("PNG") );
        }

        RedrawUI();
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransparentBaseDlg::OnTimer(UINT nIDEvent) 
{
    m_bReadyToRedrawUI = FALSE;
    KillTimer( 1 );

    RedrawUI();

    CDialog::OnTimer( nIDEvent );
}

BOOL CTransparentBaseDlg::OnEraseBkgnd(CDC* pDC) 
{
    PostMessage( WM_REDRAW_UI, NULL, NULL );

    return CDialog::OnEraseBkgnd(pDC);
}

void CTransparentBaseDlg::OnPaint() 
{
    
}

LRESULT CTransparentBaseDlg::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    if ( 0 == m_dwBkResourceID && FALSE == m_bTransparentWithoutBK )
    {
        return S_FALSE;
    }

    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }

    if ( TRUE == m_bRedrawUIImediately )
    {
        RedrawUI();

        return S_OK;
    }

    // 控制刷新，提高效率
    if ( TRUE == m_bReadyToRedrawUI )
    {
        //TRACE( "[CTransparentBaseDlg::OnRedrawUI] m_bReadyToRedrawUI = TRUE\n" );

        //return S_OK;
    }

    m_bReadyToRedrawUI = TRUE;
    
	//修改为线程模式 --定时器现象:定时器有时导致定时函数得不到执行，导致界面控件不显示
	//SetTimer( 1, 20, NULL );
	//AfxBeginThread(ReDrawThread, this);
	RedrawUI();
    return S_OK;    
}

void CTransparentBaseDlg::RedrawUI()
{
    if ( 0 == m_dwBkResourceID && FALSE == m_bTransparentWithoutBK )
    {
        return;
    }

    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
    /*if ( m_bTransparentWithoutBK == FALSE && m_pImageBK != NULL )
    {
		if ( m_bScale == TRUE && m_bAjustSize == FALSE )
		{
			m_pImageBK = CUtility::ScaleBitmap( m_pImageBK, CUtility::GetScreenScaleWidth( m_pImageBK->GetWidth() ),
				CUtility::GetScreenScaleHeight( m_pImageBK->GetHeight() ) );
			m_bAjustSize = TRUE;
		}
        szWin.cx = m_pImageBK->GetWidth();
        szWin.cy = m_pImageBK->GetHeight();
    }
    else*/
    {
        szWin.cx = rc.right - rc.left;
        szWin.cy = rc.bottom - rc.top;
    }

/*	if ( m_bAjustSize == FALSE && m_bScale == TRUE )
    {
        szWin.cx = CUtility::GetScreenScaleWidth( szWin.cx );
        szWin.cy = CUtility::GetScreenScaleHeight( szWin.cy );
		
        m_bAjustSize = TRUE;
    }*/

    BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, m_byteSourceConstantAlpha, AC_SRC_ALPHA };

    HDC hDC = ::GetDC(NULL);
    HDC hdcMemory = ::CreateCompatibleDC(hDC);

    BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
    int nBytesPerLine = ((szWin.cx * 32 + 31) & (~31)) >> 3;
    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = szWin.cx;   
    stBmpInfoHeader.biHeight = szWin.cy;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = nBytesPerLine * szWin.cy;	

    PUINT32 pvBits = NULL;   
    HBITMAP hbmpMem = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);

    ASSERT(hbmpMem != NULL);
    if(hbmpMem)   
    {   
        HGDIOBJ hbmpOld = ::SelectObject( hdcMemory, hbmpMem); 

        Graphics graph( hdcMemory );
        graph.Clear( Color( 0, 0, 0, 0 ) );

        graph.SetSmoothingMode( SmoothingModeHighQuality );

        if ( NULL != m_pImageBK )
        {
            graph.DrawImage( m_pImageBK, 0, 0, szWin.cx, szWin.cy );
        }

        // 绘制所有子窗口
        DrawChildWnd( &graph, GetSafeHwnd() );

        m_s_pfnUpdateLayeredWindow( m_hWnd,
                                    hDC,
                                    &ptWinPos,
                                    &szWin,
                                    hdcMemory,
                                    &ptSrc,
                                    0,
                                    &stBlend,
                                    ULW_ALPHA
                                   );

        ::SelectObject( hdcMemory, hbmpOld );   
        ::DeleteObject( hbmpMem ); 
    }

    ::DeleteDC( hdcMemory );
    ::DeleteDC( hDC );
}

void CTransparentBaseDlg::DrawChildWnd( Graphics *pGraphics, HWND hParentWnd )
{
    HWND hwndChild = ::GetWindow( hParentWnd, GW_CHILD );

    while( hwndChild != NULL )
    {
        // 通知子窗口进行绘制
        ::SendMessage( hwndChild, WM_REDRAW_UI, (WPARAM)pGraphics, (LPARAM)m_hWnd );

        DrawChildWnd( pGraphics, hwndChild );
#ifdef _DEBUG
        CString strWindowText;
        TCHAR abyText[128] = { 0 };
        ::GetWindowText( hwndChild, abyText, 128 );
        strWindowText = abyText;
        //TRACE( strWindowText );
#endif // _DEBUG

        hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT );
    }
}

void CTransparentBaseDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);
    
    // TODO: Add your message handler code here
    if ( TRUE == bShow )
    {
        PostMessage( WM_REDRAW_UI, NULL, NULL );
    }
}

s32 CTransparentBaseDlg::GetWindowWidth()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetWidth();
}

s32 CTransparentBaseDlg::GetWindowHeight()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetHeight();
}