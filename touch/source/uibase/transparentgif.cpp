#include "stdafx.h"
#include "transparentgif.h"


CTransparentGif::CTransparentGif()
{
	m_hParent = NULL;
	m_pImage = NULL;
	m_dwResID = 0;

	
	m_FrameCount = 0;
	m_nFramePos = 0;
	m_pGraphics = NULL;
	m_nDelay = 0;

	m_hThread = NULL;
	m_bExitThread = FALSE;
	m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hMem = NULL;
	m_bIsPlaying = false;
}

CTransparentGif::~CTransparentGif()
{
	if (GetSafeHwnd())
	{
		StopGif();
	}
	
	CloseHandle(m_hExitEvent);
	
	if (m_hMem)
	{
		GlobalFree(m_hMem);
		m_hMem = NULL;
	}
}

BEGIN_MESSAGE_MAP(CTransparentGif, CStatic)
	//{{AFX_MSG_MAP(CTransparentGif)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

BOOL CTransparentGif::SetImage( LPCTSTR szFileName)
{
	StopGif();
	
	m_pImage = Image::FromFile(szFileName);

	//获得有多少个维度，对于gif就一个维度  
	UINT count = m_pImage->GetFrameDimensionsCount();  
	GUID *pDimensionIDs = (GUID*)new GUID[count];  
	m_pImage->GetFrameDimensionsList(pDimensionIDs, count);  
	WCHAR strGuid[39];  
	StringFromGUID2(pDimensionIDs[0], strGuid, 39);  
	m_FrameCount = m_pImage->GetFrameCount(&pDimensionIDs[0]);  

	delete[] pDimensionIDs;  

	//获得各帧之间的时间间隔  
	//先获得有多少个时间间隔，PropertyTagFrameDelay是GDI+中预定义的一个GIG属性ID值，表示标签帧数据的延迟时间  
	UINT FrameDelayNums = m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);  
	PropertyItem* lpPropertyItem = new PropertyItem[FrameDelayNums];  
	m_pImage->GetPropertyItem(PropertyTagFrameDelay, FrameDelayNums, lpPropertyItem);  
	UINT nDelay = ((long*)lpPropertyItem->value)[0];
	if (nDelay < 5)
	{
		m_nDelay = 100;
	}
	else
	{
		m_nDelay = 10*nDelay;
	}


	m_guid = FrameDimensionTime;  
	m_nFramePos = 0;
	m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);  
	return TRUE;
}

void CTransparentGif::SetImage( UINT dwResID )
{
	StopGif();

	m_dwResID = dwResID;
	if ( 0 != m_dwResID )
	{
		//m_pImage = CUtility::GetImage( m_dwResID, _T("GIF") );
		GetImageFromSource(dwResID, m_pImage, _T("GIF"));
		if (m_pImage)
		{
			//获得有多少个维度，对于gif就一个维度  
			UINT count = m_pImage->GetFrameDimensionsCount();  
			GUID *pDimensionIDs = (GUID*)new GUID[count];  
			m_pImage->GetFrameDimensionsList(pDimensionIDs, count);  
			WCHAR strGuid[39];  
			StringFromGUID2(pDimensionIDs[0], strGuid, 39);  
			m_FrameCount = m_pImage->GetFrameCount(&pDimensionIDs[0]);  

			delete[] pDimensionIDs;  

			//获得各帧之间的时间间隔  
			//先获得有多少个时间间隔，PropertyTagFrameDelay是GDI+中预定义的一个GIG属性ID值，表示标签帧数据的延迟时间  
			UINT FrameDelayNums = m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);  
			PropertyItem* lpPropertyItem = new PropertyItem[FrameDelayNums];  
			m_pImage->GetPropertyItem(PropertyTagFrameDelay, FrameDelayNums, lpPropertyItem);  

			m_guid = FrameDimensionTime; 
			m_nFramePos = 0;
			m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);  
		}
		//UINT nCount = m_pImage->GetFrameDimensionsCount();	//获取帧维数
		//GUID *pGuids = new GUID[nCount];				//定义一个GUID数组
		//m_pImage->GetFrameDimensionsList(pGuids,nCount);	//获取图像帧的GUID
		//m_FrameCount = m_pImage->GetFrameCount(pGuids);	//获取GIF帧数
		//delete [] pGuids;

		////获得各帧之间的时间间隔
		////先获得有多少个时间间隔，PropertyTagFrameDelay是GDI+中预定义的一个GIG属性ID值，表示标签帧数据的延迟时间
		///*UINT FrameDelayNums = m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);
		//PropertyItem* lpPropertyItem = new PropertyItem[FrameDelayNums];
		//m_pImage->GetPropertyItem(PropertyTagFrameDelay, FrameDelayNums, lpPropertyItem);*/
		//UINT nSize;		
		//m_pImage->GetPropertySize(&nSize, &m_nDelay);			//获取属性大小
		//PropertyItem *pItem = NULL;						//定义属性指针
		//pItem = (PropertyItem*)malloc(nSize);					//为属性指针分配合适的空间
		//m_pImage->GetAllPropertyItems(nSize, m_nDelay, pItem);		//获取属性信息
		//m_nDelay = ((long*)pItem->value)[0];					//获取第一帧的延时
		//free(pItem);							

		//m_guid = FrameDimensionTime;
		//m_nFramePos = 0;
		//m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);				
	}

	m_nDelay = 300;

	if ( NULL != m_hParent )
	{
		::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
	}
}

void CTransparentGif::ShowGif()
{
	//绘制是从对话框传来的dc句柄，最终还是要返回对话框代码处整体绘制出来，导致这里不能用线程
	/*unsigned int nDummy;
	m_hThread = (HANDLE) _beginthreadex(NULL,0,_ThreadAnimation,this,
	CREATE_SUSPENDED,&nDummy);
	if (!m_hThread)
	{
	TRACE(_T("Draw: Couldn't start a GIF animation thread\n"));
	return;
	} 
	else 
	ResumeThread(m_hThread);*/
	m_bIsPlaying = true;
	SetTimer(0, m_nDelay, NULL);
	
}

void CTransparentGif::StopGif()
{

	//m_bExitThread = TRUE;
	//SetEvent(m_hExitEvent);
	//if (m_hThread)
	//{
	//	// we'll wait for 5 seconds then continue execution
	//	WaitForSingleObject(m_hThread,5000);
	//	CloseHandle(m_hThread);
	//	m_hThread = NULL;
	//}

	//// make it possible to Draw() again
	//ResetEvent(m_hExitEvent);
	//m_bExitThread = FALSE;
	if (m_bIsPlaying)
	{
		m_bIsPlaying = false;
		KillTimer(0);
		if (m_pImage && m_hParent)
		{
			m_nFramePos = 0;
			m_pImage->SelectActiveFrame(&m_guid, m_nFramePos); 
			::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
		}
	}
}

LRESULT CTransparentGif::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	 m_hParent = (HWND)lParam;
	
	if ( IsWindowVisible() == FALSE )
	{
		return S_FALSE;
	}

	if ( NULL == m_pImage && 0 != m_dwResID )
	{
		GetImageFromSource(m_dwResID, m_pImage, _T("GIF"));
	}

	m_pGraphics = (Graphics*)wParam;

	CRect cRect;
	GetWindowRect( &cRect );
	m_point = cRect.TopLeft();
	::ScreenToClient( m_hParent, &m_point );

	if (m_pGraphics && m_pImage)
	{
		m_pGraphics->DrawImage(m_pImage, m_point.x, m_point.y, cRect.Width(), cRect.Height());
	}

	return TRUE;
}

UINT WINAPI CTransparentGif::_ThreadAnimation(LPVOID pParam)
{
	ASSERT(pParam);
	CTransparentGif *pThis = reinterpret_cast<CTransparentGif *> (pParam);

	pThis->ThreadAnimation();

	// this thread has finished its work so we close the handle
	CloseHandle(pThis->m_hThread); 
	// and init the handle to zero (so that Stop() doesn't Wait on it)
	pThis->m_hThread = 0;
	return 0;
}

void CTransparentGif::ThreadAnimation()
{
	while (!m_bExitThread)
	{
		if (m_pGraphics && m_pImage)
		{
			m_pGraphics->DrawImage(m_pImage, m_point.x, m_point.y, m_pImage->GetWidth(), m_pImage->GetHeight());

			if (m_bExitThread) 
			{
				break;
			}
				
			if (m_nDelay < 5) 
				WaitForSingleObject(m_hExitEvent, 100);
			else
				WaitForSingleObject(m_hExitEvent, 10*m_nDelay);
			//设置当前需要显示的帧数  
			m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);  
			m_nFramePos++;  
			if (m_nFramePos == m_FrameCount)
			{  
				m_nFramePos = 0;  
			}  
		}
	}
}

void CTransparentGif::OnTimer(UINT nIDEvent) 
{
	if ( 0 == nIDEvent)
	{
		/*Graphics gh(m_hWnd);  
		gh.DrawImage(m_pImage, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());  

		m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);  
		m_nFramePos++;  
		if (m_nFramePos == m_FrameCount)
		{  
			m_nFramePos = 0;  
		}  */
		if ( NULL != m_hParent )
		{
			m_pImage->SelectActiveFrame(&m_guid, m_nFramePos);  
			m_nFramePos++;  
			if (m_nFramePos == m_FrameCount)
			{  
				m_nFramePos = 0;  
			}  
		    ::SendMessage( m_hParent, WM_REDRAW_UI, NULL, NULL );
		}
	}
	
	CStatic::OnTimer(nIDEvent);
}

void CTransparentGif::GetImageFromSource(UINT nID, Image*& image, LPCTSTR lpszType)
{
	if (m_hMem)
	{
		GlobalFree(m_hMem);
		m_hMem = NULL;
	}

	HINSTANCE hInstance = ::AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource ( hInstance, MAKEINTRESOURCE(nID), lpszType); 
	ASSERT(hRsrc != NULL);

	DWORD dwSize = ::SizeofResource( hInstance, hRsrc);
	LPBYTE lpRsrc = (LPBYTE)::LoadResource( hInstance, hRsrc);
	ASSERT(lpRsrc != NULL);

	HGLOBAL m_hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	LPBYTE pMem = (LPBYTE)::GlobalLock(m_hMem);
	memcpy( pMem, lpRsrc, dwSize);
	::GlobalUnlock(m_hMem);
	IStream * pStream = NULL;
	::CreateStreamOnHGlobal( m_hMem, FALSE, &pStream);

	m_pImage = Gdiplus::Image::FromStream(pStream);

	pStream->Release();
	::FreeResource(lpRsrc);
}

void CTransparentGif::SetTimerDelay(UINT nDelay)
{
	m_nDelay = nDelay;
}