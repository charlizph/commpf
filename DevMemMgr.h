// DevMemMgr.h: interface for the CDevMemMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVMEMMGR_H__C6D61D18_30FB_45AB_806B_1450F7FC11F1__INCLUDED_)
#define AFX_DEVMEMMGR_H__C6D61D18_30FB_45AB_806B_1450F7FC11F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedMemory.h"

/*
history:
    2012.09.26:在CManageDevMem类中增加CreateUpdateChg函数，用于实现
				数据刷新时通知应用程序
*/
class CSharedMemory;
typedef struct SHMEM_EXT_CLASS _TagShMemTab
{
	_TagShMemTab()
	{
		bWritable = TRUE;
		memcpy(szDevName,"BaseMem",7);
		nTabNo = 0;
		pShMem = NULL;
//		bRecLenIsFixed = FALSE;
	}

	int		nTabNo;
	char	szMemName[2*VAR_NAME_LENGTH+1];
	int		nMemSize;
	BOOL	bWritable;
//	int		nVarType;
//	BOOL	bRecLenIsFixed;
	char	szDevName[VAR_NAME_LENGTH];
	CSharedMemory* pShMem;
}ShMemTab;

#ifdef WIN32
typedef  CArray<ShMemTab*,ShMemTab*> ShMemArray;
#else
typedef  std::vector<ShMemTab*> ShMemArray;
#endif

class COneRecData;

class SHMEM_EXT_CLASS CMemMgr  
{
public:
	CMemMgr();
	virtual ~CMemMgr();

public:
	BOOL LoadMemByXml();
	//初始化共享内存
	BOOL InitMem();
	BOOL CloseMem();
//增加共享内存块
	BOOL AddShMem(const char* szDbName,const char * szShMemName,int nMemSize,BOOL bTruncCreate=FALSE,void* pTabInfo=NULL);
	int	GetShMemCount();
	ShMemTab * GetMemByType(int nTabNo);
	ShMemTab * GetMemByIndex(int nIndex);
	BOOL GetTabIndexByName(CString szDbTabName,DbIndex& dbIndex);
//增加变量名为szVarName的内存变量到类型为nTabNo的内存块
	long AddMemVar(DbIndex dbIndex,int nVarMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);
//	long AddMemVar(int nTabNo,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);
//	long AddMemVar(const char* szTabName,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);

	BOOL DelMemVar(DbIndex dbIndex);

//根据dbindex
	ShMemTab* GetShMem(DbIndex & dbIndex);
	BOOL SetMemVarVal(DbIndex dbIndex,void* pData,int & nValLen,BOOL bUpdateTime=FALSE);
	BOOL SetMemVarVal(DbIndex dbIndex,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);

	BOOL GetMemVarVal(DbIndex& dbIndex,void* pData,int & nValLen);
	BOOL GetMemVarVal(DbIndex& dbIndex,VARIANT& var,int & nValLen,ValueHeader* pVH=NULL);
	
	//将变量值转换为字符串返回
	CString GetMemVarVal(DbIndex& dbIndex, int & nVarType,int & nValLen);
//	CString GetMemVarValByIndex(int nTabNo,int nIndex);
//	CString GetMemVarVal(int nTabNo,const char * szVarName);

	int GetValLen(int nTabNo,const char * szVarName);

	int  GetMemBlockSize(DbIndex dbIndex);
	int	 ReadMemBlock(const char* szTabName,void* pDataBuf, int nBufLen,int nWritePtr,int nStartPos);//返回读取长度
	int  WriteMemBlock(const char* szTabName,void* pDataBuf,int nBufLen,int nWritePtr);//返回指针位置
	BOOL SetWritePtr(DbIndex dbIndex,int nWritePtr);

//	long GetMemVarAdr(DbIndex dbIndex);
	BOOL GetMemVarIndex(DbIndex & dbIndex);
	BOOL GetMemIndex(DbIndex & dbIndex);
//	long GetMemVarAdr(int nTabNo,const char * szVarName);
//	long GetMemVarAdr(const char* szTabName,const char * szVarName);
	int	GetMemCurIndex(int nTabNo);

	int GetMemVarCount(int nTabNo);
	
	int GetMemVarCount(DbIndex & dbIndex);
	int GetMemVarCount(const char *  szTabName);

	BOOL  GetMemVarInfo(int nTabNo,int nIndex, ValueHeader* VHInfo);
	BOOL  GetMemVarInfo(DbIndex & dbIndex, ValueHeader* VHInfo);
	BOOL SetMemVarAttr(DbIndex dbIndex,int bRODChg);
	BOOL GetMemVarAttr(DbIndex dbIndex,int &bRODChg);

	BOOL  SetMemVarStatus(DbIndex dbIndex,int nStatus);
	BOOL  SetMemVarFlag(DbIndex dbIndex,int nFlag);

	BOOL ResetMem(int nTabIndex);
	BOOL ResetMem(DbIndex dbIndex);

	BOOL SrvIsRuning();
	BOOL StopSrv();
	BOOL StartSrv();
	void InitEmpty();
	int	m_nCurWritePtr;//当前写操作指针位置;
	int m_nCurReadPtr;//当前写操作指针位置;

	void SetDataChangedFun(funMemDataChanged funMemDC,void* pFunParam);
public:
	void InitAdr();
	char	m_szDevName[VAR_NAME_LENGTH];//设备名称
	ShMemArray m_MemArray;//设备包含内存列表
	BOOL	m_bFirst;
	BOOL m_bAuto;
	BOOL m_bSystem;//是否为系统表;
};

#ifdef WIN32
typedef  CArray<CMemMgr*,CMemMgr*> ShDevMemArray;
#else
typedef  std::vector<CMemMgr*> ShDevMemArray;
#endif

struct MEMDB_CONFIG
{
	int m_iDbNum;
	BYTE m_cbVerMain;
	BYTE m_cbVerMin;
};

//注册进程窗口句柄
struct REGPROC
{
	char m_szClassName[128];
	char m_szWindowName[128];
	char m_szProcName[64];
	long lWndAdr;//窗口类指针地址(long)pWnd;
};
//#define YtMem_TABNAME 	 _T("YtMem")
//============ 遥调内存表 表结构 ================
#ifndef YtMem_TABNAME
#ifdef WIN32
#define YtMem_TABNAME 	 _T("YtMem")
#else
#define YtMem_TABNAME 	 "YtMem"
#endif
struct YtMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	float 	SetVal;	 //设置值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	BOOL 	Comand;	 //控制命令 上调:0/下调:1/急停:2/
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
#endif


//============ 遥控内存表 表结构 ================
#ifndef YkMem_TABNAME
#ifdef WIN32
#define YkMem_TABNAME 	 _T("YkMem")
#else
#define YkMem_TABNAME 	 "YkMem"
#endif

struct YkMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	BYTE 	CtrlVal;	 //控制值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	BYTE 	Comand;	 //控制命令 遥控预选:1/遥控执行:2/遥控取消:3/
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
#endif

//============ 通道信息 表结构 ================
#ifndef Chanel_Info_TABNAME
#ifdef WIN32
#define Chanel_Info_TABNAME 	 _T("Chanel_Info")
#else
#define Chanel_Info_TABNAME 	 "Chanel_Info"
#endif
struct Chanel_Info { 
	BYTE 	Desc[128];	 //描述 
	BYTE 	ComState;	 //通讯状态 断开:0/连接:1/
	int 	ComType;	 //通讯类型 串口通讯:1/Tcp客户端:2/Tcp服务端:3/Udp客户端:4/Udp服务端:5/网络监视:6/串口监视:7/DDE Server:8/DDE Client:9/
	unsigned int 	RecvLen;	 //接收字节 
	unsigned int 	SendLen;	 //发送字节 
	int 	Port;	 //端口 
	int 	RecvInterval;	 //数据接收周期(ms) 
	int 	SendInterval;	 //数据发送周期(ms) 
	int 	RecvTimeOut;	 //数据接收超时(s) 
	int 	WriteRetryTimes;	 //发送失败重试次数 
	int 	BaudRate;	 //波特率 
	BYTE 	Parity;	 //奇偶校验 无:0/偶校验:1/奇校验:2/
	int 	DataBit;	 //数据位 
	BYTE 	StopBit;	 //停止位 1:0/1.5:1/2:2/
	BYTE 	IpAdr[16];	 //Ip地址 
	int 	Options;	 //Tcp参数 
	int 	Family;	 //Tcp_Family 
	int 	MaxConnect;	 //tcpServer最大连接数 
	BYTE 	BroadAdr[16];	 //udp广播地址 
	BYTE 	TargetAdr[16];	 //udp目标地址 
	int 	TargetPort;	 //udp目标端口 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif

//============ 实时告警表 表结构 ================

#ifndef RtAlarm_TABNAME
#ifdef WIN32
#define RtAlarm_TABNAME 	 _T("RtAlarm")
#else
#define RtAlarm_TABNAME 	 "RtAlarm"
#endif

struct RtAlarm { 
	short 	m_warnType;	 //告警类型 
	short 	m_warnSubType;	 //告警子类型 
	short 	m_warnDetail;	 //告警内容详细代码 
	BYTE 	m_objName[64];	 //产生告警对象名称 
	short 	m_dbNum;	 //库号 
	short 	m_tableNum;	 //表号 
	short 	m_ptNum;	 //点号 
	short 	m_ctrlVal;	 //控制值(yk(0x33控分0xCC控合),升降(0x33控分0xCC控合)) 
	BYTE 	eventsgflag;	 //=0一般事项，=1事故 
	BYTE 	m_szVal[16];	 //告警值 
	float 	m_fVal;	 //m_fVal 
	long 	m_warnTime_L;	 //告警时间(长整形) 
	BYTE 	m_warnTime[32];	 //告警时间(字符) 
	BYTE 	m_warnStr[128];	 //告警内容 
	BYTE 	m_wavFile[32];	 //声音文件 
};
#endif

#define PROC_NONE 0
//已经执行
#define PROC_EXEC 1
//返回结果
#define PROC_RETURN 2

//#include "memtabstruct.h"
/*
//系统级表
struct YtMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	float 	SetVal;	 //设置值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};



//============ 遥控内存表 表结构 ================

//#define YkMem_TABNAME 	 _T("YkMem")

struct YkMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	BYTE 	CtrlVal;	 //控制值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	BYTE 	Comand;	 //控制命令 遥控预选:1/遥控执行:2/遥控取消:3/
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
*/
class SHMEM_EXT_CLASS CManageDevMem
{
public:
	CManageDevMem();
	~CManageDevMem();
public:
	static BOOL CreateUpdateChg(const char* szDbName,BOOL bFirst);
	static void InitAdr();
	static BOOL InitSysCfg();
	static BOOL LoadMemByXml();
	//初始化共享内存
	static BOOL InitMem();
	static BOOL CloseMem();
	static BOOL ExitMem();//退出实时库
/******************************** AddDbMem()接口 **************************************/
/* 功能说明：增加内存库
/* 参数说明：
/*			输入参数：szDbName 数据库名称
					  参数类型：字符串
/*			输出值：  返回BOOL类型：TRUE:增加成功，FALSE:增加失败
/*
/********************************************************************************************/
	static BOOL AddDbMem(const char* szDbName);
/******************************** AddShMem()接口 **************************************/
/* 功能说明：增加数据表到内存库
/* 参数说明：
/*			输入参数：szDbName 数据库名称
					  参数类型：字符串
/*			输入参数：szShMemName 数据表名称
					  参数类型：字符串
/*			输入参数：nMemSize 数据表大小
					  参数类型：整型
/*			输入参数：nVarType 数据表的数据记录类型
					  参数类型：VARIANT
/*			输入参数：pTabInfo 数据表相关联的结构表
					  参数类型：void*
/*			输出值：  返回BOOL类型：TRUE:增加成功，FALSE:增加失败
/*
/********************************************************************************************/
	static BOOL AddShMem(const char* szDbName,const char * szShMemName,int nMemSize,BOOL bTruncCreate=FALSE,void* pTabInfo=NULL);
/******************************** AddMemVar()接口 **************************************/
/* 功能说明：增加数据变量到内存库
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，需要指定数据库的库和表的名称或者索引
					  参数类型：DbIndex
/*			输入参数：nVarMemSize 数据变量占用内存空间大小
					  参数类型：整型
/*			输入参数：nMemSize 数据变量类型
					  参数类型：VARIANT
/*			输入参数：pData 数据记录初始值
					  参数类型：void*
/*			输出值：  返回long类型：<0，增加失败，>-1表示内存变量在内存中的索引
/*
/********************************************************************************************/

	static long AddMemVar(DbIndex dbIndex,int nVarMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);

//	static long AddMemVar(const char* szDevName,int nTabNo,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL);
//	static long AddMemVar(const char* szDevName,const char* szTabName,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL);
/******************************** DelMemVar()接口 **************************************/
/* 功能说明：删除数据变量
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，需要指定数据库的库和表，点的名称或者索引
					  参数类型：DbIndex
/*			输出值：  返回BOOL类型：TRUE:删除成功，FALSE:删除失败
/*
/********************************************************************************************/
	static BOOL DelMemVar(DbIndex dbIndex);

/******************************** GetShMemCount()接口 **************************************/
/* 功能说明：获得内存中某数据库的所包含的表个数
/* 参数说明：
/*			输入参数：szDevName 数据库名称
					  参数类型：字符串
/*			输出值：  返回int类型：表个数
/*
/********************************************************************************************/
	static int	GetShMemCount(const char* szDevName);
/******************************** GetShMemCount()接口 **************************************/
/* 功能说明：获得内存中某数据库的所包含的表个数
/* 参数说明：
/*			输入参数：nDbIndex 数据库索引号
					  参数类型：整型
/*			输出值：  返回int类型：表个数
/*
/********************************************************************************************/
	static int	GetShMemCount(int nDbIndex);
/******************************** GetShDevMemCount()接口 **************************************/
/* 功能说明：获得内存中总的数据库个数
/* 参数说明：
/*			输出值：  返回int类型：数据库个数
/*
/********************************************************************************************/
	static int	GetShDevMemCount();

/******************************** GetShDevMemCount()接口 **************************************/
/* 功能说明：根据数据库名_表名 来获得表的dbindex
/* 参数说明：szDbTabName 由数据库名和表名组成，中间用_连接
			dbIndex：返回的表的索引信息
/*			输出值：  返回BOOL类型：成功与否
/*
/********************************************************************************************/
	static BOOL GetTabIndexByName(CString szDbTabName,DbIndex& dbIndex);

	static CMemMgr * GetMemByType(int nTabNo);
	static CMemMgr * GetMemByIndex(int nIndex);

	//根据dbIndex获得数据库(by db's index or db's name)
	static CMemMgr* GetMemMgr(DbIndex & dbIndex);

/******************************** SetMemVarVal()接口 **************************************/
/* 功能说明：给内存数据变量的赋值
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，dbIndex.nFldNo如果为-1 表示对
					  整条记录赋值，pData对应一条记录的结构，nValLen为记录的大小
					  参数类型：DbIndex
/*			输入参数：pData 数据变量的值
					  参数类型：void*
/*			输入参数：var 数据变量的值
					  参数类型：VARIANT
/*			输入参数：nValLen 数据变量值的长度
					  参数类型：int
/*			输入参数：pData 数据记录初始值
					  参数类型：void*
/*			输出值：  返回BOOL类型：TRUE:赋值成功，FALSE:赋值失败
/*
/********************************************************************************************/
//根据dbindex,调用时候需要设置dbIndex.nAcesType 
	static BOOL SetMemVarVal(DbIndex dbIndex,void* pData,int & nValLen,BOOL bUpdateTime=FALSE);
	static BOOL SetMemVarVal(DbIndex dbIndex,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);
	static BOOL SetMemVarVal(COneRecData* pORD,int nFldIndex,CString strVal,BOOL bUpdateTime=FALSE);//nFldIndex 不包含固定字段

/******************************** GetMemVarVal()接口 **************************************/
/* 功能说明：获取内存数据变量的值
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引
					  参数类型：DbIndex
/*			输入参数：pData 数据变量的值
					  参数类型：void*
/*			输入参数：var 数据变量的值
					  参数类型：VARIANT
/*			输入参数：nValLen 数据变量值的长度
					  参数类型：int
/*			输入参数：pData 数据记录初始值
					  参数类型：void*
/*			输出值：  返回BOOL类型：TRUE:取值成功，FALSE:取值失败
/*
/*$$$$$$    特别注意：对于var是BSTR类型的使用完了之后要调用SysFreeString(var.bstrVal) $$$$$$$
/********************************************************************************************/
	static BOOL GetMemVarVal(DbIndex& dbIndex,void* pData,int & nValLen);
	static BOOL GetMemVarVal(DbIndex& dbIndex,VARIANT& var,int & nValLen,ValueHeader* pVH=NULL);//对于var是BSTR类型的使用完了之后要调用SysFreeString(var.bstrVal)
	static int GetValLen(const char* szDevName,int nTabNo,const char * szVarName);

	static CString GetMemVarVal(DbIndex& DbIndex,int & nVarType,int & nValLen);
	static CString GetMemVarVal(COneRecData* pORD,int nFldIndex);//nFldIndex 不包含固定字段
/******************************** GetMemVarIndex()接口 **************************************/
/* 功能说明：获取内存数据变量的索引，可以根据名称获取索引，也可以根据索引获取名称，结果在dbIndex返回
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL GetMemVarIndex(DbIndex & dbIndex);
/******************************** GetMemIndex()接口 **************************************/
/* 功能说明：获取内存数据库表的索引，可以根据名称获取索引，也可以根据索引获取名称，结果在dbIndex返回
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL GetMemIndex(DbIndex & dbIndex);
//	static long GetMemVarAdr(DbIndex dbIndex);
//	static long GetMemVarAdr(const char* szDevName,int nTabNo,const char * szVarName);
//	static long GetMemVarAdr(const char* szDevName,const char* szTabName,const char * szVarName);

//	static int	GetMemCurIndex(const char* szDevName,int nTabNo);

/******************************** GetMemVarInfo()接口 **************************************/
/* 功能说明：获取内存数据变量的信息，
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输入参数：VHInfo，变量信息指针，接收变量信息
					  参数类型：ValueHeader*
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL  GetMemVarInfo(DbIndex& dbIndex, ValueHeader* VHInfo);
/******************************** SetMemVarStatus()接口 **************************************/
/* 功能说明：获取内存数据变量的信息，
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输入参数：status，变量的遥信告警状态，遥测是否越限等 参见MemMacro.h中定义的status
					  参数类型：int
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL  SetMemVarStatus(DbIndex dbIndex,int nStatus);

/******************************** SetMemVarFlag()接口 **************************************/
/* 功能说明：获取内存数据变量的信息，
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输入参数：nFlags，变量状态标志，是否要告警，是否存历史库等 参见MemMacro.h中定义的Flags
					  参数类型：ValueHeader*
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL	 SetMemVarFlag(DbIndex dbIndex,int nFlags);
/******************************** SetMemVarAttr()接口 **************************************/
/* 功能说明：获取内存数据变量的信息，
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输入参数：bRODChg (位顺序 7 6 5 4 3 2 1 0 )
                           dbIndex 对应变量的属性包括只读属性，变化送数
						   bRODChg 的最低位描述变化送数属性如果为1表示变化送数，为0表示变化的时候不送数到应用程序
						   bRODChg 的第2位描述只读属性，1表示数据只读，0表示不为只读 
					  参数类型：BOOL
/*			输出值：  返回BOOL类型：TRUE:成功，FALSE:失败
/*
/********************************************************************************************/
	static BOOL SetMemVarAttr(DbIndex dbIndex,int bRODChg);
	static BOOL GetMemVarAttr(DbIndex dbIndex,int &bRODChg);
/******************************** GetMemVarCount()接口 **************************************/
/* 功能说明：获取指定数据库的某表下内存数据变量的个数，
/* 参数说明：
/*			输入参数：dbIndex 数据库，表信息，调用时候需要设置dbIndex.nAcesType
					  相应地指定数据库的库，表和点的名称或者索引，其结果也放在dbIndex中
					  参数类型：DbIndex
/*			输出值：  返回int类型：内存变量个数
/*
/********************************************************************************************/
	static int GetMemVarCount(DbIndex & dbIndex);
//	static int GetMemVarCount(const char* szDevName,int nTabNo);
//	static int GetMemVarCount(const char* szDevName,const char* szTabName);

	static TABLE_INFO* GetTabInfo(DbIndex dbIndex);
	static BOOL ResetMem(int nDbIndex,int nTabIndex);
	static BOOL ResetMem(DbIndex dbIndex);
	static BOOL SrvIsRuning();
	static BOOL StopSrv();
	static BOOL StartSrv();
	static void InitEmpty();
//内存块操作函数
	static BOOL GetFileBuf(DbIndex dbIndex,int startPos,int& nLen,BYTE* pRetBuf);
	static int GetFileMemSize(DbIndex dbIndex);
	static int GetMemBlockSize(DbIndex dbIndex);
	static int ReadMemBlock(const char* szDevName,const char* szTabName,void* pDataBuf, int nBufLen,int nStartPos = -1);
	static BOOL WriteMemBlock(const char* szDevName,const char* szTabName,void* pDataBuf,int nBufLen);
	static void SetReadPtr(const char* szDbName,const char* szTabName,int nReadPtr);
	static BOOL SetWritePtr(const char* szDbName,const char* szTabName,int nWritePtr);
	static int	GetReadPtr(const char* szDbName,const char* szTabName);
	static int  GetWritePtr(const char* szDbName,const char* szTabName);

	static int ReadMemBlock(DbIndex dbIndex,void* pDataBuf, int nBufLen,int nStartPos = -1);
	static BOOL WriteMemBlock(DbIndex dbIndex,void* pDataBuf,int nBufLen);
	static void SetReadPtr(int dbNo,int nReadPtr);
	static BOOL SetWritePtr(int dbNo,int nWritePtr);
	static int	GetReadPtr(int dbNo);
	static int  GetWritePtr(int dbNo);

//end 内存块操作

	static BOOL IsAuto();
	static void SetAuto(BOOL bAuto);
	static CRtDbMgr m_gRtDbMgr;
#ifdef WIN32
	static UINT WINAPI GetMemData(LPVOID pParam);
#else
	static void * GetMemData(LPVOID pParam);
#endif
	static BOOL GetOneDbMemData(CRecArray* pRA);
	static BOOL IsFirst();
	static BOOL m_bInitSuc;

//内存数据变化通知函数
//**************** SetDataChangedFun 内存数据变化通知回调函数*****************/
// pParam：调用者传入的参数可以是一个CWnd* 或者其他指针 通过SetDataChangedFun设置
// dbIndex：变化的数据的信息
// var:		变化数据的值
	static BOOL SetBufTime(DbIndex dbIndex,int nBufTime);
	static void SetDataChangedFun(funMemDataChanged funMemDC,void* pFunParam);
	static BOOL RegProcWnd(RegWndInfo rwi);
	static BOOL UnRegProcWnd(RegWndInfo rwi);
	static BOOL IsRightPrj();
	static CString GetMemPrjPath();
	static void StartGetMemData(CRtDbMgr* pRtDbMgr);

/*创建变化数据存储表，该表保存发生变化的数据的索引(对应结构ChDIndex)，应用程序不需要调用该函数*/
	static BOOL CreateDChgDb(const char* szDbName,BOOL bFirst);
	static BOOL CreateImpDChgDb(const char* szDbName,BOOL bFirst);
	static BOOL CreateRtAlarmDb(BOOL bFirst);

	/* WriteProcStat向告警库里写入进程启动/退出信息，在每个进程的启动和退出的时候调用该函数
	BOOL bStat 0:进程退出
			   1:进程启动
	*/
	static BOOL WriteProcStat(BOOL bStat,RtAlarm& ra);
public:
	/*向遥调内存表中写入遥调信息：整个工程中只有一个遥调内存表，系统启动时自动读取遥调内存表所在的库名
	　　　保存在m_szYtDbName，遥调表名为YtMem
	输入：pYtMem待写入的遥调信息
	返回值：写入成功与否
	*/
	static BOOL WriteYtMem(YtMem* pYtMem);
	static BOOL WriteYtMem(char* szDbName,YtMem* pYtMem);
	/*从遥调内存表中读取遥调信息
	输入：pYtMem待接受遥调信息的指针
	返回值：读取成功与否
	*/
	static BOOL GetYtMem(YtMem* pYtMem);//获得系统遥调
	static BOOL GetYtMem(char* szDbName,YtMem* pYtMem);
	static void GetYtDbName(char* szYtName,int& nNameLen);

	/*向遥控内存表中写入遥调信息：整个工程中只有一个遥控内存表，系统启动时自动读取遥控内存表所在的库名
	　　　保存在m_szYkDbName，遥调表名为YkMem
	输入：pYkMem待写入的遥调信息
	返回值：写入成功与否
	*/
	static BOOL WriteYkMem(YkMem* pYkMem);
	static BOOL WriteYkMem(char* szDbName,YkMem* pYkMem);
	/*从遥控内存表中读取遥调信息
	输入：pYkMem待接受遥调信息的指针
	返回值：读取成功与否
	*/
	static BOOL GetYkMem(YkMem* pYkMem);
	static BOOL GetYkMem(char* szYkName,YkMem* pYkMem);
	static void GetYkDbName(char* szYkName,int & nNameLen);
	/*初始化所有通讯状态
	输入：BOOL bStatus 通道的通讯状态
	返回值：读取成功与否 1-成功，0-失败
	*/
	static BOOL InitChannelStatus(BOOL bStatus);
	/*初始化通讯状态
	输入：DbIndex dbIndex;只需要指定szPtName 或者nPtNo，DbName 和TabName系统指定
		BOOL bStatus 通道的通讯状态
	返回值：读取成功与否 1-成功，0-失败
	*/
	static BOOL InitChannelStatus(DbIndex & dbIndex,BOOL bStatus);
	/*读取通讯状态
	输入：DbIndex dbIndex;只需要指定szPtName 或者nPtNo，DbName 和TabName系统指定
		BOOL & bStatus 返回通道的通讯状态
	返回值：读取成功与否 1-成功，0-失败
	*/
	static BOOL GetChannelStatus(DbIndex & dbIndex, BOOL & bStatus);
	static BOOL GetChannelInfo(DbIndex & dbIndex, Chanel_Info* pCi);

	/*写通讯信息
	输入：DbIndex dbIndex;只需要指定szPtName 或者nPtNo，DbName 和TabName系统指定
		BOOL & bStatus 返回通道的通讯状态
	返回值：读取成功与否 1-成功，0-失败
	*/
	static BOOL SetChannelInfo(DbIndex & dbIndex, Chanel_Info* pCi);

	/*读取/设置系统级服务状态
	输入：nStatus 服务状态如挂牌状态
		
	返回值：读取成功与否 1-成功，0-失败
	*/
	static BOOL GetSrvStatus(int & nStatus);
	static BOOL SetSrvStatus(int nStatus);

	/*********GetMemInfo(BYTE* pRecv,int nRecvBufLen)**********
	
	  获得所有数据库，表信息，用于网络同步，判断是否为相同的数据
	  输入：pRecv调用者分配内存，用于接收内存信息
	        nRecvBufLen 调用者分配的内存大小
	  返回值：整型，内存信息大小，0表示失败
	*/
	static int GetMemInfo(BYTE* pRecv,int nRecvBufLen);
private:

private:
	static	BOOL m_bAuto;
	static  BOOL m_bFirst;
	static  long m_lWriteCount;
	static ShDevMemArray m_DevMemArray;
//	static CArray<long,long> m_lAdrList;
	static MEMDB_CONFIG *m_pConfig;
	static HANDLE m_hConfig;
#ifdef WIN32
	static METERED_SECTION * m_pInitSync; //共享内存初始化同步信号
#else
	static pthread_mutex_t * m_pInitSync; //共享内存初始化同步信号
#endif
private://遥控，遥调 系统中只能定义一次遥控表和遥调表
	static char m_szYtDbName[64];
	static char m_szYkDbName[64];
};

#endif // !defined(AFX_DEVMEMMGR_H__C6D61D18_30FB_45AB_806B_1450F7FC11F1__INCLUDED_)
