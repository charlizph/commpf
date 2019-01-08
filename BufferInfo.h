// BufferInfo.h: interface for the CBufferInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFERINFO_H__FE75B309_E863_48F2_8DB4_94506B4CF0C9__INCLUDED_)
#define AFX_BUFFERINFO_H__FE75B309_E863_48F2_8DB4_94506B4CF0C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXPDU_LEN 8096
#define HEADER_LEN 4
#define RETRY_TIMES 5
#define MAX_TMPBUF	128

#ifdef WIN32
#include "MeteredSection.h"
#else
#include "msystem.h"
#include "mtype.h"
#include "cstring.h"
#endif

typedef union _Int1
{
	_Int1()
	{
		cVal = 0;
	}
	BYTE cVal;
	UINT nVal:8;
}Int1;

typedef union _Int2
{
	_Int2()
	{
		cVal[0] = 0;
		cVal[1] = 0;
	}
	BYTE cVal[2];
	UINT  nVal:16;
}Int2;

class CBufferInfo  
{
public:
	CBufferInfo();
	~CBufferInfo();
	int		m_nRetris;
	BOOL	m_bRecv;
	CString m_strTime;
private:
	int		m_nHeaderLen;
	int		m_nLen;
	BYTE*	m_pData;
	BOOL	m_bMore;
	BYTE	m_cType;
public:
	BOOL	HasMore();
	BOOL	IsValid();
	int		GetHeaderLen();
	int		GetBodyLen();
	int		GetBodyLenByHeader();
	int		GetDataLen();
	void	SetDataLen(int nLen);
	int		SetData(BYTE* pBuf,int nLen);
	BYTE*	GetData(int& nLen);
	void	GetData(BYTE* pBuf/*application alloc mem*/);
	void	GetHeader(BYTE* pBuf/*application alloc mem*/);
	void	GetBody(BYTE* pBuf/*application alloc mem*/);
	int		SetHeader(BYTE* pBuf);
	void	SetBody(BYTE* pBuf,int nLen);
	BYTE    GetDataType();
public:
	void	SetTime();
	void	SetTime(BOOL bRecv );
};

class CManageBuffer
{
public:
	CManageBuffer();
	~CManageBuffer();
private:
#ifdef WIN32
	METERED_SECTION * m_pMutex;
	CPtrList m_aBufferList;
#else
	vector<CBufferInfo*> m_aBufferList;
#endif
	int	m_nRecvIndex;
	int m_nProcIndex;
public:
	void CreateMutex(CString szName);
public:
#ifdef WIN32
	CBufferInfo* GetFirstBuf(POSITION& pos);
	CBufferInfo* GetNextBuf(POSITION& pos);
#else
	CManageBuffer* GetThis(){return this;}
#endif
	int	 GetCount();
	void RemoveAll();
	int	 AddBuffer(CBufferInfo* pInfo);
	int	 AddBuffer(BYTE* pBuf,int nLen);
	void RemoveBuf();
	void RemoveBuf(int nNums);
	CBufferInfo* GetFirstBuf();
	int	 GetFirstBufLen();//与GetCanUseBuf成对使用
	int	 GetCanUseBufLen();//与GetCanUseBuf成对使用
	int	 GetCanUseBuf(BYTE* pBuf,int nLen,BYTE & bufType);
};
#endif // !defined(AFX_BUFFERINFO_H__FE75B309_E863_48F2_8DB4_94506B4CF0C9__INCLUDED_)
