#if !defined(AFX_TRANSPARENTPROGRESSCTRL_H__8963BDFE_152D_4018_9ED0_DDB2E0251CC7__INCLUDED_)
#define AFX_TRANSPARENTPROGRESSCTRL_H__8963BDFE_152D_4018_9ED0_DDB2E0251CC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Utility.h"
#include "uicommon.h"
// transparentprogressctrl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CTransparentProgressCtrl window

class CTransparentProgressCtrl : public CProgressCtrl
{
// Construction
public:
	CTransparentProgressCtrl();

// Attributes
public:

// Operations
public:
    void SetImage( UINT dwLeftBK, UINT dwMidBK, UINT dwRightBK,
		           UINT dwLeft, UINT dwMid, UINT dwRight )
    {
        m_dwLeftResID = dwLeft;
        m_dwMidResID = dwMid;
        m_dwRightResID = dwRight;
		m_dwLeftBKResID = dwLeftBK;
		m_dwMidBKResID = dwMidBK;
		m_dwRightBKResID = dwRightBK;
		
        
        /*if ( NULL != m_pImgFront )
        {
            delete m_pImgFront;
        }
        if ( NULL != m_pImgMid )
        {
            delete m_pImgMid;
        }
        if ( NULL != m_pImgTail )
        {
            delete m_pImgTail;
        }
		if ( NULL != m_pImgFrontBK )
		{
			delete m_pImgFrontBK;
		}
		if ( NULL != m_pImgMidBK )
		{
			delete m_pImgMidBK;
		}
		if ( NULL != m_pImgTailBK )
		{
			delete m_pImgTailBK;
		}*/

        if ( 0 != m_dwLeftResID )
        {
            m_pImgFrontBK = CUtility::GetImage( m_dwLeftBKResID, _T("PNG") );
        }
        if ( 0 != m_dwMidResID )
        {
            m_pImgMidBK = CUtility::GetImage( m_dwMidBKResID, _T("PNG") );
        }
        if ( 0 != m_dwRightResID )
        {
            m_pImgTailBK = CUtility::GetImage( m_dwRightBKResID, _T("PNG") );
        }
		if ( 0 != m_dwLeftBKResID )
        {
            m_pImgFront = CUtility::GetImage( m_dwLeftResID, _T("PNG") );
        }
        if ( 0 != m_dwMidBKResID )
        {
            m_pImgMid = CUtility::GetImage( m_dwMidResID, _T("PNG") );
        }
        if ( 0 != m_dwRightBKResID )
        {
            m_pImgTail = CUtility::GetImage( m_dwRightResID, _T("PNG") );
        }

		if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
		
    }

	void SetPos( s32 dwPos );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparentProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentProgressCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
		
protected:
	UINT    m_dwLeftResID;
	UINT    m_dwMidResID;
	UINT    m_dwRightResID;
	UINT    m_dwLeftBKResID;
	UINT    m_dwMidBKResID;
	UINT    m_dwRightBKResID;
	
    Image   *m_pImgFront;
	Image   *m_pImgFrontBK;
    Image   *m_pImgMid;
    Image   *m_pImgMidBK;
    Image   *m_pImgTail;
    Image   *m_pImgTailBK;

	s32      m_nWidth;

    HWND    m_hParent;
	
    enum EmStatus
    {
        emStatusOrigin = 0,
		emStatusModify,
    };
    EmStatus    m_emStatus;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTPROGRESSCTRL_H__8963BDFE_152D_4018_9ED0_DDB2E0251CC7__INCLUDED_)
