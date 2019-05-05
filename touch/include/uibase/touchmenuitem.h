// TouchMenuItem.h: interface for the CTouchMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHMENUITEM_H__1D9A65DB_47EA_4D93_96CC_D481D5E223F1__INCLUDED_)
#define AFX_TOUCHMENUITEM_H__1D9A65DB_47EA_4D93_96CC_D481D5E223F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTouchMenuSubDlg;

class CTouchMenuItem : public CStatic
{
public:
    enum EmItemType
    {
        emItemTypeAddrInfo = 0,
        emItemtypeAddrList,
		emItemTypeCallRate,
    };

	enum EmItemHitStatus
    {
        emItemHitStatusNormal = 0,
			emItemHitStatusLBtnDown,
			emItemHitStatusLBtnUp,
			emItemHitStatusSel,
			emItemHitStatusHover,
    };
    // Construction
public:
    CTouchMenuItem();

    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTouchMenuItem)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTouchMenuItem();
	CString GetItemText(){ return m_strItemText; }
//	int GetItemData(){ return m_nItemData; }
	IItem*	GetItemData() { return m_pItemData; }
	//-----------------------------------
	// muxingmao
    BOOL32 HitTest(CPoint point){ return m_cClientRect.PtInRect(point); }
	void SetItemHitStauts( EmItemHitStatus emItemHitStatus, BOOL32 bInvalidate = TRUE );
	EmItemHitStatus GetItemHitStatus(){ return m_emItemHitStatus; }
    // Generated message map functions
protected:
    //{{AFX_MSG(CTouchMenuItem)
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

public:
    //void RedrawUI( Graphics *pGraphics, HWND hParent );

	void SetFont( const u32 dwFontSize = 20 , const s8* achFontFamlyName = ("Arial") )
	{
		m_dwFontSize = dwFontSize;
		
		if ( achFontFamlyName == NULL )
		{
			return;
		}
		ZeroMemory( m_awszFontName, sizeof(m_awszFontName) );
		MultiByteToWideChar(CP_ACP, 0, achFontFamlyName, -1, m_awszFontName, strlen(achFontFamlyName) );
	}
	virtual BOOL32	SetStatusImage( UINT nImageID, BOOL32 bInvalidate = FALSE ){ return FALSE; }
	virtual u32		GetStatusImageId(){ return m_dwStatusImageId; }
protected:
    virtual BOOL OnMouseMove(UINT nFlags, CPoint point );
    virtual BOOL OnLButtonDown(UINT nFlags, CPoint point );
    virtual BOOL OnLButtonUp(UINT nFlags, CPoint point );
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void Draw(Graphics* pGraphics);

    //virtual BOOL OnPaint( CDC *pDC );
    
    //virtual BOOL OnTimer();
    
    virtual BOOL OnBtnClick();
    
protected:
	u32		m_dwStatusImageId;
    CTouchMenuSubDlg* m_pcTouchMenuSubDlg;
    
    CRect   m_cClientRect;

	EmItemHitStatus m_emItemHitStatus;

	HWND    m_hParent;

    int     m_nItemIndex;
   
	//int     m_nItemData;
	IItem*	m_pItemData;

    CString m_strItemText;
    
    BOOL    m_bSetTimer;
    
    

    EmItemType m_emItemType;

    int     m_nDrawFrame;
    
    

	WCHAR	m_awszFontName[64];
	u32		m_dwFontSize;

    friend class CTouchMenuSubDlg;
	friend class CTouchMenuCtrl;
	friend class CDragList;
};

#endif // !defined(AFX_TOUCHMENUITEM_H__1D9A65DB_47EA_4D93_96CC_D481D5E223F1__INCLUDED_)
