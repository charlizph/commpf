// DGFrame.h: interface for the CDGFrame class.
#if !defined(AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_)
#define AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ʱ���ʽ1��yyyy-mm-dd hh:mm:ss.xxx
#define TIMETYPE1 1
//ʱ���ʽ2��yyyy-mm-dd hh:mm:ss
#define TIMETYPE2 2
//ʱ���ʽ3  mm-dd hh:mm:ss.xxx
#define TIMETYPE3 3
//ʱ���ʽ4��dd hh:mm:ss.xxx
#define TIMETYPE4 4
//ʱ���ʽ5��hh:mm:ss.xxx
#define TIMETYPE5 5
//ʱ���ʽ6��hh:mm:ss
#define TIMETYPE6 6

//���屨���Ƿ��ͻ���պ�
//����
#define DIREC_SEND 0
//����
#define DIREC_RECV 1

/********************************************************************************************
* ����˵��      : ����ϸ������CDetailAnalyse
*				  ÿһ��������γ�һ�����ε����˽ṹ	
* ��  ��        : �����
*              
* ��������      : 2007��06��11��
* �汾��        : 1.0.1
*********************************************************************************************/
//////////////////////////////////////////////////////////////////////
#include <afxcmn.h>

class CDetailAnalyse
{
public:
	CDetailAnalyse();
	~CDetailAnalyse();
public:
	void AttachToTreeCtrl(CTreeCtrl* pTree,HTREEITEM pParentItem=NULL);
//	void SaveDA(CArchive& ar);
//	void LoadDA(CArchive& ar);

	void AddSubDa(CDetailAnalyse* pSubDA);
	//�ý�������Ƿ�����ӽڵ㣻
	BOOL HasSub();
	void ClearList();//����ӽڵ㼯��
public:
	CString m_strResult;
	CPtrList m_aSubDA;//�ӽڵ㼯��
	int		m_nStartPos;//������ʼλ��
	int		m_nLen;//���ĳ���
	int		m_nCurPos;//��ǰλ��
	static HTREEITEM m_hLastItem;
};

/********************************************************************************************
* ����˵��      : ��������CDGFrame
*				  ���沢�������ͻ���յı���	
* ��  ��        : �����
*              
* ��������      : 2007��06��06��
* �汾��        : 1.0.1
*********************************************************************************************/
//////////////////////////////////////////////////////////////////////
#include "CPUTicker.h"

class CDGFrame  
{
public:
	CDGFrame(BYTE* pBuf,int nLen,int nDirec=DIREC_RECV);
	CDGFrame();
	~CDGFrame();
public:
	void    CopyFrm(CDGFrame* pRaw);
	void	SetWholeFrm(BOOL bWholeFrm);
	BOOL	IsWholeFrm();

	void	SaveDgFrm(CArchive& ar);
	void	LoadDgFrm(CArchive& ar);

	CString GetRawBufByString(BOOL bCase=TRUE);
	BYTE*	GetRawBuf() const;
	int		GetRawLen();
	void	SetRawBuf(BYTE* pBuf,int nLen);
	void	AddRawBuf(BYTE* pNewBuf,int nAddLen);//׷�ӱ���

	//���ø��巢����ʱ�伴�շ���ʱ��
	void	SetOcurTime(int nTType=TIMETYPE1);
	void	SetOcurTime(CString strOcurTime);
	CString GetOcurTime();
	void    GetOcurTime(SYSTEMTIME & st);
	//���ø���򵥷������
	void	SetSmpAnalyse(CString strSmpAnaly);
	CString	GetSmpAnalyse();
	//���ø�����ϸ�������,�����߸��𴴽������pDA���󣬵��������ͷ�pDA��CDGFrame�����ͷ��ڴ�
	void	SetDetailAnalyse(CDetailAnalyse* pDA);
	CDetailAnalyse* GetDetailAnalyse();
public:
	int		m_nIndex;//������ı�ţ�ϵͳ�Զ����ӣ�
	int		m_nDirection;//��Ĵ��ͷ���

	int		m_nRunTimes;//Ԥ�����·��壬�·�������-1��ʾ���޴�
	int		m_nSendInterval;//����ʱ����(ms)
	int		m_nDgFrmType;
	BOOL	m_bIsWrongFrm;//�Ƿ��Ǵ���ı�����;
	CString m_strSrcMac;
	CString m_strDestMac;
	CString m_strSrcIp;
	CString m_strDestIp;
	CString m_strDgType;
	CString m_strSPort;
	CString m_strDPort;
	CString m_strSrcDesc;
	unsigned int m_nTcpAckNo;//tcp��Ӧ�����
	int		m_aRefSeq[10];
	int		m_nRefCount;
	BOOL	m_bFirst;
private:
	CCPUTicker	m_ticker;//������þ�ȷ����
	int		m_nTimeType;//ʱ�����ͣ�
	BOOL	m_bWholeFrm;//��ʶ�����Ƿ���������һ�� ��Ĭ��ֵ��1����ʾ������һ��
	BYTE*	m_pRawBuf;//����ԭʼ������ݣ�
	int		m_nLen;//ԭʼ�峤�ȣ�

	SYSTEMTIME m_stOcurTime;
	CString m_strOcurTime;//�շ�ʱ��
	CString m_strSmpAnaly;//�򵥷������;
	CDetailAnalyse* m_pDA;//��ϸ�������
};

#include "meteredsection.h"
/********************************************************************************************
* ����˵��      : �������CMgrDgFrm
*				  �����շ�����,
* ��  ��        : �����
*              
* ��������      : 2007��06��11��
* �汾��        : 1.0.1
*********************************************************************************************/
//////////////////////////////////////////////////////////////////////

class CMgrDgFrm
{
public:
	CMgrDgFrm();
	~CMgrDgFrm();
public:
	CDGFrame* GetDgFrmByAckNo(int nAckNo);
	void	SetProto(CString strProto);
	CString	GetProto();
	void	SetAutoSave(BOOL bAutoSave);
	BOOL	IsAutoSave();
	void	SetSavePath(CString strPath);
	CString GetSavePath();

	void	ClearFullFlag();
	BOOL	IsFull();
	void	SetMaxDgFrm(int nMaxDgFrm);
	int		GetMaxDgFrm();
	CDGFrame* GetFirstFrm();
	CDGFrame* GetNextFrm(POSITION& pos);
	POSITION  GetFirstFrmPos();
	CDGFrame* GetFirstFrm(POSITION& pos);
	POSITION  GetLastFrmPos();
	CDGFrame* GetPrevFrm(POSITION& pos);

	int		GetCount();
	int		AddDgFrm(CDGFrame* pInfo);
	int		AddDgFrm(BYTE* pFrm,int nLen,int nDirec);
	void	RmFirstFrm();
	void	RemoveAt(POSITION pos);
	void	RemoveAll();

	void	SaveDgFrm(CString strType=_T(""));
	BOOL	LoadDgFrm(CString strName=_T(""));
	void	SaveDgFrm(CArchive& ar);
	void	LoadDgFrm(CArchive& ar);
private:
	BOOL	m_bAutoSave;//�Զ����汨�ģ�Ĭ���Զ�����
	CString	m_strSavePath;//�����·��
	BOOL	m_bFull;//�������ﵽ���ֵ
	METERED_SECTION * m_pMutex;
	CPtrList m_aFrmList; 
	int		m_nIndex;
	int		m_nProcIndex;
	int		m_nMaxDgFrm;
	CString	m_strProtoPath;//Э���������ȫ·����
};

#endif // !defined(AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_)
