/**  
 *@ 功能：ppt相关函数
 *@ 作者: wk
 *@ 时间: 2018-4-19
 */
#ifndef _PPT_H_
#define _PPT_H_

class CPpt
{
public:
	CPpt();
	~CPpt();

	static bool IsPptPlaying();                                       //判断ppt是否正在播放

	static void PPT_StopPlay();                                       //停止播放
	static void PPT_NextPage();                                       //下一页
	static void PPT_PriviousPage();                                   //上一页

private:
	static BOOL IsFullScreenActive(DWORD &dwProcessID);               //判断当前活动窗口是否全屏  
	static BOOL ProcessIdToName(CString &strProcessName, DWORD dwPID);//由进程ID获取名称
	static bool CheckSame(DWORD dwProcessID,int niX,int niY);         //判断屏幕上的一点(niX,niY)所属的process id是否和dwProcessID相同 
};

#endif//_PPT_H_
