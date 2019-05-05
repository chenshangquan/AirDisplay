#if !defined(AFX_TRANSPARENTEDIT_H__5DA170FD_67DD_449A_A4D4_FBD8A7DE22DF__INCLUDED_)
#define AFX_TRANSPARENTEDIT_H__5DA170FD_67DD_449A_A4D4_FBD8A7DE22DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Utility.h"
#include "uicommon.h"
// TransparentEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentEdit window

class CTransparentEdit : public CEdit
{
// Construction
public:
    CTransparentEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CTransparentEdit();

    // Generated message map functions
protected:
	//{{AFX_MSG(CTransparentEdit)
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnChange();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

public:
    void    SetImage( UINT dwNormalLeft, UINT dwNormalMiddle, UINT dwNormalRight,
                      UINT dwFocusLeft, UINT dwFocusMiddle, UINT dwFocusRight )
    {
        m_dwNormalLeft = dwNormalLeft;
        m_dwNormalMiddle = dwNormalMiddle;
        m_dwNormalRight = dwNormalRight;

        m_dwFocusLeft = dwFocusLeft;
        m_dwFocusMiddle = dwFocusMiddle;
        m_dwFocusRight = dwFocusRight;

        /*if ( NULL != m_pImgNormalLeft )
        {
            delete m_pImgNormalLeft;
        }
        if ( NULL != m_pImgNormalMiddle )
        {
            delete m_pImgNormalMiddle;
        }
        if ( NULL != m_pImgNormalRight )
        {
            delete m_pImgNormalRight;
        }
        if ( NULL != m_pImgFocusLeft )
        {
            delete m_pImgFocusLeft;
        }
        if ( NULL != m_pImgFocusMiddle )
        {
            delete m_pImgFocusMiddle;
        }
        if ( NULL != m_pImgFocusRight )
        {
            delete m_pImgFocusRight;
        }
*/
        if ( 0 != m_dwNormalLeft )
        {
            m_pImgNormalLeft = CUtility::GetImage( m_dwNormalLeft, _T("PNG") );
        }
        if ( 0 != m_dwNormalMiddle )
        {
            m_pImgNormalMiddle = CUtility::GetImage( m_dwNormalMiddle, _T("PNG") );
        }
        if ( 0 != m_dwNormalRight )
        {
            m_pImgNormalRight = CUtility::GetImage( m_dwNormalRight, _T("PNG") );
        }
        if ( 0 != m_dwFocusLeft )
        {
            m_pImgFocusLeft = CUtility::GetImage( m_dwFocusLeft, _T("PNG") );
        }
        if ( 0 != m_dwFocusMiddle )
        {
            m_pImgFocusMiddle = CUtility::GetImage( m_dwFocusMiddle, _T("PNG") );
        }
        if ( 0 != m_dwFocusRight )
        {
            m_pImgFocusRight = CUtility::GetImage( m_dwFocusRight, _T("PNG") );
        }

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void    SetIconImage( UINT dwIcon )
    {
        m_dwIcon = dwIcon;

       /* if ( NULL != m_pImgIcon )
        {
            delete m_pImgIcon;
        }*/

        if ( 0 != m_dwIcon )
        {
            m_pImgIcon = CUtility::GetImage( m_dwIcon, _T("PNG") );
        }

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
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

    void    SetTextColor( Color colorNormal, Color colorFocus )
    {
        m_cNormalColor = colorNormal;
        m_cFocusColor = colorFocus;
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

    void SetTipStr( CString strTip ){ m_strTip = strTip; }
    CString GetTipStr(){ return m_strTip; }

protected:
    HWND    m_hParent;

    BOOL32  m_bShowCursor;

    enum EmStatus
    {
        emStatusNormal = 0,
        emStatusSetFocus,
    };
    EmStatus    m_emStatus;

    EmTextAlignment m_emTextAlign;

    UINT    m_dwNormalLeft;
    UINT    m_dwNormalMiddle;
    UINT    m_dwNormalRight;

    UINT    m_dwFocusLeft;
    UINT    m_dwFocusMiddle;
    UINT    m_dwFocusRight;

    UINT    m_dwIcon;

    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;

    Image   *m_pImgFocusLeft;
    Image   *m_pImgFocusMiddle;
    Image   *m_pImgFocusRight;

    Image   *m_pImgIcon;

    Color   m_cNormalColor;
    Color   m_cFocusColor;

    WCHAR   m_awszFontName[64];
    u32     m_dwFontSize;

    CString m_strTip;
    BOOL32  m_bFocus;
public:
    CString GetShowText();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic window

class CTransparentStatic : public CStatic
{
    // Construction
public:
    CTransparentStatic();
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentStatic)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentStatic();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentStatic)
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    
    DECLARE_MESSAGE_MAP()

public:
    void SetImage( UINT dwImageID )
    {
        m_dwBkResID = dwImageID;

        /*if ( NULL != m_pImgBk )
        {
            delete m_pImgBk;
        }*/

        if ( 0 != m_dwBkResID )
        {
            m_pImgBk = CUtility::GetImage( m_dwBkResID, _T("PNG") );
        }

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void SetWindowText( CString strWindowText)
    {
        CStatic::SetWindowText( strWindowText );

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

    void    SetTextColor( Color colorNormal )
    {
        m_cNormalColor = colorNormal;
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

	void SetOverShow(bool bOverShow, StringTrimming stOverShowType)//设置文字超出时如何显示
	{
		m_bOverShow = bOverShow;
		m_stOverShowType = stOverShowType;
	}

protected:
    HWND    m_hParent;

    UINT    m_dwBkResID;

    Image   *m_pImgBk;


	WCHAR	m_awszFontName[64];
	u32		m_dwFontSize;
	Color   m_cNormalColor;

	StringTrimming m_stOverShowType;
	bool m_bOverShow;
public:
	EmTextAlignment m_emTextAlign;
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CTransparentIPAddrCtrl window

class CTransparentIPAddrCtrl : public CIPAddressCtrl
{
    // Construction
public:
    CTransparentIPAddrCtrl();
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentIPAddrCtrl)
    protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentIPAddrCtrl();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentIPAddrCtrl)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnParentNotify(UINT message, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

public:
    void    SetImage( UINT dwNormalLeft, UINT dwNormalMiddle, UINT dwNormalRight,
                      UINT dwFocusLeft, UINT dwFocusMiddle, UINT dwFocusRight )
    {
        m_dwNormalLeft = dwNormalLeft;
        m_dwNormalMiddle = dwNormalMiddle;
        m_dwNormalRight = dwNormalRight;
        
        m_dwFocusLeft = dwFocusLeft;
        m_dwFocusMiddle = dwFocusMiddle;
        m_dwFocusRight = dwFocusRight;
        
        /*if ( NULL != m_pImgNormalLeft )
        {
            delete m_pImgNormalLeft;
        }
        if ( NULL != m_pImgNormalMiddle )
        {
            delete m_pImgNormalMiddle;
        }
        if ( NULL != m_pImgNormalRight )
        {
            delete m_pImgNormalRight;
        }
        if ( NULL != m_pImgFocusLeft )
        {
            delete m_pImgFocusLeft;
        }
        if ( NULL != m_pImgFocusMiddle )
        {
            delete m_pImgFocusMiddle;
        }
        if ( NULL != m_pImgFocusRight )
        {
            delete m_pImgFocusRight;
        }*/
        
        if ( 0 != m_dwNormalLeft )
        {
            m_pImgNormalLeft = CUtility::GetImage( m_dwNormalLeft, _T("PNG") );
        }
        if ( 0 != m_dwNormalMiddle )
        {
            m_pImgNormalMiddle = CUtility::GetImage( m_dwNormalMiddle, _T("PNG") );
        }
        if ( 0 != m_dwNormalRight )
        {
            m_pImgNormalRight = CUtility::GetImage( m_dwNormalRight, _T("PNG") );
        }
        if ( 0 != m_dwFocusLeft )
        {
            m_pImgFocusLeft = CUtility::GetImage( m_dwFocusLeft, _T("PNG") );
        }
        if ( 0 != m_dwFocusMiddle )
        {
            m_pImgFocusMiddle = CUtility::GetImage( m_dwFocusMiddle, _T("PNG") );
        }
        if ( 0 != m_dwFocusRight )
        {
            m_pImgFocusRight = CUtility::GetImage( m_dwFocusRight, _T("PNG") );
        }
        
        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

	void SetFont( const u32 dwFontSize = 14 , const s8* achFontFamlyName = ("Arial") )
	{
		m_dwFontSize = dwFontSize;
		
		if ( achFontFamlyName == NULL )
		{
			return;
		}
		ZeroMemory( m_awszFontName, sizeof(m_awszFontName) );
		MultiByteToWideChar(CP_ACP, 0, achFontFamlyName, -1, m_awszFontName, strlen(achFontFamlyName) );
	}

    void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);

protected:
    HWND    m_hParent;
    HWND    m_hChild1;
    HWND    m_hChild2;
    HWND    m_hChild3;
    HWND    m_hChild4;
    HWND    m_hFocusWnd;
    
    BOOL32  m_bShowCursor;
    BOOL32  m_bShowCursorInChild1;
    BOOL32  m_bShowCursorInChild2;
    BOOL32  m_bShowCursorInChild3;
    BOOL32  m_bShowCursorInChild4;

    enum EmStatus
    {
        emStatusNormal = 0,
        emStatusSetFocus,
    };
    EmStatus    m_emStatus;

    UINT    m_dwNormalLeft;
    UINT    m_dwNormalMiddle;
    UINT    m_dwNormalRight;

    UINT    m_dwFocusLeft;
    UINT    m_dwFocusMiddle;
    UINT    m_dwFocusRight;

    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;

    Image   *m_pImgFocusLeft;
    Image   *m_pImgFocusMiddle;
    Image   *m_pImgFocusRight;

    Color   m_cNormalColor;
    Color   m_cFocusColor;

	WCHAR	m_awszFontName[64];
	u32		m_dwFontSize;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTransparentSliderCtrl window

class CTransparentSliderCtrl : public CSliderCtrl
{
    // Construction
public:
    CTransparentSliderCtrl();
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentSliderCtrl)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentSliderCtrl();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentSliderCtrl)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()


public:
    void    SetImage( UINT dwNormalLeft, UINT dwNormalMiddle, UINT dwNormalRight,
                      UINT dwHighLightLeft, UINT dwHighLightMiddle, UINT dwHighLightRight,
                      UINT dwThumbNormal, UINT dwThumbPress )
    {
        m_dwNormalLeft = dwNormalLeft;
        m_dwNormalMiddle = dwNormalMiddle;
        m_dwNormalRight = dwNormalRight;

        m_dwHighLightLeft = dwHighLightLeft;
        m_dwHighLightMiddle = dwHighLightMiddle;
        m_dwHighLightRight = dwHighLightRight;

        m_dwThumbNormal = dwThumbNormal;
        m_dwThumbPress = dwThumbPress;

        /*if ( NULL != m_pImgNormalLeft )
        {
            delete m_pImgNormalLeft;
        }
        if ( NULL != m_pImgNormalMiddle )
        {
            delete m_pImgNormalMiddle;
        }
        if ( NULL != m_pImgNormalRight )
        {
            delete m_pImgNormalRight;
        }
        if ( NULL != m_pImgHighLightLeft )
        {
            delete m_pImgHighLightLeft;
        }
        if ( NULL != m_pImgHighLightMiddle )
        {
            delete m_pImgHighLightMiddle;
        }
        if ( NULL != m_pImgHighLightRight )
        {
            delete m_pImgHighLightRight;
        }
        if ( NULL != m_pImgThumbNormal )
        {
            delete m_pImgThumbNormal;
        }
        if ( NULL != m_pImgThumbPress )
        {
            delete m_pImgThumbPress;
        }*/

        if ( 0 != m_dwNormalLeft )
        {
            m_pImgNormalLeft = CUtility::GetImage( m_dwNormalLeft, _T("PNG") );
        }
        if ( 0 != m_dwNormalMiddle )
        {
            m_pImgNormalMiddle = CUtility::GetImage( m_dwNormalMiddle, _T("PNG") );
        }
        if ( 0 != m_dwNormalRight )
        {
            m_pImgNormalRight = CUtility::GetImage( m_dwNormalRight, _T("PNG") );
        }
        if ( 0 != m_dwHighLightLeft )
        {
            m_pImgHighLightLeft = CUtility::GetImage( m_dwHighLightLeft, _T("PNG") );
        }
        if ( 0 != m_dwHighLightMiddle )
        {
            m_pImgHighLightMiddle = CUtility::GetImage( m_dwHighLightMiddle, _T("PNG") );
        }
        if ( 0 != m_dwHighLightRight )
        {
            m_pImgHighLightRight = CUtility::GetImage( m_dwHighLightRight, _T("PNG") );
        }
        if ( 0 != m_dwThumbNormal )
        {
            m_pImgThumbNormal = CUtility::GetImage( m_dwThumbNormal, _T("PNG") );
        }
        if ( 0 != m_dwThumbPress )
        {
            m_pImgThumbPress = CUtility::GetImage( m_dwThumbPress, _T("PNG") );
        }

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

protected:
    HWND    m_hParent;

    UINT    m_dwNormalLeft;
    UINT    m_dwNormalMiddle;
    UINT    m_dwNormalRight;

    UINT    m_dwHighLightLeft;
    UINT    m_dwHighLightMiddle;
    UINT    m_dwHighLightRight;

    UINT    m_dwThumbNormal;
    UINT    m_dwThumbPress;

    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;

    Image   *m_pImgHighLightLeft;
    Image   *m_pImgHighLightMiddle;
    Image   *m_pImgHighLightRight;

    Image   *m_pImgThumbNormal;
    Image   *m_pImgThumbPress;

    enum EmStatus
    {
        emStatusNormal = 0,
        emStatusSetFocus,
    };
    EmStatus    m_emStatus;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTransparentCheckButton window

class CTransparentCheckButton : public CButton
{
    // Construction
public:
    CTransparentCheckButton();
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentCheckButton)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentCheckButton();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentCheckButton)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBMSetCheck(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

public:
    void    SetImage( UINT dwCheckNormal, UINT dwCheckPress, UINT dwCheckDiable,
                      UINT dwUnCheckNormal, UINT dwUnCheckPress, UINT dwUnCheckDiable )
    {
        m_dwCheckNormal = dwCheckNormal;
        m_dwCheckPress = dwCheckPress;
        m_dwCheckDiable = dwCheckDiable;

        m_dwUnCheckNormal = dwUnCheckNormal;
        m_dwUnCheckPress = dwUnCheckPress;
        m_dwUnCheckDiable = dwUnCheckDiable;

        /*if ( NULL != m_pImgCheckNormal )
        {
            delete m_pImgCheckNormal;
        }
        if ( NULL != m_pImgCheckPress )
        {
            delete m_pImgCheckPress;
        }
        if ( NULL != m_pImgCheckDiable )
        {
            delete m_pImgCheckDiable;
        }
        if ( NULL != m_pImgUnCheckNormal )
        {
            delete m_pImgUnCheckNormal;
        }
        if ( NULL != m_pImgUnCheckPress )
        {
            delete m_pImgUnCheckPress;
        }
        if ( NULL != m_pImgUnCheckDiable )
        {
            delete m_pImgUnCheckDiable;
        }*/

        if ( 0 != m_dwCheckNormal )
        {
            m_pImgCheckNormal = CUtility::GetImage( m_dwCheckNormal, _T("PNG") );
        }
        if ( 0 != m_dwCheckPress )
        {
            m_pImgCheckPress = CUtility::GetImage( m_dwCheckPress, _T("PNG") );
        }
        if ( 0 != m_dwCheckDiable )
        {
            m_pImgCheckDiable = CUtility::GetImage( m_dwCheckDiable, _T("PNG") );
        }
        if ( 0 != m_dwUnCheckNormal )
        {
            m_pImgUnCheckNormal = CUtility::GetImage( m_dwUnCheckNormal, _T("PNG") );
        }
        if ( 0 != dwUnCheckNormal )
        {
            m_pImgUnCheckPress = CUtility::GetImage( m_dwUnCheckPress, _T("PNG") );
        }
        if ( 0 != m_dwUnCheckDiable )
        {
            m_pImgUnCheckDiable = CUtility::GetImage( m_dwUnCheckDiable, _T("PNG") );
        }

        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
    }

protected:
    HWND    m_hParent;

    UINT    m_dwCheckNormal;
    UINT    m_dwCheckPress;
    UINT    m_dwCheckDiable;

    UINT    m_dwUnCheckNormal;
    UINT    m_dwUnCheckPress;
    UINT    m_dwUnCheckDiable;

    Image   *m_pImgCheckNormal;
    Image   *m_pImgCheckPress;
    Image   *m_pImgCheckDiable;
    
    Image   *m_pImgUnCheckNormal;
    Image   *m_pImgUnCheckPress;
    Image   *m_pImgUnCheckDiable;

    enum EmStatus
    {
        emStatusNormal = 0,
        emStatusPress,
    };
    EmStatus    m_emStatus;
};

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTEDIT_H__5DA170FD_67DD_449A_A4D4_FBD8A7DE22DF__INCLUDED_)
