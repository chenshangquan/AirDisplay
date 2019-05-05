// MenuEx.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuEx.h"



CMenuEx::CMenuEx()
{
	m_hook = NULL;
	m_nItemHeight = ::GetSystemMetrics(SM_CYMENU);
	m_nFontSize = GetSysFontSize();
	m_strFontFaceName = GetSysFontFaceName();
	m_nLeftWidth = 30;
	m_nIconWidth = 16;
	m_nIconHeight = 16;
	m_nIconCheckWidth = 10;
	m_nIconCheckHeight = 10;
	m_clrBk = RGB(255,255,255);
	m_clrBkHover = RGB(30,148,248);
	m_clrText = RGB(76,76,76);
    m_clrHoverText = RGB(255,255,255);
	m_clrSeparator = RGB(230,230,230);
	m_clrTextDisable = RGB(180,180,180);
	m_clrBorder = RGB(85,85,85);
	m_nMenuWidth = 124;
	m_bHasIcon = false;
	m_nSeparatorHeight = 7;
	
}

CMenuEx::~CMenuEx()
{
}

void CMenuEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项

 	CString strText;   
 	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC); //获取菜单项的设备句柄   
 	StruItemInfo *pStruItemInfo =(StruItemInfo*)lpDrawItemStruct->itemData;  
 	if(pStruItemInfo == NULL)
 	{
 		return;
 	}
 
 	CRect rect(lpDrawItemStruct->rcItem);  
 
 	if(pStruItemInfo->eItemType == ITEMTYPE_SEPARATOR)		//分隔条  
 	{  
		// 画背景
 		pDC->FillSolidRect(rect, m_clrBk);  

		// 画线
 		CRect rcSeparator(rect);  
 		rcSeparator.top = rcSeparator.top + rcSeparator.Height() / 2;  
 		rcSeparator.bottom = rcSeparator.top + 1; 
		rcSeparator.left += 5;
 		rcSeparator.right -= 5;  
 		pDC->Draw3dRect(rcSeparator, m_clrSeparator, m_clrSeparator);
 
 	}
	else
	{
		// 画背景
		if(lpDrawItemStruct->itemState & ODS_GRAYED)	// 无效变灰
		{  
			pDC->FillSolidRect(rect, m_clrBk);  
			pDC->SetTextColor(m_clrTextDisable);  
		}      
		else if(lpDrawItemStruct->itemState & ODS_SELECTED )	// 经过
		{   
			//在菜单项上自绘矩形框的背景颜色   
			pDC->FillSolidRect(rect, m_clrBkHover);  
			//设置菜单文字颜色  
			pDC->SetTextColor(m_clrHoverText);  
		}   
		else  
		{  
			pDC->FillSolidRect(rect, m_clrBk);  
			pDC->SetTextColor(m_clrText);  
		}

		pDC->SetBkMode(TRANSPARENT); 

		/*if (lpDrawItemStruct->itemState & ODS_CHECKED)
		{
		CRect rctmp(rect);
		rctmp.left = rect.left + 15;
		rctmp.right = rctmp.left + 8;
		pDC->DrawText(_T("√"),&rctmp,DT_EXPANDTABS|DT_VCENTER|DT_SINGLELINE);
		}*/

		CRect rcIcon(rect);
		rcIcon.left += (m_nLeftWidth - m_nIconWidth) / 2;
		rcIcon.right = rcIcon.left + m_nIconWidth;
		rcIcon.top += (rcIcon.Height() - m_nIconHeight) / 2;

		if(pStruItemInfo->hIcon != NULL)  
		{  
			DrawIconEx(pDC->m_hDC, rcIcon.left, rcIcon.top, pStruItemInfo->hIcon, m_nIconWidth, m_nIconHeight, 0, NULL, DI_NORMAL);  
		}   

		//画选中的图标
		CRect rcCheckIcon(rect);
		rcCheckIcon.left += (m_nLeftWidth - m_nIconCheckWidth) / 2;
		rcCheckIcon.right = rcCheckIcon.left + m_nIconCheckWidth;
		rcCheckIcon.top += (rcCheckIcon.Height() - m_nIconCheckHeight) / 2;

		if (pStruItemInfo->hIconCheckNormal != NULL && pStruItemInfo->hIconCheckHover != NULL)
		{
			if (lpDrawItemStruct->itemState & ODS_CHECKED)
			{
				//经过
				if (lpDrawItemStruct->itemState & ODS_SELECTED )
				{
					DrawIconEx(pDC->m_hDC, rcCheckIcon.left, rcCheckIcon.top, pStruItemInfo->hIconCheckHover, m_nIconCheckWidth, m_nIconCheckHeight, 0, NULL, DI_NORMAL);  
				}
				else
				{
					DrawIconEx(pDC->m_hDC, rcCheckIcon.left, rcCheckIcon.top, pStruItemInfo->hIconCheckNormal, m_nIconCheckWidth, m_nIconCheckHeight, 0, NULL, DI_NORMAL);  
				}
			}
			
		}

		// 文字字体和字号设置  
		LOGFONT fontInfo;  
		pDC->GetCurrentFont()->GetLogFont(&fontInfo);  

		fontInfo.lfHeight = m_nFontSize;
		lstrcpy(fontInfo.lfFaceName, CA2W(m_strFontFaceName.c_str())); 
		CFont fontCh;  
		fontCh.CreateFontIndirect(&fontInfo);  
		pDC->SelectObject(&fontCh);  

		CRect rcText(rect);
		if (m_bHasIcon)
		{
			rcText.left += m_nLeftWidth;
		}
		else
		{
			rcText.left += 35;
		}
		rcText.top += (rcText.Height() - m_nFontSize) / 2;
		rcText.bottom = rcText.top + m_nFontSize;

		//子菜单项
		if(pStruItemInfo->eItemType == ITEMTYPE_SUBMENU)	
		{  
			pDC->TextOut(rcText.left, rcText.top, pStruItemInfo->strText, pStruItemInfo->strText.GetLength()); 
			// 换上自定义小箭头
			//::ExcludeClipRect(pDC->m_hDC,rect.right-15,rect.top,rect.right,rect.bottom);  
			//DrawIconEx(pDC->m_hDC,rect.right-40,rect.top+7,AfxGetApp()->LoadIconA(IDI_ICON1),32,32,1,NULL,DI_NORMAL);          
		}  
		else if (pStruItemInfo->eItemType == ITEMTYPE_STRING)		
		{  
			// 字符串项
			pDC->TextOut(rcText.left, rcText.top, pStruItemInfo->strText, pStruItemInfo->strText.GetLength());  
			//fontInfo.lfHeight = 16;  
			//CFont fontEn;  
			//lstrcpy(fontInfo.lfFaceName, _T("Arial"));  
			//fontEn.CreateFontIndirect(&fontInfo);  
			//pDC->SelectObject(&fontEn);  
			pDC->TextOut(rcText.left, rcText.top, pStruItemInfo->strShortcut, pStruItemInfo->strShortcut.GetLength());  
		}    
	
	}
 
	// 画边框
	CPen penBorder(PS_SOLID, 1, m_clrBorder);
	CPen *pOldPen = pDC->SelectObject(&penBorder);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->MoveTo(rect.right-1, rect.top);
	pDC->LineTo(rect.right-1, rect.bottom);

	if (m_ItemList.size() == 1)
	{
		// 如果只有一项的话就上下边都画
		pDC->MoveTo(rect.left, rect.top);
		pDC->LineTo(rect.right-1, rect.top);
		pDC->MoveTo(rect.left, rect.bottom-1);
		pDC->LineTo(rect.right-1, rect.bottom-1);
	}
	else
	{
		// 有多项的话，第一项画上边，最后一项画下边
		if (pStruItemInfo->eOrderType == ORDERTYPE_FIRST)
		{
			pDC->MoveTo(rect.left, rect.top);
			pDC->LineTo(rect.right-1, rect.top);
		} 
		else if (pStruItemInfo->eOrderType == ORDERTYPE_LAST)
		{
			pDC->MoveTo(rect.left, rect.bottom-1);
			pDC->LineTo(rect.right-1, rect.bottom-1);
		}
	}
	pDC->SelectObject(pOldPen);

}

void CMenuEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

	// TODO:  添加您的代码以确定指定项的大小

	StruItemInfo *pStruItemInfo =(StruItemInfo*)lpMeasureItemStruct->itemData;  
	if (pStruItemInfo->eItemType == ITEMTYPE_SEPARATOR)
	{
		// 设置分隔符项高度
		lpMeasureItemStruct->itemHeight = m_nSeparatorHeight;
	}
	else
	{
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
	}

	// 设置项宽度
	lpMeasureItemStruct->itemWidth = m_nMenuWidth;

}

void CMenuEx::AppendSeparator(UINT nFlags, UINT nID)  
{  
	StruItemInfo *pStruItemInfo = new StruItemInfo;
	pStruItemInfo->nID = nID;
	pStruItemInfo->hIcon = NULL;
	pStruItemInfo->hIconCheckNormal = NULL;  
	pStruItemInfo->hIconCheckHover = NULL;  
	pStruItemInfo->strText = "";
	pStruItemInfo->strShortcut = "";
	pStruItemInfo->eItemType = ITEMTYPE_SEPARATOR;
	nFlags |= MF_SEPARATOR|MF_OWNERDRAW;
	pStruItemInfo->nFlags = nFlags;
	pStruItemInfo->eOrderType = GenerateOrderType();

	m_ItemList.push_back(pStruItemInfo);

	CMenu::AppendMenu(nFlags, 0, (LPCTSTR)pStruItemInfo);  
}  

void CMenuEx::AppendSubMenu(UINT nFlags, UINT nID, CMenuEx* subMenu, CString strText,UINT nIconID)   
{  
	StruItemInfo *pStruItemInfo = new StruItemInfo;  
	pStruItemInfo->nID = nID;  
	if(nIconID == 0)  
	{  
		pStruItemInfo->hIcon = NULL;  
	}  
	else  
	{  
		pStruItemInfo->hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(nIconID),IMAGE_ICON, m_nIconWidth, m_nIconHeight, 0);
		if (pStruItemInfo->hIcon != NULL)
		{
			m_bHasIcon = true;
		}
	}  

	pStruItemInfo->hIconCheckNormal = NULL;  
	pStruItemInfo->hIconCheckHover = NULL;  
	pStruItemInfo->strText = strText;  
	pStruItemInfo->strShortcut = "";  
	pStruItemInfo->eItemType = ITEMTYPE_SUBMENU;      
	nFlags |= MF_POPUP|MF_OWNERDRAW;  
	pStruItemInfo->nFlags = nFlags;  
	pStruItemInfo->eOrderType = GenerateOrderType();

	m_ItemList.push_back(pStruItemInfo);

	CMenu::AppendMenu(nFlags, (UINT)subMenu->GetSafeHmenu(), (LPCTSTR)pStruItemInfo);      
} 

void CMenuEx::AppendItem(UINT nFlags, UINT nID, CString strText, CString strShortcut, UINT nIconID)   
{  
	StruItemInfo *pStruItemInfo = new StruItemInfo;  
	pStruItemInfo->nID = nID;  
	if(nIconID == 0)  
	{  
		pStruItemInfo->hIcon = NULL;  
	}  
	else  
	{  

		pStruItemInfo->hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIconID), IMAGE_ICON, m_nIconWidth, m_nIconHeight, 0);  
		//pStruItemInfo->hIcon = AfxGetApp()->LoadIcon(nIconID) ;  

		if (pStruItemInfo->hIcon != NULL)
		{
			m_bHasIcon = true;
		}
	}  

	pStruItemInfo->hIconCheckNormal = NULL;  
	pStruItemInfo->hIconCheckHover = NULL;  
	pStruItemInfo->strText = strText;  
	pStruItemInfo->strShortcut = strShortcut;  
	pStruItemInfo->eItemType = ITEMTYPE_STRING;  
	nFlags |= MF_OWNERDRAW;  
	pStruItemInfo->nFlags = nFlags;  
	pStruItemInfo->eOrderType = GenerateOrderType();

	m_ItemList.push_back(pStruItemInfo);

	CMenu::AppendMenu(nFlags, pStruItemInfo->nID, (LPCTSTR)pStruItemInfo);      
}  

void CMenuEx::AppendCheckItem(UINT nFlags, UINT nID, CString strText, CString strShortcut, UINT nIconCheckNormalID, UINT nIconCheckHoverID)
{
	StruItemInfo *pStruItemInfo = new StruItemInfo;  
	pStruItemInfo->nID = nID;  
	if(nIconCheckNormalID == 0)  
	{  
		pStruItemInfo->hIconCheckNormal = NULL;  
	}  
	else  
	{  

		pStruItemInfo->hIconCheckNormal = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIconCheckNormalID), IMAGE_ICON, m_nIconCheckWidth, m_nIconCheckHeight, 0);  
		//pStruItemInfo->hIcon = AfxGetApp()->LoadIcon(nIconID) ;  

		if (pStruItemInfo->hIconCheckNormal != NULL)
		{
			m_bHasIcon = true;
		}
	}  

	if(nIconCheckHoverID == 0)  
	{  
		pStruItemInfo->hIconCheckHover = NULL;  
	}  
	else  
	{  

		pStruItemInfo->hIconCheckHover = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIconCheckHoverID), IMAGE_ICON, m_nIconCheckWidth, m_nIconCheckHeight, 0);  
		//pStruItemInfo->hIcon = AfxGetApp()->LoadIcon(nIconID) ;  

		if (pStruItemInfo->hIconCheckHover != NULL)
		{
			m_bHasIcon = true;
		}
	}  

	pStruItemInfo->hIcon = NULL;
	pStruItemInfo->strText = strText;  
	pStruItemInfo->strShortcut = strShortcut;  
	pStruItemInfo->eItemType = ITEMTYPE_STRING;  
	nFlags |= MF_OWNERDRAW;  
	pStruItemInfo->nFlags = nFlags;  
	pStruItemInfo->eOrderType = GenerateOrderType();

	m_ItemList.push_back(pStruItemInfo);

	CMenu::AppendMenu(nFlags, pStruItemInfo->nID, (LPCTSTR)pStruItemInfo);      
}

static LRESULT WINAPI CallWndProc(int, WPARAM, LPARAM);				// 安装的钩子的窗口过程  
static LRESULT WINAPI MenuWndProc(HWND, UINT, WPARAM, LPARAM);		// 用来处理菜单的窗口过程  
WNDPROC oldWndProc = NULL;											// 用来保存被替换的窗口过程  

LRESULT WINAPI CallWndProc(int code, WPARAM wParam, LPARAM lParam)  
{  
	CWPSTRUCT* pStruct =(CWPSTRUCT*)lParam;  
	while(code == HC_ACTION)//HC_ACTION 为必须处理  
	{  
		HWND hWnd = pStruct->hwnd;  
		// 捕捉创建消息WM_CREATE，后面筛选为是否是菜单的创建  
		if( pStruct->message != WM_CREATE)  
			break;  
		TCHAR sClassName[10];  
		int Count = ::GetClassName(hWnd, sClassName, sizeof(sClassName)/sizeof(sClassName[0]));  
		// 检查是否菜单窗口，#32768为菜单类名  
		if( Count != 6 || _tcscmp(sClassName, _T("#32768")) != 0 )   
			break;  

		WNDPROC lastWndProc =(WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC); //获得指定窗口的信息 GWL_WNDPROC得到窗口回调函数的地址或句柄  
		//获取传入进程中窗口的窗口过程，这个窗口过程用于接收和处理系统向窗口发送的消息  
		if(lastWndProc != MenuWndProc)   
		{   
			// 替换菜单窗口过程   
			SetWindowLong(hWnd, GWL_WNDPROC, (long)MenuWndProc);   
			// 保留原有的窗口过程   
			oldWndProc = lastWndProc;   
		}  
		break;   
	}  


	//每一个钩子函数在进行处理时都要考虑是否需要把事件传递给下一个钩子处理函数。如果需要传递，就要调用函数CallNestHookEx（）。  
	//在实际使用时还是强烈建议无论是否需要进行事件传递都要在过程的最后调用一次CallNextHookEx( )，否则将会引起一些无法预知的系统行为或是系统锁定。  
	return CallNextHookEx((HHOOK)WH_CALLWNDPROC, code, wParam, lParam);   
}  

// 处理菜单的窗口过程  
LRESULT WINAPI MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  
{  
	LRESULT lResult;  
	switch(message)   
	{   
	case WM_CREATE://是否是菜单的创建  
		{   
			// 首先要去掉菜单窗口的一些扩展风格  
			// 包括：WS_BORDER、WS_EX_DLGMODALFRAME、WS_EX_WINDOWEDGE  
			lResult = CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);   
			DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);   
			DWORD dwNewStyle =(dwStyle & ~WS_BORDER);  
			::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);   
			DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);  
			DWORD dwNewExStyle =(dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE));   
			::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle);   
			return lResult;   
		}   
	case WM_PRINT: // 此处阻止非客户区地绘制  
		return CallWindowProc( oldWndProc, hWnd, WM_PRINTCLIENT, wParam, lParam);  

	case WM_WINDOWPOSCHANGING:   
		{   
			// 最后,由于我们在MeasureItem里指定了菜单大小，而系统会自动替菜单加边框，  
			// 因此必须去掉此部分额外地尺寸，将菜单大小改小  
			LPWINDOWPOS lpPos =(LPWINDOWPOS)lParam;   
			lpPos->cx -= 2*GetSystemMetrics(SM_CXBORDER)+4;   
			lpPos->cy -= 2*GetSystemMetrics(SM_CYBORDER)+4;  
			lResult = CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);   
			return 0;  
		}   
	case WM_GETICON:  
		return 0;   
	default:   
		return CallWindowProc( oldWndProc, hWnd, message, wParam, lParam);   
	}   
}  

void CMenuEx::InstallHook(HINSTANCE hInst)  
{  
	// 需要移除边框时，要安装钩子  
	if(m_hook == NULL)  
	{  
		DWORD id = ::GetCurrentThreadId(); // 获取当前线程的ID          
		m_hook = SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,hInst,id);//负责将回调函数放置于钩子链表的开始位置。  

		//HHOOK SetWindowsHookEx(int idHook;HOOKPROC lpfn;HINSTANCE hMod;DWORD dwThreadId);  
		//idHook 指定了钩子的类型，WH_CALLWNDPROC 系统将消息发送到指定窗口之前的“钩子”   
		//参数lpfn为指向钩子函数的指针，也即回调函数的首地址；  
		//参数hMod标识了钩子处理函数所处模块的句柄；  
		//参数dwThreadId 指定被监视的线程，如果明确指定了某个线程的ID就只监视该线程，此时的钩子即为线程钩子；  
		//如果该参数被设置为0，则表示此钩子为监视系统所有线程的全局钩子。  
		//此函数在执行完后将返回一个钩子句柄。  
	}  
}  

void CMenuEx::UnInstallHook()  
{  
	if(m_hook != NULL)  
	{  
		UnhookWindowsHookEx(m_hook);  
		m_hook = NULL;  
	}  
} 

int CMenuEx::GetSysFontSize()
{
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	if (hFont == NULL)
	{
		return 12;
	}

	LOGFONT lf;
	GetObject(hFont, sizeof(LOGFONT), &lf);

	return abs(lf.lfHeight);
}

string CMenuEx::GetSysFontFaceName()
{
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	if (hFont == NULL)
	{
		return "";
	}

	LOGFONT lf;
	GetObject(hFont, sizeof(LOGFONT), &lf);

	string strName(CW2A(lf.lfFaceName));
	return strName;
}



void CMenuEx::SetFontInfo(int nSize, const char* szFontFaceName/*=NULL*/)
{
	m_nFontSize = nSize;

	if (szFontFaceName != NULL)
	{
		m_strFontFaceName = szFontFaceName;
	}
}

void CMenuEx::DestroyMenu()
{
	ItemInfoIter it = m_ItemList.begin();
	for ( ; it != m_ItemList.end(); it++)
	{
		StruItemInfo* pStruItemInfo = (StruItemInfo*)*it;
		if (pStruItemInfo != NULL)
		{
			delete pStruItemInfo;
			pStruItemInfo = NULL;
		}
	}

	CMenu::DestroyMenu();
}

EnumaOrderType CMenuEx::GenerateOrderType()
{
	int nSize = m_ItemList.size();
	if (nSize == 0)
	{
		return ORDERTYPE_FIRST;
	} 
	else
	{
		ItemInfoIter it = m_ItemList.begin();
		for ( ; it != m_ItemList.end(); it++)
		{
			if ((*it)->eOrderType == ORDERTYPE_LAST)
			{
				(*it)->eOrderType = ORDERTYPE_CENTER;
				break;
			}
		}

		return ORDERTYPE_LAST;
	}
}