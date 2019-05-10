#if !defined(AFX_TRANSPARENTBTN_H__F7BB1CC0_42CB_4CB6_A69C_1B9F31CEC366__INCLUDED_)
#define AFX_TRANSPARENTBTN_H__F7BB1CC0_42CB_4CB6_A69C_1B9F31CEC366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentBtn.h : header file
//
#include "Utility.h"
#include "uicommon.h"
/////////////////////////////////////////////////////////////////////////////
// CTransparentBtn window

class CTransparentBtn : public CButton
{
// Construction
public:
	CTransparentBtn();
	void SetTargetHwnd(HWND hwnd){ m_hTargetWnd = hwnd ;}
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparentBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentBtn)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    void    SetImage( UINT dwNormal, UINT dwPress, UINT dwOver, UINT dwDisable )
    {
		m_dwNormalResID = dwNormal;
		m_dwPressResID = dwPress;
		m_dwOverResID = dwOver;
		m_dwDisableResID = dwDisable;

		if ( 0 != m_dwNormalResID )
		{
			m_pImgNormal = CUtility::GetImage( m_dwNormalResID, _T("PNG") );
		}
		if ( 0 != m_dwPressResID )
		{
			m_pImgPress = CUtility::GetImage( m_dwPressResID, _T("PNG") );
		}
		if ( 0 != m_dwOverResID )
		{
			m_pImgOver = CUtility::GetImage( m_dwOverResID, _T("PNG") );
		}
		if ( 0 != m_dwDisableResID )
		{
			m_pImgDisable = CUtility::GetImage( m_dwDisableResID, _T("PNG") );
		}

		if ( NULL != m_hParent )
		{
			::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
		}
    }

    BOOL    EnableWindow(BOOL bEnable = TRUE)
    {
        BOOL bRet = CButton::EnableWindow( bEnable );

		if( bEnable )
		{
			m_emStatus = emStatusNormal;
		}
		else
		{
			m_emStatus = emStatusBtnDisable;
		}
        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

    void    ShowText( BOOL32 bShow )
    {
        m_bShowText = bShow;
    }

    enum EmTextAlignment
    {
        emAlignmentLeft = 0,
        emAlignmentCenter,
        emAlignmentRight,
        emAlignmentUserDef,
    };

    void    SetTextAlign( EmTextAlignment emTextAlign )
    {
        m_emTextAlign = emTextAlign;

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void    SetTextPoint( CPoint &cPoint )
    {
        m_emTextAlign = emAlignmentUserDef;
        m_cPoint = cPoint;

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE )
    {
        CButton::MoveWindow( x, y, nWidth, nHeight, bRepaint );

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE)
    {
        CButton::MoveWindow( lpRect, bRepaint );

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void SetFont( const u32 dwFontSize = 18 , const s8* achFontFamlyName = ("Arial") )
    {
        m_dwFontSize = dwFontSize;
        
        if ( achFontFamlyName == NULL )
        {
            return;
        }
        ZeroMemory( m_awszFontName, sizeof(m_awszFontName) );
        MultiByteToWideChar(CP_ACP, 0, achFontFamlyName, -1, m_awszFontName, strlen(achFontFamlyName) );
	}

	void SetOffset( u16 wOffset ){ m_wOffset = wOffset; }

	void BtnPressed( BOOL bIsPressed ){ m_bPressed = bIsPressed; }
	void SetTextColor( Color colorNormal, Color colorPress, Color colorHover, Color colorDisable );

public:
    BOOL32  m_bScale;
	BOOL32  m_bAjustSize;
protected:
    UINT    m_dwNormalResID;
    UINT    m_dwPressResID;
	UINT    m_dwOverResID;
    UINT    m_dwDisableResID;

    Image   *m_pImgNormal;
    Image   *m_pImgPress;
	Image   *m_pImgOver;
    Image   *m_pImgDisable;

    HWND    m_hParent;

	HWND	m_hTargetWnd;
    enum EmStatus
    {
        emStatusNormal = 0,
		emStatusBtnDown,
		emStatusOver,
		emStatusBtnDisable,
    };
    EmStatus    m_emStatus;

    BOOL32  m_bShowText;

    EmTextAlignment m_emTextAlign;
    CPoint  m_cPoint;

    WCHAR	m_awszFontName[64];
	u32		m_dwFontSize;
	
	u16		m_wOffset;

	BOOL    m_bPressed;

	Color   m_cColor[4];//ÎÄ×ÖÑÕÉ«
private:
	bool m_bButtonDown;
	bool m_bTracking;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBTN_H__F7BB1CC0_42CB_4CB6_A69C_1B9F31CEC366__INCLUDED_)
