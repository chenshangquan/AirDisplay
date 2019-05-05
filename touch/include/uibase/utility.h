#pragma once

#ifndef ATLASSERT
#define ATLASSERT	ASSERT
#endif

#include <map>
#include "MMSYSTEM.H"

#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


//typedef map<UINT, Image*> CImageMap;
typedef std::map<UINT, Image*> CImageMap;

class CUtility
{
public:
	static CString GetModulePath(HMODULE hModule = NULL);

	static BOOL IsFileExist(LPCTSTR lpszFilePath);

	static BOOL ExtractResourceToFile( LPCTSTR lpszType
									, UINT nResID
									, LPCTSTR lpszFilename
									, HMODULE hModule
									);

	static Image * LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL);
	

	static u16	GetItemGrpId(s32 nIndex)
	{
		return (nIndex>>12) & 0x000FF;
	}
	static u16	GetItemIndexId(s32 nIndex)
	{
		return nIndex & 0x00FFF;
	}

	static u32	MakeItemData(u16 wGrpId, u16 nItemIndex)
	{
		return ( (wGrpId<<12) & 0xFF000 ) | (nItemIndex & 0xFFF);
	}


	static void GetUpperDir(CString &strDir)
	{
		strDir = strDir.Left( strDir.GetLength() - 1 );
		strDir = strDir.Left( strDir.ReverseFind('\\') + 1 );
	}

	//----------------------------------------------------------
	//函 数 名: GetImage
	//功    能：根据ID获得图片指针，请勿释放任何获得的图片指针，由系统统一释放
	//参数说明:
	//返 回 值：图片指针
	//修改记录:
	//日期		版本		修改人		修改记录
	//2010/4/19	V1.0		muxingmao	创建
	//----------------------------------------------------------
	static Image*		GetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );
	static CImageMap	m_smapImage;

	//
	// GetDebugPriv
	// 在 Windows NT/2000/XP 中可能因权限不够导致以上函数失败
	// 如以　System 权限运行的系统进程，服务进程
	// 用本函数取得　debug 权限即可
	//
	static BOOL32	GetDebugPriv();

	// 获取当前屏幕分辨率相对于1680*1050的分辨率的缩放比例
	static double   GetScreenScale();
	
	// 根据缩放比例调整宽度
	static u32      GetScreenScaleWidth( u32 dwWidth );
	
	// 根据缩放比例调整高度
	static u32      GetScreenScaleHeight( u32 dwHeight );
	
	// 根据缩放比例调整X坐标
	static u32      GetScreenScalePosX( u32 dwPosX );
	
	// 根据缩放比例调整Y坐标
	static u32      GetScreenScalePosY( u32 dwPosY );

	static void		GetScreenScaleRect( CRect& rect );

	static Image*	ScaleBitmap(Image * pBitmap ,s32 nWidth ,s32 nHeight );	
};





