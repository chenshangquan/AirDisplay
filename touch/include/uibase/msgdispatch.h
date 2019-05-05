// MsgDispatch.h: interface for the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
#define AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <list>
using namespace std;

class CMsgDispatch : public CWnd
{
public:
	CMsgDispatch();
	virtual ~CMsgDispatch();

public:
    static void Init();
    static void Destroy();

    static HWND GetMsgReceiveHandle();

    static void RegMsgHandler( u32 nMsgId, HWND hHandleWnd );
	
	static void DetachMsgHandler( u32 nMsgId, HWND hHandleWnd );

	static LRESULT SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam );

	static LRESULT PostMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam );
protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
    DECLARE_MESSAGE_MAP()

private:
    void DisPatchMsg();

private:
    static CMsgDispatch *m_pMySelf;
    static map< u32, vector<HWND> > m_mapDispatch;
};

#endif // !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
