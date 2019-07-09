// DbConInfo.h: interface for the CDbConInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONINFO_H__DB9C7451_5465_4181_AF38_8382EB455758__INCLUDED_)
#define AFX_DBCONINFO_H__DB9C7451_5465_4181_AF38_8382EB455758__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WIN32
#include "msystem.h"
#include "cstring.h"
#endif

typedef struct _tagDbConInfo{
	CString strSrvAddr;//db server ip address or host name
	int		nPort;
	CString strDbName;
	CString strUserName;
	CString strPassword;
	int		nTimeOut;
	int		nDbAlive;
	int		nDbType;//
	int		nCompac;//����������Ĭ��80%
	int		nAlarmData;//�澯���ݱ���ʱ�䳤Ĭ��12����
	int     nOtherData;//������ʷ���ݱ���ʱ�䳤Ĭ��3����
	int		nHisDbSaveInt;//��ʷ���ݱ������� ��λs Ĭ��30s
//	CString	strSrvName;
	CString	strDriverName;//sql server 
//��־����
	int		nBmpSaveTime;//λͼ����ʱ�� Ĭ��3����
	int     nVideoSaveTime;//��Ƶ����ʱ�� ��λ�� Ĭ��1
	int     nLogAliveTime;//��־����ʱ�� Ĭ��3����
	_tagDbConInfo()
	{
		nDbType = 0;
		strSrvAddr = "127.0.0.1";
		nPort = 0;
		nTimeOut = 30;//second
		strDbName = "ZzjDb";
		strUserName = "sa";
		strPassword = "";
		nDbAlive = 6;//���ݱ������
		strDriverName = "Sql Server";
		nCompac = 80;
		nAlarmData =12;//��ʷ�澯
		nOtherData=3;//��ʷ����
		nHisDbSaveInt=30;
		nBmpSaveTime = 3;
		nVideoSaveTime = 1;
		nLogAliveTime = 3;
	}
	_tagDbConInfo* operator=(_tagDbConInfo * pInfo)
	{
		strSrvAddr = pInfo->strSrvAddr;
		nPort = pInfo->nPort;
		strDbName = pInfo->strDbName;
		strUserName = pInfo->strUserName;
		strPassword = pInfo->strPassword;
		nTimeOut = pInfo->nTimeOut;
		strDriverName = pInfo->strDriverName;
		nDbType = pInfo->nDbType;
		nCompac = pInfo->nCompac;
		nAlarmData = pInfo->nAlarmData;
		nOtherData = pInfo->nOtherData;
		nHisDbSaveInt = pInfo->nHisDbSaveInt;
		nBmpSaveTime = pInfo->nBmpSaveTime;
		nVideoSaveTime = pInfo->nVideoSaveTime;
		nLogAliveTime = pInfo->nLogAliveTime;
		return this;
	}
	_tagDbConInfo operator=(_tagDbConInfo Info)
	{
		strSrvAddr = Info.strSrvAddr;
		nPort = Info.nPort;
		strDbName = Info.strDbName;
		strUserName = Info.strUserName;
		strPassword = Info.strPassword;
		nTimeOut = Info.nTimeOut;
		strDriverName = Info.strDriverName;
		nDbType = Info.nDbType;
		nCompac = Info.nCompac;
		nAlarmData = Info.nAlarmData;
		nOtherData = Info.nOtherData;
		nHisDbSaveInt = Info.nHisDbSaveInt;
		nBmpSaveTime = Info.nBmpSaveTime;
		nVideoSaveTime = Info.nVideoSaveTime;
		nLogAliveTime = Info.nLogAliveTime;
		return *(this);
	}

	BOOL Save();//Ĭ�ϱ��浽��ǰ����Ŀ¼��\config\hisdb.cfg
	BOOL Load();
}DbConInfo;

#endif // !defined(AFX_DBCONINFO_H__DB9C7451_5465_4181_AF38_8382EB455758__INCLUDED_)
