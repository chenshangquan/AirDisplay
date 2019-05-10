/**  
 *@ 功能：进程相关函数封装类
 *@ 作者: wk
 *@ 时间: 2017-8-9
 */
#ifndef _PROGRESS_H_
#define _PROGRESS_H_

class CProgress
{
public:
	CProgress();
	~CProgress();

	/** 
	*功能:打开进程
	*@param CString strPathName [in] 带有路径的exe文件名
	*@return bool 是否打开成功
	*/
	static bool OpenProgress(CString strPathName);
	/** 
	*功能:关闭进程
	*param CString strName [in] exe文件名
	*@return 无
	*/
	static void CloseProgress(CString strName);
	/** 
	*功能:获取进程id
	*@param CString strName [in] exe文件名
	*@return DWORD 返回进程id,返回值不为0则进程存在，为0则进程不存在
	*/
	static DWORD GetProcessidFromName(CString strName);
	/** 
	*功能:判断进程是否正在运行
	*@param CString strName [in] exe文件名
	*@return bool 是否正在运行
	*/
	static bool IsProgressRunning(CString strName);

};

#endif//_PROGRESS_H_