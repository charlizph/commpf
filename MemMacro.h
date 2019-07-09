/********************************************************************************************
* 功能说明      : 定义共享内存常用宏
*
* 作  者        : 张培洪
*              
* 创建日期      : 2006年10月17日
* 版本号        : 1.0.1
*********************************************************************************************/

#ifndef MEMMACRO_H
#define MEMMACRO_H

#ifndef WIN32
#include <string.h>
#include "msystem.h"
#include "mtype.h"
#include <errno.h>
#endif

#define MEMTYPE_SRVINFO	1
#define SRVINFO_SIZE	4096
#define DEF_SHARED_SIZE		128
#define VAR_NAME_LENGTH		64

//flag
//第一位状态变化
#define FLAG_NONE 0x01
//产生遥信告警
#define FLAG_YXALARM 0x02
//产生遥测越限告警
#define FLAG_YCALARM 0x04
//保存历史
#define FLAG_SAVEHIS 0x08
#define FLAG_DATACHG 0x10
#define FLAG_READONLY 0x20
#define FLAG_IMPT	0x40
//数据是否上传 转发
#define FLAG_UPTRANS 0x80
//web中显示
#define FLAG_TOWEB   0x100

//status
//数据正常
#define ST_NONE 0x00
//第一位状态变化
#define ST_YXALARM 0x01
//遥测越上限
#define ST_YCHL 0x02
//遥测越上上限
#define ST_YCHHL 0x04
//遥测越下限
#define ST_YCLL 0x08
//遥测越下下限
#define ST_YCLLL 0x10
//挂牌
#define ST_FLAG 0x20
//数据无效
#define ST_INVALID 0x40
#define ST_READONLY 0x80
#define ST_IMPT	0x100

//共享内存变量结构
typedef struct _tagValueHeader {
	char  szValueName[VAR_NAME_LENGTH];		//共享内存中变量名称
	int  nType;		//如果记录中的类型是变化的即变长记录，改类型起作用，最高位为1
					//最高位为0，nType的值无意义，由m_pTabInfo的Field定义类型；
					//变量数据类型;采用VARIANT 类型
//	char rsv1[2];
	int dwUsedLen;                            //变量值使用空间大小
	int dwLength;								//变量占用内存空间大小
	unsigned int	nFlag;//标志位
//	char rsv2[3];
	unsigned int   bValid;
//	char rsv3[3];
	int	nStatus; //告警状态，变量在内存中的索引号
	char szLastTime[32];
	char rsv[32];
//	int   offset;								//变量在内存空间中的起始位置
//	long  lComAdr;//61850 DA 内存地址
	_tagValueHeader()
	{
		memset(szValueName,0,VAR_NAME_LENGTH);
		dwUsedLen = dwLength = 0;
		nFlag = FLAG_NONE;//默认变化传数，只读，不缓存
		bValid = TRUE;
		nStatus = 0;
		nType = 0;
		strcpy(szLastTime,"1970-01-01 08:00:00.000");
		memset(rsv,0,32);
	}

	void operator =(_tagValueHeader vh)
	{
		strcpy(szValueName,vh.szValueName);
		nType = vh.nType;
		dwUsedLen = vh.dwUsedLen;
		dwLength = vh.dwLength;
		nFlag = vh.nFlag;
		bValid = vh.bValid;
		nStatus = vh.nStatus;
	}
	BOOL DataChg(){return GetFlag(FLAG_DATACHG);}
	BOOL IsReadOnlly(){return GetFlag(FLAG_READONLY);}
	BOOL IsImportant(){return GetFlag(FLAG_IMPT);}
	void SetDataChg(BOOL bVal)
	{
		SetFlag(FLAG_DATACHG,bVal);
	}
	void SetReadOnly(BOOL bVal)
	{
		SetFlag(FLAG_READONLY,bVal);
	}
	void SetImportant(BOOL bVal)
	{
		SetFlag(FLAG_IMPT,bVal);
	}

	BOOL GetFlag(int nInFlag){return nInFlag == (nInFlag&nFlag);}
	void SetFlag(int nFlag,BOOL bAdd)
	{
		if(bAdd)
			nFlag |= nFlag;
		else
			nFlag &=~nFlag;
	}
	BOOL GetStatus(int nSt){return nSt == (nSt & nStatus);}
	void SetStatus(int nSt,BOOL bAdd)
	{
		if(bAdd)
			nStatus |= nSt;
		else
			nStatus &=~nSt;
	}
	void SetRecLenIsChg(BOOL bFixed)
	{
		if(bFixed)
			nType= nType|0x10000000;
		else
			nType = nType & 0x0FFFFFFF;
	}
	BOOL RecLenIsChg()
	{
		return ((nType & 0x10000000)==0x10000000);
	}
	int GetType(){return nType & 0x0FFFFFFF;}
} ValueHeader;

//DAT data access type

//字段全部按照索引号访问

//库D，表T，点P都按照索引号
#define DAT_ALLINDEX	0	

//库，表，点都按照名称
#define DAT_ALLNAME		1

//库，表按照名称，点按照内存地址
//#define DAT_DN_TN_PA	2

//库，表按照名称，点按照索引
#define DAT_DN_TN_PI	2

//库按照名称，表按照索引，点按照内存地址
//#define DAT_DN_TI_PA	4

//库按照名称，表，点按照索引
#define DAT_DN_TI_PI	3

//库，点按照名称，表按照索引
#define DAT_DN_TI_PN	4

//库按照索引，表按照名称，点按照内存地址
//#define DAT_DI_TN_PA	7

//库，点按照索引，表按照名称
#define DAT_DI_TN_PI	5

//库按照索引，表，点按照名称
#define DAT_DI_TN_PN	6

//库，表按照索引，点按照内存地址
//#define DAT_DI_TI_PA	10

//库，表按照索引，点按照名称
#define DAT_DI_TI_PN	7

typedef struct _TagDbIndex
{
	_TagDbIndex()
	{
		memset(szDbName,0,VAR_NAME_LENGTH);
		memset(szTabName,0,VAR_NAME_LENGTH);
		memset(szPtName,0,VAR_NAME_LENGTH);
		szDbName[0] = '\0';
		szTabName[0] = '\0';
		szPtName[0] = '\0';

		nDbNo = -1;
		nTabNo = -1;
		nPtNo = -1;
		nFieldNo = -1;//-1对整个记录操作，>-1对相应字段操作  FIXED_FIELD_NUM 对应到0
//		lVarAdr = -1;
		nAcesType = DAT_ALLINDEX;
//		nAttr = -1;
		nFlag = 0x01;//默认变化传数，只读，不缓存
	}
	BOOL operator == (_TagDbIndex dbIn)
	{
		BOOL bDb,bTab,bPt;
		
		bDb = bTab=bPt = FALSE;
		if(dbIn.nDbNo == nDbNo ||
			strcmp(&szDbName[0],&dbIn.szDbName[0]) == 0)
			bDb = TRUE;
		if(dbIn.nTabNo == nTabNo ||
			strcmp(&szTabName[0],&dbIn.szTabName[0]) == 0)
			bTab = TRUE;
		if(dbIn.nPtNo == nPtNo ||
			strcmp(&szPtName[0],&dbIn.szPtName[0]) == 0)
			bPt = TRUE;
		BOOL bEq = bDb && bTab && bPt;
		return bEq;
	}
//	BOOL IsReadOnly()
//	{
//		if(nAttr<0)
//			return FALSE;
//		return (nAttr&0x00000001);
//	}
	char szDbName[VAR_NAME_LENGTH];
	char szTabName[VAR_NAME_LENGTH];
	char szPtName[VAR_NAME_LENGTH];
	int	 nDbNo;//数据库索引号
	int  nTabNo;//数据库表索引号
	int  nPtNo;//记录索引号
	int  nFieldNo;//字段索引号
//	long lVarAdr;
//	int nAttr;//属性0-31位：第0位状态标识是否为只读 ，
	BOOL nFlag;
	short nAcesType;//数据访问方式;
}DbIndex;

typedef struct _TagRegWndInfo{
	char szClassName[128];
	char szWindowName[128];
}RegWndInfo;

//变化传数的索引
typedef struct _TagChgDataIndex{
	_TagChgDataIndex()
	{
		nDbNo = -1;
		nTabNo = -1;
		nPtNo = -1;
		szProcName[0]='\0';
	}
	int	 nDbNo;//数据库索引号
	int  nTabNo;//数据库表索引号
	int  nPtNo;//记录索引号
	BYTE szProcName[32];//产生变化数据进程名称
}ChDIndex;

#endif