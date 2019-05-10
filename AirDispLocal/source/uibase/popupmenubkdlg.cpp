// PopupMenuBkDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "touch.h"
#include "PopupMenuBkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupMenuBkDlg dialog


CPopupMenuBkDlg::CPopupMenuBkDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CPopupMenuBkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupMenuBkDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//     m_cNormalRect = CRect( 0, 0, 1580, 1024 );
//     m_cShrinkRect = CRect( 0, 0, 0, 1024 );
//     m_cEnlargeRect = CRect( 0, 0, 1580, 1024 );
//     m_cCurrentRect = CRect( 0, 0, 0, 1024 );
// 
//     m_cWindowPos = CPoint( 200, 1024 );
// 
//     m_emAction = emHided;
//     m_emMoveDirction = emDirLeftAndRight;
}


void CPopupMenuBkDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupMenuBkDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopupMenuBkDlg, CBaseDlg)
	//{{AFX_MSG_MAP(CPopupMenuBkDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupMenuBkDlg message handlers

BOOL CPopupMenuBkDlg::OnInitDialog() 
{
	CBaseDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
