#include "stdafx.h"
#include "datalistclass.h"


CDataListClass::CDataListClass()
{

}

CDataListClass::~CDataListClass()
{

}

void CDataListClass::AddDataTail(TUSBData& tUSBData)
{
	CAutoLock cAuto(&m_tSemaphore);
	m_dataList.push_back(tUSBData);
}

void CDataListClass::DeletDataFront()
{
	CAutoLock cAuto(&m_tSemaphore);

	if (!m_dataList.empty())
	{
		m_dataList.pop_front();
	}
}

TUSBData& CDataListClass::GetDataFront()
{
	CAutoLock cAuto(&m_tSemaphore);

	if (!m_dataList.empty())
	{
		return m_dataList.front();
	}
	TUSBData tUSBData;
	return tUSBData;
}

void CDataListClass::Clear()
{
	CAutoLock cAuto(&m_tSemaphore);

	m_dataList.clear();
}

bool CDataListClass::IsEmpty()
{
	return m_dataList.empty();
}

u32  CDataListClass::Size()
{
	return m_dataList.size();
}

u32 CDataListClass::Max_Size()
{
	return m_dataList.max_size();
}


