// TouchMenuCtrl1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TouchMenuCtrl.h"
#include "PopupMenu.h"
#include "touchpcmt.h"

#include "draglist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuCtrl dialog

extern CTouchPcmtApp theApp;

CTouchMenuCtrl::CTouchMenuCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CTouchMenuCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTouchMenuCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_bShowPopupMenu = FALSE;

	m_bCanShow = TRUE;

    m_nCurSelItem = -1;

    m_dwNormalResID = 0;
    m_dwSelResID = 0;

    m_pImgNormal = NULL;
    m_pImgSel = NULL;
	m_pImgHover = NULL;

    m_hParent = NULL;

	m_pcTouchMenuSubDlg = NULL;
}


void CTouchMenuCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTouchMenuCtrl)
	DDX_Control(pDX, IDC_TOUCH_MENU_SCROLLBAR, m_cScrollBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTouchMenuCtrl, CDialog)
	//{{AFX_MSG_MAP(CTouchMenuCtrl)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_MENU_ITEM_CLICK, OnItemClick )
    ON_MESSAGE( WM_MENU_UPDATE_POS, OnUpdatePos )
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
	ON_MESSAGE( WM_HIDE_WND_CMD, OnHideWndCmd )
	ON_MESSAGE( WM_MENU_ITEM_DBCLICK, OnItemDbClick )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuCtrl message handlers

BOOL CTouchMenuCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect cRect;
    GetClientRect( &cRect );

    CRect cMenuRect, cScrollBarRect;
    cMenuRect = cRect;
    cScrollBarRect = cRect;

    cMenuRect.bottom = cRect.top + 1000;//1000+ 50 
    //cMenuRect.right  = cRect.right - 100;
	//CTouchMenuSubDlg* pCtrl = new CTouchMenuSubDlg( this );
//	pCtrl->Create(CTouchMenuSubDlg::IDD, this);

	m_pcTouchMenuSubDlg = new CTouchMenuSubDlg( this );
    m_pcTouchMenuSubDlg->Create( CTouchMenuSubDlg::IDD, this );
    m_pcTouchMenuSubDlg->MoveWindow( &cMenuRect );
    m_pcTouchMenuSubDlg->ShowWindow( SW_SHOW );

	SetImage( IDR_TOUCH_LIST_CTRL_ITEM_NORMAL, IDR_TOUCH_LIST_CTRL_ITEM_SEL );

    cScrollBarRect.left = cRect.right - 10;
    cScrollBarRect.right = cRect.right - 10;
    m_cScrollBar.MoveWindow( &cScrollBarRect );

    m_cScrollBar.SetScrollRange( 0, 0 );


//	CDragWindow* pDragWindow = CDragWindow::GetDragWindow();
//	pDragWindow->RegisterDropWindow( this );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CTouchMenuCtrl::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    m_hParent = (HWND)wParam;

    return S_OK;
}

s32 CTouchMenuCtrl::InserItem()
{
    s32 nMinPos = 0, nMaxPos = 0;
    m_cScrollBar.GetScrollRange( &nMinPos, &nMaxPos );
    nMaxPos++;
    m_cScrollBar.SetScrollRange( 0, nMaxPos );

    return m_pcTouchMenuSubDlg->InserItem();    
}

s32 CTouchMenuCtrl::InserItem(UINT nImgNormal, UINT nImgSel, UINT nImgHover, UINT nImgStatus, BOOL bCanDrag )
{
    s32 nMinPos = 0, nMaxPos = 0;
    m_cScrollBar.GetScrollRange( &nMinPos, &nMaxPos );
    nMaxPos++;
    m_cScrollBar.SetScrollRange( 0, nMaxPos );
	
    return m_pcTouchMenuSubDlg->InserItem(nImgNormal, nImgSel, nImgHover, nImgStatus, bCanDrag);
}


LRESULT CTouchMenuCtrl::OnItemClick( WPARAM wParam, LPARAM lParam )
{
	GetParent()->SendMessage( WM_MENU_ITEM_CLICK, wParam, lParam );
	
	CTouchMenuItem* pItem = (CTouchMenuItem*)wParam;

	m_nCurSelItem = pItem->m_nItemIndex;
	
    if ( FALSE == m_bShowPopupMenu )
    {
        return S_OK;
    }

	CRect cRect;

	pItem->GetWindowRect( &cRect );	
	
    m_cPopupMenu.SetWindowPos( CPoint( cRect.right + 28, cRect.top ) );
	
    m_cPopupMenu.SetItem( pItem->GetItemData() );
	
	m_nCurSelItem = pItem->m_nItemIndex;


    return S_OK;
}

LRESULT CTouchMenuCtrl::OnItemDbClick(WPARAM wParam, LPARAM lParam)
{
	GetParent()->SendMessage( WM_MENU_ITEM_DBCLICK, wParam, lParam );
	
	CTouchMenuItem* pItem = (CTouchMenuItem*)wParam;

	//	m_nCurSelItem = pItem->m_nItemIndex;

	if ( FALSE == m_bCanShow )
    {
        return S_OK;
    }
	
 
   // CRect cRect = m_pcTouchMenuSubDlg->GetItemRect( m_nCurSelItem );
	CRect cRect;
	pItem->GetWindowRect( &cRect );	

    m_cPopupMenu.SetWindowPos( CPoint( cRect.right + 28, cRect.top ) );

    m_cPopupMenu.SetItem( pItem->GetItemData() );

	m_nCurSelItem = pItem->m_nItemIndex;

	m_bShowPopupMenu = TRUE;

	
    /*m_nCurSelItem = wParam >> 20;
	
    if ( FALSE == m_bShowPopupMenu )
    {
        return S_OK;
    }
	
    if ( lParam == CTouchMenuItem::emItemtypeAddrList )
    {
        s32 nItemData = wParam & 0xFFFFF;
        CRect cRect = m_pcTouchMenuSubDlg->GetItemRect( m_nCurSelItem );
		
        m_cPopupMenu.SetWindowPos( CPoint( cRect.right + 28, cRect.top ) );
        m_cPopupMenu.ShowGroupList( nItemData );
    }
    else if ( lParam == CTouchMenuItem::emItemTypeAddrInfo )
    {
        s32 nItemData = wParam & 0xFFFFF;
        CRect cRect = m_pcTouchMenuSubDlg->GetItemRect( m_nCurSelItem );
		
        m_cPopupMenu.SetWindowPos( CPoint( cRect.right + 28, cRect.top ) );
        m_cPopupMenu.ShowItemInfo( nItemData );
    }
	else if ( lParam == CTouchMenuItem::emItemTypeCallRate )
	{
		s32 nItemData = wParam & 0xFFFFF;
	}*/

	return S_OK;
}

LRESULT CTouchMenuCtrl::OnUpdatePos( WPARAM wParam, LPARAM lParam )
{
    s32 nMinPos = 0, nMaxPos = 0;
    m_cScrollBar.GetScrollRange( &nMinPos, &nMaxPos );

    m_cScrollBar.SetScrollPos( ( (double)lParam / wParam ) * ( nMaxPos - nMinPos ) );

    return S_OK;
}

void CTouchMenuCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if ( SB_THUMBPOSITION == nSBCode || SB_THUMBTRACK == nSBCode )
    {
        s32 nMinPos = 0, nMaxPos = 0;
        m_cScrollBar.GetScrollRange( &nMinPos, &nMaxPos );

        float fPos = (float)nPos / nMaxPos;

        m_cScrollBar.SetScrollPos( nPos );
        m_pcTouchMenuSubDlg->UpdatePos( fPos );
    }

    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL32 CTouchMenuCtrl::SetItemText( s32 nItem, CString strItemText )
{
    return m_pcTouchMenuSubDlg->SetItemText( nItem, strItemText );
}

BOOL32 CTouchMenuCtrl::SetItemData( s32 nItem, IItem* pItemData )
{
    return m_pcTouchMenuSubDlg->SetItemData( nItem, pItemData );
}

BOOL32 CTouchMenuCtrl::SetItemType( s32 nItem, CTouchMenuItem::EmItemType emItemType )
{
    return m_pcTouchMenuSubDlg->SetItemType( nItem, emItemType );
}

s32 CTouchMenuCtrl::GetCurSel()
{
    return m_nCurSelItem;
}

IItem* CTouchMenuCtrl::GetItemData( s32 nItem )
{
    return m_pcTouchMenuSubDlg->GetItemData( nItem );
}

BOOL32 CTouchMenuCtrl::DeleteAllItems()
{
    return m_pcTouchMenuSubDlg->DeleteAllItems();
}

void CTouchMenuCtrl::HidePopupMenu()
{
    m_cPopupMenu.HidePopupMenu();  
	m_bShowPopupMenu = FALSE;
}

void CTouchMenuCtrl::SetCurSel(s32 nSelItem)
{
	m_nCurSelItem = nSelItem;
}
/*
//主要用来解析click传上来的wparam参数
BOOL32 CTouchMenuCtrl::GetItem(u32 nIndex, TAddrItem &tAddrItem)
{
	nIndex = nIndex &0xfffff;
	u32 dwGrpId = nIndex >> 12;
	u32 dwItemId = nIndex & 0xfff;
	
	CAddrManager &cAddrbook = theApp.m_cAddrbook;
	
	CAddrGroup cAddrGrp;
	if ( FALSE == cAddrbook.GetGroup( dwGrpId, cAddrGrp ) )
	{
		return FALSE;
	}
	
	if ( FALSE == cAddrGrp.GetItem( dwItemId, tAddrItem ) )
	{
        return FALSE;
	}
	
	return TRUE;
}
*/
void CTouchMenuCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

    if ( m_pcTouchMenuSubDlg != NULL && m_pcTouchMenuSubDlg->GetSafeHwnd() != NULL )
    {
        CRect cRect;
        GetClientRect( &cRect );

        CRect cMenuRect;
        cMenuRect = cRect;

        cMenuRect.bottom = cRect.top + 1000;
        //cMenuRect.right  = cRect.right - 10;

        m_pcTouchMenuSubDlg->MoveWindow( &cMenuRect );
    }

}

LRESULT CTouchMenuCtrl::OnHideWndCmd(WPARAM wParam, LPARAM lParam)
{
	m_cPopupMenu.OnHidePopMenu();
	m_bShowPopupMenu = FALSE;
	return S_OK;
}

s32 CTouchMenuCtrl::GetItemCount()
{
	return m_pcTouchMenuSubDlg->GetItemCount();
}

CTouchMenuItem *CTouchMenuCtrl::GetMenuItem( s32 nIndex )
{
	return m_pcTouchMenuSubDlg->GetMenuItem(nIndex);
}

void CTouchMenuCtrl::SetFont(const u32 dwFontSize, const s8* achFontFamlyName )
{
	m_pcTouchMenuSubDlg->SetFont( dwFontSize, achFontFamlyName );
}


// --------------------------------------------------------
// muxingmao
BOOL32 CTouchMenuCtrl::DeleteItem(u32 nIndex)
{
	return m_pcTouchMenuSubDlg->DeleteItem(nIndex);
}

BOOL32 CTouchMenuCtrl::DeleteItem( CString strName )
{
	return m_pcTouchMenuSubDlg->DeleteItem( strName );
}

BOOL32 CTouchMenuCtrl::IsItemExist(IItem *pItemData, CString strText)
{
	return m_pcTouchMenuSubDlg->IsItemExist( pItemData, strText );
}
// --------------------------------------------------------