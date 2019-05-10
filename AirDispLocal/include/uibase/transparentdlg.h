#if !defined(AFX_TRANSPARENTDLG_H__C1B589E5_CCA2_458F_8D43_AA8EE7D8E0C4__INCLUDED_)
#define AFX_TRANSPARENTDLG_H__C1B589E5_CCA2_458F_8D43_AA8EE7D8E0C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// transparentdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentDlg dialog


#include "transparentbasedlg.h"

class CTransparentDlg : public CTransparentBaseDlg
{
// Construction
public:
	CTransparentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransparentDlg)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:	
	virtual	BOOL32	IniUI( UINT nTitle, UINT nMid, UINT nBottom );
protected:
	virtual void RedrawUI();
	// Èý·ùÍ¼Æ¬
	Image*	m_pImgTitle;
	Image*	m_pImgMid;
	Image*	m_pImgBottom;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTDLG_H__C1B589E5_CCA2_458F_8D43_AA8EE7D8E0C4__INCLUDED_)
