/********************************************************************************************
* 功能说明      : 共享内存类，将CreateFileMapping进行一层封装
*
* 作  者        : 张培洪
*              
* 创建日期      : 2006年10月17日
* 版本号        : 1.0.1
*********************************************************************************************/
#ifndef __MEMMAPFILE_H__
#define __MEMMAPFILE_H__
 
#ifdef WIN32
	#if _MSC_VER > 1000
	#pragma once
	#endif // _MSC_VER > 1000
	#pragma warning( disable: 4251 )

// SharedMemory.h : header file
//
	#include "meteredsection.h"

	#include <afxmt.h>
	#include <afxtempl.h>


#else

	#include "cstring.h"
	#include "variant.h"

#endif
//#include "sh61850memext.h"
#include "RtDbInfo.h"

#include "rtdbext.h"

//定义数据变化通知消息id
extern int SHMEM_EXT_DATA MEM_DATACHANGED ;

//typedef void (*PINITMEMORY)(CSharedMemory *);

/////////////////////////////////////////////////////////////////////////////
// 共享内存组织形式
//DWORD		...		变量总数
//DWORD		...		总的内存大小
//ValueHeader[0]
//value 0
//ValueHeader[1]
//value 1
// .....
//ValueHeader[n]
//value n

//**************** funMemDataChanged 内存数据变化通知回调函数*****************/
// pParam：调用者传入的参数可以是一个CWnd* 或者其他指针 通过SetDataChangedFun设置
// dbIndex：变化的数据的信息
// var:		变化数据的值
typedef void (*funMemDataChanged)(DbIndex  dbIndex,VARIANT var,void* pParam);

/////////////////////////////////////////////////////////////////////////////
// CSharedMemory class
class SHMEM_EXT_CLASS CSharedMemory //: public CObject
{
//	DECLARE_DYNAMIC(CSharedMemory)
public:
	CSharedMemory(const char *szName, DWORD dwSize = DEF_SHARED_SIZE, BOOL bFirst=TRUE,BOOL bTruncCreate=FALSE,BOOL bAuto=TRUE,void * pTabInfo=NULL);//, PINITMEMORY InitMemoryProcedure = NULL,LPSECURITY_ATTRIBUTES lpsaAttributes = NULL
	~CSharedMemory();
public:
	int  m_nBufTime;//传送变化数据缓存时间 单位ms

	BOOL m_bTruncCreate;
	BOOL m_bCircle;
#ifdef WIN32
//	HANDLE LoadBakDb(const char *szName,HANDLE & hmap,int size);
	BOOL LoadDb(const char *szName,HANDLE & hmap,int size);
#else
//	BOOL LoadBakDb(const char *szName,int & hmap,int size);
	BOOL LoadDb(const char *szName,int size);
#endif
	BOOL SaveBakDb();
	BOOL SaveDb();

	CString GetMemName(void);
#ifdef WIN32
	BOOL SetSdMem(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor);
	BOOL GetSdMem(SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded);
	BOOL SetSdSem(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor);
	BOOL GetSdSem(SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded);
	BOOL SetSa(LPSECURITY_ATTRIBUTES lpsaAttributes);
#endif
	long AddValue(DbIndex dbIndex, DWORD size, int nVarType=0, void *pDefaultData = NULL,BOOL bSetAttr=FALSE);
//	BOOL AddDwordValue(const char *szName, DWORD dwDefault = 0);
	BOOL DeleteValue(DbIndex dbIndex);

	BOOL ExistValue(const char *szName);
	BOOL IsCreated(void);

	DWORD GetVariablesCount(void);
	BOOL GetValueInfo(DWORD dwIndex, ValueHeader *pVarInfo);
	BOOL GetValueInfo(DbIndex& dbIndex, ValueHeader *pVarInfo);
	BOOL GetValueInfo(const char* szName, ValueHeader *pVarInfo);
	BOOL SetMemVarAttr(DbIndex dbIndex,int bRODChg);
	BOOL GetMemVarAttr(DbIndex dbIndex,int& bRODChg);

	BOOL SetStatus(DbIndex dbIndex, int nStatus);
	BOOL SetFlag(DbIndex dbIndex, int nFlag);

	BOOL SetData(LPBYTE pData,int nIndexNo,int nFieldNo,ValueHeader* vh,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);
	//getdata 需要指定var.vt的值
	BOOL GetData(LPBYTE pData,int nFieldNo,ValueHeader* vh,VARIANT& var,int & nValLen);
	CString GetData(LPBYTE pData,int nFieldNo,ValueHeader* vh,int & nVarType,int & nValLen);

	BOOL SetValueByAdr(unsigned long lValAdr,int nIndexNo,int nFieldNo,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);
	BOOL SetValueByIndex(int nIndex,int nFieldNo,VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);
	BOOL SetValueByName(const char *szName,int nFieldNo, VARIANT var,int & nValLen,BOOL bUpdateTime=FALSE);

	BOOL SetValueByAdr(unsigned long lValAdr,int nFieldNo,void* bData,DWORD dwLength,BOOL bUpdateTime=FALSE);
	BOOL SetValueByIndex(int nIndex,int nFieldNo,void* bData,DWORD dwLength,BOOL bUpdateTime=FALSE);
	BOOL SetValueByName(const char *szName,int nFieldNo, void *bData, DWORD dwLength,BOOL bUpdateTime=FALSE);

	BOOL GetValueByAdr(unsigned long lValAdr,int nFieldNo, VARIANT& var,int & nValLen);
	BOOL GetValueByIndex(DbIndex& DbIndex, VARIANT& var,int & nValLen);
	BOOL GetValueByName(DbIndex& dbIndex, VARIANT& var,int & nValLen);

	BOOL GetValueByAdr(unsigned long lValAdr,int nFieldNo, void* bData,LPDWORD dwLength);
	BOOL GetValueByIndex(DbIndex& dbIndex, void* bData,LPDWORD dwLength);
	BOOL GetValueByName(DbIndex& DbIndex, void *bData, LPDWORD dwLength);


	int	 ReadMemBlock(int nIndex,void* pDataBuf, int nBufLen,int nWritePtr,int nTotalLen);
	int  WriteMemBlock(int nIndex,void* pDataBuf,int nBufLen,int nWritePtr);
	int  GetMemBlockSize(){return m_dwMemSize-2*sizeof(DWORD)-sizeof(ValueHeader);}
	int  GetBlockRecSize(){return m_nRecSize;}
	int  GetBlockRecNum(){return m_nRecNum;}
	BOOL GetValueByDbInd(DbIndex& dbIndex ,void* pData,int & nValLen);
	BOOL GetValueByDbInd(DbIndex& dbIndex,VARIANT& var,int & nValLen,ValueHeader* pVH=NULL);
	CString GetValueByDbInd(DbIndex& dbIndex, int & nVarType,int & nValLen);

	BOOL SetValueByDbInd(DbIndex dbIndex,void* pData,int& nValLen,BOOL bUpdateTime=FALSE);
	BOOL SetValueByDbInd(DbIndex dbIndex,VARIANT var,int& nValLen,BOOL bUpdateTime=FALSE);

//	long GetVarIndex(const char* szName);
	BOOL GetVarIndex(DbIndex & dbIndex);
//	long GetVarAdr(DbIndex dbIndex);
//	long GetVarIndex(DbIndex dbIndex);

//	BOOL SetDwordValue(const char *szName, DWORD dwVal);
//	DWORD GetDwordValue(const char *szName, DWORD dwDefVal = -1);

	void *GetPointer(const char *szName);

	DWORD WaitForMemChange(DWORD dwMilliseconds = INFINITE);
	DWORD WaitForValueChange(const char *szName, DWORD dwMilliseconds = INFINITE);
#ifdef WIN32
	DWORD WaitForMultipleValuesChanges(CStringArray &str, BOOL bWaitForAll = TRUE, DWORD dwMilliseconds = INFINITE);
#endif
	BOOL InterlockedIncrement(const char *szName, LPLONG plNewVal = NULL);
	BOOL InterlockedDecrement(const char *szName, LPLONG plNewVal = NULL);
	BOOL InterlockedExchange(const char *szTargetName, LONG lNewVal, LPLONG plPrevValue = NULL);
	BOOL InterlockedTestExchange(const char *szTargetName, LONG lOldValue, LONG lNewValue, LPLONG plPrevValue = NULL);
	BOOL InterlockedCompareExchange(const char *szTargetName, LONG lExchange, LONG lComperand, LPLONG plIntiVal = NULL);
	BOOL InterlockedExchangeAdd(const char *szTargetName, LONG lIncrement, LPLONG plIntiVal = NULL);

	BOOL Write(BYTE *pbData, DWORD dwLength, DWORD dwOffset = 0);
	BOOL Read(BYTE *pbData, DWORD dwLength, DWORD dwOffset = 0);
	BOOL ResetMem();
#ifdef _DEBUG
	virtual void AssertValid(void);
	virtual void Dump(CDumpContext & dc);
#endif

	DWORD GetLastError(void);
	BOOL AmIFirst(void);
	void SetFirst(BOOL bFirst);
	BOOL IsAuto();
	void SetAuto(BOOL bAuto);
	void InitAdr();

	void SetReadPtr(int nReadPtr);
//	void SetWritePtr(int nWritePtr);
	int	 GetReadPtr();
//	int  GetWritePtr();
	void SetTabInfo(TABLE_INFO* pTabInfo);
	void SetDataChangedFun(funMemDataChanged fMemDataChanged,void* pFunParam);

	const BYTE* GetMemBuffer();
	DWORD GetMemSize(void);
	BOOL  SetMemBuffer(int nStartPos,BYTE* pBuf,int nBufLen);
	CString m_strDbName;
	CString m_strTabName;
	DbIndex m_CurSetInd;
//	SYSTEMTIME	m_lLastST;//最后发送变化数据的时间
	BOOL	m_bSended;
	TABLE_INFO* GetTabInfo(){return m_pTabInfo;}
	void SetRecLenIsChg(BOOL bChg){m_bRecLenIsChg=bChg;}
	BOOL GetRecLenIsChg(){return m_bRecLenIsChg;}
protected:
	funMemDataChanged m_fMemDataChanged;
	void*	m_pFunParam;
	TABLE_INFO* m_pTabInfo;
	void SetLastError(DWORD dwErrCode);
	BOOL CreateSa(void);
	BOOL FindValue(const char *wszName,LPBYTE *pData, ValueHeader **pTmp,int &nIndex);
	WCHAR *AllocateUnicodeStr(const char *szStr);

	char m_CsName[2*VAR_NAME_LENGTH+1];			//共享内存名称

	DWORD m_dwLastError;		

//	CSemaphore *m_pSync;		//共享内存同步信号
//	CSingleLock *m_pLock;		
#ifdef WIN32
	METERED_SECTION * m_pSync; //共享内存同步信号
	METERED_SECTION * m_pBlockSync; //共享内存块同步信号
#else
	pthread_mutex_t * m_pSync;
#endif
	BOOL m_bFirst;				
	BOOL m_bAutoLoadSave;
	BOOL m_bCreated;			

	DWORD m_dwMemSize;			

	LPBYTE m_lpView;			//共享内存起始位置
	HANDLE m_hFileMap;			//共享内存局并
	int m_hFileHandle;			//共享文件打开句柄
//	HANDLE m_hFile;//文件句柄
	BOOL m_bSecPres;			
#ifdef WIN32
	UCHAR m_SdEvent[SECURITY_DESCRIPTOR_MIN_LENGTH];
	SECURITY_ATTRIBUTES m_SecAtr;
	SID *m_pLogSid;
	SID *m_pSysSid;
	ACL *m_pNewAcl;
	SID *m_pEvrSid;
	CArray<unsigned long,unsigned long> m_lAdrList;
#else
	vector<unsigned long> m_lAdrList;
#endif
//	CArray<DbIndex* ,DbIndex*> m_aBufChgIndex;//缓存变化数据
	CPtrArray m_aBufChgIndex;
#ifdef WIN32
	SYSTEMTIME m_stStart;
	SYSTEMTIME m_stEnd;
#else
	struct timeval m_stStart;
	struct timeval m_stEnd;
#endif
//	int	m_nCurWritePtr;//当前写操作指针位置;
	int m_nCurReadPtr;//当前写操作指针位置;
	int m_nTotalCount;
	int	m_nRecNum;
	int m_nRecSize;
	int	m_nSglLen;
	BOOL	m_bRecLenIsChg;

	char szAppName[32];
};

/////////////////////////////////////////////////////////////////////////////

#endif //__MEMMAPFILE_H__
