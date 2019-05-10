#include "StdAfx.h"
#include "AirDispRemotemsgmanager.h"
#include "WndObserver.h"

CAirDispRemoteMsgManager::CAirDispRemoteMsgManager(void)
{
}


CAirDispRemoteMsgManager::~CAirDispRemoteMsgManager(void)
{
}

void CAirDispRemoteMsgManager::AddObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.AddObserver(pObserver);
}


void CAirDispRemoteMsgManager::RemoveObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.RemoveObserver(pObserver);
}

void CAirDispRemoteMsgManager::SendMsg(TMsgParam& tMsgParam)
{
	m_cMsgManager.SendMsg(tMsgParam);
}

void CAirDispRemoteMsgManager::PostMsg( TMsgParam& tMsgParam )
{
	m_cMsgManager.PostMsg(tMsgParam);
}

void CAirDispRemoteMsgManager::AddWindowObserver(HWND hwnd)
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

void CAirDispRemoteMsgManager::RemoveWindowObserver( HWND hwnd )
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
