/*****************************************************************************
模块名      : CNC控制台
文件名      : cncConst.h
相关文件    : 
文件实现功能: 声明常量和错误代码,供cnc的UI部分和cnclib部分共同使用
作者        : 
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期       版本        修改人      修改内容
2014/12/20   1.4         肖楚然        创建
******************************************************************************/
#pragma once

#ifndef _AirDispRemoteCONST_20190410_H_
#define _AirDispRemoteCONST_20190410_H_

#include "kdvtype.h"
#include <map> 
using namespace std;

#define CONNETCT_SIPSERVER_PORT      60002                                     //sip服务器端口号 

#define PrtAirDispRemoteMsg (CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg)                        //打印Curl消息接口
#define AirDispRemoteMAPPING_HELPER (CAirDispRemotePrintCtrl::GetPrintCtrl()->MappingHelper)                  //注册打印的消息名

//------------------------------错误码部分------begin-------------------------------
/*终端控制台错误(27501 - 29500)*/
#define ERR_BGN		100
#define ERR_END		ERR_BGN + 1999

#define MAX_IP_LENGTH               16
#define MAX_ALIAS_LENGTH            32
#define MAX_SEARCH_TIME             10000

//rkcLib中的错误码
enum EmErrRkcLib
{

#define ERR_AirDispRemote_LIB_BEGIN  ERR_BGN

    // 控制台错误
    errAirDispRemote = ERR_AirDispRemote_LIB_BEGIN,
#define ERR_AirDispRemote                                 errAirDispRemote

	// 控制台错误
	err_AirDispRemote_creatinstance,
#define ERR_AirDispRemote_CREATINSTANCE                    err_AirDispRemote_creatinstance

    // 实例无效
    errInterface,
#define ERR_AirDispRemote_INTERFACE                        errInterface

    //osp 初始化失败
    errOspInit,
#define  ERR_OSP_INIT                                errOspInit

    //osp 创建监听节点失败
    errOspCreateTcpNode,
#define  ERR_OSP_CREATE_TCP_NODE                     errOspCreateTcpNode

    //已连接上
    errActiveConnect,
#define	ERR_AirDispRemote_ACTIVE_CONNECT                   errActiveConnect

    //TCP连接失败
    errTcpConnect,
#define	ERR_AirDispRemote_TCPCONNECT                       errTcpConnect


	errAirDispRemoteLibEnd,
#define ERR_AirDispRemote_LIB_END                         errAirDispRemoteLibEnd
		
};
 
#endif
