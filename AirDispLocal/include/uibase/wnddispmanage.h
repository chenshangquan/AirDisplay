// wndwispmanage.h: interface for the CWndDispManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDWISPMANAGE_H__144C2C52_DE4E_4CFE_8FB9_63A91F3B7FA8__INCLUDED_)
#define AFX_WNDWISPMANAGE_H__144C2C52_DE4E_4CFE_8FB9_63A91F3B7FA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
#include "dynamicwnd.h"
using namespace std;

class CWndDispManage : public CWnd  
{
public:
	CWndDispManage();
	virtual ~CWndDispManage();

protected:
	afx_msg s32 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnHideFinishNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowFinishNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	static BOOL32 PushHideWnd( CDynamicWnd *cWnd );
	static void HideWnd();
	static void Init();

private:
	static void Reset();
	static CWndDispManage			*m_s_pMySelf;
	static BOOL32					m_bDoing;	//标识正在过程中(包括隐藏中或者显示过程中，如果在过程中则压栈失败)
	
public:
	static stack<CDynamicWnd*>		m_s_stack;
	static CDynamicWnd				*m_s_pcWndShow;
};

#endif // !defined(AFX_WNDWISPMANAGE_H__144C2C52_DE4E_4CFE_8FB9_63A91F3B7FA8__INCLUDED_)
