/**  
 *@ 功能：生成台标图片
 *@ 作者: wk
 *@ 时间: 2017-7-27
 */
#ifndef _LOGO_H_
#define _LOGO_H_

//logo数值 --1080p
#define TEXT_WIDTH			    700
#define LOGO_HEIGHT			    104
#define LOGO_POINTSIZE			60
#define LOGO_TEXT_COLOR         Color(255,201,14)
#define LOGO_LEFT			    80
#define TEXT_TOP			    45

#define TP_TEMPFILE_PATH       _T("temp\\")
#define LOGO_BMP_FILE          _T("logo.bmp")

class CLogo
{
public:
	CLogo();
	~CLogo();

	/**
	*功能:获取模块所在文件夹全路径, 包括最后的\
	*@param[in] 
	*@return 返回路径
    */
	static CString GetModuleFullPath(void);
	/**	 
	* 功能: 制作显示文字的图片
	* @param    const LPCTSTR strCharacters     [in]     文字内容
	* @param    const LPCTSTR strFontFamily     [in]     字体格式(宋体、微软雅黑等) 
	* @param    const FontStyle emFontStyle     [in]     字体结构(加粗、下划线等) 
	* @param    const Color clText				[in]     字体颜色 
	* @param    const Color clBorder			[in]     字体边界颜色 
	* @param    const Color clBkGrd				[in]     图片背景颜色 
	* @param    const int nFontSizeByPx			[in]     字体Px 
	* @param    const int borderWidthByPx		[in]     字体边界Px 
	* @param    const LPCTSTR strFileName		[in]     图片存储路径 
	* @return   bool
	* @remarks  
	*/
	static BOOL MakeImgByChar(const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
		const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName, int nWidth = 0, int nHeight = 0 );
	
	/**	 
	* 功能: 获取显示文字的大小
	* @param    const WCHAR * strCharacters     [in]     文字内容
	* @param    Font*pFont				        [in]     字体内容信息
	* @param    CSize& cSize					[out]    文字的大小
	* @return   
	* @remarks  
	*/
	static void GetCharExtent(IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize);
	/**	 
	* 功能: 保存图片
	* @param    HBITMAP   hBitmap     [in]     图片句柄
	* @param    CString szfilename	  [in]     输出路径
	* @return   BOOL 是否保存成功
	* @remarks  
	*/
	static BOOL SaveBitmapToFile(HBITMAP   hBitmap, CString szfilename);

};

#endif//_LOGO_H_