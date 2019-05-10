// transparentdlg.cpp : implementation file
//

#include "stdafx.h"
#include "transparentdlg.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentDlg dialog
#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif

#ifndef AC_SRC_ALPHA
#	define AC_SRC_ALPHA				0x01
#endif


CTransparentDlg::CTransparentDlg(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg( CTransparentDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CTransparentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransparentDlg, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CTransparentDlg)
		// NOTE: the ClassWizard will add message map macros here

		//}}AFX_MSG_MAP
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentDlg message handlers
BOOL CTransparentDlg::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	RedrawUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransparentDlg::RedrawUI()
{
    if ( m_pImgTitle == NULL || m_pImgMid == NULL || m_pImgBottom == NULL )
    {
        return;
    }

    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
    
	s32 nMinHeigh = m_pImgTitle->GetHeight() + m_pImgBottom->GetHeight();

	szWin.cx = m_pImgTitle->GetWidth();
	szWin.cy = abs( rc.bottom - rc.top );
	if ( nMinHeigh > szWin.cy )
    {  
        szWin.cy = nMinHeigh;
    }

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

      
        graph.DrawImage( m_pImgTitle, 0, 0, m_pImgTitle->GetWidth(),m_pImgTitle->GetHeight() );

		s32 nMidImgCounts = ( szWin.cy - nMinHeigh ) / m_pImgMid->GetHeight();

		s32 nMidTop = m_pImgTitle->GetHeight();
		s32 nMidImgHeight = m_pImgMid->GetHeight();

		for ( s32 i = 0; i < nMidImgCounts; i++ )
		{
			graph.DrawImage( m_pImgMid, 0, nMidTop + i * nMidImgHeight, m_pImgTitle->GetWidth(),m_pImgMid->GetHeight() );
		}

		if ( nMidImgCounts != 0 )
		{
			graph.DrawImage( m_pImgMid, 0, nMidTop + nMidImgCounts * nMidImgHeight, m_pImgTitle->GetWidth(), szWin.cy - nMinHeigh - nMidImgCounts * nMidImgHeight );
		}
        
		graph.DrawImage( m_pImgBottom, 0, szWin.cy - m_pImgBottom->GetHeight(), m_pImgBottom->GetWidth(),m_pImgBottom->GetHeight() );

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

BOOL32 CTransparentDlg::IniUI( UINT nTitle, UINT nMid, UINT nBottom )
{
	m_pImgTitle = CUtility::GetImage( nTitle, _T("PNG") );
	m_pImgMid	= CUtility::GetImage( nMid,	_T("PNG") );
	m_pImgBottom = CUtility::GetImage( nBottom, _T("PNG") );
	return TRUE;
}
