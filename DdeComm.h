// DdeComm.h: interface for the CDdeComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDECOMM_H__5BC04239_58DA_4C66_8AD5_CF8BE0841B0D__INCLUDED_)
#define AFX_DDECOMM_H__5BC04239_58DA_4C66_8AD5_CF8BE0841B0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommBase.h"
#include "ddeml.h"

class CDdeComm : public CBaseComm  
{
public:
	CDdeComm();
	virtual ~CDdeComm();
public:
	BOOL	m_bServer;
	static HCONV	m_hConv;//»á»°¾ä±ú£»
	static DWORD	m_idlnst; //DDEMLÊµÀý¾ä±ú£»
	static HWND	m_hWnd; //´°¿Ú¾ä±ú£»
	static HANDLE	m_hlnst; //ÊµÀý¾ä±ú£»
	static HSZ		m_hszApp; //SERVER·þÎñ×Ö·û´®¾ä±ú£»
	static HSZ		m_hszTopic; //SERVERÄ¿Â¼×Ö·û´®¾ä±ú£»
public:
	BOOL OpenComm();
	BOOL OpenComm(CCommParam oneParam);
	BOOL CloseComm(BOOL bPost = false);
	BOOL IsConnected();
	int  WriteData(void* pBuf,int nLen);
	int	 ReadData(void* pBuf,int nLen);
	virtual bool WatchComm();
};

#endif // !defined(AFX_DDECOMM_H__5BC04239_58DA_4C66_8AD5_CF8BE0841B0D__INCLUDED_)
