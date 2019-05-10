/*****************************************************************************
ģ����      : CNC����̨
�ļ���      : cncConst.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���������ʹ������,��cnc��UI���ֺ�cnclib���ֹ�ͬʹ��
����        : 
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��       �汾        �޸���      �޸�����
2014/12/20   1.4         Ф��Ȼ        ����
******************************************************************************/
#pragma once

#ifndef _AirDispRemoteCONST_20190410_H_
#define _AirDispRemoteCONST_20190410_H_

#include "kdvtype.h"
#include <map> 
using namespace std;

#define CONNETCT_SIPSERVER_PORT      60002                                     //sip�������˿ں� 

#define PrtAirDispRemoteMsg (CAirDispRemotePrintCtrl::GetPrintCtrl()->PrintMsg)                        //��ӡCurl��Ϣ�ӿ�
#define AirDispRemoteMAPPING_HELPER (CAirDispRemotePrintCtrl::GetPrintCtrl()->MappingHelper)                  //ע���ӡ����Ϣ��

//------------------------------�����벿��------begin-------------------------------
/*�ն˿���̨����(27501 - 29500)*/
#define ERR_BGN		100
#define ERR_END		ERR_BGN + 1999

#define MAX_IP_LENGTH               16
#define MAX_ALIAS_LENGTH            32
#define MAX_SEARCH_TIME             10000

//rkcLib�еĴ�����
enum EmErrRkcLib
{

#define ERR_AirDispRemote_LIB_BEGIN  ERR_BGN

    // ����̨����
    errAirDispRemote = ERR_AirDispRemote_LIB_BEGIN,
#define ERR_AirDispRemote                                 errAirDispRemote

	// ����̨����
	err_AirDispRemote_creatinstance,
#define ERR_AirDispRemote_CREATINSTANCE                    err_AirDispRemote_creatinstance

    // ʵ����Ч
    errInterface,
#define ERR_AirDispRemote_INTERFACE                        errInterface

    //osp ��ʼ��ʧ��
    errOspInit,
#define  ERR_OSP_INIT                                errOspInit

    //osp ���������ڵ�ʧ��
    errOspCreateTcpNode,
#define  ERR_OSP_CREATE_TCP_NODE                     errOspCreateTcpNode

    //��������
    errActiveConnect,
#define	ERR_AirDispRemote_ACTIVE_CONNECT                   errActiveConnect

    //TCP����ʧ��
    errTcpConnect,
#define	ERR_AirDispRemote_TCPCONNECT                       errTcpConnect


	errAirDispRemoteLibEnd,
#define ERR_AirDispRemote_LIB_END                         errAirDispRemoteLibEnd
		
};
 
#endif
