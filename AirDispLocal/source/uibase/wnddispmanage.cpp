// wndwispmanage.cpp: implementation of the CWndDispManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "touch.h"
#include "wnddispmanage.h"
#include "msgdispatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <map>
#include <vector>
#include <stack>
using namespace std;
using namespace std;

stack<CDynamicWnd*>		CWndDispManage::m_s_stack;
CDynamicWnd				*CWndDispManage::m_s_pcWndShow = NULL;
CWndDispManage			*CWndDispManage::m_s_pMySelf = NULL;
BOOL32					CWndDispManage::m_bDoing = FALSE;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndDispManage::CWndDispManage()
{

}

CWndDispManage::~CWndDispManage()
{

}

BEGIN_MESSAGE_MAP(CWndDispManage, CWnd)
	ON_WM_CREATE()
	ON_MESSAGE( WM_HIDE_FINISH_NOTIFY, OnHideFinishNotify)	
	ON_MESSAGE( WM_SHOW_FINISH_NOTIFY, OnShowFinishNotify)

END_MESSAGE_MAP()

//implement
void CWndDispManage::Init()
{
	m_s_pMySelf = new CWndDispManage;
	ASSERT( m_s_pMySelf != NULL );

	VERIFY( m_s_pMySelf->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("TouchView"),
		                             WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
}

s32 CWndDispManage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CMsgDispatch::RegMsgHandler( WM_HIDE_FINISH_NOTIFY, m_hWnd );
	CMsgDispatch::RegMsgHandler( WM_SHOW_FINISH_NOTIFY, m_hWnd );
	return 0;
}

BOOL32 CWndDispManage::PushHideWnd( CDynamicWnd *cWnd )
{
	if ( m_bDoing )
	{
		return FALSE;
	}

	if ( cWnd->m_emAction ==  CDynamicWnd::emShowing 
		|| cWnd->m_emAction ==  CDynamicWnd::emHiding )
	{
		Reset();
		return FALSE;
	}

	::SendMessage( cWnd->GetSafeHwnd(), WM_HIDE_WND_CMD, 0, 0 );
	return TRUE;
}

//主要进行压栈对象的检测
void CWndDispManage::HideWnd()
{
	m_bDoing = FALSE;

	if (!m_s_stack.empty())//主要验证压入栈中的对象都是showed状态的，否则回调不上来
	{
		CDynamicWnd *cHideWnd = NULL;

		//1 只保存显示了的窗口
		stack<CDynamicWnd*> stackfliter;
		while ( !m_s_stack.empty() )
		{
			cHideWnd = m_s_stack.top();
			m_s_stack.pop();
			if ( cHideWnd != NULL 
				&& cHideWnd->m_emAction == CDynamicWnd::emShowed )
			{
				stackfliter.push( cHideWnd );
			}
		}		
		while ( !stackfliter.empty() )//2 赋值
		{
			m_s_stack.push( stackfliter.top() );
			stackfliter.pop();
		}

		if ( !m_s_stack.empty() )
		{
			cHideWnd = m_s_stack.top();
			cHideWnd->DoHide();

			m_bDoing = TRUE;
		}
		else		//如果没有要隐藏的则判断是否有要显示的
		{
			if ( m_s_pcWndShow != NULL && m_s_pcWndShow->GetSafeHwnd() )
			{
				if ( m_s_pcWndShow->m_emAction == CDynamicWnd::emHided )
				{
					m_s_pcWndShow->DoShow();
					m_bDoing = TRUE;
				}		
			}
			else
			{
				Reset();//多重保护
			}
		}
	}
	else
	{
		if ( m_s_pcWndShow != NULL && m_s_pcWndShow->GetSafeHwnd() )
		{
			if ( m_s_pcWndShow->m_emAction == CDynamicWnd::emHided )//此步防止双击
			{
				m_s_pcWndShow->DoShow();				
				m_bDoing = TRUE;
			}
		}
	}
}

void CWndDispManage::Reset()
{
	while ( !m_s_stack.empty() )
	{
		m_s_stack.pop();
	}
	
	m_s_pcWndShow = NULL;
	m_bDoing = FALSE;
}

LRESULT CWndDispManage::OnHideFinishNotify(WPARAM wParam, LPARAM lParam)
{
	CDynamicWnd *cHideFinishWnd = (CDynamicWnd*)lParam;
	
	if ( !m_s_stack.empty() )
	{
		CDynamicWnd *cHideWnd = m_s_stack.top();
		if ( cHideFinishWnd == cHideWnd )
		{
			m_s_stack.pop();
		}
	}

	if ( m_s_stack.empty() )
	{
		if ( m_s_pcWndShow != NULL && m_s_pcWndShow->GetSafeHwnd() )
		{
			m_s_pcWndShow->DoShow();
		}
		else //无需显示任何窗口
		{
			Reset();
		}
	}
	else
	{
		if ( !m_s_stack.empty() )
		{
			CDynamicWnd *cHideWnd = m_s_stack.top();
			cHideWnd->DoHide();
		} 
	}
	
	return S_OK;
}

LRESULT CWndDispManage::OnShowFinishNotify(WPARAM wParam, LPARAM lParam)
{
	CDynamicWnd *cHideFinishWnd = (CDynamicWnd*)lParam;
	if ( m_s_stack.empty() && m_s_pcWndShow == cHideFinishWnd )
	{
		Reset();
	}

	return S_OK;
}