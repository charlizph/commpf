#ifndef CALLBACKFUNDEF_H
#define CALLBACKFUNDEF_H
#ifdef WIN32
#include <afxcmn.h>
#else
#include "mtype.h"
#include "cstring.h"
#endif

#define	PROTEXPORT extern "C" __declspec( dllexport )
//����Ϣ���͸�������m_pWndParent
typedef void (*funSendMsgToParent)(CString strMsg,void* pParentWnd);
//����Ϣ���͸���Ϣ����
typedef void (*funSendDataToWnd)(void* pRecvWnd,void* pBuf,int nLen,BOOL bRecv);
typedef void (*funProtExit)(void* pDevCfg);
typedef void (*funProtInit)(void * pDevCfg,void* pComm);
typedef void (*funSetFlags)(BYTE index,BYTE value);
typedef BOOL (*funSendFram)(void* pComm,void* pDevCfg);
//typedef void (*funSetDataConfPoint)(DATACONF *pDConf);
#ifdef WIN32
typedef void (*funExpFram)(CString strFr,BYTE *pBuf,WORD wLen,CTreeCtrl &tree,BYTE flag);
#endif
//�������ݷ��ͣ����մ���ص����� funProcData
//����˵����pBuf ���յ��ı���
//			nLen ���յ����ĳ���
//			nFlag ���ͽ��ձ�־
//			pComm ���ձ��ĵ�ͨ������CBaseComm��������
//			pWnd ͨ���ĸ����ھ��,���ڽ���ͨ���¼�
//			pDevCfg �豸ָ���Ӧ����CDevCfg
typedef int (*funProcData)(BYTE* pBuf,int nLen,int nFlag,void* pComm,void* pDevCfg);

//�������ݽ��մ���ص����� funProcessData
//����˵����pBuf ���յ��ı���
//			nLen ���յ����ĳ���
//			pComm ���ձ��ĵ�ͨ������CBaseComm��������
//			pWnd ͨ���ĸ����ھ��,���ڽ���ͨ���¼�
//			pDevCfg �豸ָ���Ӧ����CDevCfg
typedef int (*funProcessData)(void* pBuf,int nLen,void* pComm,void* pWnd,void* pDevCfg);

//�������ӶϿ�����ص����� funProcDisCon
//����˵����
//			pComm ���ձ��ĵ�ͨ������CBaseComm��������
//			pWnd ͨ���������ھ��,���ڽ���ͨ���¼�m_pWndMain
typedef void (*funProcDisCon)(void* pComm,void* pWnd,void* pDevCfg);

//�������Ӵ���ص����� funProcConnect
//����˵����
//			pComm ���ձ��ĵ�ͨ������CBaseComm��������
//			pWnd ͨ���������ھ��,���ڽ���ͨ���¼�m_pWndMain
typedef void (*funProcConnect)(void* pComm,void* pWnd,void* pDevCfg);

typedef void (*funSetLinkAdr)(int nAdr);
typedef void (*funInitFF)(void* pComm);

typedef  int (*funSendData)(void* pBuf,int nLen,void* pComm,void* pWnd);
typedef BOOL (*funCreateCfgDlg)(void* pWnd,LPCSTR strFileName);
typedef void (*funLoadProtCfg)(void * pDevCfg,LPCSTR strFileName);
//�޸�����ʱ�Ĳ���
typedef void (*funModRuntimeCfg)(void * pDevCfg,LPCSTR strFileName);
//���½�������֪ͨ
typedef void (*funNotifyReconnect)(void* pDevCfg);

typedef void (*funEmptyParam)();
typedef void (*funVoidPoint)(void* pPoint);
typedef UINT (*funSendThread)(void* pComm);

typedef void (*funAnalyseFrm)(BYTE* pBuf,int wLen,void* pComm);

//�¼�����ص�����
// uEvent:�¼�����EVT_CONSUCCESS��EVT_CONFAILURE����
// pOwner:�¼����մ���
// pSocket:�����¼���ͨ������CBaseComm��������
typedef void (*funEvent)(UINT uEvent,void* pParentWnd,void* pComm);

//�����Զ����
// void* pDevCfg:ͨ���������ã�����ͨ����������ʵʱ����Ϣ����Ӧ����ΪCDevCfg;
typedef BOOL (*funAddOwnTable)(void* pDevCfg);

//������չ���ֶ�
//void* pTableInfo:����Ϣ��TABLE_INFO,�µı��ֶ�ֱ�ӵ���pTableInfo->AddField����;�µ��ֶ�׷���ڱ���ֶμ�ĩ;
typedef void (*funAddExtFld)(void* pTableInfo);

//���ʹ�õ��ı�
//void* pDev CDevCfg�ࣻ
typedef void (*funFillUsedTab)(void* pDev);

//ͨ����������Լ�¼����ά�������ӣ��޸ģ�ɾ����¼��
//void* pRecArray:��������ļ�¼��ָ�룬��Ӧ������ΪCRecArray����������ֻ��Ҫ��pRecArray���в���
//		���Ե���pOneRec->SetStringData������ʵ��.
//CWnd* pParent :������Ϣ���ڣ�֧��������ϢID
//void	pDevCfg �豸ָ���Ӧ����CDevCfg
//����ֵ��ʾ�ɹ����
#define UM_REFRESHITEM WM_USER+20000
//������Ӽ�¼�ĸ�����
//bRemoveOld���Ƿ�ɾ����ǰ�ļ�¼
//typedef bool (*funGetAddedCount)(void* pRecArray,void* pDevCfg,int & nCount,bool & bRemoveOld);
#ifdef WIN32
typedef bool (*funAddRecs)(void* pRecArray,int nStart,CWnd* pParent,void* pDevCfg);
typedef bool (*funAddRecsWithDbMgr)(void* pDbMgr,void* pRecArray,int nStart,CWnd* pParent,void* pDevCfg);
typedef int  (*funGetAddRecsCount)(void* pRecArray,CWnd* pParent,void* pDevCfg);
typedef bool (*funModRecs)(void* pRecArray,CWnd* pParent,void* pDevCfg);
//��ϵͳ�����ʱ�򣬶�̬������Լ�����Ӧ�Ĵ��� 
typedef bool (*funSaveEvent)(void* pRecArray,CWnd* pParent,void* pDevCfg);
#endif
//�������ã���ֵ����
typedef bool (*funSetParam)(void* pDevCfg,void* pComm);

//ά������sysmgrɾ���豸ʵ��֮ǰ���е��ã����������ʵ�ֵĻص�������
typedef bool (*funDelDevice)(void* pDevCfg,LPCSTR strFileName);
//
#endif