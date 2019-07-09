// CommBase.h: interface for the CCommBase class.
//
/********************************************************************************************
* 功能说明      : 通讯基类
*				  	
* 作  者        : 张培洪
*              
* 创建日期      : 2007年05月16日
* 版本号        : 1.0.1
*********************************************************************************************/

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMBASE_H__B46A4BCE_AA17_4DC6_81B1_189CF242EC74__INCLUDED_)
#define AFX_COMMBASE_H__B46A4BCE_AA17_4DC6_81B1_189CF242EC74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "dgframe.h"

#include "comminc.h"
   
class CBaseComm  
{
public:
	CBaseComm();
	virtual ~CBaseComm();
public:
	CCommParam   m_comParam;
//for singal manage
public:
	void    InitFunToNull();
	BOOL	ParentExit(int nTimeOut =1);
	BOOL    CommExit(int nTimeOut = 1);
#ifdef WIN32
	void	SetParentExitHandle(HANDLE hPExit){m_hParentExit = hPExit;}
	HANDLE  GetParentExitHandle(){return m_hParentExit;}
	HANDLE GetCommExitHandle(){return m_hCommExit;}
	void SetCommExitHandle(HANDLE hCommExit){m_hCommExit = hCommExit;}
#else
	void	SetParentExitHandle(BOOL hPExit){m_hParentExit = hPExit;}
	BOOL  GetParentExitHandle(){return m_hParentExit;}
	BOOL GetCommExitHandle(){return m_hCommExit;}
	void SetCommExitHandle(BOOL hCommExit){m_hCommExit = hCommExit;}
#endif
//	virtual BOOL InfoExit(int nTimeOut = 10);//*10 ms
	virtual void SetReadyExit(BOOL bExit);
	BOOL IsReadyExit(){return m_bReadyExit;}
	BOOL IsFinishExit(){return m_bFinishExit;}
	BOOL ReadThreadIsOk(){return m_bReadThreadIsOk;}
	void SetFinishExit(BOOL bFinish){m_bFinishExit = bFinish;}
	virtual int	 GetClientCount(){return 0;}//主要针对tcpserver
//	virtual void StopComm();//完成退出,信息记录,强制退出
protected:
	BOOL	m_bReadThreadIsOk;//读线程是否在运行
	BOOL	m_bReadyExit;
	BOOL    m_bFinishExit;//通知调用者已经完成退出 ;
#ifdef WIN32
	HANDLE m_hCommExit;//通知调用者，我已经退出;该句柄由调用者创建,调用者负责回收,
	HANDLE m_hParentExit;//调用者通知我退出，每个通道拥有自己的信号.该句柄由调用者创建,调用者负责回收,
	HANDLE		m_hMutex;		// Mutex object
#else
	BOOL m_hCommExit;//通知调用者，我已经退出;该句柄由调用者创建,调用者负责回收,
	BOOL m_hParentExit;//调用者通知我退出，每个通道拥有自己的信号.该句柄由调用者创建,调用者负责回收,
	pthread_mutex_t	*m_hMutex;		// Mutex object
#endif
protected:
	// Synchronization function
	void LockList();			// Lock the object
	void UnlockList();			// Unlock the object

public:
	void SetParam(CCommParam comParam);
	void LoadParam();
	int GetCommType();
	void SetCommType(int nType);
//	int GetCommSt();
	funEvent	m_pFunEvent;//事件信息处理，有两种方式，1。通过回调函数，2。通过windows消息机制m_pWndParent传送
	funProcessData m_pFunProcData;
	funProcessData	m_pFunSendData;
	funProcDisCon  m_pFunProcDisCon;
	funProcConnect m_pFunProcConnect;

	funSendDataToWnd m_pFunSendDataToWnd;
	funSendMsgToParent m_pFunSendMsgToParent;

	CString GetCommTypeName();
#ifdef WIN32
	HANDLE GetThreadHandle(){return m_hThread;}
	void SetThreadHandle(HANDLE hHandle){m_hThread = hHandle;}
	virtual void SetParentWnd(CWnd* pWnd);
	virtual void SetInfoWnd(CWnd* pWnd);
	virtual void SetMainWnd(CWnd* pWnd);
	virtual CWnd* GetParentWnd();
	virtual CWnd* GetInfoWnd();
	virtual CWnd* GetMainWnd();
#endif
public:
	
	virtual BOOL IsMonitor();//是否为监听通道
	virtual void ClosePort();//仅仅是关闭端口
	virtual BOOL CloseComm(BOOL bPost = false);//int nTimeOut=10);//nTimeOut 等待线程退出的超时时间ms 设置退出标记和信号
	virtual BOOL OpenComm();
	virtual BOOL OpenComm(CCommParam comParam);
	virtual BOOL IsConnected();
	virtual int WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);//返回写成功的字节数，-1表示写失败
	virtual int ReadData(void* pBuf,int nLen);//pBuf接收的缓冲区,由调用者负责分配,返回读到字节数，-1 表示读失败
// Event function - override to get data
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent,BOOL bPost = FALSE);
	virtual bool WatchComm(){return true;}//接收数据线程
	virtual void SetDevCfg(void* pDevCfg);
	virtual void* GetDevCfg();
	virtual void MallocRecvBuf();
	virtual void FreeRecvBuf();
public:
	BOOL m_bReading;//正在接收数据
	BOOL m_bSending;//正在发送数据
	void*	m_pMainThread;//启动通讯的主线程
//	HWND m_pViewWnd;

//	int		m_nRecvInterval;//数据接收扫描周期 单位毫秒 默认10ms;
//	int		m_nSendInterval;//数据发送队列扫描周期，单位毫秒 默认1000ms;
	BOOL	m_bNeedAnalyse;//是否需要进行报文分析；默认不需要
	BOOL	m_bRecDataGram;//是否保存报文;默认不需要
	BOOL	m_bDisDG;//是否需要显示报文；默认不需要
//	CMgrDgFrm	m_mgrFrm;//收发报文管理成员
//	CMgrDgFrm	m_fixedDgFrm;//固定格式的发送报文
//	CMgrDgFrm	m_sendFrm;//发送报文队列；
	BOOL		m_bReceive;//用于报文监听 true ：是接收报文，false: 发送报文
//	BOOL		m_bUsing ;//
	int		m_nWriteRetryTimes;
	int		m_nLocalPort;
//	void	SetOwnExit(HANDLE hOwnExit);

	void	SendRSInfo(CString strData,int nMsgType,BOOL bLog=FALSE,BOOL bPost = FALSE);//nMsgType :UM_SENDDATA or UM_RECVDATA
	void    SendMsgToParent(CString strMsg,BOOL bLog=FALSE,BOOL bPost = FALSE);//是否要记入日志文件;
//	BYTE	m_pSendBuf[BUFFER_SIZE];
	int		m_nSendLen;
	int		GetReceiveBuf(BYTE* pRecvBuf);
	unsigned long	m_lTotalRecvLen;//总的接收报文长度
	unsigned long	m_lTotalSendLen;//总的发送报文长度
protected:
	BYTE*	m_pRecvBuf;//[BUFFER_SIZE];
	int		m_nBufSize;
	unsigned long		m_nRecvLen;//接收的报文长度
	void* m_pDevCfg;//通道实例配置参数，包括了通道所关联的数据库记录集 数据类型为CDevCfg
	int	m_nCommType;
//	int	m_nCommStatus;
#ifdef WIN32
	HWND  m_hWndParent;
	HWND  m_hWndInfo;
	HWND  m_hWndMain;
	CWnd* m_pInfoWnd;//事件信息,错误信息等
	CWnd* m_pMainWnd;//状态栏用
	CWnd* m_pWndParent;//定义父窗口，显示收发报文,有两种方式，1。通过回调函数，2。通过windows消息机制m_pWndParent传送
	HANDLE		m_hThread;		// Thread Comm handle
#else
	pthread_t * m_hThread;	// Thread Comm handle
#endif
	BOOL	m_bLoged;//记录日至，主要防止同一条日志重复纪录
	BOOL    m_bDisConStatusAlarm;//是否需要显示连接、断开信息
//private:
//	int	m_nRecvTimeOut;
public:
	void SetDisConSA(BOOL bDis){m_bDisConStatusAlarm = bDis;}
	BOOL GetDisConSA(){return m_bDisConStatusAlarm;}
	virtual void ForceClose();
	long m_lLastTime;//更新数据最新时间;
	int	m_nNodataCount;//没有数据收发计数器;
	CString m_strComInfo;
	CString m_strErrMsg;
};

#endif // !defined(AFX_COMMBASE_H__B46A4BCE_AA17_4DC6_81B1_189CF242EC74__INCLUDED_)
