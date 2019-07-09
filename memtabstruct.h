/////////////////////////////////////////////////
//   
//    MemDbTabStruct.h        
//   
//    ��ʵʱ���ݿ⵼��ʵʱ���ݿ��ṹ.H�ļ�   
//   
/////////////////////////////////////////////////


#ifndef __MEMTABSTRUCT_H_2003_12_LT
#define __MEMTABSTRUCT_H_2003_12_LT



//============ ϵͳ��Ϣ ��ṹ ================

#ifndef Snmp_System_TABNAME
#define Snmp_System_TABNAME 	 _T("Snmp_System")

struct Snmp_System { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //ң��ֵ ��:0/��:1/ֵ00:2/ֵ11:3/
	short 	m_oid;	 //�����ʶ�� 
};
#endif



//============ �˿ڱ� ��ṹ ================

#ifndef Snmp_ifTable_TABNAME
#define Snmp_ifTable_TABNAME 	 _T("Snmp_ifTable")

struct Snmp_ifTable { 
	BYTE 	ifIndex;	 //�˿ں� 
	BYTE 	ifDesc[32];	 //���� 
	BYTE 	ifType;	 //���� unknown:0/other:1/regular1822:2/hdh1822:3/ddnX25:4/rfc877x25:5/ethernetCsmacd:6/iso88023Csmacd:7/iso88024TokenBus:8/iso88025TokenRing:9/iso88026Man:10/starLan:11/proteon10Mbit:12/proteon80Mbit:13/hyperchannel:14/fddi:15/lapb:16/sdlc:17/ds1:18/e1:19/
	unsigned short 	ifMtu;	 //����ĳ��� 
	unsigned int 	ifSpeed;	 //�����ٶ� 
	BYTE 	ifPhysAddress[32];	 //�����ַ 
	BYTE 	ifAdminStatus;	 //����״̬ ����:1/ͣ��:2/����:3/
	BYTE 	ifOperStatus;	 //����״̬ ����:1/�Ͽ�:2/����:3/δ֪:4/����:5/����:6/�ײ�Ͽ�:7/
	BYTE 	ifLastChange[32];	 //������ 
	unsigned long 	ifInOctets;	 //�����ֽ� 
	unsigned long 	ifInUcastPkts;	 //����Ucast�� 
	unsigned long 	ifInNUcastPkts;	 //����NUcast�� 
	unsigned long 	ifInDiscards;	 //�����İ� 
	unsigned long 	ifInErrors;	 //���մ��� 
	unsigned long 	ifInUnknownProtos;	 //����δ֪Э�� 
	unsigned long 	ifOutOctets;	 //�����ֽ� 
	unsigned long 	ifOutUcastPkts;	 //����Ucast�� 
	unsigned long 	ifOutNUcastPkts;	 //����NUcast�� 
	unsigned long 	ifOutDiscards;	 //���ͷ����İ� 
	unsigned long 	ifOutErrors;	 //���ʹ��� 
	unsigned long 	ifOutQLen;	 //���Ͱ����г��� 
	BYTE 	ifSpecific[64];	 //��ע 
};
#endif



//============ ˫ң���� ��ṹ ================

#ifndef DYX_STRUCT_TABNAME
#define DYX_STRUCT_TABNAME 	 _T("DYX_STRUCT")

struct DYX_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //ң��ֵ �쳣:00/��:01/��10:2/�쳣11:3/
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� ����:0/��բ:1/�����ź�:2/�¹����ź�:3/�¹��ź�:4/�澯�ź�:5/
	BYTE 	m_inverter;	 //������ ����:0/����:1/
	BYTE 	m_op_status;	 //����״̬ ����:0/����:1/����:2/�ӵ�:3/
	BYTE 	m_yx_status;	 //ң��״̬ ����:0/��λ:1/�¹�:2/
	BYTE 	m_processtag;	 //�����־ ��澯:0/���¼:1/���ӡ:2/����:3/���ƻ���:4/
	int 	m_fh_count;	 //��-�ϴ��� 
	int 	m_hf_count;	 //��-�ִ��� 
	int 	m_sg_count;	 //�¹ʴ��� 
	BYTE 	m_vol_degree;	 //��ѹ�ȼ� 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //�澯�ȼ� һ���澯:0/�����澯:1/�����澯:2/
	BYTE 	m_picture[64];	 //�Ƴ������� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ң���� ��ṹ ================

#ifndef YX_STRUCT_TABNAME
#define YX_STRUCT_TABNAME 	 _T("YX_STRUCT")

struct YX_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //ң��ֵ ��:0/��:1/ֵ10:2/ֵ11:3/
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� ����:0/��բ:1/�����ź�:2/�¹����ź�:3/�¹��ź�:4/�澯�ź�:5/
	BYTE 	m_inverter;	 //������ ����:0/����:1/
	BYTE 	m_op_status;	 //����״̬ ����:0/����:1/����:2/�ӵ�:3/
	BYTE 	m_yx_status;	 //ң��״̬ ����:0/��λ:1/�¹�:2/
	BYTE 	m_processtag;	 //�����־ ��澯:0/���¼:1/���ӡ:2/����:3/���ƻ���:4/
	int 	m_fh_count;	 //��-�ϴ��� 
	int 	m_hf_count;	 //��-�ִ��� 
	int 	m_sg_count;	 //�¹ʴ��� 
	BYTE 	m_vol_degree;	 //��ѹ�ȼ� 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //�澯�ȼ� һ���澯:0/�����澯:1/�����澯:2/
	BYTE 	m_picture[64];	 //�Ƴ������� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ң��� ��ṹ ================

#ifndef YC_STRUCT_TABNAME
#define YC_STRUCT_TABNAME 	 _T("YC_STRUCT")

struct YC_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //ʵ��ֵ 
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� �й�:0/�޹�:1/����:2/��ѹ:3/Ƶ��:4/��������:5/ˮλ:6/�¶�:7/
	int 	m_code;	 //��ֵ 
	float 	m_coeff;	 //ϵ�� 
	float 	m_base;	 //��ֵ 
	float 	m_zero;	 //���㷶Χ 
	float 	m_top;	 //���ֵ 
	float 	m_bottom;	 //��Сֵ 
	float 	m_dead;	 //������Χ 
	BYTE 	m_op_status;	 //����״̬ ����:0/����:1/
	BYTE 	m_processtag;	 //�����־ ��澯:0/���¼:1/���ӡ:2/����:3/��׷��:5/
	BYTE 	m_vol_degree;	 //��ѹ�ȼ� 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //�澯�ȼ� һ���澯:0/�����澯:1/�����澯:2/
	BYTE 	m_yc_status;	 //ң��״̬ ����:0/Խ����:1/Խ������:2/Խ����:3/Խ������:4/
	BYTE 	m_limit_mark;	 //��ֵ��־ ����ֵ:0/����ֵ:1/
	float 	m_uplimit;	 //���� 
	float 	m_uuplimit;	 //������ 
	float 	m_downlimit;	 //���� 
	float 	m_ddownlimit;	 //������ 
	int 	m_over_time;	 //Խ��ʱ�� 
	int 	m_over_up_time;	 //Խ����ʱ�� 
	int 	m_over_uup_time;	 //Խ������ʱ�� 
	int 	m_over_down_time;	 //Խ����ʱ�� 
	int 	m_over_ddown_time;	 //Խ������ʱ�� 
	float 	m_hgl;	 //Խ����ʱ�� 
	float 	m_updead;	 //�������� 
	float 	m_downdead;	 //�������� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ �������� ��ṹ ================

#ifndef PULSE_STRUCT_TABNAME
#define PULSE_STRUCT_TABNAME 	 _T("PULSE_STRUCT")

struct PULSE_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //ʵ��ֵ 
	short 	m_facno;	 //���� 
	BYTE 	m_terminal[32];	 //������ 
	int 	m_code;	 //��ֵ 
	float 	m_coeff;	 //ϵ�� 
	float 	m_base;	 //��ֵ 
	float 	m_zero;	 //���㷶Χ 
	float 	m_top;	 //����ֵ 
	float 	m_dead;	 //������Χ 
	BYTE 	m_op_status;	 //����״̬ ����:0/����:1/
	BYTE 	m_processtag;	 //�����־ ��澯:0/���¼:1/���ӡ:2/����:3/
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ��ȱ� ��ṹ ================

#ifndef KWH_STRUCT_TABNAME
#define KWH_STRUCT_TABNAME 	 _T("KWH_STRUCT")

struct KWH_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //ʵ��ֵ 
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� ���ֵ:0/���ֵ:1/
	BYTE 	m_pulseid[6];	 //���ң���� 
	float 	m_pre_frame;	 //��ֵ֡ 
	float 	m_top;	 //����ֵ 
	DATE 	m_start_time;	 //��ʼ����ʱ�� 
	DATE 	m_end_time;	 //�����ۼ�ʱ�� 
	float 	m_kwh_accumulate;	 //�ۼ�ֵ 
	float 	m_kwh_hour;	 //ʱ�ۼ� 
	float 	m_kwh_day;	 //���ۼ� 
	float 	m_kwh_month;	 //���ۼ� 
	float 	m_kwh_year;	 //���ۼ� 
	BYTE 	m_op_status;	 //����״̬ ����:0/����:1/
	BYTE 	m_sample_tag;	 //������־ 
	int 	m_mincycle;	 //���Ӽ�� 
	float 	m_kwh_minute;	 //�����ۼ� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ң�ر� ��ṹ ================

#ifndef YK_STRUCT_TABNAME
#define YK_STRUCT_TABNAME 	 _T("YK_STRUCT")

struct YK_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //ʵ��ֵ 
	short 	m_facno;	 //���� 
	BYTE 	m_yx_rel[64];	 //���ң�� 
	short 	m_switch_no;	 //���غ� 
	short 	m_open_obj;	 //�ֶ���� 
	short 	m_close_obj;	 //�϶���� 
	BYTE 	m_yktype;	 //�������� �������:0/˫�����:1/
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ң�ر����� ��ṹ ================

#ifndef YK_LOCK_TABNAME
#define YK_LOCK_TABNAME 	 _T("YK_LOCK")

struct YK_LOCK { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_value;	 //����ң��ֵ ��:0/��:1/
	short 	m_facno;	 //���� 
	BYTE 	m_yk_obj[6];	 //����ң�ض��� 
	BYTE 	m_lock_condition[6];	 //��������ID 
	BYTE 	m_yk_op_status;	 //����ң�ز��� ��:0/��:1/
	BYTE 	m_lock_op;	 //�������� ����:0/����:1/С��:2/
	float 	m_yc_value;	 //����ң��ֵ 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ����ң�ű� ��ṹ ================

#ifndef YX_BH_STRUCT_TABNAME
#define YX_BH_STRUCT_TABNAME 	 _T("YX_BH_STRUCT")

struct YX_BH_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //ʵ��ֵ ��:0/��:1/
	short 	m_facno;	 //���� 
	BYTE 	m_yx[6];	 //ң��ID 
	short 	m_num;	 //��ر������� 
	BYTE 	m_bh1[6];	 //��ر���1 
	BYTE 	m_bh2[6];	 //��ر���2 
	BYTE 	m_bh3[6];	 //��ر���3 
	BYTE 	m_bh4[6];	 //��ر���4 
	BYTE 	m_bh5[6];	 //��ر���5 
	BYTE 	m_bh6[6];	 //��ر���6 
	BYTE 	m_bh7[6];	 //��ر���7 
	BYTE 	m_bh8[6];	 //��ر���8 
	BYTE 	m_bh9[6];	 //��ر���9 
	BYTE 	m_bh10[6];	 //��ر���10 
	BYTE 	m_bh11[6];	 //��ر���11 
	BYTE 	m_bh12[6];	 //��ر���12 
	BYTE 	m_bh13[6];	 //��ر���13 
	BYTE 	m_bh14[6];	 //��ر���14 
	BYTE 	m_bh15[6];	 //��ر���15 
	BYTE 	m_bh16[6];	 //��ر���16 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ ������ڵ�� ��ṹ ================

#ifndef NodeInfo_TABNAME
#define NodeInfo_TABNAME 	 _T("NodeInfo")

struct NodeInfo { 
	BYTE 	m_cpname[32];	 //������� 
	BYTE 	m_mIpAdr[32];	 //��IP��ַ 
	BYTE 	m_sIpAdr[32];	 //��IP��ַ 
	BYTE 	m_rdbMaster;	 //ʵʱ������ ��ͨ����վ:0/ֵ������:1/��������
	BYTE 	m_hisMaster;	 //��ʷ������ ��ͨ����վ:0/����:1/��������:2/
	BYTE 	m_tciMaster;	 //ǰ�û����� ��ͨ����վ:0/��ǰ�û�:1/����ǰ�û�:2/
	BYTE 	m_status;	 //�ڵ�״̬ �˳�:0/Ͷ��:1/
	int 	m_functype;	 //������ �����ӡ:0/����༭:1/�޸����ݿ�:2/�û�����:3/�澯��ӡ:4/��������:5/�ƻ���:6/
	int 	m_heartbeat;	 //�������� 
};
#endif



//============ ϵͳ���̱� ��ṹ ================

#ifndef SysProcess_TABNAME
#define SysProcess_TABNAME 	 _T("SysProcess")

struct SysProcess { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //״̬ �˳�:0/����:1/����:2/
	BYTE 	m_fullpath[255];	 //·�� 
	BYTE 	m_type;	 //���� ��ͨ:0/�ؼ�����:1/
	int 	m_pid;	 //���̺� 
	BYTE 	m_runhost[255];	 //���л��� 
};
#endif



//============ ң���� ��ṹ ================

#ifndef YT_STRUCT_TABNAME
#define YT_STRUCT_TABNAME 	 _T("YT_STRUCT")

struct YT_STRUCT { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //��ǰֵ 
	short 	m_facno;	 //���� 
	short 	m_up_yt_no;	 //�ϵ�ң���� 
	short 	m_down_yt_no;	 //�µ�ң���� 
	short 	m_stop_yt_no;	 //��ͣң���� 
	BYTE 	m_current_yt_pos;	 //��λ 
	BYTE 	m_max_yt_pos;	 //���λ 
	BYTE 	m_min_yt_pos;	 //��С��λ 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ 61850DAֵ ��ṹ ================

#ifndef DAMEM_TABNAME
#define DAMEM_TABNAME 	 _T("DAMEM")

struct DAMEM { 
	BYTE 	m_desc[128];	 //���� 
	BYTE 	DADATA[64];	 //DAֵ 
};
#endif



//============ �ͻ���61850DAֵ ��ṹ ================

#ifndef CLTDAMEM_TABNAME
#define CLTDAMEM_TABNAME 	 _T("CLTDAMEM")

struct CLTDAMEM { 
	BYTE 	m_desc[128];	 //���� 
	BYTE 	DADATA[64];	 //DAֵ 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ SOE ��ṹ ================

#ifndef SOEMEM_TABNAME
#define SOEMEM_TABNAME 	 _T("SOEMEM")

struct SOEMEM { 
	BYTE 	Status;	 //״̬ 
	short 	Year;	 //�� 
	BYTE 	Month;	 //�� 
	BYTE 	Day;	 //�� 
	BYTE 	Hour;	 //ʱ 
	BYTE 	Minute;	 //�� 
	BYTE 	Second;	 //�� 
	short 	Mics;	 //���� 
	BYTE 	PointName[64];	 //�������� 
	BYTE 	DbName[32];	 //�������ݿ��� 
	short 	TableNo;	 //������� 
};
#endif



//============ ң���ڴ�� ��ṹ ================

#ifndef YtMem_TABNAME
#define YtMem_TABNAME 	 _T("YtMem")

struct YtMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	float 	SetVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	BOOL 	Comand;	 //�������� �ϵ�:0/�µ�:1/��ͣ:2/
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};
#endif



//============ ң���ڴ�� ��ṹ ================

#ifndef YkMem_TABNAME
#define YkMem_TABNAME 	 _T("YkMem")

struct YkMem { 
	long 	InvokeId;	 //���ݱ�ʶ 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	BYTE 	CtrlVal;	 //����ֵ 
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	BYTE 	Comand;	 //�������� ң��Ԥѡ:1/ң��ִ��:2/ң��ȡ��:3/
	long 	SendTime;	 //����ʱ�� 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};
#endif



//============ ��дָ�� ��ṹ ================

#ifndef RWPTR_TABNAME
#define RWPTR_TABNAME 	 _T("RWPTR")

struct RWPTR { 
	int 	PtrPos;	 //ָ��λ�� 
};
#endif



//============ Modbusģ���� ��ṹ ================

#ifndef MODBUS_YC_TABNAME
#define MODBUS_YC_TABNAME 	 _T("MODBUS_YC")

struct MODBUS_YC { 
	BYTE 	Desc[32];	 //���� 
	float 	Value;	 //����ֵ 
	unsigned short 	DevAdr;	 //�豸��ַ 
	unsigned short 	StartAdr;	 //�Ĵ�����ַ 
	float 	Coeff;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ�޷�������:4/32λIEEE������:5/32λ�з�������:6/64λ˫����:7/
	BYTE 	CmdType;	 //�������� ��Ȧ״̬:1/����״̬:2/���ּĴ���:3/����Ĵ���:4/ǿ�Ƶ�����Ȧ:5/Ԥ�õ����Ĵ���:6/��������״̬:7/���:8/ͨѶ�¼�����:11/ͨѶ�¼���¼:12/���������:13/��ѯ������:14/ǿ�ƶ���Ĵ���:15/Ԥ�ö���Ĵ���:16/����ӻ� ID:17/ͨѶ��·��λ:19/��ͨ��ֵ:20/дͨ��ֵ:21/
};
#endif



//============ Modbus������ ��ṹ ================

#ifndef MODBUS_YX_TABNAME
#define MODBUS_YX_TABNAME 	 _T("MODBUS_YX")

struct MODBUS_YX { 
	BYTE 	Desc[32];	 //���� 
	BYTE 	Value;	 //����ֵ 
	unsigned short 	DevAdr;	 //�豸��ַ 
	unsigned short 	StartAdr;	 //�Ĵ�����ַ 
	unsigned int 	UsedBit;	 //ʹ�õ�λ ��0λ:0/��1λ:1/��2λ:2/��3λ:3/��4λ:4/��5λ:5/��6λ:6/��7λ:7/��8λ:8/��9λ:9/��10λ:10/��11λ:11/��12λ:12/��13λ:13/��14λ:14/��15λ:15/ȫ��λ:16/
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ����:4/32λIEEE������:5/
	BYTE 	CmdType;	 //�������� ��Ȧ״̬:1/����״̬:2/���ּĴ���:3/����Ĵ���:4/ǿ�Ƶ�����Ȧ:5/Ԥ�õ����Ĵ���:6/��������״̬:7/���:8/ͨѶ�¼�����:11/ͨѶ�¼���¼:12/���������:13/��ѯ������:14/ǿ�ƶ���Ĵ���:15/Ԥ�ö���Ĵ���:16/����ӻ� ID:17/ͨѶ��·��λ:19/��ͨ��ֵ:20/дͨ��ֵ:21/
};
#endif



//============ 61850Modbusģ���� ��ṹ ================

#ifndef MMSMODBUS_YC_TABNAME
#define MMSMODBUS_YC_TABNAME 	 _T("MMSMODBUS_YC")

struct MMSMODBUS_YC { 
	BYTE 	Desc[32];	 //���� 
	float 	Value;	 //����ֵ 
	unsigned short 	DevAdr;	 //�豸��ַ 
	unsigned short 	StartAdr;	 //�Ĵ�����ַ 
	float 	Coeff;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ�޷�������:4/32λIEEE������:5/32λ�з�������:6/64λ˫����:7/
	BYTE 	CmdType;	 //�������� ��Ȧ״̬:1/����״̬:2/���ּĴ���:3/����Ĵ���:4/ǿ�Ƶ�����Ȧ:5/Ԥ�õ����Ĵ���:6/��������״̬:7/���:8/ͨѶ�¼�����:11/ͨѶ�¼���¼:12/���������:13/��ѯ������:14/ǿ�ƶ���Ĵ���:15/Ԥ�ö���Ĵ���:16/����ӻ� ID:17/ͨѶ��·��λ:19/��ͨ��ֵ:20/дͨ��ֵ:21/
	BYTE 	Map61850Db[16];	 //61850������ 
	BYTE 	Map61850Tab[16];	 //61850������ 
	BYTE 	Map61850Pt[64];	 //61850������ 
	int 	Map61850PtId;	 //61850���������� 
};
#endif



//============ 61850Modbus������ ��ṹ ================

#ifndef MMSMODBUS_YX_TABNAME
#define MMSMODBUS_YX_TABNAME 	 _T("MMSMODBUS_YX")

struct MMSMODBUS_YX { 
	BYTE 	Desc[32];	 //���� 
	BYTE 	Value;	 //����ֵ 
	unsigned short 	DevAdr;	 //�豸��ַ 
	unsigned short 	StartAdr;	 //�Ĵ�����ַ 
	unsigned int 	UsedBit;	 //ʹ�õ�λ ��0λ:0/��1λ:1/��2λ:2/��3λ:3/��4λ:4/��5λ:5/��6λ:6/��7λ:7/��8λ:8/��9λ:9/��10λ:10/��11λ:11/��12λ:12/��13λ:13/��14λ:14/��15λ:15/ȫ��λ:16/
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ����:4/32λIEEE������:5/
	BYTE 	CmdType;	 //�������� ��Ȧ״̬:1/����״̬:2/���ּĴ���:3/����Ĵ���:4/ǿ�Ƶ�����Ȧ:5/Ԥ�õ����Ĵ���:6/��������״̬:7/���:8/ͨѶ�¼�����:11/ͨѶ�¼���¼:12/���������:13/��ѯ������:14/ǿ�ƶ���Ĵ���:15/Ԥ�ö���Ĵ���:16/����ӻ� ID:17/ͨѶ��·��λ:19/��ͨ��ֵ:20/дͨ��ֵ:21/
	BYTE 	Map61850Db[16];	 //61850������ 
	BYTE 	Map61850Tab[16];	 //61850������ 
	BYTE 	Map61850Pt[64];	 //61850������ 
	int 	Map61850PtId;	 //61850���������� 
};
#endif



//============ ��������������ֵ ��ṹ ================

#ifndef EP_SP_TABNAME
#define EP_SP_TABNAME 	 _T("EP_SP")

struct EP_SP { 
	BYTE 	Desc[32];	 //���� 
	BYTE 	Value[600];	 //����ֵ 
	float 	Coeff;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ����:4/32λIEEE������:5/
	BYTE 	Map61850Db[16];	 //61850������ 
	BYTE 	Map61850Tab[16];	 //61850������ 
	BYTE 	Map61850Pt[64];	 //61850������ 
	int 	Map61850PtId;	 //61850���������� 
};
#endif



//============ ��������ң�� ��ṹ ================

#ifndef EP_YC_TABNAME
#define EP_YC_TABNAME 	 _T("EP_YC")

struct EP_YC { 
	BYTE 	Desc[32];	 //���� 
	BYTE 	Value[400];	 //����ֵ 
	float 	Coeff;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
	BYTE 	ByteOrder;	 //�ֽ�˳�� 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //�������� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ����:4/32λIEEE������:5/
	BYTE 	Map61850Db[16];	 //61850������ 
	BYTE 	Map61850Tab[16];	 //61850������ 
	BYTE 	Map61850Pt[64];	 //61850������ 
	int 	Map61850PtId;	 //61850���������� 
};
#endif



//============ ������ֵ���� ��ṹ ================

#ifndef EP_SETSP_TABNAME
#define EP_SETSP_TABNAME 	 _T("EP_SETSP")

struct EP_SETSP { 
	BYTE 	SetVal[400];	 //����ֵ 
	BYTE 	ValType;	 //����ֵ���� 
	BYTE 	MapDb[16];	 //������ 
	BYTE 	MapTab[16];	 //������ 
	BYTE 	MapPt[64];	 //������ 
	int 	MapPtId;	 //���������� 
};
#endif



//============ ʵʱ�澯�� ��ṹ ================

#ifndef RtAlarm_TABNAME
#define RtAlarm_TABNAME 	 _T("RtAlarm")

struct RtAlarm { 
	short 	m_warnType;	 //�澯���� 
	short 	m_warnSubType;	 //�澯������ 
	short 	m_warnDetail;	 //�澯������ϸ���� 
	BYTE 	m_objName[64];	 //�����澯�������� 
	short 	m_dbNum;	 //��� 
	short 	m_tableNum;	 //��� 
	short 	m_ptNum;	 //��� 
	short 	m_ctrlVal;	 //����ֵ(yk(0x33�ط�0xCC�غ�),����(0x33�ط�0xCC�غ�)) 
	BYTE 	eventsgflag;	 //=0һ�����=1�¹� 
	BYTE 	m_szVal[16];	 //�澯ֵ 
	float 	m_fVal;	 //m_fVal 
	long 	m_warnTime_L;	 //�澯ʱ��(������) 
	BYTE 	m_warnTime[32];	 //�澯ʱ��(�ַ�) 
	BYTE 	m_warnStr[128];	 //�澯���� 
	BYTE 	m_wavFile[32];	 //�����ļ� 
};
#endif



//============ dlt645��Լ ��ṹ ================

#ifndef DLT645_TABNAME
#define DLT645_TABNAME 	 _T("DLT645")

struct DLT645 { 
	BYTE 	desc[32];	 //���� 
	BYTE 	value[16];	 //��ֵ 
	int 	type;	 //���� 8λ�з�����:0/8λ�޷�����:1/16λ�з�����:2/16λ�޷�����:3/32λ����:4/32λIEEE������:5/
	int 	DI1H;	 //���ݱ�ʶDI1H ������:9/�������:10/����:11/�α���:12/��������:13/�û��Զ���:14/����:15/
	int 	DI1L;	 //���ݱ�ʶDI1L ��ǰ�й�:0/��ǰ�޹�:1/��ǰ����:2/��ǰ����:3/�����й�:4/�����޹�:5/���±���:6/���¼���:7/�������й�:8/�������޹�:9/�����±���:10/�����¼���:11/�����й�:12/�����޹�:13/���ϱ���:14/���ϼ���:15/
	int 	DI0H;	 //���ݱ�ʶDI0H �������:1/�������:2/һ�����޹�:3/�������޹�:4/�������޹�:5/�������޹�:6/����:15/
	int 	DI0L;	 //���ݱ�ʶDI0L �ܵ���:0/����1:1/����2:2/����3:3/����4:4/����5:5/����6:6/����7:7/����8:8/����9:9/����10:10/����11:11/����12:12/����13:13/����14:14/�����ݿ鼯��15:15/
	BYTE 	DevAdr[12];	 //�豸��ַ 
	int 	reverve1;	 //����1 
};
#endif



//============ OPC_DA ��ṹ ================

#ifndef OPCDA_TABNAME
#define OPCDA_TABNAME 	 _T("OPCDA")

struct OPCDA { 
	BYTE 	Desc[32];	 //���� 
	BYTE 	Value[400];	 //����ֵ 
	float 	Coeff;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
	BYTE 	DataType;	 //�������� BOOL��:0/8λ�з�����:1/8λ�޷�����:2/16λ�з�����:3/16λ�޷�����:4/32λ�з�������:5/32λ�޷�������:6/32λIEEE������:7/�ַ���:8/ʱ��:9/����:10/
};
#endif



//============ ��ң��� ��ṹ ================

#ifndef SMP_YC_TABNAME
#define SMP_YC_TABNAME 	 _T("SMP_YC")

struct SMP_YC { 
	BYTE 	m_desc[32];	 //���� 
	float 	m_val;	 //ң��ֵ 
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� �й�:0/�޹�:1/����:2/��ѹ:3/Ƶ��:4/��������:5/ˮλ:6/�¶�:7/
	float 	m_coeff;	 //ϵ�� 
	float 	m_base;	 //��ֵ 
};
#endif



//============ ��ң�ű� ��ṹ ================

#ifndef SMP_YX_TABNAME
#define SMP_YX_TABNAME 	 _T("SMP_YX")

struct SMP_YX { 
	BYTE 	m_desc[32];	 //���� 
	BYTE 	m_val;	 //ң��ֵ ��:0/��:1/ֵ00:2/ֵ11:3/
	short 	m_facno;	 //���� 
	BYTE 	m_type;	 //���� ����:0/��բ:1/�����ź�:2/�¹����ź�:3/�¹��ź�:4/�澯�ź�:5/
	BYTE 	m_inverter;	 //������ ����:0/����:1/
};
#endif



//============ 104ң��� ��ṹ ================

#ifndef IEC104_YC_TABNAME
#define IEC104_YC_TABNAME 	 _T("IEC104_YC")

struct IEC104_YC { 
	BYTE 	desc[32];	 //���� 
	float 	value;	 //ֵ 
	int 	InfAddr;	 //��Ϣ��ַ 
	float 	coef;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
};
#endif



//============ 104ң�ű� ��ṹ ================

#ifndef IEC104_YX_TABNAME
#define IEC104_YX_TABNAME 	 _T("IEC104_YX")

struct IEC104_YX { 
	BYTE 	desc[32];	 //���� 
	BYTE 	value;	 //ֵ 
	int 	InfAddr;	 //��Ϣ���ַ 
	BYTE 	NotFlag;	 //�Ƿ�ȡ�� 
};
#endif



//============ 104��ȱ� ��ṹ ================

#ifndef IEC104_DD_TABNAME
#define IEC104_DD_TABNAME 	 _T("IEC104_DD")

struct IEC104_DD { 
	BYTE 	desc[32];	 //���� 
	float 	value;	 //ֵ 
	int 	InfAddr;	 //��Ϣ���ַ 
	float 	Coef;	 //ϵ�� 
	float 	BaseValue;	 //��ֵ 
};
#endif



//============ ������ ��ṹ ================

#ifndef BASE_TABNAME
#define BASE_TABNAME 	 _T("BASE")

struct BASE { 
	BYTE 	DESC[32];	 //���� 
	double 	VALUE;	 //��ֵ 
	double 	VALUE1;	 //��ֵ1 
	int 	DATA0;	 //��� 
	int 	DATA1;	 //FUN 
	int 	DATA2;	 //INf 
	int 	DATA3;	 //Addr 
	int 	DATA4;	 //ItemNo 
	int 	DATA5;	 //DevAddr 
	int 	DATA6;	 //Data6 
	int 	DATA7;	 //Data7 
};
#endif



//============ ������ ��ṹ ================

#ifndef BASE_TABLE_TABNAME
#define BASE_TABLE_TABNAME 	 _T("BASE_TABLE")

struct BASE_TABLE { 
	BYTE 	Name[64];	 //���� 
	BYTE 	DESCRIPTION[64];	 //���� 
	float 	CV;	 //��ǰֵ 
	float 	LV;	 //��һ��ֵ 
	BYTE 	STR1[128];	 //�ַ���1 
	BYTE 	STR2[128];	 //�ַ���2 
	BYTE 	STR3[128];	 //�ַ���3 
	BYTE 	STR4[128];	 //�ַ���4 
	int 	DATA1;	 //����1 
	int 	DATA2;	 //����2 
	int 	DATA3;	 //����3 
	int 	DATA4;	 //����4 
	int 	DATA5;	 //����5 
	int 	DATA6;	 //����6 
	int 	DATA7;	 //����7 
	int 	DATA8;	 //����8 
	int 	DATA9;	 //����9 
	int 	DATA10;	 //����10 
};
#endif



//============ ͨ����Ϣ ��ṹ ================

#ifndef Chanel_Info_TABNAME
#define Chanel_Info_TABNAME 	 _T("Chanel_Info")

struct Chanel_Info { 
	BYTE 	Desc[128];	 //���� 
	BYTE 	ComState;	 //ͨѶ״̬ �Ͽ�:0/����:1/
	int 	ComType;	 //ͨѶ���� ����ͨѶ:1/Tcp�ͻ���:2/Tcp�����:3/Udp�ͻ���:4/Udp�����:5/�������:6/���ڼ���:7/DDE Server:8/DDE Client:9/
	unsigned int 	RecvLen;	 //�����ֽ� 
	unsigned int 	SendLen;	 //�����ֽ� 
	int 	Port;	 //�˿� 
	int 	RecvInterval;	 //���ݽ�������(ms) 
	int 	SendInterval;	 //���ݷ�������(ms) 
	int 	RecvTimeOut;	 //���ݽ��ճ�ʱ(s) 
	int 	WriteRetryTimes;	 //����ʧ�����Դ��� 
	int 	BaudRate;	 //������ 
	BYTE 	Parity;	 //��żУ�� ��:0/żУ��:1/��У��:2/
	int 	DataBit;	 //����λ 
	BYTE 	StopBit;	 //ֹͣλ 1:0/1.5:1/2:2/
	BYTE 	IpAdr[16];	 //Ip��ַ 
	int 	Options;	 //Tcp���� 
	int 	Family;	 //Tcp_Family 
	int 	MaxConnect;	 //tcpServer��������� 
	BYTE 	BroadAdr[16];	 //udp�㲥��ַ 
	BYTE 	TargetAdr[16];	 //udpĿ���ַ 
	int 	TargetPort;	 //udpĿ��˿� 
	BYTE 	RelDb[16];	 //������ 
	BYTE 	RelTab[16];	 //������ 
	BYTE 	RelPt[64];	 //������ 
	int 	RelId;	 //���������� 
};
#endif



//============ �û���Ϣ ��ṹ ================

#ifndef User_Info_TABNAME
#define User_Info_TABNAME 	 _T("User_Info")

struct User_Info { 
	BYTE 	Desc[64];	 //���� 
	BYTE 	Password[32];	 //���� 
	unsigned int 	Power;	 //Ȩ�� 
	BYTE 	GrpName[64];	 //������ 
	BYTE 	Group;	 //�Ƿ�Ϊ�� ����:0/��:1/
	unsigned int 	LogonTime_L;	 //��½ʱ�� 
	BYTE 	LogonTime_C[32];	 //��½ʱ��(�ַ�) 
	unsigned int 	PersistTime;	 //��Чʱ�䳤(s) 
	unsigned int 	LogoffTime_L;	 //�˳�ʱ�� 
	BYTE 	LogoffTime_C[32];	 //�˳�ʱ��(�ַ�) 
	BYTE 	Status;	 //��½״̬ �˳�:0/�ѵ�½:1/
};
#endif



//============ GOOSE���� ��ṹ ================

#ifndef GOOSE_CFG_TABNAME
#define GOOSE_CFG_TABNAME 	 _T("GOOSE_CFG")

struct GOOSE_CFG { 
	BYTE 	desc[64];	 //���� 
	BOOL 	value;	 //ֵ 
	BOOL 	trig;	 //����¼�� 
	BYTE 	refmac1[32];	 //������smv1 
	BYTE 	refmac2[32];	 //������smv2 
	BYTE 	refmac3[32];	 //������smv3 
	BYTE 	refmac4[32];	 //������smv4 
	BYTE 	refmac5[32];	 //������smv5 
	BYTE 	refmac6[32];	 //������smv6 
	BYTE 	refmac7[32];	 //������smv7 
	BYTE 	refmac8[32];	 //������smv8 
	BYTE 	refmac9[32];	 //������smv9 
	BYTE 	refmac10[32];	 //������smv10 
};
#endif



//============ MMS���� ��ṹ ================

#ifndef MMS_CFG_TABNAME
#define MMS_CFG_TABNAME 	 _T("MMS_CFG")

struct MMS_CFG { 
};
#endif



//============ ����ֵ9-2���� ��ṹ ================

#ifndef SMV92_CFG_TABNAME
#define SMV92_CFG_TABNAME 	 _T("SMV92_CFG")

struct SMV92_CFG { 
};
#endif



//============ ����ֵ9-1���� ��ṹ ================

#ifndef SMV91_CFG_TABNAME
#define SMV91_CFG_TABNAME 	 _T("SMV91_CFG")

struct SMV91_CFG { 
};
#endif



//============ �ļ����� ��ṹ ================

#ifndef FileService_TABNAME
#define FileService_TABNAME 	 _T("FileService")

struct FileService { 
	BYTE 	DbName[32];	 //���ݿ��� 
	BYTE 	TabName[32];	 //���ݱ��� 
	BYTE 	PtName[64];	 //���� 
	unsigned int 	DbIndex;	 //������ 
	unsigned int 	TabIndex;	 //������ 
	unsigned int 	PtIndex;	 //������ 
	BYTE 	FileName[64];	 //�ļ��� 
	BYTE 	CmdType;	 //�ļ����� ���ļ�:0/���ļ�:1/ɾ�ļ�:2/���ز���:3/
	char 	Result;	 //���Ʒ��ؽ�� 
	BOOL 	ValidFlag;	 //��Ч��־ 
	long 	LSendTime;	 //����ʱ��(����) 
	BYTE 	StrSendTime[32];	 //����ʱ��(�ַ�) 
	unsigned int 	TimeOut;	 //��ʱ 
	BOOL 	ProcFlag;	 //�����־ 
};
#endif

#endif //__MEMTABSTRUCT_H_LT
