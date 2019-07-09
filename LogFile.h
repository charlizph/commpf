// LogFile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__ABEBC66A_9657_45DF_93D5_3FE3F943816C__INCLUDED_)
#define AFX_LOGFILE_H__ABEBC66A_9657_45DF_93D5_3FE3F943816C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef WIN32
#include "mtype.h"
#include "cstring.h"
#endif
//0－超标录波；
#define LOG_WAVE 0

//1－电能质量监测设备故障；
#define LOG_IEDFAIL 1

//2－子站内通信故障；
#define LOG_INSUBCOMMFAIL 2

//3－参数设置成功；
#define LOG_PARAM_SUC 3

//4－参数设置失败；
#define LOG_PARAM_FAIL 4

//5－设备上电；
#define LOG_DEVPOWER 5

//6－站间通信故障；
#define LOG_BSUBCOMFAIL 6

//7－网络消息；
#define LOG_NETMSG 7

//8－进程消息；
#define LOG_PROCMSG 8

//9－用户消息；
#define LOG_USRMSG 9

//10－其他
#define LOG_OTHER 10

class CLogFile  
{
public:
#ifdef WIN32
	static BOOL LogMessage(LPCTSTR msg,int nLogType=LOG_OTHER,BOOL bHasModName=FALSE);
	static BOOL LogMessage64(char* msg,int nLogType=LOG_OTHER,int bHasModName=FALSE);
#else
	static BOOL LogMessage(CString msg,BOOL bDis=TRUE,BOOL bLog=TRUE);
#endif
	CLogFile();
	virtual ~CLogFile();

private:
	static BOOL GetLogFileName(CString &fname);
};

#endif // !defined(AFX_LOGFILE_H__ABEBC66A_9657_45DF_93D5_3FE3F943816C__INCLUDED_)
