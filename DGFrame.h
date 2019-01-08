// DGFrame.h: interface for the CDGFrame class.
#if !defined(AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_)
#define AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

/********************************************************************************************
* 功能说明      : 桢详细解析类CDetailAnalyse
*				  每一桢解析后形成一个树形的拓扑结构	
* 作  者        : 张培洪
*              
* 创建日期      : 2007年06月11日
* 版本号        : 1.0.1
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
	//该解析结果是否包含子节点；
	BOOL HasSub();
	void ClearList();//清空子节点集合
public:
	CString m_strResult;
	CPtrList m_aSubDA;//子节点集合
	int		m_nStartPos;//报文起始位置
	int		m_nLen;//报文长度
	int		m_nCurPos;//当前位置
	static HTREEITEM m_hLastItem;
};

/********************************************************************************************
* 功能说明      : 报文桢类CDGFrame
*				  保存并分析发送或接收的报文	
* 作  者        : 张培洪
*              
* 创建日期      : 2007年06月06日
* 版本号        : 1.0.1
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
	void	AddRawBuf(BYTE* pNewBuf,int nAddLen);//追加报文

	//设置该桢发生的时间即收发的时间
	void	SetOcurTime(int nTType=TIMETYPE1);
	void	SetOcurTime(CString strOcurTime);
	CString GetOcurTime();
	void    GetOcurTime(SYSTEMTIME & st);
	//设置该桢简单分析结果
	void	SetSmpAnalyse(CString strSmpAnaly);
	CString	GetSmpAnalyse();
	//设置该桢详细分析结果,调用者负责创建输入的pDA对象，但不负责释放pDA由CDGFrame负责释放内存
	void	SetDetailAnalyse(CDetailAnalyse* pDA);
	CDetailAnalyse* GetDetailAnalyse();
public:
	int		m_nIndex;//报文桢的编号，系统自动增加；
	int		m_nDirection;//桢的传送方向；

	int		m_nRunTimes;//预定义下发桢，下发次数，-1表示无限次
	int		m_nSendInterval;//发送时间间隔(ms)
	int		m_nDgFrmType;
	BOOL	m_bIsWrongFrm;//是否是错误的报文桢;
	CString m_strSrcMac;
	CString m_strDestMac;
	CString m_strSrcIp;
	CString m_strDestIp;
	CString m_strDgType;
	CString m_strSPort;
	CString m_strDPort;
	CString m_strSrcDesc;
	unsigned int m_nTcpAckNo;//tcp桢应答序号
	int		m_aRefSeq[10];
	int		m_nRefCount;
	BOOL	m_bFirst;
private:
	CCPUTicker	m_ticker;//用来获得精确毫秒
	int		m_nTimeType;//时间类型；
	BOOL	m_bWholeFrm;//标识该桢是否是完整的一桢 ，默认值是1，表示是完整一桢
	BYTE*	m_pRawBuf;//保存原始桢的内容；
	int		m_nLen;//原始桢长度；

	SYSTEMTIME m_stOcurTime;
	CString m_strOcurTime;//收发时间
	CString m_strSmpAnaly;//简单分析结果;
	CDetailAnalyse* m_pDA;//详细分析结果
};

#include "meteredsection.h"
/********************************************************************************************
* 功能说明      : 桢管理类CMgrDgFrm
*				  管理收发的桢,
* 作  者        : 张培洪
*              
* 创建日期      : 2007年06月11日
* 版本号        : 1.0.1
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
	BOOL	m_bAutoSave;//自动保存报文；默认自动保存
	CString	m_strSavePath;//保存的路径
	BOOL	m_bFull;//报文数达到最大值
	METERED_SECTION * m_pMutex;
	CPtrList m_aFrmList; 
	int		m_nIndex;
	int		m_nProcIndex;
	int		m_nMaxDgFrm;
	CString	m_strProtoPath;//协议库名及其全路径；
};

#endif // !defined(AFX_DGFRAME_H__D81F7094_7DFF_4A12_BEC7_89BAB47D8A47__INCLUDED_)
