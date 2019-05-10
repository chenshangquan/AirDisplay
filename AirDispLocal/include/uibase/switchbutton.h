#if !defined(AFX_SWITCHBUTTON_H__6B16C8AC_7340_4665_88DB_9E428F06AFF5__INCLUDED_)
#define AFX_SWITCHBUTTON_H__6B16C8AC_7340_4665_88DB_9E428F06AFF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// switchbutton.h : header file
//

#define GETSWBTNRES(p, RES) if( p->GetYesNo() ) \
								{				\
								RES = "1";	\
								}				\
								else			\
								{				\
								RES = "0";	\
								}				\
								
#define SETSWBINFO(p, RES)	if( RES == "0") \
					{						\
					p->SetYesNo(FALSE);	\
					}						\
					else					\
					{						\
					p->SetYesNo(TRUE);	\
					}						\

/////////////////////////////////////////////////////////////////////////////
// CSwitchButton window
#include "alternativebutton.h "
#define SWITCHBTN_CHANGE		ALTERNATIVEBTN_BASEMSG + 10
class CSwitchButton : public CStatic
{
// Construction
public:
	CSwitchButton();

// Attributes
public:

// Operations
public:
	BOOL CreateBtns(CRect &rect,  CWnd *pWnd);
	void SetBmpButtonLeft(  u32 use, u32 unuse );
	void SetBmpButtonRight( u32 use, u32 unuse );
	void ShowButton( BOOL bFlag );

	void EnableBtns();
	LRESULT OnLeftClick(WPARAM wParam, LPARAM lParam);

	void SetYesNo(BOOL byn){m_bYesNo = byn;  EnableBtns();/*ShowButton();*/}
	BOOL GetYesNo(){return m_bYesNo;}

	BOOL IsBtn(u32 pBtn)
	{
		HWND hwnd = GetSafeHwnd();
		if( NULL == m_pcBtnLeft || NULL == m_pcBtnRight || NULL == pBtn )
		{
			return FALSE;
		}
		if( pBtn == (u32)m_pcBtnLeft || pBtn == (u32)m_pcBtnRight )
		{
			return TRUE;
		}
		return FALSE;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitchButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
	CRect					m_cRectLeft;
	CRect					m_cRectRight;
	CAlternativeButton/*CTransparentBtn*/		*m_pcBtnLeft;
	CAlternativeButton/*CTransparentBtn*/		*m_pcBtnRight;

	u32						m_dwUseLeft;
	u32						m_dwUnuseLeft;

	u32						m_dwUseRight;
	u32						m_dwUnuseRight;

	BOOL					m_bYesNo;//True == Yes   False == NO
	HWND					m_HwndParent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHBUTTON_H__6B16C8AC_7340_4665_88DB_9E428F06AFF5__INCLUDED_)
