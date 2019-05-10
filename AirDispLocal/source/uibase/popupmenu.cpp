// PopupMenu.cpp: implementation of the CPopupMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "touch.h"
#include "touchmenuctrl.h"
#include "PopupMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// muxingmao

CPopupMenu::CPopupMenu()
{
    m_pcAddrListDlg = NULL;
    m_pcAddrInfoDlg = NULL;
}

CPopupMenu::~CPopupMenu()
{

}

void CPopupMenu::SetItem(IItem* pItem)
{
	//HidePopupMenu();
	if ( pItem->GetItemType() == IItem::emGroup )
	{
		if ( NULL == m_pcAddrListDlg )
		{
			m_pcAddrListDlg = new CAddrListDlg( NULL );
			
			m_pcAddrListDlg->Create( CAddrListDlg::IDD, NULL );

			m_pcAddrListDlg->SetItem( pItem );

			m_pcAddrListDlg->UpdateUI();
			m_pcAddrListDlg->ShowWindow( SW_SHOW );
			
			m_pcAddrListDlg->SetWindowPos( m_cWindowPos );
			m_pcAddrListDlg->DoShow();
		}
		else
		{
			m_pcAddrListDlg->SetItem( pItem );
			m_pcAddrListDlg->UpdateUI();
			m_pcAddrListDlg->ShowWindow( SW_SHOW );
			m_pcAddrListDlg->SetWindowPos( m_cWindowPos );
			m_pcAddrListDlg->DoShow();
		}
	}
	else if ( pItem->GetItemType() == IItem::emItem )
	{
		if ( NULL == m_pcAddrInfoDlg )
		{
			m_pcAddrInfoDlg = new CAddrInfoDlg( NULL );
		
			m_pcAddrInfoDlg->Create( CAddrInfoDlg::IDD, NULL );

			m_pcAddrInfoDlg->SetItem( pItem );

			m_pcAddrInfoDlg->UpdateUI();

			m_pcAddrInfoDlg->ShowWindow( SW_SHOW );
			
			m_pcAddrInfoDlg->SetWindowPos( m_cWindowPos );
			m_pcAddrInfoDlg->DoShow();
		}
		else
		{
			m_pcAddrInfoDlg->SetItem( pItem );
			m_pcAddrInfoDlg->UpdateUI();
			m_pcAddrInfoDlg->ShowWindow( SW_SHOW );
			m_pcAddrInfoDlg->SetWindowPos( m_cWindowPos );
			m_pcAddrInfoDlg->DoShow();
		}
	}
    
}

void CPopupMenu::HidePopupMenu()
{
    if ( NULL != m_pcAddrListDlg )
    {
        m_pcAddrListDlg->DoHide();
    }

    if ( NULL != m_pcAddrInfoDlg )
    {
        m_pcAddrInfoDlg->DoHide();
    }
}

LRESULT CPopupMenu::OnHidePopMenu()
{
	if ( NULL != m_pcAddrListDlg && m_pcAddrListDlg->IsWindowVisible() )
    {
        m_pcAddrListDlg->SendMessage(WM_HIDE_WND_CMD, 0, 0);
    }
	
    if ( NULL != m_pcAddrInfoDlg && m_pcAddrInfoDlg->IsWindowVisible() )
    {
        m_pcAddrInfoDlg->SendMessage(WM_HIDE_WND_CMD, 0, 0);
    }
	
	return S_OK;
}

// ----------------------------------------------------------------------