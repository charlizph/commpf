/************************************************************
    Module Name: MeteredSection.h
    Author: Dan Chou
    Description: Defines the metered section synchronization object
************************************************************/
#pragma once

#ifndef _METERED_SECTION_H_
#define _METERED_SECTION_H_

#define MIN_TIMEOUT 1000
#define MAX_TIMEOUT 90000

#define MAX_METSECT_NAMELEN 128
#define MAX_METSECT_COUNT 2048

#ifdef WIN32
#include <afxmt.h>
#else
#include <pthread.h>  
#include "../../inc/pthread/msdk.h"
#endif

//定义信号锁
//需要自己定义信号
/* 
sample.h
	#ifdef WIN32
		CMutex* m_pMutex;
	#else
		msdk::Mutex * m_pMutex;
	#endif
sample.cpp
	CString strTmp;
	strTmp.Format("mgrInvoke%d" ,(long)this);
	#ifdef WIN32
		m_pMutex = new CMutex(FALSE, strTmp);
	#else
		m_pMutex = new msdk::Mutex;
	#endif

*/

#ifndef DEF_SINGLE
#define DEF_SINGLE

	#ifdef WIN32
		#define SINGLELOCK	CSingleLock m_lock(m_pMutex);	\
							m_lock.Lock();
		#define SINGLEUNLOCK	m_lock.Unlock();

		#define SINGLEUNLOCKRT(rt)	\
			{m_lock.Unlock();		\
			return(rt);}
	#else
		#define SINGLELOCK	m_pMutex->Lock();//CSingleLock m_lock(m_pMutex);	\
							//m_lock.Lock();
		#define SINGLEUNLOCK	m_pMutex->Unlock();//m_lock.Unlock();

		#define SINGLEUNLOCKRT(rt)	\
			{m_pMutex->Unlock();		\
			return(rt);}
	#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Shared info needed for metered section
typedef struct _METSECT_SHARED_INFO {
    BOOL   fInitialized;     // Is the metered section initialized?
    LONG   lSpinLock;        // Used to gain access to this structure
    LONG   lThreadsWaiting;  // Count of threads waiting
    LONG   lAvailableCount;  // Available resource count
    LONG   lMaximumCount;    // Maximum resource count
} METSECT_SHARED_INFO, *LPMETSECT_SHARED_INFO;

// The opaque Metered Section data structure
typedef struct _METERED_SECTION {
#ifdef WIN32
	HANDLE hEvent;           // Handle to a kernel event object
    HANDLE hFileMap;         // Handle to memory mapped file
#else
	pthread_mutex_t	*m_hMutex;		// Mutex object
#endif
    LPMETSECT_SHARED_INFO lpSharedInfo;
} METERED_SECTION, *LPMETERED_SECTION;

// Interface functions
LPMETERED_SECTION
CreateMeteredSection(LONG lInitialCount, LONG lMaximumCount, LPCTSTR lpName);

#ifndef _WIN32_WCE
LPMETERED_SECTION OpenMeteredSection(LPCTSTR lpName);
#endif

DWORD EnterMeteredSection(LPMETERED_SECTION lpMetSect, DWORD dwMilliseconds);
BOOL LeaveMeteredSection(LPMETERED_SECTION lpMetSect, LONG lReleaseCount, LPLONG lpPreviousCount);
void CloseMeteredSection(LPMETERED_SECTION lpMetSect);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _METERED_SECTION_H_
