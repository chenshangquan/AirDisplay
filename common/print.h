#ifndef _COMMON_H_
#define _COMMON_H_

#include "osp.h"
#include <Windows.h>
#include <iostream>
using namespace std;

#define BUF_SIZE          1024
#define LOG_FILE0          _T("temp\\NexTransmitter0.log")
#define LOG_FILE1          _T("temp\\NexTransmitter1.log")
#define LOG_SIZE          (1024*1024)

typedef enum emPRT_TYPE
{
	PRT_TYPE_OFF = 0,                 //打印关
	PRT_TYPE_CMD,                     //打印命令信息
	PRT_TYPE_VIDEO,                   //打印视频信息
	PRT_TYPE_AUDIO,                   //打印音频信息
	PRT_TYPE_OPEN_ALL                 //打印所有的信息
}PRT_TYPE;

class CPrint
{
public:
	CPrint();
	~CPrint();

	//prt
	static void Print( u8 byPrintLevel);               //放开打印
	static u8  GetPrintLevel();
	static bool  IsPrintVideo();
	static bool  IsPrintAudio();
	
	static void PrintMsg( char * format,... );     //打印，无日期
	static void PrintTimeMsg( char * format,... ); //打印，有日期
	static void PrintMsgNolog( char * format,... );//打印，不写到日志里

private:
	static void WriteLog(const char *pTemp);
private:
	static u8 m_byPrintLevel;

};

#define PRINTMSG CPrint::PrintMsg
#define PRINTMSG_TIME CPrint::PrintTimeMsg
#define PRINTMSG_NOLOG CPrint::PrintMsgNolog

#endif//_COMMON_H_