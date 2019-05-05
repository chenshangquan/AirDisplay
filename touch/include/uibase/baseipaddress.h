#if !defined(AFX_BaseIPAddress_H__48268A05_FC49_47AF_B30C_B60DCB0C0F48__INCLUDED_)
#define AFX_BaseIPAddress_H__48268A05_FC49_47AF_B30C_B60DCB0C0F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseIPAddress.h : header file
#include "baseedit.h"
#include "uilibhead.h"
#include "CfgControl.h"
//

/////////////////////////////////////////////////////////////////////////////
// CBaseIPAddress window
class CSoftKeyboardDlg;

class CBaseIPAddress : public CTransparentIPAddrCtrl
{
// Construction
public:
	CBaseIPAddress();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseIPAddress)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBaseIPAddress();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBaseIPAddress)
	afx_msg LRESULT OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BaseIPAddress_H__48268A05_FC49_47AF_B30C_B60DCB0C0F48__INCLUDED_)
