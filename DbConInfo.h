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
	int		nCompac;//磁盘容量比默认80%
	int		nAlarmData;//告警数据保存时间长默认12个月
	int     nOtherData;//其他历史数据保存时间长默认3个月
	int		nHisDbSaveInt;//历史数据保存周期 单位s 默认30s
//	CString	strSrvName;
	CString	strDriverName;//sql server 
//日志配置
	int		nBmpSaveTime;//位图保存时长 默认3个月
	int     nVideoSaveTime;//视频保存时长 单位月 默认1
	int     nLogAliveTime;//日志保存时长 默认3个月
	_tagDbConInfo()
	{
		nDbType = 0;
		strSrvAddr = "127.0.0.1";
		nPort = 0;
		nTimeOut = 30;//second
		strDbName = "ZzjDb";
		strUserName = "sa";
		strPassword = "";
		nDbAlive = 6;//数据保存半年
		strDriverName = "Sql Server";
		nCompac = 80;
		nAlarmData =12;//历史告警
		nOtherData=3;//历史数据
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

	BOOL Save();//默认保存到当前工程目录下\config\hisdb.cfg
	BOOL Load();
}DbConInfo;

#endif // !defined(AFX_DBCONINFO_H__DB9C7451_5465_4181_AF38_8382EB455758__INCLUDED_)
