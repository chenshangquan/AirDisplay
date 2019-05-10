#if !defined(AFX_BASEDLG_H__ED97D575_50D9_4BE4_923F_0045DA698CAF__INCLUDED_)
#define AFX_BASEDLG_H__ED97D575_50D9_4BE4_923F_0045DA698CAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseDlg.h : header file
//
#include "TransparentBaseDlg.h"
#include "Transparentbtn.h"
#include "Transparentedit.h"
#include "transparentgif.h"
#include "transparentsyslink.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg dialog

class CBaseDlg : public CTransparentBaseDlg
{
// Construction
public:
	CBaseDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseDlg)
	enum { IDD = IDD_DYNAMIC_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseDlg)
	virtual BOOL OnInitDialog();
	LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEDLG_H__ED97D575_50D9_4BE4_923F_0045DA698CAF__INCLUDED_)
