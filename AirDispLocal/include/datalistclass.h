#ifndef _DATALISTCLASS_H_
#define _DATALISTCLASS_H_

#include <list>
#include "semaphoreclass.h"
using namespace std;
#include "quickshare.h"

typedef list<TUSBData> DATALIST;

class CDataListClass
{
public:
	CDataListClass();
	~CDataListClass();

	void AddDataTail(TUSBData& tUSBData);//从后面添加数据
	void DeletDataFront();//从前面删除一个元素
	TUSBData& GetDataFront();//从前面获取一个元素
	void Clear();
	bool IsEmpty();
	u32  Size();
	u32  Max_Size();

private:
	DATALIST m_dataList;

	CSemaphoreClass m_tSemaphore;
};
#endif//_DATALISTCLASS_H_