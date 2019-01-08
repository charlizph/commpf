#if !defined(AFX_PROCTHREAD_H__38775329_C50F_4758_8E0C_3F0FE9BFE789__INCLUDED_)
#define AFX_PROCTHREAD_H__38775329_C50F_4758_8E0C_3F0FE9BFE789__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcThread.h : header file
//

//#include "proexp_comm.h"

#include "SocketComm.h"

//typedef void (*funSetDataConfPoint)(DATACONF *pDConf);
typedef int (*funGetCounter)();
/////////////////////////////////////////////////////////////////////////////
// CHeartBeatThread thread

#ifdef WIN32
class CHeartBeatThread : public CWinThread
{
	DECLARE_DYNCREATE(CHeartBeatThread)
#else
class CHeartBeatThread
{
#endif
public:
	CHeartBeatThread();           // protected constructor used by dynamic creation

// Attributes
public:
#ifdef WIN32
	HANDLE m_hOwnExit;
	HANDLE m_hParentExit;
	HANDLE m_hCommExit;
	HWND   m_hWnd; 
#else
	pthread_t * m_hThread;	// Thread Comm handle
#endif
	CSocketComm*  m_pComm;
	BOOL	m_bReadyExit;
	CCommParam m_comParam ;
	int    m_nTimeOut;
	CString m_strFileName;
	BOOL	m_bRunning;
	funProcessData m_pFunProcData;
	funGetCounter fGetCounter;
private:
// Operations
public:
	void SendHeartBeat();
	BOOL InitComm();
	BOOL OpenComm();
	BOOL IsConnected();
	void StopComm();
	void SendStopCmd();
	void Clear();
#ifdef WIN32
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeartBeatThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL
#else
	int Run();
#endif
// Implementation
protected:
	virtual ~CHeartBeatThread();

	// Generated message map functions
	//{{AFX_MSG(CHeartBeatThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
#ifdef WIN32
	DECLARE_MESSAGE_MAP()
#endif
};
/////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
bool StartHeartBeat();
bool OpenHBComm();
bool StopHeartBeat();
bool HeartBeatIsAlive();
void SendHeartBeat();
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCTHREAD_H__38775329_C50F_4758_8E0C_3F0FE9BFE789__INCLUDED_)
