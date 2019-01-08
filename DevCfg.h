// DevCfg.h: interface for the CDevCfg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVCFG_H__1E43576D_98CE_4CFF_9E0F_1934B1A731EC__INCLUDED_)
#define AFX_DEVCFG_H__1E43576D_98CE_4CFF_9E0F_1934B1A731EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommBase.h"

typedef union _OwnDWORD
{
	DWORD dwVal;
	BYTE  cVal[8];
}OwnDWORD;

#include "PrjCfgMacro.h"
#include "RtDbInfo.h"

#ifndef WIN32
#include "cstring.h"
//for linux
//装载驱动动态库的接口
class CProInterface
{
public:
	CProInterface()
	{
		//memset(name,0,sizeof(name));
		loadFlag = -1;
		m_pFunSetFlags=NULL;
		m_pFunSendFram=NULL;
		m_pFunProcData=NULL;
		m_pFunSetAdr=NULL;
		m_pFunSendData=NULL;
	 	m_pLoadProtCfg=NULL;
		m_pFunProtInit=NULL;
		m_pFunSendThread=NULL;
		m_pFunInitFF=NULL;
		m_pFunProtExit=NULL;
		m_pFunProcDisCon = NULL;
		m_pFunProcConnect =NULL;
		m_pFunNotifyReconnect=NULL;
   
	}
	~CProInterface(){}	
	bool LoadLibrary(CString strProtoName);
	
public:
	//BaseComm *m_pComm;
	CString name;
	int loadFlag;
	funSetFlags		m_pFunSetFlags;
	funSendFram		m_pFunSendFram;
	funProcessData	m_pFunProcData;
	funSetLinkAdr	m_pFunSetAdr;
	funSendData		m_pFunSendData;
	funLoadProtCfg  m_pLoadProtCfg;
	funProtInit		m_pFunProtInit;
	funSendThread	m_pFunSendThread;
	funInitFF		m_pFunInitFF;
	funProtExit		m_pFunProtExit;
	funProcConnect	m_pFunProcConnect;
	funProcDisCon   m_pFunProcDisCon ;
	funNotifyReconnect m_pFunNotifyReconnect;	
};
#endif

#define MAX_PROTPARAM_LEN 2048
#define MAX_VARPARAM_LEN 2048

typedef struct _tagUsedTab{
	_tagUsedTab()
	{
		szTabName[0] = '\0';
		pTabInfo = NULL;
		bUsed = FALSE;
	}
	char szTabName[64];
	TABLE_INFO* pTabInfo;
	BOOL bUsed;
}UsedTab;
 
class CDevCfg  
{
public:
	CDevCfg();
	virtual ~CDevCfg();
public:
	//发送线程 
	BOOL m_bCanSend;
	BOOL m_bSending;

	BOOL m_bRunning;
	int m_nHeartCounter;
#ifdef WIN32
	BOOL LoadDevCfg(CString strRead);
#endif
//	BOOL SaveDevCfg(CStdioFile& file);
//	BOOL LoadInstCfg(CArchive& ar);
	BOOL LoadInstCfg(XMLElement* pRootNode);//CArchive& ar);
//	BOOL SaveInstCfg(CArchive& ar);
	BOOL SaveInstCfg(XMLElement* pRootNode);//CArchive& ar);
	CString	 GetFlag();
public:
	CString m_strDevFType;//设备所属行业，在ProtCfg.txt配置
	CString m_strDevCompany;//设备所属公司，在ProtCfg.txt配置
	CString m_strDevType;//设备类型，在ProtCfg.txt配置
	CString m_strDevName;//设备名称，在ProtCfg.txt配置
	CString m_strDevInstName;//设备实例名称；
	CString m_strDevInstDesc;//实例的描述;
	CString m_strProName;//设备采用的协议库名称，在ProtCfg.txt配置
	BOOL m_bSaveWeb;//是否将数据保存到数据库，以供web浏览
//	int		m_nSendInterval;//数据发送间隔 毫秒
//	int		m_nRecvInterval;//数据接收扫描间隔 毫秒
#ifdef WIN32
	HTREEITEM m_hTreeItem;
	HINSTANCE	m_hDllModule;//动态库的实例句柄;
#endif
	CString m_strDevCfgFileName;
	CCommParam m_oneParam;
	CBaseComm* m_pComm;//采集程序中使用 
public:
	//对于有扩展表字段的驱动，调用者两个函数对扩展字段进行读写
	BOOL GetStructData(COneRecData* pORD,LPCSTR szTabName,void* pBaseTab,int nBaseTabSize,void* pExtTab=NULL,int nExtTabSize=0);
//	BOOL GetFldVal(COneRecData* pORD,int nFldNo,CString & strVal);
	BOOL WriteStructData(COneRecData* pORD,LPCSTR szTabName,void* pBaseTab,int nBaseTabSize,void* pExtTab=NULL,int nExtTabSize=0,BOOL bUpdateTime=FALSE);
//	BOOL WriteFldVal(COneRecData* pORD,int nFldNo,CString strVal);
/*
	BOOL ReadIoVal(CString strTabName,int nPtNo, int nFieldNo, CString& strVal);//采集用
	BOOL ReadConvVal(CString strTabName,int nPtNo, int nFieldNo, CString& strVal);//转发用
	BOOL WriteIoVal(CString strTabName,int nPtNo, int nFieldNo, CString strVal);//采集用
	BOOL WriteConvVal(CString strTabName,int nPtNo, int nFieldNo, CString strVal);//转发用
*/	CString m_strFlag;
	BOOL	m_bProItem;
	int		m_nType;
	CPtrArray  m_aRecTabs;//每个设备通道采集用到的所有数据表 数据类型为CRecArray
//	CPtrArray  m_aConvTabs;//每个设备通道转发用到的所有数据表 

	BOOL SetGVarParam(BYTE* pBuf,int nLen);//分配全局变量参数内存，只能调用一次
	BOOL SetProtParam(BYTE* pBuf,int nLen);//分配协议库的参数内存，只能调用一次

	BYTE* GetProtParam(int & nLen);//调用协议库参数
	BYTE* GetGVarParam(int & nLen);
	BOOL WriteProtParam(BYTE* pBuf,int nLen);//修改协议库的参数值；
	BOOL WriteGVarParam(BYTE* pBuf,int nLen);//修改全局变量参数;
	
	void EmptyGVarBuf();
	void EmptyProtBuf();
	int	 GetUsedTabCount();
	void InitUsedTab(int nSize);
	UsedTab* GetUsedTab(int nIndex);
	BOOL AddUsedTab(CString strTabName,TABLE_INFO* pTI=NULL);//增加使用到的表；调用完后要自己释放pTI;
	int CopyFromSysTab(CString strSysTabName,TABLE_INFO* pTargetTI);//拷贝名为strSysTabName的表到目标表pTargetTI,
																	//如果返回0表示成功
																	//1:pTargetTI为空，2：没有找到指定系统表;

	int  GetSysTabSize(){
#ifdef WIN32
		return m_aSysTab.GetSize();
#else
		return m_aSysTab.size();
#endif
	}
	void EmptySysTab();
	void FillSysTab(TABLE_INFO* pTab);
/******************************************************************
	在系统配置增加设备实例时，调用该函数，系统自动将通道信息保存到
	SysDevDb->Chanel_Info_TABNAME中，其他应用程序可以通过该表获得
	通道的运行状态
	void* pMemMgr CManageDevMem类型
*******************************************************************/
	BOOL AddChannelInfoToDb(void* pMemMgr=NULL);//保存通道信息到数据库2017.3.5 by zph

	BOOL AddChannelInfoToDb(CRtDbMgr* pRtDbMgr);//保存通道信息到数据库2017.3.5 by zph
	BOOL DelChannelInfoFromDb(CRtDbMgr* pRtDbMgr);//保存通道信息到数据库2017.3.5 by zph

/******************************************************************
	更新通道信息保存到
	SysDevDb->Chanel_Info_TABNAME中，其他应用程序可以通过该接口更新
	通道的运行状态
	参数void* pChannelInfo 类型为Chanel_Info 该结构在memtabstruct.h
	中定义
	void* pMemMgr CManageDevMem类型
*******************************************************************/

	BOOL UpdateChannelInfo(void* pChannelInfo,void* pMemMgr=NULL);//保存通道信息到数据库2017.3.5 by zph
	BOOL UpdateChannelInfo(void* pChannelInfo,CRtDbMgr* pMemMgr);//保存通道信息到数据库2017.3.5 by zph
	BOOL UpdateChannelInfo(void* pChannelInfo,CString strName,CRtDbMgr* pMemMgr);//保存通道信息到数据库2017.3.5 by zph
	CRtDbMgr* m_pRtDbMgr;
private:
	BYTE*	m_pProtParam;//保存协议库的参数;
	int		m_nParamLen;//参数长度
	
	BYTE*    m_pGVarParam;//保存协议中所有全局变量
	int		m_nGVarLen;//全局变量长度
#ifdef WIN32
	CArray<UsedTab*,UsedTab*> m_aUsedTabList;//该类型设备使用到的数据表列表；需要在驱动中FillUsedTab函数中实现
	CArray<TABLE_INFO*,TABLE_INFO*> m_aSysTab;//系统表;
#else
	CPtrArray m_aUsedTabList;
	CPtrArray m_aSysTab;
#endif

#ifndef WIN32
//for linux 设备实例的线程
public:
	bool m_bReadyExit;
	//驱动
	CProInterface m_proInterface;
	//驱动协议处理线程
	pthread_t  * m_hThread;
	//驱动协议中发送线程
	pthread_t * m_hSendThread;
	//初始化，Comm实例，装载函数
	bool Init();
	//创建Comm实例
	bool InitComm();
	bool OpenComm();
	bool LoadFun();
	bool StartCommThread();
	bool WriteChanelState(BYTE bState);
#endif
};

class CDevCfgMgr
{
public:
	CDevCfgMgr();
	~CDevCfgMgr();
public:
	CPtrArray	m_aList;
	int			m_nType;
	CString		m_strFileName;
	CString		m_strDllPath;
public:
	void Clear();
#ifdef WIN32
	BOOL LoadOneDev();
//	BOOL SaveOneDev();
	BOOL LoadAllDev();
#endif
//	BOOL SaveAllDev();
//	BOOL LoadAllInst();
//	BOOL SaveAllInst();

	BOOL LoadAllnstXml();
	BOOL SaveAllInstXml();

	void AddDevCfg(CDevCfg* pDC);
	void RemoveDC(CDevCfg* pDC);
	CDevCfg* FindDevCfg(CString strInstName);
};

extern BOOL LoadAllIoDev();
extern BOOL LoadAllDataDev();
extern BOOL LoadAllInstIo(CString strPrjPath);
extern BOOL LoadAllInstData(CString strPrjPath);
extern BOOL SaveAllInstIo(CString strPrjPath);
extern BOOL SaveAllInstData(CString strPrjPath);

extern CDevCfgMgr gIoDevList;//所有采集设备类型列表
extern CDevCfgMgr gDataDevList;//所有转发设备类型列表
extern CDevCfgMgr gInstIoList;//所有采集设备实例列表
extern CDevCfgMgr gInstDataList;//所有转发设备实例列表
extern CDevCfgMgr gAllDbList;

#endif // !defined(AFX_DEVCFG_H__1E43576D_98CE_4CFF_9E0F_1934B1A731EC__INCLUDED_)
