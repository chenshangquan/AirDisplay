// PopupMenu.h: interface for the CPopupMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPUPMENU_H__53331DD3_FED8_42F8_8208_F15CDC9309A8__INCLUDED_)
#define AFX_POPUPMENU_H__53331DD3_FED8_42F8_8208_F15CDC9309A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PopupMenuDlg.h"
// #include "addrinfodlg.h"
// #include "addrlistdlg.h"

class CTouchMenuCtrl;
class CAddrListDlg;
class CAddrInfoDlg;

// class CPopupMenu  
// {
// public:
// 	CPopupMenu();
// 	virtual ~CPopupMenu();
// 
// public:
// 	void SelItemInfo( u32 nIndex );
// 	void SelGroupList( u32 bIndex );
//     void SetWindowPos( CPoint cPoint )
//     {
//         if ( cPoint.y > 260 )
//         {
//             cPoint.y = 260;
//         }
//         m_cWindowPos = cPoint;
//     }
// 
//     void ShowGroupList( u32 nIndex );
//     void ShowItemInfo( u32 nIndex );
// 
//     void HidePopupMenu();
// 
// 	LRESULT OnHidePopMenu();
// 
// private:
//     //vector<CPopupMenuDlg*>  m_vctPopupMenu;
// 
//     CAddrListDlg    *m_pcAddrListDlg;
//     CAddrInfoDlg    *m_pcAddrInfoDlg;
// 
//     CPoint          m_cWindowPos;
// 
//     friend class CTouchMenuCtrl;
// };

class CAddrListDlg;
class CAddrInfoDlg;
// -----------------------------------------------------------
class CPopupMenu  
{
public:
	CPopupMenu();
	virtual ~CPopupMenu();
	
public:
    void SetWindowPos( CPoint cPoint )
    {
        if ( cPoint.y > CUtility::GetScreenScalePosY( 260 ) )
        {
            cPoint.y = CUtility::GetScreenScalePosY( 260 );
        }
        m_cWindowPos = cPoint;
    }
	
    void SetItem(IItem* pItem);
	
    void HidePopupMenu();
	
	LRESULT OnHidePopMenu();
	
private:
    CAddrListDlg    *m_pcAddrListDlg;
    CAddrInfoDlg    *m_pcAddrInfoDlg;
	
    CPoint          m_cWindowPos;
	
    friend class CTouchMenuCtrl;
};

// -----------------------------------------------------------

#endif // !defined(AFX_POPUPMENU_H__53331DD3_FED8_42F8_8208_F15CDC9309A8__INCLUDED_)
