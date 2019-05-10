#include "stdafx.h"
#include "transparentsyslink.h"

CTransparentSysLink::CTransparentSysLink()
{
	m_hParent = NULL;
	wcscpy( m_awszFontName, _T("微软雅黑") );
	m_dwFontSize = 9;
	m_cTextColor = Color( 0, 122, 192 );
}

CTransparentSysLink::~CTransparentSysLink()
{

}

BEGIN_MESSAGE_MAP(CTransparentSysLink, CLinkCtrl)
	//{{AFX_MSG_MAP(CTransparentGif)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

LRESULT CTransparentSysLink::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	m_hParent = (HWND)lParam;

	if ( IsWindowVisible() == FALSE )
	{
		return S_FALSE;
	}
	
	Graphics *pGraphics = (Graphics*)wParam;

	CString strUrl;
	GetItemUrl(0, strUrl);
	if (strUrl.IsEmpty())
	{
		return S_FALSE;
	}

	CRect cRect;
	GetWindowRect( &cRect );
	POINT point = cRect.TopLeft();
	::ScreenToClient( m_hParent, &point );

	FontFamily fontFamily( m_awszFontName );
	Gdiplus::Font font( &fontFamily, m_dwFontSize, FontStyleUnderline );

	Color colorText;
	colorText = m_cTextColor;
	SolidBrush brush( colorText ); // 创建绿色的实心刷（写字符串用）
	pGraphics->SetTextRenderingHint( TextRenderingHint( TextRenderingHintAntiAlias ) );

	StringFormat sf;
	sf.SetLineAlignment( StringAlignmentNear );
    pGraphics->DrawString( strUrl, -1, &font, RectF( (float)point.x , (float)point.y, cRect.Width(), cRect.Height() ), &sf, &brush );
	
	return S_OK;    
}

