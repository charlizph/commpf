// CUserMsg.h: interface for the CUserMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMSG_H__891CCD4B_4E55_47CA_A430_420211D5E134__INCLUDED_)
#define AFX_USERMSG_H__891CCD4B_4E55_47CA_A430_420211D5E134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "memtabstruct.h"

#define USER_NOEXIST    6
#define USER_ERRPWD     7
#define USER_OK			8
#define USER_NOPOWER	9
#define USER_OUTTIME	10

//UP --- UserPower
#define URPW_NONE		0
//登陆权限
#define URPW_EDIT		1
//运行程序的权限
#define URPW_RUN		2

#define URPW_PREYK		4

#define URPW_YK			8
#define URPW_CFMALARM	16
#define URPW_RUNMSG		32
//用户管理
#define URPW_USRMGR		64
//系统管理
#define URPW_SYSMGR		128
//修改数据
#define URPW_WRITE		256
//退出程序
#define URPW_EXIT		512

#define CheckPriv_Edit(nPower)		((nPower & URPW_EDIT)==URPW_EDIT)
#define CheckPriv_Run(nPower)		((nPower & URPW_RUN)==URPW_RUN)
#define CheckPriv_PREYK(nPower)		((nPower & URPW_PREYK)==URPW_PREYK)
#define CheckPriv_YK(nPower)		((nPower & URPW_YK)==URPW_YK)
#define CheckPriv_CFMAlarm(nPower)	((nPower & URPW_CFMALARM)==URPW_CFMALARM)
#define CheckPriv_RunMsg(nPower)	((nPower & URPW_RUNMSG)==URPW_RUNMSG)
#define CheckPriv_UsrMgr(nPower)	((nPower & URPW_USRMGR)==URPW_USRMGR)
#define CheckPriv_SysMgr(nPower)	((nPower & URPW_SYSMGR)==URPW_SYSMGR)
#define CheckPriv_Write(nPower)	((nPower & URPW_WRITE)==URPW_WRITE)
#define CheckPriv_Exit(nPower)	((nPower & URPW_EXIT)==URPW_EXIT)

#ifndef baseCUserMsg
#define baseCUserMsg CObject
#endif

#include <afxtempl.h>
#ifndef DLLEXPORT
//	#define	DLLEXPORT	__declspec( dllexport )
	#define	DLLEXPORT extern "C" __declspec( dllexport )
#endif

typedef struct _CUserMsg
{
	CString strDesc;
	CString strUserName;
	CString strPwd;
	CString strEncrypPwd;
	CString strGroupName;

	CString strLoginTime;
	CString strLogoutTime;
	CString strStatus;
	int     nPersistTime;

	int     nPower;
	BOOL	bGroup;

	_CUserMsg()
	{
		nPower = 0;
		bGroup = FALSE;
		nPersistTime = 0;
	}

	operator = (_CUserMsg inUser)
	{
		strUserName = inUser.strUserName;
		strPwd = inUser.strPwd;
		strEncrypPwd = inUser.strEncrypPwd;
		nPower = inUser.nPower;
		strDesc = inUser.strDesc;
		bGroup = inUser.bGroup;
		strGroupName = inUser.strGroupName;
		strLoginTime = inUser.strLoginTime;
		strLogoutTime = inUser.strLogoutTime;
		strStatus = inUser.strStatus;
		nPersistTime = inUser.nPersistTime;
	}
	operator = (User_Info ui)
	{
		strPwd.Format("%s",ui.Password);
		nPower=ui.Power;
		strDesc.Format("%s",ui.Desc);
		bGroup=ui.Group;
		strGroupName.Format("%s",ui.GrpName);
		strLoginTime.Format("%s",ui.LogonTime_C);
		strLogoutTime.Format("%s",ui.LogoffTime_C);
		if(ui.Status==0)
			strStatus.Format("退出");
		else
			strStatus.Format("已登陆");
		nPersistTime = ui.PersistTime;
	}
	void InitUserInfo(User_Info &ui)
	{
		strcpy((char*)ui.Desc,strDesc);
		strcpy((char*)ui.Password,strPwd);
		ui.Power=nPower;
		strcpy((char*)ui.Desc,strDesc);
		ui.Group=bGroup;
		strcpy((char*)ui.GrpName,strGroupName);
	}
	BOOL Serialize(CArchive & ar);
	BOOL EncryptPwd();
	void DecryptPwd();
}CUserMsg;

typedef CArray<CUserMsg,CUserMsg> MsgUserInfoArray;

extern MsgUserInfoArray	m_gAllCUser;
extern MsgUserInfoArray	m_gAllGrp;

DLLEXPORT BOOL LoadAllUser(LPCTSTR strInpath);
DLLEXPORT BOOL SaveAllUser(LPCTSTR strInpath);
DLLEXPORT BOOL SaveDefaultUser();

DLLEXPORT BOOL UserLogon(BYTE* strName,BOOL bRefreshMem=TRUE, HWND hWnd = NULL);
DLLEXPORT BOOL UserLogonWithPower(BYTE* strName,int nPower=3600,BOOL bRefreshMem=TRUE, HWND hWnd = NULL);
DLLEXPORT BOOL UserLogoff(BYTE* strName, HWND hWnd = NULL);
DLLEXPORT BOOL ManageUserInfo(CString & strName, HWND hWnd = NULL);
DLLEXPORT void ManageGrp(HWND hWnd = NULL);

DLLEXPORT int	 CheckUser(LPCTSTR strName,LPCTSTR strPwd);
DLLEXPORT int	 CheckUserPower(LPCTSTR strName, int nPower);
DLLEXPORT int  GetPower(LPCTSTR strName);
DLLEXPORT BOOL GetCurUser(CUserMsg & refUm);
DLLEXPORT BOOL FindUser(LPCTSTR strName,CUserMsg & refUm);
DLLEXPORT int UserIsOuttime(LPCTSTR strName);
#endif // !defined(AFX_USERMSG_H__891CCD4B_4E55_47CA_A430_420211D5E134__INCLUDED_)
