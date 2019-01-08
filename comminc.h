#ifndef _COMMINC_H
#define _COMMINC_H

#ifndef WIN32
#include "msystem.h"
#include "mtype.h"
#include "cstring.h"
#endif
//����ͨѶ����(Communication Type - CT)

//û��ͨѶ
#define CT_NONE 0
//����ͨѶ
#define CT_SERIAL 1 
//Tcp �ͻ���
#define CT_TCP_CLIENT 2
//Tcp �����
#define CT_TCP_SERVER 3
//Udp client
#define CT_UDP_CLIENT 4
//udp server
#define CT_UDP_SERVER 5
//net ����
#define CT_MON_NET	6
//port ����
#define CT_MON_PORT	7

//DDE Server
#define CT_DDE_SERVER 8
//DDE Client
#define CT_DDE_CLIENT 9
//���ݿⷽʽͨѶ
#define CT_DATABASE 10
//GSMͨѶ
#define CT_GSM 11

//sample value 
#define CT_ETH_SV 21
//GSSE
#define CT_ETH_GSSE 22
//GOOSE
#define CT_ETH_GOOSE 23

#define ETH_GOOSE	0x88B8
#define ETH_GSE		0x88B9
#define ETH_SV		0x88BA

//����ͨѶ״̬(Communication Status - CS)
//û������
#define CS_DISCON  0
//����
#define CS_CONNECT 1
//�쳣
#define CS_ABORT   2

//�����ջ�����
#ifdef WIN32
#define BUFFER_SIZE		1024000
#else
#define BUFFER_SIZE		65535
#endif
//1024000
//65535

//Enums
enum FlowControl
{
	NoFlowControl,
		CtsRtsFlowControl,
		CtsDtrFlowControl,
		DsrRtsFlowControl,
		DsrDtrFlowControl,
		XonXoffFlowControl
};

enum Parity
{    
		NoParity,
		OddParity,
		EvenParity,
		MarkParity,
		SpaceParity
};

enum StopBits
{
	OneStopBit,
		OnePointFiveStopBits,
		TwoStopBits
};

// Event value
#define EVT_CONSUCCESS		0x0000	// Connection established
#define EVT_CONFAILURE		0x0001	// General failure - Wait Connection failed
#define EVT_CONDROP			0x0002	// Connection dropped
#define EVT_ZEROLENGTH		0x0003	// Zero length message
#define EVT_CRTCLTSOCK		0x0004  // ����˽��յ��ͻ������󣬲��ɹ�������sock

//�¼�id wparam Ϊ�¼�����ֵevent value
#define UM_EVENT	WM_USER+20000
//ͨ�����յ�������Ϣ
#define UM_RECVDATA	WM_USER+20001
//ͨ������������Ϣ
#define UM_SENDDATA WM_USER+20002
//��Ϣ��Ϣ
#define UM_MSGINFO  WM_USER+20003
//ͨ�����յ�����ASCCII��Ϣ
#define UM_RECVASCDATA	WM_USER+20004
//ͨ����������ASCCII��Ϣ
#define UM_SENDASCDATA	WM_USER+20005

//ʱ���ʽ1��yyyy-mm-dd hh:mm:ss.xxx
#define TIMETYPE1 1
//ʱ���ʽ2��yyyy-mm-dd hh:mm:ss
#define TIMETYPE2 2
//ʱ���ʽ3  mm-dd hh:mm:ss.xxx
#define TIMETYPE3 3
//ʱ���ʽ4��dd hh:mm:ss.xxx
#define TIMETYPE4 4
//ʱ���ʽ5��hh:mm:ss.xxx
#define TIMETYPE5 5
//ʱ���ʽ6��hh:mm:ss
#define TIMETYPE6 6

//���屨���Ƿ��ͻ���պ�
//����
#define DIREC_SEND 0
//����
#define DIREC_RECV 1



//�¼�����ص�����
//typedef void (*funEvent)(UINT uEvent,void* pOwner);
#include "xml.h"

//tcp serverĬ�����������
#define MAX_CONN	10

class CCommParam{
public:
	CCommParam();
	virtual ~CCommParam();
public:
	BOOL SaveParam(XMLElement* pRootNode);
	BOOL LoadParam(XMLElement* pRootNode);
public:
	BOOL bUsed;//�Ƿ�����
	BOOL bAsync;//�շ������Ƿ��첽;
	int nWriteRetryTimes;//����ʧ�����Դ���,Ĭ��Ϊ3
	int nPort; //���ڴ��ڡ��ǣ����ںţ����ڣ����/udp ��server�˿�
	int nTimeOut;//���ڴ����Ƕ����ݳ�ʱ��tcp�����ӳ�ʱ ��λ��
	int nCommType;//ͨѶ����;Ĭ��tcp client��
	int	nRecvInterval;//���ݽ���ɨ������ ��λ���� Ĭ��10ms;
	int	nSendInterval;//���ݷ��Ͷ���ɨ�����ڣ���λ���� Ĭ��1000ms;
	int nRecvTimeOut;//���ݽ��ճ�ʱ����λ�� < 1 ���жϳ�ʱ
	int nDelateConAlert;//���ӶϿ����ӳٸ澯ʱ�� ��λ��<1��ʾ���ж�
	int lLastAlertTime;
//for serial
	int	nBaudRate;//Ĭ��ֵ������������
	int nParity;//Ĭ��ֵ��NoParity
	int nDataBits;//Ĭ��ֵ����
	int nStopBits;//Ĭ��ֵ��OneStopBit
	int nFlowControl;//Ĭ��ֵ��XonXoffFlowControl
	int bOverlapped;//Ĭ��ֵ���ԣңգ�
	int nRecvBufLen;
	int nSendBufLen;
//for tcp
	CString strIpAdr;//for db is dbserver name for serial is com name;
	UINT nOptions;//
	int nFamily;//Ĭ��ֵ AF_INET
	int	nCircleTime;//select ������ʱʱ�䣬Ĭ��ֵ60000ms
//	BOOL bKeepAlive;//
	int	nMaxConnect;//���������Ĭ��10��for server
//for udp
	BOOL bSendHand;
	BOOL bSmartAdr;//�㲥/�㴫������
	CString strBroadAdr;//
//	CString strBroadAdr2;//
//	CString strBroadAdr3;//
	int nTargetPort;
// for net monitor
	CString strNetDevName;//�����豸��; for dde is service name
	CString strFilter;//��������� Ĭ��tcp or ip;  for dde is topic
	CString strDesIpAdr;//Ŀ��ip��ַ; 
//for db
	CString strDriver;
public:
	void operator = (CCommParam inParam);
};


#define MSG_INFO	12000
#define MSG_RCDATA WM_USER + 10000
#define MSG_CRTSOCK WM_USER+ 10001
#define MSG_CLOSESOCK WM_USER+ 10002
#define MSG_UPDATESTATUS WM_USER + 10010
#define MSG_UPFILE	WM_USER+10020

#define WM_UPDATE_CONNECTION	WM_APP+0x1234

#include "CallBackFunDef.h"
#ifndef WIN32
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKET int
#define SOCKADDR_IN sockaddr_in
#define CloseHandle close
#endif
#endif

#endif