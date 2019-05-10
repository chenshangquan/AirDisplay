#include "StdAfx.h"
#include "Utility.h"
#include "resource.h"

CImageMap CUtility::m_smapImage;
//-------------------------------------------------------------------------
// Function Name    :GetModulePath
// Parameter(s)     :HMODULE hModule	Get module handle
// Return           :The module file path
// Create			:2007-1-10 11:24	Jerry.Wang
// Memo             :Retrieve the path of the given module
//-------------------------------------------------------------------------
CString CUtility::GetModulePath(HMODULE hModule /* = NULL */)
{
	TCHAR buf[MAX_PATH] = {'\0'};
	CString strDir, strTemp;

	::GetModuleFileName( hModule, buf, MAX_PATH);
	strTemp = buf;
	strDir = strTemp.Left( strTemp.ReverseFind('\\') + 1 );
	return strDir;
}


//-------------------------------------------------------------------------
// Function Name    :IsFileExist
// Parameter(s)     :LPCTSTR lpszFilePath	File path
// Return           :
// Create			:2007-4-23 15:13	Jerry.Wang
// Memo             :verify the file exist
//-------------------------------------------------------------------------
BOOL CUtility::IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile( lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}

	return bExist;
}


//-------------------------------------------------------------------------
// Function Name    :ExtractResourceToFile
// Parameter(s)     :UINT nResID			The resource id
//					:LPCTSTR lpszFilename	The file name
//					:HMODULE hModule		The module handle
// Return           :BOOL					Success on TRUE
// Create			:2007-1-8 17:35		Jerry.Wang
// Memo             :Extract resource to file
//-------------------------------------------------------------------------
BOOL CUtility::ExtractResourceToFile( LPCTSTR lpszType
									 , UINT nResID
									 , LPCTSTR lpszFilename
									 , HMODULE hModule
									 )
{
	HRSRC hRes = ::FindResource( hModule, MAKEINTRESOURCE(nResID), lpszType);
	if( hRes == NULL )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	DWORD dwSize = ::SizeofResource( hModule, hRes); 
	if( dwSize == 0 )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	HGLOBAL hGlobal = ::LoadResource( hModule, hRes); 
	if( hGlobal == NULL )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	LPVOID pBuffer = ::LockResource(hGlobal); 
	if( pBuffer == NULL )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	HANDLE hFile = ::CreateFile( lpszFilename
		, GENERIC_WRITE
		, FILE_SHARE_WRITE | FILE_SHARE_READ
		, NULL
		, CREATE_ALWAYS
		, 0
		, NULL
		);
	if( hFile == NULL )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	DWORD dwWritten = 0;
	::WriteFile( hFile, pBuffer, dwSize, &dwWritten, NULL);
	if( dwWritten != dwSize )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	::FlushFileBuffers(hFile);
	::CloseHandle(hFile);
	::FreeResource(hGlobal); 

	return TRUE;
}// ExtractResourceToFile


//-------------------------------------------------------------------------    
// Function Name    :LoadImage
// Parameter(s)     :UINT nID				The resource id
//					:LPCTSTR lpszType		The resource type
//					:HINSTANCE hInstance	The module handle
// Return           :Image *
// Create			:2009-3-12 14:28 Jerry.Wang                                     
// Memo             :Load the GDIPlus::Image from resource
//-------------------------------------------------------------------------   
Image * CUtility::LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance /*=NULL*/)
{
	Image * pImage = NULL;

	if( lpszType == RT_BITMAP )
	{
		HBITMAP hBitmap = ::LoadBitmap( hInstance, MAKEINTRESOURCE(nID) );
		pImage = (Image*)Bitmap::FromHBITMAP(hBitmap, 0);
		::DeleteObject(hBitmap);
		return pImage;
	}		

	hInstance = (hInstance == NULL) ? ::AfxGetResourceHandle() : hInstance;
	HRSRC hRsrc = ::FindResource ( hInstance, MAKEINTRESOURCE(nID), lpszType); 
	ASSERT(hRsrc != NULL);

	DWORD dwSize = ::SizeofResource( hInstance, hRsrc);
	LPBYTE lpRsrc = (LPBYTE)::LoadResource( hInstance, hRsrc);
	ASSERT(lpRsrc != NULL);

	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	LPBYTE pMem = (LPBYTE)::GlobalLock(hMem);
	memcpy( pMem, lpRsrc, dwSize);
	::GlobalUnlock(hMem);
	IStream * pStream = NULL;
	::CreateStreamOnHGlobal( hMem, FALSE, &pStream);

	pImage = Gdiplus::Image::FromStream(pStream);

	
	pStream->Release();
	::FreeResource(lpRsrc);
	GlobalFree(hMem);
	return pImage;
}

Image* CUtility::GetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance /* = NULL */ )
{
	if ( nID == 0 )
	{
		return NULL;
	}
	
	m_smapImage.find(nID);

	CImageMap::iterator itr = m_smapImage.find( nID );
	
	Image* pImage = NULL;

    if ( m_smapImage.end() == itr )
    {
		pImage = LoadImage(nID, lpszType, hInstance);
		if ( NULL != pImage )
		{
			m_smapImage.insert( CImageMap::value_type( nID, pImage ) );
		}
    }
	else
	{
		pImage = itr->second;
	}
	return pImage;
}

//
// GetDebugPriv
// 在 Windows NT/2000/XP 中可能因权限不够导致以上函数失败
// 如以　System 权限运行的系统进程，服务进程
// 用本函数取得　debug 权限即可
//

BOOL CUtility::GetDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	
	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
    {
		return FALSE;
    }
	
	
	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		CloseHandle( hToken );
		return FALSE;
	}
	
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	if (!AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
    {
        CloseHandle( hToken );
        return FALSE;
    }
	
    return TRUE;
}

// 获取当前屏幕分辨率相对于1680*1050的分辨率的缩放比例
double CUtility::GetScreenScale()
{
    static double dScale = 0.0;
	
    if ( dScale == 0.0 )
    {
		//DWORD dwScrWidth  = 1680;//::GetSystemMetrics( SM_CXSCREEN );
		//DWORD dwScrHeight = 1050;//::GetSystemMetrics( SM_CYSCREEN );
		
		DWORD dwScrWidth  = 1600;//::GetSystemMetrics( SM_CXSCREEN );
        DWORD dwScrHeight = 900;//::GetSystemMetrics( SM_CYSCREEN );

		//DWORD dwScrWidth	= ::GetSystemMetrics( SM_CXSCREEN );
        //DWORD dwScrHeight	= ::GetSystemMetrics( SM_CYSCREEN );

        double dScaleWidth = (double)dwScrWidth / 1680;
        double dScaleHeight = (double)dwScrHeight / 1050;
				
        // 按大的缩放
        dScale = ( dScaleWidth > dScaleHeight ) ? dScaleWidth: dScaleHeight;
    }
	
    return dScale;
}

// 根据缩放比例调整宽度
u32 CUtility::GetScreenScaleWidth( u32 dwWidth )
{
    return dwWidth * GetScreenScale();
}

// 根据缩放比例调整高度
u32 CUtility::GetScreenScaleHeight( u32 dwHeight )
{
    return dwHeight * GetScreenScale();
}

// 根据缩放比例调整X坐标
u32 CUtility::GetScreenScalePosX( u32 dwPosX )
{
    static double dScale = 0.0;
    static u32 dwScrWidth = 0, dwScrHeight = 0;
	
    if ( dScale == 0.0 )
    {
        dwScrWidth  = 1600;//::GetSystemMetrics( SM_CXSCREEN );
        dwScrHeight = 900;//::GetSystemMetrics( SM_CYSCREEN );
		
		//dwScrWidth  = 1680;//::GetSystemMetrics( SM_CXSCREEN );
        //dwScrHeight = 1050;//::GetSystemMetrics( SM_CYSCREEN );

		//dwScrWidth	= ::GetSystemMetrics( SM_CXSCREEN );
        //dwScrHeight	= ::GetSystemMetrics( SM_CYSCREEN );

        double dScaleWidth = (double)dwScrWidth / 1680;
        double dScaleHeight = (double)dwScrHeight / 1050;
		
        if ( dScaleWidth > dScaleHeight )
        {
            dScale = 0;
        }
        else
        {
            dScale = dScaleHeight - dScaleWidth;
        }
    }
	
    /*return dwPosX * ( GetScreenScale() - dScale );*/
    return dwScrWidth - ( 1680 - dwPosX ) * GetScreenScale();
}

// 根据缩放比例调整Y坐标
u32 CUtility::GetScreenScalePosY( u32 dwPosY )
{
    static double dScale = 0.0;
    static u32 dwScrWidth = 0, dwScrHeight = 0;
	
    if ( dScale == 0.0 )
    {
        dwScrWidth  = 1600;//::GetSystemMetrics( SM_CXSCREEN );
		dwScrHeight = 900;//::GetSystemMetrics( SM_CYSCREEN );
		
		//dwScrWidth  = 1680;//::GetSystemMetrics( SM_CXSCREEN );
        //dwScrHeight = 1050;//::GetSystemMetrics( SM_CYSCREEN );
		
		//dwScrWidth	= ::GetSystemMetrics( SM_CXSCREEN );
        //dwScrHeight	= ::GetSystemMetrics( SM_CYSCREEN );

        double dScaleWidth = (double)dwScrWidth / 1680;
        double dScaleHeight = (double)dwScrHeight / 1050;
		
        if ( dScaleWidth < dScaleHeight )
        {
            dScale = 0;
        }
        else
        {
            dScale = dScaleHeight;//dScaleWidth - dScaleHeight;
        }
    }
	
    return dwScrHeight - ( 1050 - dwPosY ) * GetScreenScale();
}

void CUtility::GetScreenScaleRect( CRect& rect )
{
	rect.left	= GetScreenScalePosX( rect.left );
	rect.right	= GetScreenScalePosX( rect.right );
	rect.top	= GetScreenScalePosY( rect.top );
	rect.bottom = GetScreenScalePosY( rect.bottom );
}

Image * CUtility::ScaleBitmap(Image * pBitmap, s32 nWidth,s32 nHeight)
{	
	Bitmap * pTemp = new Bitmap(nWidth,nHeight,pBitmap->GetPixelFormat());
	
	if( pTemp )		
	{	
		Graphics * pGraphics = Graphics::FromImage(pTemp);	
		if( NULL != pGraphics )
		{			
			pGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);
			
			pGraphics->DrawImage(pBitmap, 0, 0, nWidth, nHeight);
			
			delete pGraphics;
			
		}
	}
	
	return pTemp;	
}
