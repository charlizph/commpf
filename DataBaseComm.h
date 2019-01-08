// DataBaseComm.h: interface for the CDataBaseComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASECOMM_H__7BB091AB_B884_49BE_90C9_AE6CAFA4D698__INCLUDED_)
#define AFX_DATABASECOMM_H__7BB091AB_B884_49BE_90C9_AE6CAFA4D698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommBase.h"
#include "RldbRecs.h"

//#include <afxdao.h>
#ifdef WIN32
#include <afxdb.h>
#endif
class CDataBaseComm : public CBaseComm  
{
public:
	CDataBaseComm();
	virtual ~CDataBaseComm();
 
public:
	BOOL OpenComm();
	BOOL OpenComm(DbConInfo oneParam);
	BOOL CloseComm(BOOL bPost = false);
	BOOL IsConnected();
	int  WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);
	int	 ReadData(void* pBuf,int nLen);
	BOOL ExecuteSql(CString strSql);
	virtual bool WatchComm();
	BOOL LoadDbCfg();
public:
	CRldbRecs m_rldb;//数据库访问类
#ifdef WIN32
//	CDatabase m_database;//for sql server or odbc
#endif
	CString   m_strConnect;//连接库的命令行

};

#endif // !defined(AFX_DATABASECOMM_H__7BB091AB_B884_49BE_90C9_AE6CAFA4D698__INCLUDED_)
