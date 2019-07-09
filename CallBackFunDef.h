#ifndef CALLBACKFUNDEF_H
#define CALLBACKFUNDEF_H
#ifdef WIN32
#include <afxcmn.h>
#else
#include "mtype.h"
#include "cstring.h"
#endif

#define	PROTEXPORT extern "C" __declspec( dllexport )
//将信息发送给父窗体m_pWndParent
typedef void (*funSendMsgToParent)(CString strMsg,void* pParentWnd);
//将信息发送给信息窗体
typedef void (*funSendDataToWnd)(void* pRecvWnd,void* pBuf,int nLen,BOOL bRecv);
typedef void (*funProtExit)(void* pDevCfg);
typedef void (*funProtInit)(void * pDevCfg,void* pComm);
typedef void (*funSetFlags)(BYTE index,BYTE value);
typedef BOOL (*funSendFram)(void* pComm,void* pDevCfg);
//typedef void (*funSetDataConfPoint)(DATACONF *pDConf);
#ifdef WIN32
typedef void (*funExpFram)(CString strFr,BYTE *pBuf,WORD wLen,CTreeCtrl &tree,BYTE flag);
#endif
//定义数据发送，接收处理回调函数 funProcData
//参数说明：pBuf 接收到的保文
//			nLen 接收到保文长度
//			nFlag 发送接收标志
//			pComm 接收报文的通道对象CBaseComm的派生类
//			pWnd 通道的父窗口句柄,用于接收通道事件
//			pDevCfg 设备指针对应类型CDevCfg
typedef int (*funProcData)(BYTE* pBuf,int nLen,int nFlag,void* pComm,void* pDevCfg);

//定义数据接收处理回调函数 funProcessData
//参数说明：pBuf 接收到的保文
//			nLen 接收到保文长度
//			pComm 接收报文的通道对象CBaseComm的派生类
//			pWnd 通道的父窗口句柄,用于接收通道事件
//			pDevCfg 设备指针对应类型CDevCfg
typedef int (*funProcessData)(void* pBuf,int nLen,void* pComm,void* pWnd,void* pDevCfg);

//定义连接断开处理回调函数 funProcDisCon
//参数说明：
//			pComm 接收报文的通道对象CBaseComm的派生类
//			pWnd 通道的主窗口句柄,用于接收通道事件m_pWndMain
typedef void (*funProcDisCon)(void* pComm,void* pWnd,void* pDevCfg);

//定义连接处理回调函数 funProcConnect
//参数说明：
//			pComm 接收报文的通道对象CBaseComm的派生类
//			pWnd 通道的主窗口句柄,用于接收通道事件m_pWndMain
typedef void (*funProcConnect)(void* pComm,void* pWnd,void* pDevCfg);

typedef void (*funSetLinkAdr)(int nAdr);
typedef void (*funInitFF)(void* pComm);

typedef  int (*funSendData)(void* pBuf,int nLen,void* pComm,void* pWnd);
typedef BOOL (*funCreateCfgDlg)(void* pWnd,LPCSTR strFileName);
typedef void (*funLoadProtCfg)(void * pDevCfg,LPCSTR strFileName);
//修改运行时的参数
typedef void (*funModRuntimeCfg)(void * pDevCfg,LPCSTR strFileName);
//重新建立连接通知
typedef void (*funNotifyReconnect)(void* pDevCfg);

typedef void (*funEmptyParam)();
typedef void (*funVoidPoint)(void* pPoint);
typedef UINT (*funSendThread)(void* pComm);

typedef void (*funAnalyseFrm)(BYTE* pBuf,int wLen,void* pComm);

//事件处理回调函数
// uEvent:事件类型EVT_CONSUCCESS，EVT_CONFAILURE，等
// pOwner:事件接收窗口
// pSocket:产生事件的通道对象CBaseComm的派生类
typedef void (*funEvent)(UINT uEvent,void* pParentWnd,void* pComm);

//增加自定义表
// void* pDevCfg:通道参数配置，包括通道所关联的实时库信息，对应类型为CDevCfg;
typedef BOOL (*funAddOwnTable)(void* pDevCfg);

//增加扩展的字段
//void* pTableInfo:表信息类TABLE_INFO,新的表字段直接调用pTableInfo->AddField函数;新的字段追加在表的字段集末;
typedef void (*funAddExtFld)(void* pTableInfo);

//填充使用到的表
//void* pDev CDevCfg类；
typedef void (*funFillUsedTab)(void* pDev);

//通过驱动程序对记录进行维护：增加，修改，删除记录。
//void* pRecArray:主程序传入的记录集指针，对应的类型为CRecArray，在驱动中只需要对pRecArray进行操作
//		可以调用pOneRec->SetStringData函数来实现.
//CWnd* pParent :接收消息窗口，支持下面消息ID
//void	pDevCfg 设备指针对应类型CDevCfg
//返回值表示成功与否
#define UM_REFRESHITEM WM_USER+20000
//获得增加记录的个数，
//bRemoveOld：是否删除以前的记录
//typedef bool (*funGetAddedCount)(void* pRecArray,void* pDevCfg,int & nCount,bool & bRemoveOld);
#ifdef WIN32
typedef bool (*funAddRecs)(void* pRecArray,int nStart,CWnd* pParent,void* pDevCfg);
typedef bool (*funAddRecsWithDbMgr)(void* pDbMgr,void* pRecArray,int nStart,CWnd* pParent,void* pDevCfg);
typedef int  (*funGetAddRecsCount)(void* pRecArray,CWnd* pParent,void* pDevCfg);
typedef bool (*funModRecs)(void* pRecArray,CWnd* pParent,void* pDevCfg);
//在系统保存的时候，动态库可以自己做相应的处理 
typedef bool (*funSaveEvent)(void* pRecArray,CWnd* pParent,void* pDevCfg);
#endif
//参数设置，定值设置
typedef bool (*funSetParam)(void* pDevCfg,void* pComm);

//维护工具sysmgr删除设备实例之前先行调用，在驱动里的实现的回调函数，
typedef bool (*funDelDevice)(void* pDevCfg,LPCSTR strFileName);
//
#endif