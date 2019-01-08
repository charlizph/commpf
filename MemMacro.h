/********************************************************************************************
* ����˵��      : ���干���ڴ泣�ú�
*
* ��  ��        : �����
*              
* ��������      : 2006��10��17��
* �汾��        : 1.0.1
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
//��һλ״̬�仯
#define FLAG_NONE 0x01
//����ң�Ÿ澯
#define FLAG_YXALARM 0x02
//����ң��Խ�޸澯
#define FLAG_YCALARM 0x04
//������ʷ
#define FLAG_SAVEHIS 0x08
#define FLAG_DATACHG 0x10
#define FLAG_READONLY 0x20
#define FLAG_IMPT	0x40
//�����Ƿ��ϴ� ת��
#define FLAG_UPTRANS 0x80
//web����ʾ
#define FLAG_TOWEB   0x100

//status
//��������
#define ST_NONE 0x00
//��һλ״̬�仯
#define ST_YXALARM 0x01
//ң��Խ����
#define ST_YCHL 0x02
//ң��Խ������
#define ST_YCHHL 0x04
//ң��Խ����
#define ST_YCLL 0x08
//ң��Խ������
#define ST_YCLLL 0x10
//����
#define ST_FLAG 0x20
//������Ч
#define ST_INVALID 0x40
#define ST_READONLY 0x80
#define ST_IMPT	0x100

//�����ڴ�����ṹ
typedef struct _tagValueHeader {
	char  szValueName[VAR_NAME_LENGTH];		//�����ڴ��б�������
	int  nType;		//�����¼�е������Ǳ仯�ļ��䳤��¼�������������ã����λΪ1
					//���λΪ0��nType��ֵ�����壬��m_pTabInfo��Field�������ͣ�
					//������������;����VARIANT ����
//	char rsv1[2];
	int dwUsedLen;                            //����ֵʹ�ÿռ��С
	int dwLength;								//����ռ���ڴ�ռ��С
	unsigned int	nFlag;//��־λ
//	char rsv2[3];
	unsigned int   bValid;
//	char rsv3[3];
	int	nStatus; //�澯״̬���������ڴ��е�������
	char szLastTime[32];
	char rsv[32];
//	int   offset;								//�������ڴ�ռ��е���ʼλ��
//	long  lComAdr;//61850 DA �ڴ��ַ
	_tagValueHeader()
	{
		memset(szValueName,0,VAR_NAME_LENGTH);
		dwUsedLen = dwLength = 0;
		nFlag = FLAG_NONE;//Ĭ�ϱ仯������ֻ����������
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

//�ֶ�ȫ�����������ŷ���

//��D����T����P������������
#define DAT_ALLINDEX	0	

//�⣬���㶼��������
#define DAT_ALLNAME		1

//�⣬�������ƣ��㰴���ڴ��ַ
//#define DAT_DN_TN_PA	2

//�⣬�������ƣ��㰴������
#define DAT_DN_TN_PI	2

//�ⰴ�����ƣ������������㰴���ڴ��ַ
//#define DAT_DN_TI_PA	4

//�ⰴ�����ƣ����㰴������
#define DAT_DN_TI_PI	3

//�⣬�㰴�����ƣ���������
#define DAT_DN_TI_PN	4

//�ⰴ���������������ƣ��㰴���ڴ��ַ
//#define DAT_DI_TN_PA	7

//�⣬�㰴����������������
#define DAT_DI_TN_PI	5

//�ⰴ�����������㰴������
#define DAT_DI_TN_PN	6

//�⣬�����������㰴���ڴ��ַ
//#define DAT_DI_TI_PA	10

//�⣬�����������㰴������
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
		nFieldNo = -1;//-1��������¼������>-1����Ӧ�ֶβ���  FIXED_FIELD_NUM ��Ӧ��0
//		lVarAdr = -1;
		nAcesType = DAT_ALLINDEX;
//		nAttr = -1;
		nFlag = 0x01;//Ĭ�ϱ仯������ֻ����������
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
	int	 nDbNo;//���ݿ�������
	int  nTabNo;//���ݿ��������
	int  nPtNo;//��¼������
	int  nFieldNo;//�ֶ�������
//	long lVarAdr;
//	int nAttr;//����0-31λ����0λ״̬��ʶ�Ƿ�Ϊֻ�� ��
	BOOL nFlag;
	short nAcesType;//���ݷ��ʷ�ʽ;
}DbIndex;

typedef struct _TagRegWndInfo{
	char szClassName[128];
	char szWindowName[128];
}RegWndInfo;

//�仯����������
typedef struct _TagChgDataIndex{
	_TagChgDataIndex()
	{
		nDbNo = -1;
		nTabNo = -1;
		nPtNo = -1;
		szProcName[0]='\0';
	}
	int	 nDbNo;//���ݿ�������
	int  nTabNo;//���ݿ��������
	int  nPtNo;//��¼������
	BYTE szProcName[32];//�����仯���ݽ�������
}ChDIndex;

#endif