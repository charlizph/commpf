// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "lencode.h"
//#include "utility.h"
#include "BufferInfo.h"

#include "SocketComm.h"
#ifdef WIN32
#include "meteredsection.h"
typedef CTypedPtrArray<CPtrArray , CSocketComm*>  CSockArray;
#else
typedef std::vector<CSocketComm*> CSockArray;
#endif
  
class CSocketServer : public CSocketComm  
{
public:
	CSocketServer();
	~CSocketServer();

public:
//	virtual void OnEvent(UINT uEvent);
	virtual void SetReadyExit(BOOL bExit);
	virtual int GetClientCount();
	virtual void Run();
	virtual BOOL CloseComm(BOOL bPost = false);
	virtual bool WatchComm();
	void	SocketIsRuning();
	void	CloseAllClient(int nTimeOut = 10);
	int WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);//返回写成功的字节数，-1表示写失败
#ifdef WIN32
	void SetParentWnd(CWnd* pWnd);
	CArray<HANDLE,HANDLE> m_aSockHandle;
	HANDLE m_hCheckThreadExit;
#else
	CPtrList m_aSockHandle;
#endif
public:
	void InitSocket(CSocketComm* pSocket);
	CSocketComm* CheckClientSocket();//返回连接是断开的socketcom；
	BOOL FindSocket(long lSock);
	void RemoveSocket(CSocketComm* pSocket);
	void RemoveSocket(CSocketComm* pSocket,int index);
	void RemoveHandle(CSocketComm* pSocket);
	CSockArray m_aSocketArray;
	BOOL	m_bIec61850;//默认值为TRUE;
	BOOL	m_bAdding;
	BOOL	m_bChecking;
protected:
/*
#ifdef 
	static UINT WINAPI CheckSocketThread(LPVOID pParam);
#else
	static void * CheckSocketThread(LPVOID pParam);
#endif
	*/
//	CEdit* m_pMsgCtrl;
#ifdef WIN32
	METERED_SECTION * m_pSync; //同步信号
	HANDLE m_hCheckThread;
#else
	pthread_t * m_hCheckThread;
#endif
};
#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
