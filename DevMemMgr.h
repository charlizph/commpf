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
    2012.09.26:��CManageDevMem��������CreateUpdateChg����������ʵ��
				����ˢ��ʱ֪ͨӦ�ó���
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
	//��ʼ�������ڴ�
	BOOL InitMem();
	BOOL CloseMem();
//���ӹ����ڴ��
	BOOL AddShMem(const char* szDbName,const char * szShMemName,int nMemSize,BOOL bTruncCreate=FALSE,void* pTabInfo=NULL);
	int	GetShMemCount();
	ShMemTab * GetMemByType(int nTabNo);
	ShMemTab * GetMemByIndex(int nIndex);
	BOOL GetTabIndexByName(CString szDbTabName,DbIndex& dbIndex);
//���ӱ�����ΪszVarName���ڴ����������ΪnTabNo���ڴ��
	long AddMemVar(DbIndex dbIndex,int nVarMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);
//	long AddMemVar(int nTabNo,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);
//	long AddMemVar(const char* szTabName,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);

	BOOL DelMemVar(DbIndex dbIndex);

//����dbindex
	ShMemTab* GetShMem(DbIndex & dbIndex);
	BOOL SetMemVarVal(DbIndex dbIndex,void* pData,int & nValLen,BOOL bUpdateTime=FALSE);
	BOOL SetMemVarVal(DbIndex dbIndex,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);

	BOOL GetMemVarVal(DbIndex& dbIndex,void* pData,int & nValLen);
	BOOL GetMemVarVal(DbIndex& dbIndex,VARIANT& var,int & nValLen,ValueHeader* pVH=NULL);
	
	//������ֵת��Ϊ�ַ�������
	CString GetMemVarVal(DbIndex& dbIndex, int & nVarType,int & nValLen);
//	CString GetMemVarValByIndex(int nTabNo,int nIndex);
//	CString GetMemVarVal(int nTabNo,const char * szVarName);

	int GetValLen(int nTabNo,const char * szVarName);

	int  GetMemBlockSize(DbIndex dbIndex);
	int	 ReadMemBlock(const char* szTabName,void* pDataBuf, int nBufLen,int nWritePtr,int nStartPos);//���ض�ȡ����
	int  WriteMemBlock(const char* szTabName,void* pDataBuf,int nBufLen,int nWritePtr);//����ָ��λ��
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
	int	m_nCurWritePtr;//��ǰд����ָ��λ��;
	int m_nCurReadPtr;//��ǰд����ָ��λ��;

	void SetDataChangedFun(funMemDataChanged funMemDC,void* pFunParam);
public:
	void InitAdr();
	char	m_szDevName[VAR_NAME_LENGTH];//�豸����
	ShMemArray m_MemArray;//�豸�����ڴ��б�
	BOOL	m_bFirst;
	BOOL m_bAuto;
	BOOL m_bSystem;//�Ƿ�Ϊϵͳ��;
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

//ע����̴��ھ��
struct REGPROC
{
	char m_szClassName[128];
	char m_szWindowName[128];
	char m_szProcName[64];
	long lWndAdr;//������ָ���ַ(long)pWnd;
};
//#define YtMem_TABNAME 	 _T("YtMem")
//============ ң���ڴ�� ��ṹ ================
#ifndef YtMem_TABNAME
#ifdef WIN32
#define YtMem_TABNAME 	 _T("YtMem")
#else
#define YtMem_TABNAME 	 "YtMem"
#endif
struct YtMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	float 	SetVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	BOOL 	Comand;	 //�������� �ϵ�:0/�µ�:1/��ͣ:2/
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};
#endif


//============ ң���ڴ�� ��ṹ ================
#ifndef YkMem_TABNAME
#ifdef WIN32
#define YkMem_TABNAME 	 _T("YkMem")
#else
#define YkMem_TABNAME 	 "YkMem"
#endif

struct YkMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	BYTE 	CtrlVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	BYTE 	Comand;	 //�������� ң��Ԥѡ:1/ң��ִ��:2/ң��ȡ��:3/
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};
#endif

//============ ͨ����Ϣ ��ṹ ================
#ifndef Chanel_Info_TABNAME
#ifdef WIN32
#define Chanel_Info_TABNAME 	 _T("Chanel_Info")
#else
#define Chanel_Info_TABNAME 	 "Chanel_Info"
#endif
struct Chanel_Info { 
	BYTE 	Desc[128];	 //���� 
	BYTE 	ComState;	 //ͨѶ״̬ �Ͽ�:0/����:1/
	int 	ComType;	 //ͨѶ���� ����ͨѶ:1/Tcp�ͻ���:2/Tcp�����:3/Udp�ͻ���:4/Udp�����:5/�������:6/���ڼ���:7/DDE Server:8/DDE Client:9/
	unsigned int 	RecvLen;	 //�����ֽ� 
	unsigned int 	SendLen;	 //�����ֽ� 
	int 	Port;	 //�˿� 
	int 	RecvInterval;	 //���ݽ�������(ms) 
	int 	SendInterval;	 //���ݷ�������(ms) 
	int 	RecvTimeOut;	 //���ݽ��ճ�ʱ(s) 
	int 	WriteRetryTimes;	 //����ʧ�����Դ��� 
	int 	BaudRate;	 //������ 
	BYTE 	Parity;	 //��żУ�� ��:0/żУ��:1/��У��:2/
	int 	DataBit;	 //����λ 
	BYTE 	StopBit;	 //ֹͣλ 1:0/1.5:1/2:2/
	BYTE 	IpAdr[16];	 //Ip��ַ 
	int 	Options;	 //Tcp���� 
	int 	Family;	 //Tcp_Family 
	int 	MaxConnect;	 //tcpServer��������� 
	BYTE 	BroadAdr[16];	 //udp�㲥��ַ 
	BYTE 	TargetAdr[16];	 //udpĿ���ַ 
	int 	TargetPort;	 //udpĿ��˿� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif

//============ ʵʱ�澯�� ��ṹ ================

#ifndef RtAlarm_TABNAME
#ifdef WIN32
#define RtAlarm_TABNAME 	 _T("RtAlarm")
#else
#define RtAlarm_TABNAME 	 "RtAlarm"
#endif

struct RtAlarm { 
	short 	m_warnType;	 //�澯���� 
	short 	m_warnSubType;	 //�澯������ 
	short 	m_warnDetail;	 //�澯������ϸ���� 
	BYTE 	m_objName[64];	 //�����澯�������� 
	short 	m_dbNum;	 //��� 
	short 	m_tableNum;	 //��� 
	short 	m_ptNum;	 //��� 
	short 	m_ctrlVal;	 //����ֵ(yk(0x33�ط�0xCC�غ�),����(0x33�ط�0xCC�غ�)) 
	BYTE 	eventsgflag;	 //=0һ�����=1�¹� 
	BYTE 	m_szVal[16];	 //�澯ֵ 
	float 	m_fVal;	 //m_fVal 
	long 	m_warnTime_L;	 //�澯ʱ��(������) 
	BYTE 	m_warnTime[32];	 //�澯ʱ��(�ַ�) 
	BYTE 	m_warnStr[128];	 //�澯���� 
	BYTE 	m_wavFile[32];	 //�����ļ� 
};
#endif

#define PROC_NONE 0
//�Ѿ�ִ��
#define PROC_EXEC 1
//���ؽ��
#define PROC_RETURN 2

//#include "memtabstruct.h"
/*
//ϵͳ����
struct YtMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	float 	SetVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};



//============ ң���ڴ�� ��ṹ ================

//#define YkMem_TABNAME 	 _T("YkMem")

struct YkMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	BYTE 	CtrlVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	BYTE 	Comand;	 //�������� ң��Ԥѡ:1/ң��ִ��:2/ң��ȡ��:3/
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
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
	//��ʼ�������ڴ�
	static BOOL InitMem();
	static BOOL CloseMem();
	static BOOL ExitMem();//�˳�ʵʱ��
/******************************** AddDbMem()�ӿ� **************************************/
/* ����˵���������ڴ��
/* ����˵����
/*			���������szDbName ���ݿ�����
					  �������ͣ��ַ���
/*			���ֵ��  ����BOOL���ͣ�TRUE:���ӳɹ���FALSE:����ʧ��
/*
/********************************************************************************************/
	static BOOL AddDbMem(const char* szDbName);
/******************************** AddShMem()�ӿ� **************************************/
/* ����˵�����������ݱ��ڴ��
/* ����˵����
/*			���������szDbName ���ݿ�����
					  �������ͣ��ַ���
/*			���������szShMemName ���ݱ�����
					  �������ͣ��ַ���
/*			���������nMemSize ���ݱ��С
					  �������ͣ�����
/*			���������nVarType ���ݱ�����ݼ�¼����
					  �������ͣ�VARIANT
/*			���������pTabInfo ���ݱ�������Ľṹ��
					  �������ͣ�void*
/*			���ֵ��  ����BOOL���ͣ�TRUE:���ӳɹ���FALSE:����ʧ��
/*
/********************************************************************************************/
	static BOOL AddShMem(const char* szDbName,const char * szShMemName,int nMemSize,BOOL bTruncCreate=FALSE,void* pTabInfo=NULL);
/******************************** AddMemVar()�ӿ� **************************************/
/* ����˵�����������ݱ������ڴ��
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ����Ҫָ�����ݿ�Ŀ�ͱ�����ƻ�������
					  �������ͣ�DbIndex
/*			���������nVarMemSize ���ݱ���ռ���ڴ�ռ��С
					  �������ͣ�����
/*			���������nMemSize ���ݱ�������
					  �������ͣ�VARIANT
/*			���������pData ���ݼ�¼��ʼֵ
					  �������ͣ�void*
/*			���ֵ��  ����long���ͣ�<0������ʧ�ܣ�>-1��ʾ�ڴ�������ڴ��е�����
/*
/********************************************************************************************/

	static long AddMemVar(DbIndex dbIndex,int nVarMemSize,int nType=VT_R4,void * pData=NULL,BOOL bSetAttr=FALSE);

//	static long AddMemVar(const char* szDevName,int nTabNo,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL);
//	static long AddMemVar(const char* szDevName,const char* szTabName,const char * szVarName,int nMemSize,int nType=VT_R4,void * pData=NULL);
/******************************** DelMemVar()�ӿ� **************************************/
/* ����˵����ɾ�����ݱ���
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ����Ҫָ�����ݿ�Ŀ�ͱ�������ƻ�������
					  �������ͣ�DbIndex
/*			���ֵ��  ����BOOL���ͣ�TRUE:ɾ���ɹ���FALSE:ɾ��ʧ��
/*
/********************************************************************************************/
	static BOOL DelMemVar(DbIndex dbIndex);

/******************************** GetShMemCount()�ӿ� **************************************/
/* ����˵��������ڴ���ĳ���ݿ���������ı����
/* ����˵����
/*			���������szDevName ���ݿ�����
					  �������ͣ��ַ���
/*			���ֵ��  ����int���ͣ������
/*
/********************************************************************************************/
	static int	GetShMemCount(const char* szDevName);
/******************************** GetShMemCount()�ӿ� **************************************/
/* ����˵��������ڴ���ĳ���ݿ���������ı����
/* ����˵����
/*			���������nDbIndex ���ݿ�������
					  �������ͣ�����
/*			���ֵ��  ����int���ͣ������
/*
/********************************************************************************************/
	static int	GetShMemCount(int nDbIndex);
/******************************** GetShDevMemCount()�ӿ� **************************************/
/* ����˵��������ڴ����ܵ����ݿ����
/* ����˵����
/*			���ֵ��  ����int���ͣ����ݿ����
/*
/********************************************************************************************/
	static int	GetShDevMemCount();

/******************************** GetShDevMemCount()�ӿ� **************************************/
/* ����˵�����������ݿ���_���� ����ñ��dbindex
/* ����˵����szDbTabName �����ݿ����ͱ�����ɣ��м���_����
			dbIndex�����صı��������Ϣ
/*			���ֵ��  ����BOOL���ͣ��ɹ����
/*
/********************************************************************************************/
	static BOOL GetTabIndexByName(CString szDbTabName,DbIndex& dbIndex);

	static CMemMgr * GetMemByType(int nTabNo);
	static CMemMgr * GetMemByIndex(int nIndex);

	//����dbIndex������ݿ�(by db's index or db's name)
	static CMemMgr* GetMemMgr(DbIndex & dbIndex);

/******************************** SetMemVarVal()�ӿ� **************************************/
/* ����˵�������ڴ����ݱ����ĸ�ֵ
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ���������dbIndex.nFldNo���Ϊ-1 ��ʾ��
					  ������¼��ֵ��pData��Ӧһ����¼�Ľṹ��nValLenΪ��¼�Ĵ�С
					  �������ͣ�DbIndex
/*			���������pData ���ݱ�����ֵ
					  �������ͣ�void*
/*			���������var ���ݱ�����ֵ
					  �������ͣ�VARIANT
/*			���������nValLen ���ݱ���ֵ�ĳ���
					  �������ͣ�int
/*			���������pData ���ݼ�¼��ʼֵ
					  �������ͣ�void*
/*			���ֵ��  ����BOOL���ͣ�TRUE:��ֵ�ɹ���FALSE:��ֵʧ��
/*
/********************************************************************************************/
//����dbindex,����ʱ����Ҫ����dbIndex.nAcesType 
	static BOOL SetMemVarVal(DbIndex dbIndex,void* pData,int & nValLen,BOOL bUpdateTime=FALSE);
	static BOOL SetMemVarVal(DbIndex dbIndex,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);
	static BOOL SetMemVarVal(COneRecData* pORD,int nFldIndex,CString strVal,BOOL bUpdateTime=FALSE);//nFldIndex �������̶��ֶ�

/******************************** GetMemVarVal()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ�����ֵ
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������
					  �������ͣ�DbIndex
/*			���������pData ���ݱ�����ֵ
					  �������ͣ�void*
/*			���������var ���ݱ�����ֵ
					  �������ͣ�VARIANT
/*			���������nValLen ���ݱ���ֵ�ĳ���
					  �������ͣ�int
/*			���������pData ���ݼ�¼��ʼֵ
					  �������ͣ�void*
/*			���ֵ��  ����BOOL���ͣ�TRUE:ȡֵ�ɹ���FALSE:ȡֵʧ��
/*
/*$$$$$$    �ر�ע�⣺����var��BSTR���͵�ʹ������֮��Ҫ����SysFreeString(var.bstrVal) $$$$$$$
/********************************************************************************************/
	static BOOL GetMemVarVal(DbIndex& dbIndex,void* pData,int & nValLen);
	static BOOL GetMemVarVal(DbIndex& dbIndex,VARIANT& var,int & nValLen,ValueHeader* pVH=NULL);//����var��BSTR���͵�ʹ������֮��Ҫ����SysFreeString(var.bstrVal)
	static int GetValLen(const char* szDevName,int nTabNo,const char * szVarName);

	static CString GetMemVarVal(DbIndex& DbIndex,int & nVarType,int & nValLen);
	static CString GetMemVarVal(COneRecData* pORD,int nFldIndex);//nFldIndex �������̶��ֶ�
/******************************** GetMemVarIndex()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ��������������Ը������ƻ�ȡ������Ҳ���Ը���������ȡ���ƣ������dbIndex����
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL GetMemVarIndex(DbIndex & dbIndex);
/******************************** GetMemIndex()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݿ������������Ը������ƻ�ȡ������Ҳ���Ը���������ȡ���ƣ������dbIndex����
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL GetMemIndex(DbIndex & dbIndex);
//	static long GetMemVarAdr(DbIndex dbIndex);
//	static long GetMemVarAdr(const char* szDevName,int nTabNo,const char * szVarName);
//	static long GetMemVarAdr(const char* szDevName,const char* szTabName,const char * szVarName);

//	static int	GetMemCurIndex(const char* szDevName,int nTabNo);

/******************************** GetMemVarInfo()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ�������Ϣ��
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���������VHInfo��������Ϣָ�룬���ձ�����Ϣ
					  �������ͣ�ValueHeader*
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL  GetMemVarInfo(DbIndex& dbIndex, ValueHeader* VHInfo);
/******************************** SetMemVarStatus()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ�������Ϣ��
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���������status��������ң�Ÿ澯״̬��ң���Ƿ�Խ�޵� �μ�MemMacro.h�ж����status
					  �������ͣ�int
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL  SetMemVarStatus(DbIndex dbIndex,int nStatus);

/******************************** SetMemVarFlag()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ�������Ϣ��
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���������nFlags������״̬��־���Ƿ�Ҫ�澯���Ƿ����ʷ��� �μ�MemMacro.h�ж����Flags
					  �������ͣ�ValueHeader*
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL	 SetMemVarFlag(DbIndex dbIndex,int nFlags);
/******************************** SetMemVarAttr()�ӿ� **************************************/
/* ����˵������ȡ�ڴ����ݱ�������Ϣ��
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���������bRODChg (λ˳�� 7 6 5 4 3 2 1 0 )
                           dbIndex ��Ӧ���������԰���ֻ�����ԣ��仯����
						   bRODChg �����λ�����仯�����������Ϊ1��ʾ�仯������Ϊ0��ʾ�仯��ʱ��������Ӧ�ó���
						   bRODChg �ĵ�2λ����ֻ�����ԣ�1��ʾ����ֻ����0��ʾ��Ϊֻ�� 
					  �������ͣ�BOOL
/*			���ֵ��  ����BOOL���ͣ�TRUE:�ɹ���FALSE:ʧ��
/*
/********************************************************************************************/
	static BOOL SetMemVarAttr(DbIndex dbIndex,int bRODChg);
	static BOOL GetMemVarAttr(DbIndex dbIndex,int &bRODChg);
/******************************** GetMemVarCount()�ӿ� **************************************/
/* ����˵������ȡָ�����ݿ��ĳ�����ڴ����ݱ����ĸ�����
/* ����˵����
/*			���������dbIndex ���ݿ⣬����Ϣ������ʱ����Ҫ����dbIndex.nAcesType
					  ��Ӧ��ָ�����ݿ�Ŀ⣬��͵�����ƻ�������������Ҳ����dbIndex��
					  �������ͣ�DbIndex
/*			���ֵ��  ����int���ͣ��ڴ��������
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
//�ڴ���������
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

//end �ڴ�����

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

//�ڴ����ݱ仯֪ͨ����
//**************** SetDataChangedFun �ڴ����ݱ仯֪ͨ�ص�����*****************/
// pParam�������ߴ���Ĳ���������һ��CWnd* ��������ָ�� ͨ��SetDataChangedFun����
// dbIndex���仯�����ݵ���Ϣ
// var:		�仯���ݵ�ֵ
	static BOOL SetBufTime(DbIndex dbIndex,int nBufTime);
	static void SetDataChangedFun(funMemDataChanged funMemDC,void* pFunParam);
	static BOOL RegProcWnd(RegWndInfo rwi);
	static BOOL UnRegProcWnd(RegWndInfo rwi);
	static BOOL IsRightPrj();
	static CString GetMemPrjPath();
	static void StartGetMemData(CRtDbMgr* pRtDbMgr);

/*�����仯���ݴ洢���ñ��淢���仯�����ݵ�����(��Ӧ�ṹChDIndex)��Ӧ�ó�����Ҫ���øú���*/
	static BOOL CreateDChgDb(const char* szDbName,BOOL bFirst);
	static BOOL CreateImpDChgDb(const char* szDbName,BOOL bFirst);
	static BOOL CreateRtAlarmDb(BOOL bFirst);

	/* WriteProcStat��澯����д���������/�˳���Ϣ����ÿ�����̵��������˳���ʱ����øú���
	BOOL bStat 0:�����˳�
			   1:��������
	*/
	static BOOL WriteProcStat(BOOL bStat,RtAlarm& ra);
public:
	/*��ң���ڴ����д��ң����Ϣ������������ֻ��һ��ң���ڴ��ϵͳ����ʱ�Զ���ȡң���ڴ�����ڵĿ���
	������������m_szYtDbName��ң������ΪYtMem
	���룺pYtMem��д���ң����Ϣ
	����ֵ��д��ɹ����
	*/
	static BOOL WriteYtMem(YtMem* pYtMem);
	static BOOL WriteYtMem(char* szDbName,YtMem* pYtMem);
	/*��ң���ڴ���ж�ȡң����Ϣ
	���룺pYtMem������ң����Ϣ��ָ��
	����ֵ����ȡ�ɹ����
	*/
	static BOOL GetYtMem(YtMem* pYtMem);//���ϵͳң��
	static BOOL GetYtMem(char* szDbName,YtMem* pYtMem);
	static void GetYtDbName(char* szYtName,int& nNameLen);

	/*��ң���ڴ����д��ң����Ϣ������������ֻ��һ��ң���ڴ��ϵͳ����ʱ�Զ���ȡң���ڴ�����ڵĿ���
	������������m_szYkDbName��ң������ΪYkMem
	���룺pYkMem��д���ң����Ϣ
	����ֵ��д��ɹ����
	*/
	static BOOL WriteYkMem(YkMem* pYkMem);
	static BOOL WriteYkMem(char* szDbName,YkMem* pYkMem);
	/*��ң���ڴ���ж�ȡң����Ϣ
	���룺pYkMem������ң����Ϣ��ָ��
	����ֵ����ȡ�ɹ����
	*/
	static BOOL GetYkMem(YkMem* pYkMem);
	static BOOL GetYkMem(char* szYkName,YkMem* pYkMem);
	static void GetYkDbName(char* szYkName,int & nNameLen);
	/*��ʼ������ͨѶ״̬
	���룺BOOL bStatus ͨ����ͨѶ״̬
	����ֵ����ȡ�ɹ���� 1-�ɹ���0-ʧ��
	*/
	static BOOL InitChannelStatus(BOOL bStatus);
	/*��ʼ��ͨѶ״̬
	���룺DbIndex dbIndex;ֻ��Ҫָ��szPtName ����nPtNo��DbName ��TabNameϵͳָ��
		BOOL bStatus ͨ����ͨѶ״̬
	����ֵ����ȡ�ɹ���� 1-�ɹ���0-ʧ��
	*/
	static BOOL InitChannelStatus(DbIndex & dbIndex,BOOL bStatus);
	/*��ȡͨѶ״̬
	���룺DbIndex dbIndex;ֻ��Ҫָ��szPtName ����nPtNo��DbName ��TabNameϵͳָ��
		BOOL & bStatus ����ͨ����ͨѶ״̬
	����ֵ����ȡ�ɹ���� 1-�ɹ���0-ʧ��
	*/
	static BOOL GetChannelStatus(DbIndex & dbIndex, BOOL & bStatus);
	static BOOL GetChannelInfo(DbIndex & dbIndex, Chanel_Info* pCi);

	/*дͨѶ��Ϣ
	���룺DbIndex dbIndex;ֻ��Ҫָ��szPtName ����nPtNo��DbName ��TabNameϵͳָ��
		BOOL & bStatus ����ͨ����ͨѶ״̬
	����ֵ����ȡ�ɹ���� 1-�ɹ���0-ʧ��
	*/
	static BOOL SetChannelInfo(DbIndex & dbIndex, Chanel_Info* pCi);

	/*��ȡ/����ϵͳ������״̬
	���룺nStatus ����״̬�����״̬
		
	����ֵ����ȡ�ɹ���� 1-�ɹ���0-ʧ��
	*/
	static BOOL GetSrvStatus(int & nStatus);
	static BOOL SetSrvStatus(int nStatus);

	/*********GetMemInfo(BYTE* pRecv,int nRecvBufLen)**********
	
	  ����������ݿ⣬����Ϣ����������ͬ�����ж��Ƿ�Ϊ��ͬ������
	  ���룺pRecv�����߷����ڴ棬���ڽ����ڴ���Ϣ
	        nRecvBufLen �����߷�����ڴ��С
	  ����ֵ�����ͣ��ڴ���Ϣ��С��0��ʾʧ��
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
	static METERED_SECTION * m_pInitSync; //�����ڴ��ʼ��ͬ���ź�
#else
	static pthread_mutex_t * m_pInitSync; //�����ڴ��ʼ��ͬ���ź�
#endif
private://ң�أ�ң�� ϵͳ��ֻ�ܶ���һ��ң�ر��ң����
	static char m_szYtDbName[64];
	static char m_szYkDbName[64];
};

#endif // !defined(AFX_DEVMEMMGR_H__C6D61D18_30FB_45AB_806B_1450F7FC11F1__INCLUDED_)
