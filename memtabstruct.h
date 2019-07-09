/////////////////////////////////////////////////
//   
//    MemDbTabStruct.h        
//   
//    由实时数据库导出实时数据库表结构.H文件   
//   
/////////////////////////////////////////////////


#ifndef __MEMTABSTRUCT_H_2003_12_LT
#define __MEMTABSTRUCT_H_2003_12_LT



//============ 系统信息 表结构 ================

#ifndef Snmp_System_TABNAME
#define Snmp_System_TABNAME 	 _T("Snmp_System")

struct Snmp_System { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //遥信值 分:0/合:1/值00:2/值11:3/
	short 	m_oid;	 //对象标识号 
};
#endif



//============ 端口表 表结构 ================

#ifndef Snmp_ifTable_TABNAME
#define Snmp_ifTable_TABNAME 	 _T("Snmp_ifTable")

struct Snmp_ifTable { 
	BYTE 	ifIndex;	 //端口号 
	BYTE 	ifDesc[32];	 //描述 
	BYTE 	ifType;	 //类型 unknown:0/other:1/regular1822:2/hdh1822:3/ddnX25:4/rfc877x25:5/ethernetCsmacd:6/iso88023Csmacd:7/iso88024TokenBus:8/iso88025TokenRing:9/iso88026Man:10/starLan:11/proteon10Mbit:12/proteon80Mbit:13/hyperchannel:14/fddi:15/lapb:16/sdlc:17/ds1:18/e1:19/
	unsigned short 	ifMtu;	 //最大报文长度 
	unsigned int 	ifSpeed;	 //传输速度 
	BYTE 	ifPhysAddress[32];	 //物理地址 
	BYTE 	ifAdminStatus;	 //管理状态 启用:1/停用:2/测试:3/
	BYTE 	ifOperStatus;	 //运行状态 连接:1/断开:2/测试:3/未知:4/休眠:5/隐藏:6/底层断开:7/
	BYTE 	ifLastChange[32];	 //最后更新 
	unsigned long 	ifInOctets;	 //接收字节 
	unsigned long 	ifInUcastPkts;	 //接收Ucast包 
	unsigned long 	ifInNUcastPkts;	 //接收NUcast包 
	unsigned long 	ifInDiscards;	 //放弃的包 
	unsigned long 	ifInErrors;	 //接收错误 
	unsigned long 	ifInUnknownProtos;	 //接收未知协议 
	unsigned long 	ifOutOctets;	 //发送字节 
	unsigned long 	ifOutUcastPkts;	 //发送Ucast包 
	unsigned long 	ifOutNUcastPkts;	 //发送NUcast包 
	unsigned long 	ifOutDiscards;	 //发送放弃的包 
	unsigned long 	ifOutErrors;	 //发送错误 
	unsigned long 	ifOutQLen;	 //发送包队列长度 
	BYTE 	ifSpecific[64];	 //备注 
};
#endif



//============ 双遥信量 表结构 ================

#ifndef DYX_STRUCT_TABNAME
#define DYX_STRUCT_TABNAME 	 _T("DYX_STRUCT")

struct DYX_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //遥信值 异常:00/分:01/合10:2/异常11:3/
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 开关:0/刀闸:1/保护信号:2/事故总信号:3/事故信号:4/告警信号:5/
	BYTE 	m_inverter;	 //反向器 正常:0/反向:1/
	BYTE 	m_op_status;	 //操作状态 正常:0/封锁:1/检修:2/接地:3/
	BYTE 	m_yx_status;	 //遥信状态 正常:0/变位:1/事故:2/
	BYTE 	m_processtag;	 //处理标志 需告警:0/需登录:1/需打印:2/语音:3/需推画面:4/
	int 	m_fh_count;	 //分-合次数 
	int 	m_hf_count;	 //合-分次数 
	int 	m_sg_count;	 //事故次数 
	BYTE 	m_vol_degree;	 //电压等级 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //告警等级 一级告警:0/二级告警:1/三级告警:2/
	BYTE 	m_picture[64];	 //推出画面名 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 遥信量 表结构 ================

#ifndef YX_STRUCT_TABNAME
#define YX_STRUCT_TABNAME 	 _T("YX_STRUCT")

struct YX_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //遥信值 分:0/合:1/值10:2/值11:3/
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 开关:0/刀闸:1/保护信号:2/事故总信号:3/事故信号:4/告警信号:5/
	BYTE 	m_inverter;	 //反向器 正常:0/反向:1/
	BYTE 	m_op_status;	 //操作状态 正常:0/封锁:1/检修:2/接地:3/
	BYTE 	m_yx_status;	 //遥信状态 正常:0/变位:1/事故:2/
	BYTE 	m_processtag;	 //处理标志 需告警:0/需登录:1/需打印:2/语音:3/需推画面:4/
	int 	m_fh_count;	 //分-合次数 
	int 	m_hf_count;	 //合-分次数 
	int 	m_sg_count;	 //事故次数 
	BYTE 	m_vol_degree;	 //电压等级 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //告警等级 一级告警:0/二级告警:1/三级告警:2/
	BYTE 	m_picture[64];	 //推出画面名 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 遥测表 表结构 ================

#ifndef YC_STRUCT_TABNAME
#define YC_STRUCT_TABNAME 	 _T("YC_STRUCT")

struct YC_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //实际值 
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 有功:0/无功:1/电流:2/电压:3/频率:4/功率因数:5/水位:6/温度:7/
	int 	m_code;	 //码值 
	float 	m_coeff;	 //系数 
	float 	m_base;	 //基值 
	float 	m_zero;	 //归零范围 
	float 	m_top;	 //最大值 
	float 	m_bottom;	 //最小值 
	float 	m_dead;	 //死区范围 
	BYTE 	m_op_status;	 //操作状态 正常:0/封锁:1/
	BYTE 	m_processtag;	 //处理标志 需告警:0/需登录:1/需打印:2/语音:3/需追忆:5/
	BYTE 	m_vol_degree;	 //电压等级 380V:0/6KV:1/10KV:2/35KV:3/110KV:4/220KV:5/500KV:6/
	BYTE 	m_alarm_degree;	 //告警等级 一级告警:0/二级告警:1/三级告警:2/
	BYTE 	m_yc_status;	 //遥测状态 正常:0/越上限:1/越上上限:2/越下限:3/越下下限:4/
	BYTE 	m_limit_mark;	 //限值标志 无限值:0/有限值:1/
	float 	m_uplimit;	 //上限 
	float 	m_uuplimit;	 //上上限 
	float 	m_downlimit;	 //下限 
	float 	m_ddownlimit;	 //下下限 
	int 	m_over_time;	 //越限时刻 
	int 	m_over_up_time;	 //越上限时间 
	int 	m_over_uup_time;	 //越上上限时间 
	int 	m_over_down_time;	 //越下限时间 
	int 	m_over_ddown_time;	 //越下下限时间 
	float 	m_hgl;	 //越限总时间 
	float 	m_updead;	 //上限死区 
	float 	m_downdead;	 //下限死区 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 脉冲量表 表结构 ================

#ifndef PULSE_STRUCT_TABNAME
#define PULSE_STRUCT_TABNAME 	 _T("PULSE_STRUCT")

struct PULSE_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //实际值 
	short 	m_facno;	 //厂号 
	BYTE 	m_terminal[32];	 //端子排 
	int 	m_code;	 //码值 
	float 	m_coeff;	 //系数 
	float 	m_base;	 //基值 
	float 	m_zero;	 //归零范围 
	float 	m_top;	 //满度值 
	float 	m_dead;	 //死区范围 
	BYTE 	m_op_status;	 //操作状态 正常:0/封锁:1/
	BYTE 	m_processtag;	 //处理标志 需告警:0/需登录:1/需打印:2/语音:3/
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 电度表 表结构 ================

#ifndef KWH_STRUCT_TABNAME
#define KWH_STRUCT_TABNAME 	 _T("KWH_STRUCT")

struct KWH_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //实际值 
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 表底值:0/间隔值:1/
	BYTE 	m_pulseid[6];	 //相关遥脉点 
	float 	m_pre_frame;	 //上帧值 
	float 	m_top;	 //满码值 
	DATE 	m_start_time;	 //开始运行时刻 
	DATE 	m_end_time;	 //结束累计时刻 
	float 	m_kwh_accumulate;	 //累计值 
	float 	m_kwh_hour;	 //时累计 
	float 	m_kwh_day;	 //日累计 
	float 	m_kwh_month;	 //月累计 
	float 	m_kwh_year;	 //年累计 
	BYTE 	m_op_status;	 //操作状态 正常:0/封锁:1/
	BYTE 	m_sample_tag;	 //采样标志 
	int 	m_mincycle;	 //分钟间隔 
	float 	m_kwh_minute;	 //分钟累计 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 遥控表 表结构 ================

#ifndef YK_STRUCT_TABNAME
#define YK_STRUCT_TABNAME 	 _T("YK_STRUCT")

struct YK_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //实际值 
	short 	m_facno;	 //厂号 
	BYTE 	m_yx_rel[64];	 //相关遥信 
	short 	m_switch_no;	 //开关号 
	short 	m_open_obj;	 //分对象号 
	short 	m_close_obj;	 //合对象号 
	BYTE 	m_yktype;	 //控制类型 单点控制:0/双点控制:1/
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 遥控闭锁表 表结构 ================

#ifndef YK_LOCK_TABNAME
#define YK_LOCK_TABNAME 	 _T("YK_LOCK")

struct YK_LOCK { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_value;	 //闭锁遥信值 分:0/合:1/
	short 	m_facno;	 //厂号 
	BYTE 	m_yk_obj[6];	 //闭锁遥控对象 
	BYTE 	m_lock_condition[6];	 //闭锁条件ID 
	BYTE 	m_yk_op_status;	 //闭锁遥控操作 分:0/合:1/
	BYTE 	m_lock_op;	 //闭锁条件 等于:0/大于:1/小于:2/
	float 	m_yc_value;	 //闭锁遥测值 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 保护遥信表 表结构 ================

#ifndef YX_BH_STRUCT_TABNAME
#define YX_BH_STRUCT_TABNAME 	 _T("YX_BH_STRUCT")

struct YX_BH_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //实际值 分:0/合:1/
	short 	m_facno;	 //厂号 
	BYTE 	m_yx[6];	 //遥信ID 
	short 	m_num;	 //相关保护个数 
	BYTE 	m_bh1[6];	 //相关保护1 
	BYTE 	m_bh2[6];	 //相关保护2 
	BYTE 	m_bh3[6];	 //相关保护3 
	BYTE 	m_bh4[6];	 //相关保护4 
	BYTE 	m_bh5[6];	 //相关保护5 
	BYTE 	m_bh6[6];	 //相关保护6 
	BYTE 	m_bh7[6];	 //相关保护7 
	BYTE 	m_bh8[6];	 //相关保护8 
	BYTE 	m_bh9[6];	 //相关保护9 
	BYTE 	m_bh10[6];	 //相关保护10 
	BYTE 	m_bh11[6];	 //相关保护11 
	BYTE 	m_bh12[6];	 //相关保护12 
	BYTE 	m_bh13[6];	 //相关保护13 
	BYTE 	m_bh14[6];	 //相关保护14 
	BYTE 	m_bh15[6];	 //相关保护15 
	BYTE 	m_bh16[6];	 //相关保护16 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 计算机节点表 表结构 ================

#ifndef NodeInfo_TABNAME
#define NodeInfo_TABNAME 	 _T("NodeInfo")

struct NodeInfo { 
	BYTE 	m_cpname[32];	 //计算机名 
	BYTE 	m_mIpAdr[32];	 //主IP地址 
	BYTE 	m_sIpAdr[32];	 //备IP地址 
	BYTE 	m_rdbMaster;	 //实时库类型 普通工作站:0/值班主机:1/备用主机
	BYTE 	m_hisMaster;	 //历史库类型 普通工作站:0/主机:1/备用主机:2/
	BYTE 	m_tciMaster;	 //前置机类型 普通工作站:0/主前置机:1/备用前置机:2/
	BYTE 	m_status;	 //节点状态 退出:0/投入:1/
	int 	m_functype;	 //允许功能 报表打印:0/画面编辑:1/修改数据库:2/用户管理:3/告警打印:4/播放语音:5/推画面:6/
	int 	m_heartbeat;	 //心跳计数 
};
#endif



//============ 系统进程表 表结构 ================

#ifndef SysProcess_TABNAME
#define SysProcess_TABNAME 	 _T("SysProcess")

struct SysProcess { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //状态 退出:0/运行:1/挂起:2/
	BYTE 	m_fullpath[255];	 //路径 
	BYTE 	m_type;	 //类型 普通:0/关键进程:1/
	int 	m_pid;	 //进程号 
	BYTE 	m_runhost[255];	 //运行机器 
};
#endif



//============ 遥调表 表结构 ================

#ifndef YT_STRUCT_TABNAME
#define YT_STRUCT_TABNAME 	 _T("YT_STRUCT")

struct YT_STRUCT { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //当前值 
	short 	m_facno;	 //厂号 
	short 	m_up_yt_no;	 //上调遥调号 
	short 	m_down_yt_no;	 //下调遥调号 
	short 	m_stop_yt_no;	 //急停遥调号 
	BYTE 	m_current_yt_pos;	 //档位 
	BYTE 	m_max_yt_pos;	 //最大档位 
	BYTE 	m_min_yt_pos;	 //最小档位 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 61850DA值 表结构 ================

#ifndef DAMEM_TABNAME
#define DAMEM_TABNAME 	 _T("DAMEM")

struct DAMEM { 
	BYTE 	m_desc[128];	 //描述 
	BYTE 	DADATA[64];	 //DA值 
};
#endif



//============ 客户端61850DA值 表结构 ================

#ifndef CLTDAMEM_TABNAME
#define CLTDAMEM_TABNAME 	 _T("CLTDAMEM")

struct CLTDAMEM { 
	BYTE 	m_desc[128];	 //描述 
	BYTE 	DADATA[64];	 //DA值 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ SOE 表结构 ================

#ifndef SOEMEM_TABNAME
#define SOEMEM_TABNAME 	 _T("SOEMEM")

struct SOEMEM { 
	BYTE 	Status;	 //状态 
	short 	Year;	 //年 
	BYTE 	Month;	 //月 
	BYTE 	Day;	 //日 
	BYTE 	Hour;	 //时 
	BYTE 	Minute;	 //分 
	BYTE 	Second;	 //秒 
	short 	Mics;	 //毫秒 
	BYTE 	PointName[64];	 //关联点名 
	BYTE 	DbName[32];	 //关联数据库名 
	short 	TableNo;	 //关联表号 
};
#endif



//============ 遥调内存表 表结构 ================

#ifndef YtMem_TABNAME
#define YtMem_TABNAME 	 _T("YtMem")

struct YtMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	float 	SetVal;	 //设置值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	BOOL 	Comand;	 //控制命令 上调:0/下调:1/急停:2/
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
#endif



//============ 遥控内存表 表结构 ================

#ifndef YkMem_TABNAME
#define YkMem_TABNAME 	 _T("YkMem")

struct YkMem { 
	long 	InvokeId;	 //内容标识 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	BYTE 	CtrlVal;	 //控制值 
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	BYTE 	Comand;	 //控制命令 遥控预选:1/遥控执行:2/遥控取消:3/
	long 	SendTime;	 //发送时间 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
#endif



//============ 读写指针 表结构 ================

#ifndef RWPTR_TABNAME
#define RWPTR_TABNAME 	 _T("RWPTR")

struct RWPTR { 
	int 	PtrPos;	 //指针位置 
};
#endif



//============ Modbus模拟量 表结构 ================

#ifndef MODBUS_YC_TABNAME
#define MODBUS_YC_TABNAME 	 _T("MODBUS_YC")

struct MODBUS_YC { 
	BYTE 	Desc[32];	 //描述 
	float 	Value;	 //数据值 
	unsigned short 	DevAdr;	 //设备地址 
	unsigned short 	StartAdr;	 //寄存器地址 
	float 	Coeff;	 //系数 
	float 	BaseValue;	 //基值 
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位无符号整数:4/32位IEEE浮点数:5/32位有符号整数:6/64位双精度:7/
	BYTE 	CmdType;	 //命令类型 线圈状态:1/输入状态:2/保持寄存器:3/输入寄存器:4/强制单个线圈:5/预置单个寄存器:6/读不正常状态:7/诊断:8/通讯事件控制:11/通讯事件记录:12/程序控制器:13/查询控制器:14/强制多个寄存器:15/预置多个寄存器:16/报告从机 ID:17/通讯链路复位:19/读通用值:20/写通用值:21/
};
#endif



//============ Modbus数字量 表结构 ================

#ifndef MODBUS_YX_TABNAME
#define MODBUS_YX_TABNAME 	 _T("MODBUS_YX")

struct MODBUS_YX { 
	BYTE 	Desc[32];	 //描述 
	BYTE 	Value;	 //数据值 
	unsigned short 	DevAdr;	 //设备地址 
	unsigned short 	StartAdr;	 //寄存器地址 
	unsigned int 	UsedBit;	 //使用的位 第0位:0/第1位:1/第2位:2/第3位:3/第4位:4/第5位:5/第6位:6/第7位:7/第8位:8/第9位:9/第10位:10/第11位:11/第12位:12/第13位:13/第14位:14/第15位:15/全部位:16/
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位整数:4/32位IEEE浮点数:5/
	BYTE 	CmdType;	 //命令类型 线圈状态:1/输入状态:2/保持寄存器:3/输入寄存器:4/强制单个线圈:5/预置单个寄存器:6/读不正常状态:7/诊断:8/通讯事件控制:11/通讯事件记录:12/程序控制器:13/查询控制器:14/强制多个寄存器:15/预置多个寄存器:16/报告从机 ID:17/通讯链路复位:19/读通用值:20/写通用值:21/
};
#endif



//============ 61850Modbus模拟量 表结构 ================

#ifndef MMSMODBUS_YC_TABNAME
#define MMSMODBUS_YC_TABNAME 	 _T("MMSMODBUS_YC")

struct MMSMODBUS_YC { 
	BYTE 	Desc[32];	 //描述 
	float 	Value;	 //数据值 
	unsigned short 	DevAdr;	 //设备地址 
	unsigned short 	StartAdr;	 //寄存器地址 
	float 	Coeff;	 //系数 
	float 	BaseValue;	 //基值 
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位无符号整数:4/32位IEEE浮点数:5/32位有符号整数:6/64位双精度:7/
	BYTE 	CmdType;	 //命令类型 线圈状态:1/输入状态:2/保持寄存器:3/输入寄存器:4/强制单个线圈:5/预置单个寄存器:6/读不正常状态:7/诊断:8/通讯事件控制:11/通讯事件记录:12/程序控制器:13/查询控制器:14/强制多个寄存器:15/预置多个寄存器:16/报告从机 ID:17/通讯链路复位:19/读通用值:20/写通用值:21/
	BYTE 	Map61850Db[16];	 //61850关联库 
	BYTE 	Map61850Tab[16];	 //61850关联表 
	BYTE 	Map61850Pt[64];	 //61850关联点 
	int 	Map61850PtId;	 //61850关联点索引 
};
#endif



//============ 61850Modbus数字量 表结构 ================

#ifndef MMSMODBUS_YX_TABNAME
#define MMSMODBUS_YX_TABNAME 	 _T("MMSMODBUS_YX")

struct MMSMODBUS_YX { 
	BYTE 	Desc[32];	 //描述 
	BYTE 	Value;	 //数据值 
	unsigned short 	DevAdr;	 //设备地址 
	unsigned short 	StartAdr;	 //寄存器地址 
	unsigned int 	UsedBit;	 //使用的位 第0位:0/第1位:1/第2位:2/第3位:3/第4位:4/第5位:5/第6位:6/第7位:7/第8位:8/第9位:9/第10位:10/第11位:11/第12位:12/第13位:13/第14位:14/第15位:15/全部位:16/
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位整数:4/32位IEEE浮点数:5/
	BYTE 	CmdType;	 //命令类型 线圈状态:1/输入状态:2/保持寄存器:3/输入寄存器:4/强制单个线圈:5/预置单个寄存器:6/读不正常状态:7/诊断:8/通讯事件控制:11/通讯事件记录:12/程序控制器:13/查询控制器:14/强制多个寄存器:15/预置多个寄存器:16/报告从机 ID:17/通讯链路复位:19/读通用值:20/写通用值:21/
	BYTE 	Map61850Db[16];	 //61850关联库 
	BYTE 	Map61850Tab[16];	 //61850关联表 
	BYTE 	Map61850Pt[64];	 //61850关联点 
	int 	Map61850PtId;	 //61850关联点索引 
};
#endif



//============ 电能质量参数定值 表结构 ================

#ifndef EP_SP_TABNAME
#define EP_SP_TABNAME 	 _T("EP_SP")

struct EP_SP { 
	BYTE 	Desc[32];	 //描述 
	BYTE 	Value[600];	 //数据值 
	float 	Coeff;	 //系数 
	float 	BaseValue;	 //基值 
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位整数:4/32位IEEE浮点数:5/
	BYTE 	Map61850Db[16];	 //61850关联库 
	BYTE 	Map61850Tab[16];	 //61850关联表 
	BYTE 	Map61850Pt[64];	 //61850关联点 
	int 	Map61850PtId;	 //61850关联点索引 
};
#endif



//============ 电能质量遥测 表结构 ================

#ifndef EP_YC_TABNAME
#define EP_YC_TABNAME 	 _T("EP_YC")

struct EP_YC { 
	BYTE 	Desc[32];	 //描述 
	BYTE 	Value[400];	 //数据值 
	float 	Coeff;	 //系数 
	float 	BaseValue;	 //基值 
	BYTE 	ByteOrder;	 //字节顺序 21:0/12:1/4321:2/3412:3/1234:4/2143:5/
	BYTE 	DataType;	 //数据类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位整数:4/32位IEEE浮点数:5/
	BYTE 	Map61850Db[16];	 //61850关联库 
	BYTE 	Map61850Tab[16];	 //61850关联表 
	BYTE 	Map61850Pt[64];	 //61850关联点 
	int 	Map61850PtId;	 //61850关联点索引 
};
#endif



//============ 参数定值设置 表结构 ================

#ifndef EP_SETSP_TABNAME
#define EP_SETSP_TABNAME 	 _T("EP_SETSP")

struct EP_SETSP { 
	BYTE 	SetVal[400];	 //设置值 
	BYTE 	ValType;	 //设置值类型 
	BYTE 	MapDb[16];	 //关联库 
	BYTE 	MapTab[16];	 //关联表 
	BYTE 	MapPt[64];	 //关联点 
	int 	MapPtId;	 //关联点索引 
};
#endif



//============ 实时告警表 表结构 ================

#ifndef RtAlarm_TABNAME
#define RtAlarm_TABNAME 	 _T("RtAlarm")

struct RtAlarm { 
	short 	m_warnType;	 //告警类型 
	short 	m_warnSubType;	 //告警子类型 
	short 	m_warnDetail;	 //告警内容详细代码 
	BYTE 	m_objName[64];	 //产生告警对象名称 
	short 	m_dbNum;	 //库号 
	short 	m_tableNum;	 //表号 
	short 	m_ptNum;	 //点号 
	short 	m_ctrlVal;	 //控制值(yk(0x33控分0xCC控合),升降(0x33控分0xCC控合)) 
	BYTE 	eventsgflag;	 //=0一般事项，=1事故 
	BYTE 	m_szVal[16];	 //告警值 
	float 	m_fVal;	 //m_fVal 
	long 	m_warnTime_L;	 //告警时间(长整形) 
	BYTE 	m_warnTime[32];	 //告警时间(字符) 
	BYTE 	m_warnStr[128];	 //告警内容 
	BYTE 	m_wavFile[32];	 //声音文件 
};
#endif



//============ dlt645规约 表结构 ================

#ifndef DLT645_TABNAME
#define DLT645_TABNAME 	 _T("DLT645")

struct DLT645 { 
	BYTE 	desc[32];	 //描述 
	BYTE 	value[16];	 //数值 
	int 	type;	 //类型 8位有符号数:0/8位无符号数:1/16位有符号数:2/16位无符号数:3/32位整数:4/32位IEEE浮点数:5/
	int 	DI1H;	 //数据标识DI1H 电能量:9/最大需量:10/变量:11/参变量:12/负荷曲线:13/用户自定义:14/保留:15/
	int 	DI1L;	 //数据标识DI1L 当前有功:0/当前无功:1/当前保留:2/当前集合:3/上月有功:4/上月无功:5/上月保留:6/上月集合:7/上上月有功:8/上上月无功:9/上上月保留:10/上上月集合:11/集合有功:12/集合无功:13/集合保留:14/集合集合:15/
	int 	DI0H;	 //数据标识DI0H 正向电能:1/反向电能:2/一象限无功:3/四象限无功:4/二象限无功:5/三象限无功:6/集合:15/
	int 	DI0L;	 //数据标识DI0L 总电能:0/费率1:1/费率2:2/费率3:3/费率4:4/费率5:5/费率6:6/费率7:7/费率8:8/费率9:9/费率10:10/费率11:11/费率12:12/费率13:13/费率14:14/本数据块集合15:15/
	BYTE 	DevAdr[12];	 //设备地址 
	int 	reverve1;	 //保留1 
};
#endif



//============ OPC_DA 表结构 ================

#ifndef OPCDA_TABNAME
#define OPCDA_TABNAME 	 _T("OPCDA")

struct OPCDA { 
	BYTE 	Desc[32];	 //描述 
	BYTE 	Value[400];	 //数据值 
	float 	Coeff;	 //系数 
	float 	BaseValue;	 //基值 
	BYTE 	DataType;	 //数据类型 BOOL型:0/8位有符号数:1/8位无符号数:2/16位有符号数:3/16位无符号数:4/32位有符号整数:5/32位无符号整数:6/32位IEEE浮点数:7/字符串:8/时标:9/数组:10/
};
#endif



//============ 简单遥测表 表结构 ================

#ifndef SMP_YC_TABNAME
#define SMP_YC_TABNAME 	 _T("SMP_YC")

struct SMP_YC { 
	BYTE 	m_desc[32];	 //描述 
	float 	m_val;	 //遥测值 
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 有功:0/无功:1/电流:2/电压:3/频率:4/功率因数:5/水位:6/温度:7/
	float 	m_coeff;	 //系数 
	float 	m_base;	 //基值 
};
#endif



//============ 简单遥信表 表结构 ================

#ifndef SMP_YX_TABNAME
#define SMP_YX_TABNAME 	 _T("SMP_YX")

struct SMP_YX { 
	BYTE 	m_desc[32];	 //描述 
	BYTE 	m_val;	 //遥信值 分:0/合:1/值00:2/值11:3/
	short 	m_facno;	 //厂号 
	BYTE 	m_type;	 //类型 开关:0/刀闸:1/保护信号:2/事故总信号:3/事故信号:4/告警信号:5/
	BYTE 	m_inverter;	 //反向器 正常:0/反向:1/
};
#endif



//============ 104遥测表 表结构 ================

#ifndef IEC104_YC_TABNAME
#define IEC104_YC_TABNAME 	 _T("IEC104_YC")

struct IEC104_YC { 
	BYTE 	desc[32];	 //名称 
	float 	value;	 //值 
	int 	InfAddr;	 //信息地址 
	float 	coef;	 //系数 
	float 	BaseValue;	 //基值 
};
#endif



//============ 104遥信表 表结构 ================

#ifndef IEC104_YX_TABNAME
#define IEC104_YX_TABNAME 	 _T("IEC104_YX")

struct IEC104_YX { 
	BYTE 	desc[32];	 //描述 
	BYTE 	value;	 //值 
	int 	InfAddr;	 //信息体地址 
	BYTE 	NotFlag;	 //是否取反 
};
#endif



//============ 104电度表 表结构 ================

#ifndef IEC104_DD_TABNAME
#define IEC104_DD_TABNAME 	 _T("IEC104_DD")

struct IEC104_DD { 
	BYTE 	desc[32];	 //描述 
	float 	value;	 //值 
	int 	InfAddr;	 //信息体地址 
	float 	Coef;	 //系数 
	float 	BaseValue;	 //基值 
};
#endif



//============ 基本表 表结构 ================

#ifndef BASE_TABNAME
#define BASE_TABNAME 	 _T("BASE")

struct BASE { 
	BYTE 	DESC[32];	 //描述 
	double 	VALUE;	 //数值 
	double 	VALUE1;	 //数值1 
	int 	DATA0;	 //组号 
	int 	DATA1;	 //FUN 
	int 	DATA2;	 //INf 
	int 	DATA3;	 //Addr 
	int 	DATA4;	 //ItemNo 
	int 	DATA5;	 //DevAddr 
	int 	DATA6;	 //Data6 
	int 	DATA7;	 //Data7 
};
#endif



//============ 基本表 表结构 ================

#ifndef BASE_TABLE_TABNAME
#define BASE_TABLE_TABNAME 	 _T("BASE_TABLE")

struct BASE_TABLE { 
	BYTE 	Name[64];	 //名称 
	BYTE 	DESCRIPTION[64];	 //描述 
	float 	CV;	 //当前值 
	float 	LV;	 //上一次值 
	BYTE 	STR1[128];	 //字符串1 
	BYTE 	STR2[128];	 //字符串2 
	BYTE 	STR3[128];	 //字符串3 
	BYTE 	STR4[128];	 //字符串4 
	int 	DATA1;	 //数据1 
	int 	DATA2;	 //数据2 
	int 	DATA3;	 //数据3 
	int 	DATA4;	 //数据4 
	int 	DATA5;	 //数据5 
	int 	DATA6;	 //数据6 
	int 	DATA7;	 //数据7 
	int 	DATA8;	 //数据8 
	int 	DATA9;	 //数据9 
	int 	DATA10;	 //数据10 
};
#endif



//============ 通道信息 表结构 ================

#ifndef Chanel_Info_TABNAME
#define Chanel_Info_TABNAME 	 _T("Chanel_Info")

struct Chanel_Info { 
	BYTE 	Desc[128];	 //描述 
	BYTE 	ComState;	 //通讯状态 断开:0/连接:1/
	int 	ComType;	 //通讯类型 串口通讯:1/Tcp客户端:2/Tcp服务端:3/Udp客户端:4/Udp服务端:5/网络监视:6/串口监视:7/DDE Server:8/DDE Client:9/
	unsigned int 	RecvLen;	 //接收字节 
	unsigned int 	SendLen;	 //发送字节 
	int 	Port;	 //端口 
	int 	RecvInterval;	 //数据接收周期(ms) 
	int 	SendInterval;	 //数据发送周期(ms) 
	int 	RecvTimeOut;	 //数据接收超时(s) 
	int 	WriteRetryTimes;	 //发送失败重试次数 
	int 	BaudRate;	 //波特率 
	BYTE 	Parity;	 //奇偶校验 无:0/偶校验:1/奇校验:2/
	int 	DataBit;	 //数据位 
	BYTE 	StopBit;	 //停止位 1:0/1.5:1/2:2/
	BYTE 	IpAdr[16];	 //Ip地址 
	int 	Options;	 //Tcp参数 
	int 	Family;	 //Tcp_Family 
	int 	MaxConnect;	 //tcpServer最大连接数 
	BYTE 	BroadAdr[16];	 //udp广播地址 
	BYTE 	TargetAdr[16];	 //udp目标地址 
	int 	TargetPort;	 //udp目标端口 
	BYTE 	RelDb[16];	 //关联库 
	BYTE 	RelTab[16];	 //关联表 
	BYTE 	RelPt[64];	 //关联点 
	int 	RelId;	 //关联点索引 
};
#endif



//============ 用户信息 表结构 ================

#ifndef User_Info_TABNAME
#define User_Info_TABNAME 	 _T("User_Info")

struct User_Info { 
	BYTE 	Desc[64];	 //描述 
	BYTE 	Password[32];	 //密码 
	unsigned int 	Power;	 //权限 
	BYTE 	GrpName[64];	 //组名称 
	BYTE 	Group;	 //是否为组 不是:0/是:1/
	unsigned int 	LogonTime_L;	 //登陆时间 
	BYTE 	LogonTime_C[32];	 //登陆时间(字符) 
	unsigned int 	PersistTime;	 //有效时间长(s) 
	unsigned int 	LogoffTime_L;	 //退出时间 
	BYTE 	LogoffTime_C[32];	 //退出时间(字符) 
	BYTE 	Status;	 //登陆状态 退出:0/已登陆:1/
};
#endif



//============ GOOSE配置 表结构 ================

#ifndef GOOSE_CFG_TABNAME
#define GOOSE_CFG_TABNAME 	 _T("GOOSE_CFG")

struct GOOSE_CFG { 
	BYTE 	desc[64];	 //描述 
	BOOL 	value;	 //值 
	BOOL 	trig;	 //触发录波 
	BYTE 	refmac1[32];	 //关联的smv1 
	BYTE 	refmac2[32];	 //关联的smv2 
	BYTE 	refmac3[32];	 //关联的smv3 
	BYTE 	refmac4[32];	 //关联的smv4 
	BYTE 	refmac5[32];	 //关联的smv5 
	BYTE 	refmac6[32];	 //关联的smv6 
	BYTE 	refmac7[32];	 //关联的smv7 
	BYTE 	refmac8[32];	 //关联的smv8 
	BYTE 	refmac9[32];	 //关联的smv9 
	BYTE 	refmac10[32];	 //关联的smv10 
};
#endif



//============ MMS配置 表结构 ================

#ifndef MMS_CFG_TABNAME
#define MMS_CFG_TABNAME 	 _T("MMS_CFG")

struct MMS_CFG { 
};
#endif



//============ 采样值9-2配置 表结构 ================

#ifndef SMV92_CFG_TABNAME
#define SMV92_CFG_TABNAME 	 _T("SMV92_CFG")

struct SMV92_CFG { 
};
#endif



//============ 采样值9-1配置 表结构 ================

#ifndef SMV91_CFG_TABNAME
#define SMV91_CFG_TABNAME 	 _T("SMV91_CFG")

struct SMV91_CFG { 
};
#endif



//============ 文件服务 表结构 ================

#ifndef FileService_TABNAME
#define FileService_TABNAME 	 _T("FileService")

struct FileService { 
	BYTE 	DbName[32];	 //数据库名 
	BYTE 	TabName[32];	 //数据表名 
	BYTE 	PtName[64];	 //点名 
	unsigned int 	DbIndex;	 //库索引 
	unsigned int 	TabIndex;	 //表索引 
	unsigned int 	PtIndex;	 //点索引 
	BYTE 	FileName[64];	 //文件名 
	BYTE 	CmdType;	 //文件命令 读文件:0/传文件:1/删文件:2/返回操作:3/
	char 	Result;	 //控制返回结果 
	BOOL 	ValidFlag;	 //有效标志 
	long 	LSendTime;	 //发送时间(整型) 
	BYTE 	StrSendTime[32];	 //发送时间(字符) 
	unsigned int 	TimeOut;	 //超时 
	BOOL 	ProcFlag;	 //处理标志 
};
#endif

#endif //__MEMTABSTRUCT_H_LT
