#if !defined(AFX_DYNAMICWND_H__35F1A4B3_F7F5_4BAA_B467_3951D6B78D9C__INCLUDED_)
#define AFX_DYNAMICWND_H__35F1A4B3_F7F5_4BAA_B467_3951D6B78D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DynamicWnd.h : header file
//
#include "BaseDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDynamicWnd dialog

class CDynamicWnd : public CTransparentBaseDlg
{
public:
    enum EmMoveDirection
    {
        emDirUpAndDown = 0,
        emDirLeftAndRight,
		emDirRightAndLeft
    };

// Construction
public:
	CDynamicWnd(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDynamicWnd)
	enum { IDD = IDD_DYNAMIC_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynamicWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDynamicWnd)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBtnHide();
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    void DoShow();
    void DoHide();

protected:
    void AjustWindow();

    virtual void Hided();
    virtual void Showed();

public:
	u8 GetWndState(){ return m_emAction; }
	void SetWindowTopMost();
    EmMoveDirection m_emMoveDirction;

    CRect   m_cNormalRect;
    CRect   m_cShrinkRect;
    CRect   m_cEnlargeRect;

    CRect   m_cCurrentRect;
    
    CPoint  m_cWindowPos;   // 底部位置

protected:

    enum EmState
    {
        emShowed = 0,
        emHided,
        emShowing,
        emHiding
    };
    EmState     m_emAction;
    BOOL32      m_bTowordEnlarge;   // 是否进行扩大
    CBaseDlg    *m_pcParentWnd;

	friend class CWndDispManage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNAMICWND_H__35F1A4B3_F7F5_4BAA_B467_3951D6B78D9C__INCLUDED_)
