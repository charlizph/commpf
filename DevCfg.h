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
//װ��������̬��Ľӿ�
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
	//�����߳� 
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
	CString m_strDevFType;//�豸������ҵ����ProtCfg.txt����
	CString m_strDevCompany;//�豸������˾����ProtCfg.txt����
	CString m_strDevType;//�豸���ͣ���ProtCfg.txt����
	CString m_strDevName;//�豸���ƣ���ProtCfg.txt����
	CString m_strDevInstName;//�豸ʵ�����ƣ�
	CString m_strDevInstDesc;//ʵ��������;
	CString m_strProName;//�豸���õ�Э������ƣ���ProtCfg.txt����
	BOOL m_bSaveWeb;//�Ƿ����ݱ��浽���ݿ⣬�Թ�web���
//	int		m_nSendInterval;//���ݷ��ͼ�� ����
//	int		m_nRecvInterval;//���ݽ���ɨ���� ����
#ifdef WIN32
	HTREEITEM m_hTreeItem;
	HINSTANCE	m_hDllModule;//��̬���ʵ�����;
#endif
	CString m_strDevCfgFileName;
	CCommParam m_oneParam;
	CBaseComm* m_pComm;//�ɼ�������ʹ�� 
public:
	//��������չ���ֶε�������������������������չ�ֶν��ж�д
	BOOL GetStructData(COneRecData* pORD,LPCSTR szTabName,void* pBaseTab,int nBaseTabSize,void* pExtTab=NULL,int nExtTabSize=0);
//	BOOL GetFldVal(COneRecData* pORD,int nFldNo,CString & strVal);
	BOOL WriteStructData(COneRecData* pORD,LPCSTR szTabName,void* pBaseTab,int nBaseTabSize,void* pExtTab=NULL,int nExtTabSize=0,BOOL bUpdateTime=FALSE);
//	BOOL WriteFldVal(COneRecData* pORD,int nFldNo,CString strVal);
/*
	BOOL ReadIoVal(CString strTabName,int nPtNo, int nFieldNo, CString& strVal);//�ɼ���
	BOOL ReadConvVal(CString strTabName,int nPtNo, int nFieldNo, CString& strVal);//ת����
	BOOL WriteIoVal(CString strTabName,int nPtNo, int nFieldNo, CString strVal);//�ɼ���
	BOOL WriteConvVal(CString strTabName,int nPtNo, int nFieldNo, CString strVal);//ת����
*/	CString m_strFlag;
	BOOL	m_bProItem;
	int		m_nType;
	CPtrArray  m_aRecTabs;//ÿ���豸ͨ���ɼ��õ����������ݱ� ��������ΪCRecArray
//	CPtrArray  m_aConvTabs;//ÿ���豸ͨ��ת���õ����������ݱ� 

	BOOL SetGVarParam(BYTE* pBuf,int nLen);//����ȫ�ֱ��������ڴ棬ֻ�ܵ���һ��
	BOOL SetProtParam(BYTE* pBuf,int nLen);//����Э���Ĳ����ڴ棬ֻ�ܵ���һ��

	BYTE* GetProtParam(int & nLen);//����Э������
	BYTE* GetGVarParam(int & nLen);
	BOOL WriteProtParam(BYTE* pBuf,int nLen);//�޸�Э���Ĳ���ֵ��
	BOOL WriteGVarParam(BYTE* pBuf,int nLen);//�޸�ȫ�ֱ�������;
	
	void EmptyGVarBuf();
	void EmptyProtBuf();
	int	 GetUsedTabCount();
	void InitUsedTab(int nSize);
	UsedTab* GetUsedTab(int nIndex);
	BOOL AddUsedTab(CString strTabName,TABLE_INFO* pTI=NULL);//����ʹ�õ��ı��������Ҫ�Լ��ͷ�pTI;
	int CopyFromSysTab(CString strSysTabName,TABLE_INFO* pTargetTI);//������ΪstrSysTabName�ı�Ŀ���pTargetTI,
																	//�������0��ʾ�ɹ�
																	//1:pTargetTIΪ�գ�2��û���ҵ�ָ��ϵͳ��;

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
	��ϵͳ���������豸ʵ��ʱ�����øú�����ϵͳ�Զ���ͨ����Ϣ���浽
	SysDevDb->Chanel_Info_TABNAME�У�����Ӧ�ó������ͨ���ñ���
	ͨ��������״̬
	void* pMemMgr CManageDevMem����
*******************************************************************/
	BOOL AddChannelInfoToDb(void* pMemMgr=NULL);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph

	BOOL AddChannelInfoToDb(CRtDbMgr* pRtDbMgr);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph
	BOOL DelChannelInfoFromDb(CRtDbMgr* pRtDbMgr);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph

/******************************************************************
	����ͨ����Ϣ���浽
	SysDevDb->Chanel_Info_TABNAME�У�����Ӧ�ó������ͨ���ýӿڸ���
	ͨ��������״̬
	����void* pChannelInfo ����ΪChanel_Info �ýṹ��memtabstruct.h
	�ж���
	void* pMemMgr CManageDevMem����
*******************************************************************/

	BOOL UpdateChannelInfo(void* pChannelInfo,void* pMemMgr=NULL);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph
	BOOL UpdateChannelInfo(void* pChannelInfo,CRtDbMgr* pMemMgr);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph
	BOOL UpdateChannelInfo(void* pChannelInfo,CString strName,CRtDbMgr* pMemMgr);//����ͨ����Ϣ�����ݿ�2017.3.5 by zph
	CRtDbMgr* m_pRtDbMgr;
private:
	BYTE*	m_pProtParam;//����Э���Ĳ���;
	int		m_nParamLen;//��������
	
	BYTE*    m_pGVarParam;//����Э��������ȫ�ֱ���
	int		m_nGVarLen;//ȫ�ֱ�������
#ifdef WIN32
	CArray<UsedTab*,UsedTab*> m_aUsedTabList;//�������豸ʹ�õ������ݱ��б���Ҫ��������FillUsedTab������ʵ��
	CArray<TABLE_INFO*,TABLE_INFO*> m_aSysTab;//ϵͳ��;
#else
	CPtrArray m_aUsedTabList;
	CPtrArray m_aSysTab;
#endif

#ifndef WIN32
//for linux �豸ʵ�����߳�
public:
	bool m_bReadyExit;
	//����
	CProInterface m_proInterface;
	//����Э�鴦���߳�
	pthread_t  * m_hThread;
	//����Э���з����߳�
	pthread_t * m_hSendThread;
	//��ʼ����Commʵ����װ�غ���
	bool Init();
	//����Commʵ��
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

extern CDevCfgMgr gIoDevList;//���вɼ��豸�����б�
extern CDevCfgMgr gDataDevList;//����ת���豸�����б�
extern CDevCfgMgr gInstIoList;//���вɼ��豸ʵ���б�
extern CDevCfgMgr gInstDataList;//����ת���豸ʵ���б�
extern CDevCfgMgr gAllDbList;

#endif // !defined(AFX_DEVCFG_H__1E43576D_98CE_4CFF_9E0F_1934B1A731EC__INCLUDED_)
