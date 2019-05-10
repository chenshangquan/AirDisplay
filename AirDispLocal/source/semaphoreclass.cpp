#include "stdafx.h"
#include "semaphoreclass.h"


CSemaphoreClass::CSemaphoreClass()
{
	InitializeCriticalSection(&m_hSem);
}

CSemaphoreClass::~CSemaphoreClass()
{
	DeleteCriticalSection(&m_hSem); 
}

void CSemaphoreClass::Lock()
{
	EnterCriticalSection(&m_hSem);
}

void CSemaphoreClass::Unlock()
{
	LeaveCriticalSection(&m_hSem);
}


CAutoLock::CAutoLock( CSemaphoreClass *pCSem )
{
	ASSERT(pCSem);

	m_pAutoSem = pCSem;
	m_pAutoSem->Lock();
}

CAutoLock::~CAutoLock()
{
	ASSERT(m_pAutoSem);

	m_pAutoSem->Unlock();
	m_pAutoSem = NULL;
}
