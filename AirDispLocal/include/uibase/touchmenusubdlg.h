#if !defined(AFX_TOUCHMENUSUBDLG_H__F857490F_90B6_4DDB_AEA4_FBC24176564C__INCLUDED_)
#define AFX_TOUCHMENUSUBDLG_H__F857490F_90B6_4DDB_AEA4_FBC24176564C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TouchMenuSubDlg.h : header file
//

#include "TouchMenuItem.h"

/////////////////////////////////////////////////////////////////////////////
// CTouchMenuSubDlg dialog

class CTouchMenuSubDlg : public CDialog
{
// Construction
public:
	CTouchMenuSubDlg(CWnd* pParent = NULL);   // standard constructor
    ~CTouchMenuSubDlg();

// Dialog Data
	//{{AFX_DATA(CTouchMenuSubDlg)
	enum { IDD = IDD_TOUCH_MENU_SUB_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTouchMenuSubDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTouchMenuSubDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    afx_msg LRESULT OnItemClick( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnItemDbClick( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()
	virtual void Draw(Graphics* pGraphics);
public:
	// muxingmao
	CTouchMenuItem*	HitTest(CPoint point, CRect& rc);
	BOOL32 DeleteItem(CTouchMenuItem* pItem);
	BOOL32 DeleteItem(u32 nIndex);
	BOOL32 DeleteItem( CString strName );
//	BOOL32 IsItemExist(s32 nItemData, CString strText);
	BOOL32 IsItemExist(IItem* pItemData, CString strText);
	// 目前只支持插入到最后
    s32     InserItem();
	s32		InserItem(UINT nImgNormal, UINT nImgSel, UINT nImgHover, UINT nImgStatus = 0, BOOL bCanDrag = TRUE );

    BOOL32  DeleteAllItems();

    BOOL32  SetItemText( s32 nItem, CString strItemText );
  
	//BOOL32  SetItemData( s32 nItem, s32 nItemData );		//item data 的低12位代表条目id，次8位代表组id，如果条目为组则只有高16位有效，最高12位无效
   BOOL32  SetItemData( s32 nItem, IItem *pItemData ); // muxingmao

	BOOL32  SetItemType( s32 nItem, CTouchMenuItem::EmItemType emItemType );

	IItem*	GetItemData( s32 nItem );
    //s32     GetItemData( s32 nItem );
	s32		GetItemCount();
	CTouchMenuItem	*GetMenuItem( s32 nIndex );
	
    void    UpdatePos( float fPos );

    CRect   GetItemRect( s32 nItem );

    void    SetImage( Image *pNormal, Image *pSel, Image *pHover )
    {
        m_pImgNormal = pNormal;
        m_pImgSel = pSel;
       	m_pImgHover = pHover;
    }
	
	void SetFont( const u32 dwFontSize = 20 , const s8* achFontFamlyName = ("Arial") );

protected:
    BOOL    m_bMoving;
    int     m_nSpeed;

    CPoint  m_cPointStart;

    vector<CTouchMenuItem*> m_vctItems;
    vector<CTouchMenuItem*> m_vctItemTimer;

    int     m_nItemTop;
    int     m_nItemHeight;
    int     m_nItemWidth;

    HWND    m_hParent;

    Image   *m_pImgNormal;
    Image   *m_pImgSel;
	Image	*m_pImgHover;

    Image   *m_pImgSliderBkUp;
    Image   *m_pImgSliderBkCenter;
    Image   *m_pImgSliderBkDown;
    Image   *m_pImgSliderHilightUp;
    Image   *m_pImgSliderHilightCenter;
    Image   *m_pImgSliderHilightDown;

    friend class CTouchMenuItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOUCHMENUSUBDLG_H__F857490F_90B6_4DDB_AEA4_FBC24176564C__INCLUDED_)
