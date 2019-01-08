#ifndef HEARTBEATEXT_H
#define HEARTBEATEXT_H

#include "CallBackFunDef.h"
typedef int (*funGetCounter)();

#ifndef MAXCOUNTER
#define MAXCOUNTER 11       
#endif
 
//�����Ҫ�Լ�����������ݴ���ص�������Ҫ��bPause��ΪTRUE��Ȼ�����SetRecvFun
extern void SendStopCmd();
extern void SetRecvFun(funProcessData recvFun,BOOL bStart);
extern void ResumeHeartBeat();
#ifdef WIN32
	extern HANDLE StartHeartBeat(HANDLE hParentExit,HWND hWnd=NULL,BOOL bPause=FALSE,funGetCounter fGCounter=NULL);
	extern BOOL StopHeartBeat(HANDLE hParentExit,HANDLE hThreadExit);

	#ifndef _HEARTBEAT
		#ifdef _AFXDLL
		#   pragma comment(lib, "HeartBeatd")
		#else
		#   pragma comment(lib, "HeartBeat")
		#endif
	#endif	
	#include "CommUtilExt.h"
	#include "ethernetcommext.h"
	#include "utiltoolext.h"

	#define UM_AUTOCLOSE WM_USER + 23412
#else
	extern BOOL StartHeartBeat(funGetCounter fGCounter=NULL);
	extern BOOL StopHeartBeat();
#endif
#endif