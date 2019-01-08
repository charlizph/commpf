// CommBase.h: interface for the CCommBase class.
//
/********************************************************************************************
* ����˵��      : ͨѶ����
*				  	
* ��  ��        : �����
*              
* ��������      : 2007��05��16��
* �汾��        : 1.0.1
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
	virtual int	 GetClientCount(){return 0;}//��Ҫ���tcpserver
//	virtual void StopComm();//����˳�,��Ϣ��¼,ǿ���˳�
protected:
	BOOL	m_bReadThreadIsOk;//���߳��Ƿ�������
	BOOL	m_bReadyExit;
	BOOL    m_bFinishExit;//֪ͨ�������Ѿ�����˳� ;
#ifdef WIN32
	HANDLE m_hCommExit;//֪ͨ�����ߣ����Ѿ��˳�;�þ���ɵ����ߴ���,�����߸������,
	HANDLE m_hParentExit;//������֪ͨ���˳���ÿ��ͨ��ӵ���Լ����ź�.�þ���ɵ����ߴ���,�����߸������,
	HANDLE		m_hMutex;		// Mutex object
#else
	BOOL m_hCommExit;//֪ͨ�����ߣ����Ѿ��˳�;�þ���ɵ����ߴ���,�����߸������,
	BOOL m_hParentExit;//������֪ͨ���˳���ÿ��ͨ��ӵ���Լ����ź�.�þ���ɵ����ߴ���,�����߸������,
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
	funEvent	m_pFunEvent;//�¼���Ϣ���������ַ�ʽ��1��ͨ���ص�������2��ͨ��windows��Ϣ����m_pWndParent����
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
	
	virtual BOOL IsMonitor();//�Ƿ�Ϊ����ͨ��
	virtual void ClosePort();//�����ǹرն˿�
	virtual BOOL CloseComm(BOOL bPost = false);//int nTimeOut=10);//nTimeOut �ȴ��߳��˳��ĳ�ʱʱ��ms �����˳���Ǻ��ź�
	virtual BOOL OpenComm();
	virtual BOOL OpenComm(CCommParam comParam);
	virtual BOOL IsConnected();
	virtual int WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);//����д�ɹ����ֽ�����-1��ʾдʧ��
	virtual int ReadData(void* pBuf,int nLen);//pBuf���յĻ�����,�ɵ����߸������,���ض����ֽ�����-1 ��ʾ��ʧ��
// Event function - override to get data
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent,BOOL bPost = FALSE);
	virtual bool WatchComm(){return true;}//���������߳�
	virtual void SetDevCfg(void* pDevCfg);
	virtual void* GetDevCfg();
	virtual void MallocRecvBuf();
	virtual void FreeRecvBuf();
public:
	BOOL m_bReading;//���ڽ�������
	BOOL m_bSending;//���ڷ�������
	void*	m_pMainThread;//����ͨѶ�����߳�
//	HWND m_pViewWnd;

//	int		m_nRecvInterval;//���ݽ���ɨ������ ��λ���� Ĭ��10ms;
//	int		m_nSendInterval;//���ݷ��Ͷ���ɨ�����ڣ���λ���� Ĭ��1000ms;
	BOOL	m_bNeedAnalyse;//�Ƿ���Ҫ���б��ķ�����Ĭ�ϲ���Ҫ
	BOOL	m_bRecDataGram;//�Ƿ񱣴汨��;Ĭ�ϲ���Ҫ
	BOOL	m_bDisDG;//�Ƿ���Ҫ��ʾ���ģ�Ĭ�ϲ���Ҫ
//	CMgrDgFrm	m_mgrFrm;//�շ����Ĺ����Ա
//	CMgrDgFrm	m_fixedDgFrm;//�̶���ʽ�ķ��ͱ���
//	CMgrDgFrm	m_sendFrm;//���ͱ��Ķ��У�
	BOOL		m_bReceive;//���ڱ��ļ��� true ���ǽ��ձ��ģ�false: ���ͱ���
//	BOOL		m_bUsing ;//
	int		m_nWriteRetryTimes;
	int		m_nLocalPort;
//	void	SetOwnExit(HANDLE hOwnExit);

	void	SendRSInfo(CString strData,int nMsgType,BOOL bLog=FALSE,BOOL bPost = FALSE);//nMsgType :UM_SENDDATA or UM_RECVDATA
	void    SendMsgToParent(CString strMsg,BOOL bLog=FALSE,BOOL bPost = FALSE);//�Ƿ�Ҫ������־�ļ�;
//	BYTE	m_pSendBuf[BUFFER_SIZE];
	int		m_nSendLen;
	int		GetReceiveBuf(BYTE* pRecvBuf);
	unsigned long	m_lTotalRecvLen;//�ܵĽ��ձ��ĳ���
	unsigned long	m_lTotalSendLen;//�ܵķ��ͱ��ĳ���
protected:
	BYTE*	m_pRecvBuf;//[BUFFER_SIZE];
	int		m_nBufSize;
	unsigned long		m_nRecvLen;//���յı��ĳ���
	void* m_pDevCfg;//ͨ��ʵ�����ò�����������ͨ�������������ݿ��¼�� ��������ΪCDevCfg
	int	m_nCommType;
//	int	m_nCommStatus;
#ifdef WIN32
	HWND  m_hWndParent;
	HWND  m_hWndInfo;
	HWND  m_hWndMain;
	CWnd* m_pInfoWnd;//�¼���Ϣ,������Ϣ��
	CWnd* m_pMainWnd;//״̬����
	CWnd* m_pWndParent;//���常���ڣ���ʾ�շ�����,�����ַ�ʽ��1��ͨ���ص�������2��ͨ��windows��Ϣ����m_pWndParent����
	HANDLE		m_hThread;		// Thread Comm handle
#else
	pthread_t * m_hThread;	// Thread Comm handle
#endif
	BOOL	m_bLoged;//��¼��������Ҫ��ֹͬһ����־�ظ���¼
	BOOL    m_bDisConStatusAlarm;//�Ƿ���Ҫ��ʾ���ӡ��Ͽ���Ϣ
//private:
//	int	m_nRecvTimeOut;
public:
	void SetDisConSA(BOOL bDis){m_bDisConStatusAlarm = bDis;}
	BOOL GetDisConSA(){return m_bDisConStatusAlarm;}
	virtual void ForceClose();
	long m_lLastTime;//������������ʱ��;
	int	m_nNodataCount;//û�������շ�������;
	CString m_strComInfo;
	CString m_strErrMsg;
};

#endif // !defined(AFX_COMMBASE_H__B46A4BCE_AA17_4DC6_81B1_189CF242EC74__INCLUDED_)
