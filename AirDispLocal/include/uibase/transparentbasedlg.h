#if !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
#define AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uicommon.h"
// TransparentBaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog

typedef BOOL(WINAPI *PFN_SetLayeredWindowAttributes)(
                                                     HWND hwnd,
                                                     COLORREF crKey,
                                                     BYTE bAlpha,
                                                     DWORD dwFlags);

typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
                                              HWND hWnd,
                                              HDC hdcDst,
                                              POINT *pptDst,
                                              SIZE *psize,
                                              HDC hdcSrc,
                                              POINT *pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION *pblend,
											  DWORD dwFlags);


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


class CTransparentBaseDlg : public CDialog
{
// Construction
public:
	CTransparentBaseDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransparentBaseDlg();
// Dialog Data
	//{{AFX_DATA(CTransparentBaseDlg)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentBaseDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    BOOL ShowWindow(int nCmdShow)
    {
        BOOL bRet = CWnd::ShowWindow( nCmdShow );

        if ( SW_SHOW == nCmdShow )
        {
            SendMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

    BOOL UpdateData(BOOL bSaveAndValidate = TRUE)
    {
        BOOL bRet = CDialog::UpdateData( bSaveAndValidate );

        if ( FALSE == bSaveAndValidate )
        {
            PostMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

	//供刷新线程用的函数
	void RedrawUIAll()
	{
		RedrawUI();
	}

	void SetReadyToRedrawUI(BOOL32 bReadyToRedrawUI)
	{
		m_bReadyToRedrawUI = bReadyToRedrawUI;
	}

protected:
    virtual void RedrawUI();

    void DrawChildWnd( Graphics *pGraphics, HWND hParentWnd );

public:
    UINT    m_dwBkResourceID;
    BOOL32  m_bTransparentWithoutBK;    // 在无背景图的情况下是否透明显示
    BOOL32  m_bRedrawUIImediately;      // 是否立即刷新，用来控制刷新频率的

	// ---------------------------
	// muxingmao
	virtual s32		GetWindowWidth();
	virtual s32		GetWindowHeight();
	virtual BYTE	GetSourceConstantAlpha(){ return m_byteSourceConstantAlpha; }
	virtual void	SetSourceConstantAlpha(BYTE byteSCA){ m_byteSourceConstantAlpha = byteSCA; }
	// ---------------------------

protected:
    static PFN_SetLayeredWindowAttributes   m_s_pfnSetLayeredWindowAttributes;
	static PFN_UpdateLayeredWindow          m_s_pfnUpdateLayeredWindow;

    Image   *m_pImageBK;
    BOOL32  m_bReadyToRedrawUI; // 避免刷新太频繁，导致效率降低
	
	BYTE	m_byteSourceConstantAlpha; //透明度

	BOOL32  m_bAjustSize;       // 此窗口是否根据窗口分辨率调整过大小了
    BOOL32  m_bScale;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
