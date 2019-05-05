// TouchMenuSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TouchMenuCtrl.h"
#include "TouchMenuSubDlg.h"
#include "dragitem.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuSubDlg dialog


CTouchMenuSubDlg::CTouchMenuSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTouchMenuSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTouchMenuSubDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_nSpeed = 0;

    m_hParent = NULL;

    m_pImgNormal = NULL;
    m_pImgSel = NULL;
	m_pImgHover = NULL;
    m_pImgSliderBkUp = CUtility::LoadImage( IDR_SLIDER_BK_UP, "PNG" );
    m_pImgSliderBkCenter = CUtility::LoadImage( IDR_SLIDER_BK_CENTER, "PNG" );
    m_pImgSliderBkDown = CUtility::LoadImage( IDR_SLIDER_BK_DOWN, "PNG" );
    m_pImgSliderHilightUp = CUtility::LoadImage( IDR_SLIDER_HILIGHT_UP, "PNG" );
    m_pImgSliderHilightCenter = CUtility::LoadImage( IDR_SLIDER_HILIGHT_CENTER, "PNG" );
    m_pImgSliderHilightDown = CUtility::LoadImage( IDR_SLIDER_HILIGHT_DOWN, "PNG" );

	CString msg;
	msg.Format("\n m_pImgSliderBkUp.heigthed = %d m_pImgSliderBkUp.width = %d \
		      m_pImgSliderBkCenter.heighted = %d  m_pImgSliderBkDown.heighted = %d \
			  m_pImgSliderHilightUp.heithed = %d  m_pImgSliderHilightUp.width = %d \
			  m_pImgSliderHilightCenter.heithed = %d m_pImgSliderHilightDown.heigthed = %d \n",
			  m_pImgSliderBkUp->GetWidth(),m_pImgSliderBkUp->GetHeight(),
			  m_pImgSliderBkCenter->GetHeight(), m_pImgSliderBkDown->GetHeight(),
			  m_pImgSliderHilightUp->GetHeight(),m_pImgSliderHilightUp->GetWidth(),
			  m_pImgSliderHilightCenter->GetHeight(), m_pImgSliderHilightDown->GetHeight() );
	OutputDebugString(msg);
}

CTouchMenuSubDlg::~CTouchMenuSubDlg()
{
    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        delete m_vctItems[nIndex];
    }

    m_vctItems.clear();
    m_vctItemTimer.clear();
}

void CTouchMenuSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTouchMenuSubDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTouchMenuSubDlg, CDialog)
	//{{AFX_MSG_MAP(CTouchMenuSubDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
    ON_MESSAGE( WM_MENU_ITEM_CLICK, OnItemClick )
	ON_MESSAGE( WM_MENU_ITEM_DBCLICK, OnItemDbClick )
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuSubDlg message handlers

BOOL CTouchMenuSubDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CRect cRect;
    GetClientRect( &cRect );
    m_nItemTop = 0;
    m_nItemHeight = 55;
    m_nItemWidth = cRect.Width() - 20;


    SetTimer( 1, 20, NULL );

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CTouchMenuSubDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    m_bMoving = TRUE;
    m_nSpeed = 0;

    m_cPointStart = point;

    SetCapture();

    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        m_vctItems[nIndex]->OnLButtonDown(nFlags, point );
    }

	CDialog::OnLButtonDown(nFlags, point);
}

void CTouchMenuSubDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    m_bMoving = FALSE;

    ReleaseCapture();

    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        m_vctItems[nIndex]->OnLButtonUp(nFlags, point );
    }

    CDialog::OnLButtonUp(nFlags, point);
}

void CTouchMenuSubDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
    if ( m_bMoving == TRUE )
    {
        m_nSpeed = ( point.y - m_cPointStart.y ) / 5;
    }

    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        m_vctItems[nIndex]->OnMouseMove(nFlags, point );
    }

	CDialog::OnMouseMove(nFlags, point);
}

void CTouchMenuSubDlg::OnTimer(UINT nIDEvent) 
{
    CRect cRect, cParentRect;
    GetWindowRect( &cRect );
    GetParent()->GetClientRect( &cParentRect );

    GetParent()->ScreenToClient( &cRect );

    s32 nListHeight = m_vctItems.size() * ( m_nItemHeight + TOUCH_MENU_CTRL_ITEM_SPACE_Y );

    if ( 0 == m_nSpeed )
    {
        // 靠近上部或底部时自动调整到边上
        if ( cRect.top == 0 || cRect.top < 0 && cRect.top > ( m_nItemHeight * (-0.3) ) )
        {
            cRect.top = 0;
            cRect.bottom = cRect.top + nListHeight;

            MoveWindow( &cRect );
        }
        else if ( cRect.bottom > cParentRect.Height() && cRect.bottom < ( cParentRect.Height() + m_nItemHeight * 0.5 ) )
        {
            cRect.top = cParentRect.Height() - nListHeight;
            cRect.bottom = cRect.top + nListHeight;

            MoveWindow( &cRect );
        }

        return;
    }

    cRect.top += m_nSpeed;
    cRect.bottom += m_nSpeed;

    if ( cRect.top < 0 && cRect.top > ( cParentRect.Height() - nListHeight ) )
    {
        m_nSpeed *= 0.96;
    }
    else
    {
        m_nSpeed = 0;

        if ( cRect.top > 0 || cRect.Height() < cParentRect.Height() )
        {
            cRect.top = 0;
        }
        else if ( cRect.top < ( cParentRect.Height() - nListHeight ) )
        {
            cRect.top = cParentRect.Height() - nListHeight;
        }

        cRect.bottom = cRect.top + nListHeight;
    }

    MoveWindow( &cRect );

    GetParent()->SendMessage( WM_MENU_UPDATE_POS,
                              cRect.Height() - cParentRect.Height(),
                              cRect.top < 0 ? -1 * cRect.top : cRect.top );

    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );

	CDialog::OnTimer(nIDEvent);
}

void CTouchMenuSubDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

LRESULT CTouchMenuSubDlg::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    m_hParent = (HWND)lParam;

    if ( NULL == m_pImgSliderBkUp
         || NULL == m_pImgSliderBkCenter
         || NULL == m_pImgSliderBkDown
         || NULL == m_pImgSliderHilightUp
         || NULL == m_pImgSliderHilightCenter
         || NULL == m_pImgSliderHilightDown )
    {
        return S_FALSE;
    }
	
	Graphics *pGraphics = (Graphics*)wParam;
	
	Draw(pGraphics);

    return S_OK;
}

void CTouchMenuSubDlg::Draw(Graphics* pGraphics)
{	
    CRect cRect;
    GetParent()->GetWindowRect( &cRect );
    ::ScreenToClient( m_hParent, (LPPOINT)&cRect );
	::ScreenToClient( m_hParent, ((LPPOINT)&cRect) + 1 );
	
    // 如果项数少则不需要滚动条
    u32 dwListHeight = m_vctItems.size() * ( m_nItemHeight + TOUCH_MENU_CTRL_ITEM_SPACE_Y );
    if ( cRect.Height() == 0 || dwListHeight / cRect.Height() < 1 )
    {
        return;
    }
	
    POINT point;
    point.x = cRect.right - 20;
    point.y = cRect.top;
	
    // 绘制底图
    s32 nPosX = point.x;
    s32 nPosY = point.y + m_pImgSliderBkUp->GetHeight();
    s32 nCenterHeight = cRect.Height() - m_pImgSliderBkUp->GetHeight() - m_pImgSliderBkDown->GetHeight();
    // 上
    pGraphics->DrawImage( m_pImgSliderBkUp, nPosX, point.y, m_pImgSliderBkUp->GetWidth(), m_pImgSliderBkUp->GetHeight() );
    // 下
    pGraphics->DrawImage( m_pImgSliderBkDown, nPosX, cRect.bottom - m_pImgSliderBkDown->GetHeight(), m_pImgSliderBkDown->GetWidth(), m_pImgSliderBkDown->GetHeight() );
	
    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for ( u32 nIndex = 0; nIndex < ( nCenterHeight / m_pImgSliderBkCenter->GetHeight() ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, m_pImgSliderBkCenter->GetWidth(), m_pImgSliderBkCenter->GetHeight() );
        nPosY += m_pImgSliderBkCenter->GetHeight();
    }
    pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, m_pImgSliderBkCenter->GetWidth(), nCenterHeight % m_pImgSliderBkCenter->GetHeight() );
	
    // 绘制高亮的地方
    u32 dwHilightHeight = ( float( cRect.Height() ) ) / dwListHeight * cRect.Height();
    CRect cCtrlRect, cSubDlgRect;
    GetParent()->GetWindowRect( &cCtrlRect );
    GetWindowRect( &cSubDlgRect );
    s32 nHilightPos = cCtrlRect.top - cSubDlgRect.top;
    if ( nHilightPos < 0 ) // 靠顶
    {
        nHilightPos = 0;
    }
    else
    {
        nHilightPos = (float)nHilightPos / dwListHeight * cRect.Height();
    }
	
    nHilightPos += cRect.top;
    // 保证滚动条不出界
    if ( nHilightPos + dwHilightHeight > cRect.bottom )
    {
        nHilightPos = cRect.bottom - dwHilightHeight;
    }
	
    // 上
    pGraphics->DrawImage( m_pImgSliderHilightUp, nPosX, nHilightPos, m_pImgSliderHilightUp->GetWidth(), m_pImgSliderHilightUp->GetHeight() );
    // 下
    pGraphics->DrawImage( m_pImgSliderHilightDown, nPosX, nHilightPos + dwHilightHeight - m_pImgSliderHilightDown->GetHeight(), m_pImgSliderHilightDown->GetWidth(), m_pImgSliderHilightDown->GetHeight() );
	
    nPosY = nHilightPos + m_pImgSliderHilightUp->GetHeight();
    nCenterHeight = dwHilightHeight - m_pImgSliderHilightUp->GetHeight() - m_pImgSliderHilightDown->GetHeight();
    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for ( nIndex = 0; nIndex < ( nCenterHeight / m_pImgSliderHilightCenter->GetHeight() ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgSliderHilightCenter, nPosX, nPosY, m_pImgSliderHilightCenter->GetWidth(), m_pImgSliderHilightCenter->GetHeight() );
        nPosY += m_pImgSliderHilightCenter->GetHeight();
    }
    pGraphics->DrawImage( m_pImgSliderHilightCenter, nPosX, nPosY, m_pImgSliderHilightCenter->GetWidth(), nCenterHeight % m_pImgSliderHilightCenter->GetHeight() );
}

s32 CTouchMenuSubDlg::InserItem()
{
    CTouchMenuItem *pItem = new CDragItem(IDR_TOUCH_LIST_CTRL_ITEM_NORMAL, IDR_TOUCH_LIST_CTRL_ITEM_SEL, IDR_TOUCH_LIST_CTRL_ITEM_SEL);
    pItem->m_nItemIndex = m_vctItems.size();
    pItem->m_pcTouchMenuSubDlg = this;

    CRect cRect;
    GetClientRect( &cRect );

    CRect cItemRect;

    cItemRect.left = cRect.left + 10;
    cItemRect.right = cRect.right - 10;

    int nTopPos = TOUCH_MENU_CTRL_ITEM_SPACE_Y;
    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        nTopPos += m_nItemHeight;
        nTopPos += TOUCH_MENU_CTRL_ITEM_SPACE_Y;
    }

    cItemRect.top = nTopPos;
    cItemRect.bottom = cItemRect.top + m_nItemHeight;


    pItem->m_cClientRect = cItemRect;

    m_vctItems.push_back( pItem );

    pItem->Create( "", WS_CHILD | WS_VISIBLE /*| SS_NOTIFY*/, cItemRect, this );

    return m_vctItems.size() - 1;
}

BOOL32 CTouchMenuSubDlg::SetItemText( s32 nItem, CString strItemText )
{
    if ( nItem >= m_vctItems.size() || nItem < 0 )
    {
        return FALSE;
    }

    m_vctItems[nItem]->m_strItemText = strItemText;

    return TRUE;
}

BOOL32 CTouchMenuSubDlg::SetItemData( s32 nItem, IItem* pItemData )
{
    if ( nItem >= m_vctItems.size() || nItem < 0 )
    {
        return FALSE;
    }

    //m_vctItems[nItem]->m_nItemData = nItemData;
	m_vctItems[nItem]->m_pItemData = pItemData;
    return TRUE;
}

BOOL32 CTouchMenuSubDlg::SetItemType( s32 nItem, CTouchMenuItem::EmItemType emItemType )
{
    if ( nItem >= m_vctItems.size() || nItem < 0 )
    {
        return FALSE;
    }

    m_vctItems[nItem]->m_emItemType = emItemType;

    return TRUE;
}

IItem* CTouchMenuSubDlg::GetItemData( s32 nItem )
{
    if ( nItem >= m_vctItems.size() || nItem < 0 )
    {
        return 0;
    }
	return m_vctItems[nItem]->m_pItemData;
    //return m_vctItems[nItem]->m_nItemData;
}

void CTouchMenuSubDlg::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
    m_bMoving = FALSE;

    ReleaseCapture();
}

LRESULT CTouchMenuSubDlg::OnItemClick( WPARAM wParam, LPARAM lParam )
{
    GetParent()->SendMessage( WM_MENU_ITEM_CLICK, wParam, lParam );

    return S_OK;
}

LRESULT CTouchMenuSubDlg::OnItemDbClick( WPARAM wParam, LPARAM lParam )
{
    GetParent()->SendMessage( WM_MENU_ITEM_DBCLICK, wParam, lParam );
	
    return S_OK;
}

void CTouchMenuSubDlg::UpdatePos( float fPos )
{
    m_bMoving = FALSE;
    m_nSpeed = 0;

    CRect cRect, cParentRect;
    GetWindowRect( &cRect );
    GetParent()->GetClientRect( &cParentRect );

    GetParent()->ScreenToClient( &cRect );

    u32 nOffset = ( cParentRect.Height() - cRect.Height() ) * fPos;

    u32 nHeight = cRect.Height();
    cRect.top = nOffset;
    cRect.bottom = cRect.top + nHeight;

    MoveWindow( &cRect );
}

BOOL32 CTouchMenuSubDlg::DeleteAllItems()
{
    for ( u32 nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        delete m_vctItems[nIndex];
    }
    m_vctItems.clear();

    CRect cRect, cParentRect;
    GetWindowRect( &cRect );
    GetParent()->ScreenToClient( &cRect );

    cRect.top = 0;
    cRect.bottom = cRect.top;

    MoveWindow( &cRect );

    return TRUE;
}

CRect CTouchMenuSubDlg::GetItemRect( s32 nItem )
{
    CRect cRect( 0, 0, 0, 0 );

    if ( nItem >= m_vctItems.size() )
    {
        return CRect( 0, 0, 0, 0 );
    }
    else
    {
        m_vctItems[nItem]->GetWindowRect( &cRect );
    }

    return cRect;
}

void CTouchMenuSubDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        m_vctItems[nIndex]->OnLButtonDblClk( nFlags, point );
    }

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CTouchMenuSubDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    CRect cRect;
    GetClientRect( &cRect );
    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        ::SetWindowPos( m_vctItems[nIndex]->m_hWnd, NULL, 0, 0, cRect.Width() - 20, m_nItemHeight, SWP_NOMOVE );
    }
}

s32 CTouchMenuSubDlg::GetItemCount()
{
	return m_vctItems.size();
}

CTouchMenuItem *CTouchMenuSubDlg::GetMenuItem( s32 nIndex )
{
	return m_vctItems[nIndex];
}

void CTouchMenuSubDlg::SetFont(const u32 dwFontSize, const s8* achFontFamlyName)
{
	vector<CTouchMenuItem*>::iterator itr =  m_vctItems.begin();
	for ( ; itr != m_vctItems.end(); itr++ )
	{
		(*itr)->SetFont( dwFontSize, achFontFamlyName );
	}
}

// ---------------------------------------------------
// muxingmao 
CTouchMenuItem* CTouchMenuSubDlg::HitTest(CPoint point, CRect& rc)
{
	CPoint ptLocal = point;
	ScreenToClient(&ptLocal);
	vector<CTouchMenuItem*>::iterator itr =  m_vctItems.begin();
	for ( ; itr != m_vctItems.end(); itr++ )
	{
		CTouchMenuItem* pItem = *itr;
		if (pItem->HitTest(ptLocal))
		{
			rc = pItem->m_cClientRect;
			ClientToScreen(&rc);
			return pItem;
		}
	}
	return NULL;
}

BOOL32 CTouchMenuSubDlg::DeleteItem(CTouchMenuItem* pItem)
{
	vector<CTouchMenuItem*>::iterator itr =  find(m_vctItems.begin(), m_vctItems.end(), pItem);
	if (itr != m_vctItems.end())
	{
		delete *itr;
		*itr = NULL;
		itr = m_vctItems.erase(itr);

		s32 nOffset = m_nItemHeight + TOUCH_MENU_CTRL_ITEM_SPACE_Y;
		for (; itr != m_vctItems.end(); itr++ )
		{
			CTouchMenuItem* pItem = *itr;
			pItem->m_cClientRect.OffsetRect(0,-nOffset);
			pItem->m_nItemIndex -= 1;
			pItem->MoveWindow(&pItem->m_cClientRect,FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL32 CTouchMenuSubDlg::DeleteItem(u32 nIndex)
{
	if ( nIndex >= m_vctItems.size())
	{
		return FALSE;
	}
	CTouchMenuItem* pItem = m_vctItems[nIndex];
	
	return DeleteItem(pItem);
}

BOOL32 CTouchMenuSubDlg::DeleteItem( CString strName )
{
	vector<CTouchMenuItem*>::iterator itr =  m_vctItems.begin();
	while ( itr != m_vctItems.end() )
	{
		CTouchMenuItem* pItem = *itr;
		if ( strName.CompareNoCase( pItem->GetItemText() ) == 0 )
		{
			return DeleteItem( pItem );
		}
		itr++;
	}
	return FALSE;
}


s32 CTouchMenuSubDlg::InserItem(UINT nImgNormal, UINT nImgSel, UINT nImgHover, UINT nImgStatus /* = 0 */, BOOL bCanDrag /* = TRUE */ )
{
	CDragItem *pItem = new CDragItem(nImgNormal, nImgSel, nImgHover, nImgStatus, bCanDrag);
    pItem->m_nItemIndex = m_vctItems.size();
    pItem->m_pcTouchMenuSubDlg = this;
	
    CRect cRect;
    GetClientRect( &cRect );
	
    CRect cItemRect;
	
    cItemRect.left = cRect.left + 10;
    cItemRect.right = cRect.right - 10;
	
    int nTopPos = TOUCH_MENU_CTRL_ITEM_SPACE_Y;
    for ( int nIndex = 0; nIndex < m_vctItems.size(); nIndex++ )
    {
        nTopPos += m_nItemHeight;
        nTopPos += TOUCH_MENU_CTRL_ITEM_SPACE_Y;
    }
	
    cItemRect.top = nTopPos;
    cItemRect.bottom = cItemRect.top + m_nItemHeight;
	
	
    pItem->m_cClientRect = cItemRect;
	
    m_vctItems.push_back( pItem );
	
    pItem->Create( "", WS_CHILD | WS_VISIBLE /*| SS_NOTIFY*/, cItemRect, this );
	
    return m_vctItems.size() - 1;
}

BOOL32 CTouchMenuSubDlg::IsItemExist(IItem* pItemData, CString strText)
{
	vector<CTouchMenuItem*>::iterator itr =  m_vctItems.begin();
	for ( ; itr != m_vctItems.end(); itr++ )
	{
		CTouchMenuItem* pItem = *itr;
		//if (pItem->m_strItemText.CompareNoCase( strText ) == 0 && pItem->m_nItemData == nItemData)
		if (pItem->m_strItemText.CompareNoCase( strText ) == 0 && pItem->m_pItemData == pItemData)// muxingmao
		{
			return TRUE;
		}
	}
	return FALSE;
}