/** @defgroup 常量定义 
 *  @version V1.1.4
 *  @author  叶良平
 *  @date    2017.12.19
 */
#pragma once

#if !defined(_CONSTDEF_H_)
#define _CONSTDEF_H_


#ifndef String 
typedef tstring String;	                            // String
#endif
#ifndef MbString                                    // MultiByteString 
typedef std::string MbString;
#endif

#define NOTIFY_MSG	ISipToolCommonOp::NotifyMsg

#define WINDOW_MGR_PTR  IWindowManager::GetSingletonPtr()


#define REG_RCKTOOL_MSG_OB(ob) ISipToolMsgManager::GetSingletonPtr()->AddObserver(ob);
#define UNREG_RCKTOOL_MSG_OB(ob) ISipToolMsgManager::GetSingletonPtr()->RemoveObserver(ob);
#define REG_RCKTOOL_MSG_WND_OB(hwnd) ISipToolMsgManager::GetSingletonPtr()->AddWindowObserver(hwnd);
#define UNREG_RCKTOOL_MSG_WND_OB(hwnd) ISipToolMsgManager::GetSingletonPtr()->RemoveWindowObserver(hwnd);


#define DEFAULT_TITLE_HEIGHT   100

#define CFG_FILE    _T("configure.ini")							//配置文件

#define  MAX_DEVICEVER_LEN   38                                 //版本号最大长度

#define SIPTOOL_VERSION_ID	   "V1.0.0.0"

#endif
