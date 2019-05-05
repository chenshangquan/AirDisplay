#include "StdAfx.h"
#include "siptoolmsgmanager.h"
#include "WndObserver.h"

CSipToolMsgManager::CSipToolMsgManager(void)
{
}


CSipToolMsgManager::~CSipToolMsgManager(void)
{
}

void CSipToolMsgManager::AddObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.AddObserver(pObserver);
}


void CSipToolMsgManager::RemoveObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.RemoveObserver(pObserver);
}

void CSipToolMsgManager::SendMsg(TMsgParam& tMsgParam)
{
	m_cMsgManager.SendMsg(tMsgParam);
}

void CSipToolMsgManager::PostMsg( TMsgParam& tMsgParam )
{
	m_cMsgManager.PostMsg(tMsgParam);
}

void CSipToolMsgManager::AddWindowObserver(HWND hwnd)
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr != m_mapWndObs.end())
	{
		return;
	}
	CWndObserver *pWndOb = new CWndObserver(hwnd);
	m_mapWndObs[hwnd] = pWndOb;
	m_cMsgManager.AddObserver(pWndOb);
}

void CSipToolMsgManager::RemoveWindowObserver( HWND hwnd )
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr == m_mapWndObs.end())
	{
		return;
	}
	IObserver_MsgPrama *pWndOb = itr->second;
	m_cMsgManager.RemoveObserver(pWndOb);
	delete pWndOb;
	m_mapWndObs.erase(itr);
}
