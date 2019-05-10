#if !defined(AFX_TOUCHMENUCTRL1_H__C162F46A_80FB_4943_93DA_F5FA32E165C3__INCLUDED_)
#define AFX_TOUCHMENUCTRL1_H__C162F46A_80FB_4943_93DA_F5FA32E165C3__INCLUDED_

#include "TouchMenuSubDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TouchMenuCtrl1.h : header file
//

// #define WM_MENU_ITEM_CLICK  ( WM_USER + 0x100 )
// #define WM_MENU_UPDATE_POS  ( WM_USER + 0x101 )
// #define WM_MENU_ITEM_CANCLE  ( WM_USER + 0x102 )

#include "PopupMenu.h"

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuCtrl dialog 

class CTouchMenuCtrl : public CDialog
{
// Construction
public:
	CTouchMenuCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTouchMenuCtrl)
	enum { IDD = IDD_TOUCH_MENU_CTRL };
	CScrollBar	m_cScrollBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTouchMenuCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTouchMenuCtrl)
    virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    afx_msg LRESULT OnItemClick( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnUpdatePos( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnHideWndCmd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnItemDbClick( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public: 
	// -------------------------------------------------
	// muxingmao
	BOOL32				m_bCanShow;
	BOOL32	DeleteItem( u32 nIndex );
	BOOL32	DeleteItem( CString strName );
	s32     InserItem(UINT nImgNormal, UINT nImgSel, UINT nImgHover, UINT nImgStatus = 0, BOOL bCanDrag = TRUE );
	//BOOL32 IsItemExist(s32 nItemData, CString strText);
	BOOL32	IsItemExist(IItem *pItemData, CString strText);
	// -------------------------------------------------
	//BOOL32 GetItem( u32 nIndex, TAddrItem& tAddrItem );
	void	SetCurSel( s32 nSelItem );
    s32     InserItem();
	
    BOOL32  DeleteAllItems();
   
    BOOL32  SetItemText( s32 nItem, CString strItemText );
    //BOOL32  SetItemData( s32 nItem, s32 nItemData );		
    BOOL32	SetItemData( s32 nItem, IItem* pItemData );	
	BOOL32  SetItemType( s32 nItem, CTouchMenuItem::EmItemType emItemType );

    s32     GetCurSel();
   // s32     GetItemData( s32 nItem );
	IItem*	GetItemData( s32 nItem );
	s32		GetItemCount();
	CTouchMenuItem *GetMenuItem( s32 nIndex );

    void    HidePopupMenu();

    void    SetShowPopupMenu( BOOL32 bShowPopupMenu )
    {
        m_bShowPopupMenu = bShowPopupMenu;
    }

    void    SetImage( UINT dwNormal, UINT dwSelect,UINT dwHover = IDR_DRAG_ITEM_HOVER)
    {
        m_dwNormalResID = dwNormal;
        m_dwSelResID = dwSelect;
		m_dwHoverResID = dwHover;

       /* if ( NULL != m_pImgNormal )
        {
            delete m_pImgNormal;
        }
        if ( NULL != m_pImgSel )
        {
            delete m_pImgSel;
        }
		if ( NULL != m_pImgHover ) 
		{
			delete m_pImgHover;
		}*/

        if ( 0 != m_dwNormalResID )
        {
            m_pImgNormal = CUtility::GetImage( m_dwNormalResID, "PNG" );
        }
        if ( 0 != m_dwSelResID )
        {
            m_pImgSel = CUtility::GetImage( m_dwSelResID, "PNG" );
        }
		if ( 0 != m_dwHoverResID ) 
		{
			m_pImgHover = CUtility::GetImage( m_dwHoverResID, "PNG" );
		}

        m_pcTouchMenuSubDlg->SetImage( m_pImgNormal, m_pImgSel, m_pImgHover );

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }
	
	void SetFont( const u32 dwFontSize = 20 , const s8* achFontFamlyName = ("Arial") );
protected:
	CTouchMenuSubDlg    *m_pcTouchMenuSubDlg;

    CPopupMenu          m_cPopupMenu;
    
    BOOL32              m_bShowPopupMenu;
	
    s32                 m_nCurSelItem;

    HWND    m_hParent;

    UINT    m_dwNormalResID;
    UINT    m_dwSelResID;
	UINT	m_dwHoverResID;

    Image   *m_pImgNormal;
    Image   *m_pImgSel;
	Image	*m_pImgHover;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOUCHMENUCTRL1_H__C162F46A_80FB_4943_93DA_F5FA32E165C3__INCLUDED_)
