#ifndef _COMMINC_H
#define _COMMINC_H

#ifndef WIN32
#include "msystem.h"
#include "mtype.h"
#include "cstring.h"
#endif
//定义通讯类型(Communication Type - CT)

//没有通讯
#define CT_NONE 0
//串口通讯
#define CT_SERIAL 1 
//Tcp 客户端
#define CT_TCP_CLIENT 2
//Tcp 服务端
#define CT_TCP_SERVER 3
//Udp client
#define CT_UDP_CLIENT 4
//udp server
#define CT_UDP_SERVER 5
//net 监视
#define CT_MON_NET	6
//port 监视
#define CT_MON_PORT	7

//DDE Server
#define CT_DDE_SERVER 8
//DDE Client
#define CT_DDE_CLIENT 9
//数据库方式通讯
#define CT_DATABASE 10
//GSM通讯
#define CT_GSM 11

//sample value 
#define CT_ETH_SV 21
//GSSE
#define CT_ETH_GSSE 22
//GOOSE
#define CT_ETH_GOOSE 23

#define ETH_GOOSE	0x88B8
#define ETH_GSE		0x88B9
#define ETH_SV		0x88BA

//定义通讯状态(Communication Status - CS)
//没有联接
#define CS_DISCON  0
//连接
#define CS_CONNECT 1
//异常
#define CS_ABORT   2

//最大接收缓冲区
#ifdef WIN32
#define BUFFER_SIZE		1024000
#else
#define BUFFER_SIZE		65535
#endif
//1024000
//65535

//Enums
enum FlowControl
{
	NoFlowControl,
		CtsRtsFlowControl,
		CtsDtrFlowControl,
		DsrRtsFlowControl,
		DsrDtrFlowControl,
		XonXoffFlowControl
};

enum Parity
{    
		NoParity,
		OddParity,
		EvenParity,
		MarkParity,
		SpaceParity
};

enum StopBits
{
	OneStopBit,
		OnePointFiveStopBits,
		TwoStopBits
};

// Event value
#define EVT_CONSUCCESS		0x0000	// Connection established
#define EVT_CONFAILURE		0x0001	// General failure - Wait Connection failed
#define EVT_CONDROP			0x0002	// Connection dropped
#define EVT_ZEROLENGTH		0x0003	// Zero length message
#define EVT_CRTCLTSOCK		0x0004  // 服务端接收到客户端请求，并成功创建了sock

//事件id wparam 为事件类型值event value
#define UM_EVENT	WM_USER+20000
//通道接收到数据消息
#define UM_RECVDATA	WM_USER+20001
//通道发送数据消息
#define UM_SENDDATA WM_USER+20002
//消息信息
#define UM_MSGINFO  WM_USER+20003
//通道接收到数据ASCCII消息
#define UM_RECVASCDATA	WM_USER+20004
//通道发送数据ASCCII消息
#define UM_SENDASCDATA	WM_USER+20005

//时间格式1：yyyy-mm-dd hh:mm:ss.xxx
#define TIMETYPE1 1
//时间格式2：yyyy-mm-dd hh:mm:ss
#define TIMETYPE2 2
//时间格式3  mm-dd hh:mm:ss.xxx
#define TIMETYPE3 3
//时间格式4：dd hh:mm:ss.xxx
#define TIMETYPE4 4
//时间格式5：hh:mm:ss.xxx
#define TIMETYPE5 5
//时间格式6：hh:mm:ss
#define TIMETYPE6 6

//定义报文是发送或接收宏
//发送
#define DIREC_SEND 0
//接收
#define DIREC_RECV 1



//事件处理回调函数
//typedef void (*funEvent)(UINT uEvent,void* pOwner);
#include "xml.h"

//tcp server默认最大连接数
#define MAX_CONN	10

class CCommParam{
public:
	CCommParam();
	virtual ~CCommParam();
public:
	BOOL SaveParam(XMLElement* pRootNode);
	BOOL LoadParam(XMLElement* pRootNode);
public:
	BOOL bUsed;//是否启用
	BOOL bAsync;//收发数据是否异步;
	int nWriteRetryTimes;//发送失败重试次数,默认为3
	int nPort; //对于串口　是ｃｏｍ串口号，对于ｔｃｐ/udp 是server端口
	int nTimeOut;//对于串口是读数据超时，tcp是连接超时 单位秒
	int nCommType;//通讯类型;默认tcp client；
	int	nRecvInterval;//数据接收扫描周期 单位毫秒 默认10ms;
	int	nSendInterval;//数据发送队列扫描周期，单位毫秒 默认1000ms;
	int nRecvTimeOut;//数据接收超时，单位秒 < 1 不判断超时
	int nDelateConAlert;//连接断开后延迟告警时间 单位秒<1表示不判断
	int lLastAlertTime;
//for serial
	int	nBaudRate;//默认值　９６００；
	int nParity;//默认值　NoParity
	int nDataBits;//默认值　８
	int nStopBits;//默认值　OneStopBit
	int nFlowControl;//默认值　XonXoffFlowControl
	int bOverlapped;//默认值　ＴＲＵＥ
	int nRecvBufLen;
	int nSendBufLen;
//for tcp
	CString strIpAdr;//for db is dbserver name for serial is com name;
	UINT nOptions;//
	int nFamily;//默认值 AF_INET
	int	nCircleTime;//select 操作超时时间，默认值60000ms
//	BOOL bKeepAlive;//
	int	nMaxConnect;//最大连接数默认10；for server
//for udp
	BOOL bSendHand;
	BOOL bSmartAdr;//广播/点传送数据
	CString strBroadAdr;//
//	CString strBroadAdr2;//
//	CString strBroadAdr3;//
	int nTargetPort;
// for net monitor
	CString strNetDevName;//网络设备名; for dde is service name
	CString strFilter;//网络包过滤 默认tcp or ip;  for dde is topic
	CString strDesIpAdr;//目标ip地址; 
//for db
	CString strDriver;
public:
	void operator = (CCommParam inParam);
};


#define MSG_INFO	12000
#define MSG_RCDATA WM_USER + 10000
#define MSG_CRTSOCK WM_USER+ 10001
#define MSG_CLOSESOCK WM_USER+ 10002
#define MSG_UPDATESTATUS WM_USER + 10010
#define MSG_UPFILE	WM_USER+10020

#define WM_UPDATE_CONNECTION	WM_APP+0x1234

#include "CallBackFunDef.h"
#ifndef WIN32
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKET int
#define SOCKADDR_IN sockaddr_in
#define CloseHandle close
#endif
#endif

#endif