// FocusEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "FocusEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusEdit

CFocusEdit::CFocusEdit()
{
}

CFocusEdit::~CFocusEdit()
{
}


BEGIN_MESSAGE_MAP(CFocusEdit, CBaseEdit)
	//{{AFX_MSG_MAP(CFocusEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_SETFOCUS()
		ON_WM_KILLFOCUS()
		ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusEdit message handlers
void CFocusEdit::OnSetFocus(CWnd* pOldWnd) 
{
	//	CEdit::OnSetFocus(pOldWnd);
	CBaseEdit::OnSetFocus(pOldWnd);
	m_emStatus = emStatusSetFocus;
	if ( NULL != m_hParent )
	{
		::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
}

void CFocusEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CBaseEdit::OnKillFocus(pNewWnd);
	m_emStatus = emStatusSetFocus;
	if ( NULL != m_hParent )
	{
		::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
    }
}



void CFocusEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	this->SetFocus();
	
	CBaseEdit::OnLButtonDown(nFlags, point);
}
