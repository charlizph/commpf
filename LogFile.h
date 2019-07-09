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
//0������¼����
#define LOG_WAVE 0

//1��������������豸���ϣ�
#define LOG_IEDFAIL 1

//2����վ��ͨ�Ź��ϣ�
#define LOG_INSUBCOMMFAIL 2

//3���������óɹ���
#define LOG_PARAM_SUC 3

//4����������ʧ�ܣ�
#define LOG_PARAM_FAIL 4

//5���豸�ϵ磻
#define LOG_DEVPOWER 5

//6��վ��ͨ�Ź��ϣ�
#define LOG_BSUBCOMFAIL 6

//7��������Ϣ��
#define LOG_NETMSG 7

//8��������Ϣ��
#define LOG_PROCMSG 8

//9���û���Ϣ��
#define LOG_USRMSG 9

//10������
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
