#pragma once

#include <string>
#include <vector>

using namespace std;


// 项类型
typedef enum _EnumItemType
{
	ITEMTYPE_STRING,		// 字符串项
	ITEMTYPE_SEPARATOR,		// 分隔符项
	ITEMTYPE_SUBMENU,		// 子菜单项
}EnumItemType;

// 顺序类型
typedef enum _EnumaOrderType
{
	ORDERTYPE_FIRST,		// 第一个
	ORDERTYPE_CENTER,		// 中间
	ORDERTYPE_LAST,			// 最后一个
}EnumaOrderType;

// 项信息
typedef struct StruItemInfo  
{  
	int				nFlags;
	int				nID;  
	HICON			hIcon;
	HICON			hIconCheckNormal;//选中的正常图片
	HICON			hIconCheckHover; //选中的经过图片
	CString			strText;		// 字符串
	CString			strShortcut;	// 快捷键说明
	EnumItemType	eItemType;		// 项类型
	EnumaOrderType	eOrderType;		// 顺序类型
}StruItemInfo;

typedef vector<StruItemInfo*>	ItemInfoVec;
typedef ItemInfoVec::iterator	ItemInfoIter;


// CMenuEx 对话框

class CMenuEx : public CMenu
{

public:
	CMenuEx();   // 标准构造函数
	virtual ~CMenuEx();

private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 获取系统默认字体大小
	int GetSysFontSize();
	// 获取系统默认字体风格
	string GetSysFontFaceName();
	// 生成顺序类型
	EnumaOrderType GenerateOrderType();
 
	HHOOK		m_hook;					// 钩子句柄
	int			m_nFontSize;			// 字体大小
	int			m_nItemHeight;			// 项高度
	string		m_strFontFaceName;		// 字体风格
	int			m_nLeftWidth;			// 图标区域宽度
	int			m_nIconWidth;			// 图标宽度
	int			m_nIconHeight;			// 图标高度
	int			m_nIconCheckWidth;		// 选中的图标宽度
	int			m_nIconCheckHeight;		// 选中的图标高度
	int			m_nMenuWidth;			// 菜单宽度
	int			m_nSeparatorHeight;		// 分隔符高度
	bool		m_bHasIcon;				// 是否有图标
	COLORREF	m_clrBk;				// 背景色
	COLORREF	m_clrBkHover;			// 经过背景色
	COLORREF	m_clrText;				// 字体颜色
	COLORREF	m_clrHoverText;			// 经过字体颜色
	COLORREF	m_clrTextDisable;		// 无效字体颜色
	COLORREF	m_clrSeparator;			// 分割线颜色
	COLORREF	m_clrBorder;			// 边框颜色
	
	ItemInfoVec m_ItemList;
public:
	// 钩子
	void InstallHook(HINSTANCE hInst);
	void UnInstallHook();

	// 添加一项
	void AppendItem(UINT nFlags, UINT nID, CString strText, CString strShortcut, UINT nIconID);
	// 添加一个子菜单
	void AppendSubMenu(UINT nFlags, UINT nID, CMenuEx* subMenu, CString strText, UINT nIconID);
	// 添加分隔符
 	void AppendSeparator(UINT nFlags, UINT nID);

	//添加一个支持选中的项
	void AppendCheckItem(UINT nFlags, UINT nID, CString strText, CString strShortcut, UINT nIconCheckNormalID, UINT nIconCheckHoverID);

	void DestroyMenu();

	// 设置字体大小
	void SetFontInfo(int nSize, const char* szFontFaceName=NULL);
	// 设置项高度
	void SetItemHeight(int nItemHeight) { m_nItemHeight = nItemHeight; }
	// 设置菜单的宽度
	void SetMenuWidth(int nWidth) { m_nMenuWidth = nWidth; }
	// 设置边框颜色
	void SetBorderColor(COLORREF clr) { m_clrBorder = clr; }


};
