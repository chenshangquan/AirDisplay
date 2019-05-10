#if !defined(AFX_POPUPMENUBKDLG_H__7A710DF5_4B94_488D_A73B_CC4A710CFB62__INCLUDED_)
#define AFX_POPUPMENUBKDLG_H__7A710DF5_4B94_488D_A73B_CC4A710CFB62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupMenuBkDlg.h : header file
//
#include "dynamicwnd.h"
/////////////////////////////////////////////////////////////////////////////
// CPopupMenuBkDlg dialog

class CPopupMenuBkDlg : public CBaseDlg
{
// Construction
public:
	CPopupMenuBkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPopupMenuBkDlg)
	enum { IDD = IDD_DYNAMIC_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupMenuBkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupMenuBkDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPMENUBKDLG_H__7A710DF5_4B94_488D_A73B_CC4A710CFB62__INCLUDED_)
