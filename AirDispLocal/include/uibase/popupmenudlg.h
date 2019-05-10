#if !defined(AFX_POPUPMENUDLG_H__D0A5E453_F044_48FC_AAA3_0E0EB010B793__INCLUDED_)
#define AFX_POPUPMENUDLG_H__D0A5E453_F044_48FC_AAA3_0E0EB010B793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupMenuDlg.h : header file
//
#include "DynamicWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CPopupMenuDlg dialog

class CPopupMenuDlg : public CDynamicWnd
{
// Construction
public:
	CPopupMenuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPopupMenuDlg)
	enum { IDD = IDD_POPUP_MENU_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupMenuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupMenuDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPMENUDLG_H__D0A5E453_F044_48FC_AAA3_0E0EB010B793__INCLUDED_)
