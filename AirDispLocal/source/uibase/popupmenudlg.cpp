// PopupMenuDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "PopupMenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupMenuDlg dialog


CPopupMenuDlg::CPopupMenuDlg(CWnd* pParent /*=NULL*/)
	: CDynamicWnd(CPopupMenuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupMenuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_cNormalRect = CRect( 0, 0, 200, 200 );
    m_cShrinkRect = CRect( 0, 0, 20, 200 );
    m_cCurrentRect = CRect( 0, 0, 20, 200 );

    m_cWindowPos = CPoint( 500, 324 + 200 );

    m_emAction = emHided;
}


void CPopupMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynamicWnd::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupMenuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopupMenuDlg, CDynamicWnd)
	//{{AFX_MSG_MAP(CPopupMenuDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupMenuDlg message handlers

BOOL CPopupMenuDlg::OnInitDialog() 
{
	CDynamicWnd::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
