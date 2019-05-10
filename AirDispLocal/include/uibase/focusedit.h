#if !defined(AFX_FOCUSEDIT_H__82C39B8F_A464_4D98_B93F_8A4EA16F140F__INCLUDED_)
#define AFX_FOCUSEDIT_H__82C39B8F_A464_4D98_B93F_8A4EA16F140F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FocusEdit.h : header file
//
#include "baseedit.h"
/////////////////////////////////////////////////////////////////////////////
// CFocusEdit window

class CFocusEdit : public CBaseEdit
{
// Construction
public:
	CFocusEdit();
	void SetFocusState()
	{
		m_emStatus = emStatusSetFocus;
        if ( NULL != m_hParent )
        {
            ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
        }
	}
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFocusEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFocusEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSEDIT_H__82C39B8F_A464_4D98_B93F_8A4EA16F140F__INCLUDED_)
