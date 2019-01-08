// PrjMgr.h: interface for the CPrjMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRJMGR_H__45B9510F_E291_48E2_BAD5_57CFA3E86F7D__INCLUDED_)
#define AFX_PRJMGR_H__45B9510F_E291_48E2_BAD5_57CFA3E86F7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//节点类型NodeType-NT
//S-Sigle
//N-Node
//C-Computer
//D-Double
#ifndef WIN32
#include "cstring.h"
#endif
#define NT_SNSC 0
#define NT_SNDC	1
#define NT_DNSC	2
#define NT_DNDC 3

#include "DbConInfo.h"

class XMLElement;
class COnePrj
{
public:
	COnePrj();
	virtual ~COnePrj();
public:
//	BOOL SavePrj(CStdioFile& file);
//	BOOL LoadPrj(CString strRead);

	BOOL SavePrj(XMLElement* pXmlElement);
	BOOL LoadPrj(XMLElement* pXmlElement);
	void CopyInfo(COnePrj* pPrj)
	{
		m_bAutoRun = pPrj->m_bAutoRun;
		m_bDefault=pPrj->m_bDefault;
		m_bDlgMain=pPrj->m_bDlgMain;
		m_bSaveHisDb=pPrj->m_bSaveHisDb;
		m_nNodeType=pPrj->m_nNodeType;
		m_nSubAdr=pPrj->m_nSubAdr;
		m_strPrjName=pPrj->m_strPrjName;
		m_strPrjPath=pPrj->m_strPrjPath;
		m_strTBName = pPrj->m_strTBName;
	}
public:
	BOOL	m_bDlgMain;//是否对话框风格1,多文档风格0
	BOOL	m_bSaveHisDb;
	int		m_nSubAdr;
	CString m_strPrjName; // 工程名称
	CString m_strPrjPath;//协议库 名
	CString m_strTBName;//工具栏动态库名
	int		m_nNodeType;
	BOOL	m_bAutoRun;
	BOOL	m_bDefault;//是否为缺省工程及当前使用工程
	BOOL	IsDoubleCp();//是否为单机；
	BOOL	IsDoubleNet();//是否为单网;
	CString GetFullPrjPath();
};

class CPrjMgr
{
public:
	CPrjMgr();
	~CPrjMgr();
public:
#ifdef WIN32
	static CPtrArray m_aPrjList;
	CPtrArray m_prjList;
#else
	static std::vector<void *> m_aPrjList;
	std::vector<void *> m_prjList;
#endif 
	static COnePrj* m_pCurPrj;

public: 
	static void Clear();
	static void LoadAllPrj(); 
	static void SaveAllPrj();
	static COnePrj* GetCurPrj();

	void ClearOwn();
	void LoadAllPrj(CString strCfgFile); 
	void SaveAllPrj(CString strCfgFile);
};

//extern CPrjMgr	gPrjList;
//extern COnePrj* gCurPrj;
extern CString GetCurPrjPath();
extern CString GetPrjPath();
extern COnePrj* GetCurPrj();
extern void ClearPrjList();
//获得路局->车间->车站->车站->道岔->转辙机的逻辑关系按照顺序排列
#ifdef WIN32
extern BOOL LoadTabRelation(CStringArray & aStrTab);
extern BOOL SaveTabRelation(CStringArray & aStrTab);
#endif
//extern void LoadAllPrj();
//extern void SaveAllPrj();
#endif // !defined(AFX_PRJMGR_H__45B9510F_E291_48E2_BAD5_57CFA3E86F7D__INCLUDED_)
