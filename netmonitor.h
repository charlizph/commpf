// MyEthernet.h: interface for the CNetMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYETHERNET_H__DD06938E_4719_4446_B901_9704D4549731__INCLUDED_)
#define AFX_MYETHERNET_H__DD06938E_4719_4446_B901_9704D4549731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WINSOCK2API_
#define _WS2TCPIP_H_

#define REMOTE	1
#define	WPCAP	1

#include <afxtempl.h>
#include "pcap.h"

//define header lengths
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"wpcap.lib")

#define ETHER_LENGTH 14
#define IP_LENGTH    20
#define TCP_LENGTH   20
#define UDP_LENGTH   8
#define ICMP_LENGTH  8
#define IGMP_LENGTH  8
#define ARP_LENGTH   28
#define IGMP_MESG_LENGTH 13
#define VLAN_LENGTH 4
#define EthPduHeader_Len 8
 
	// Ethernet Header
	struct eth_header   // 14 bytes
	{
	u_char dmac[6]; //destination mac address
	u_char smac[6]; //source mac address
	u_short type;                 //IP ,ARP , RARP
	};
	
	// IPV4 Address
	struct ip_address
	{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	};

	// ARP header
	struct arp_header   //28 bytes
	{
	u_short hrd;       //hardware address space=0x0001
	u_short eth_type;  //Ethernet type ....=0x0800
	u_char maclen;     //Length of mac address=6
	u_char iplen;      //Length of ip addres=4
	u_short opcode;    //Request =1 Reply=2 (highbyte)
	u_char smac[6];    //source mac address
	ip_address saddr;  //Source ip address
	u_char dmac[6];    //Destination mac address
	ip_address daddr;  //Destination ip address
	};
	
	typedef arp_header rarp_header;

	
	/* IPv4 header */
    struct ip_header
	{
	u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service 
    u_short tlen;           // Total length 
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    ip_address  saddr;      // Source address
    ip_address  daddr;      // Destination address
   // u_int   op_pad;         // Option + Padding
	};

	// UDP header
   struct udp_header   //8 bytes
   {
    u_short sport;          // Source port
    u_short dport;          // Destination port
    u_short len;            // Datagram length
    u_short crc;            // Checksum
   };

   // TCP header
	struct tcp_header  //20 bytes : default
	{
	u_short sport;      //Source port
	u_short dport;      //Destination port
	u_long seqno;       //Sequence no
	u_long ackno;       //Ack no
	u_char offset;      //Higher level 4 bit indicates data offset
	u_char flag;        //Message flag
					//FIN - 0x01
					//SYN - 0x02
					//RST - 0x04 
					//PUSH- 0x08
					//ACK- 0x10
					//URG- 0x20
					//ACE- 0x40
					//CWR- 0x80

	u_short win;
	u_short checksum;
	u_short uptr;
  	};

	// ICMP Header
	struct icmp_header
	{
	u_char type;
	u_char code;
	u_short checksum;
	u_short id;
	u_short seqno;
	};


	//IGMP version 2 
	struct igmp_header
	{
	u_char type;         //type of igmp message
	u_char restime;      //Response time
	u_short checksum;    //checksum ...
	ip_address groupaddr; //Multicast Group Address
	};
	
	// Structure for storing IGMP messages.
	struct igmp_mesg
	{
	u_char type;
	char mesg[200];
	};

	// Structure for storing ICMP messages.
	struct icmp_mesg
	{
	u_char type;
	char mesg[200];
	};

/************************
	Destination address
	Source address
	TPID
	TCI
	Ethertype
	APPID
	Length
	Reserved 1
	Reserved 2
	APDU (of length m)
	(Pad bytes if necessary)
	Frame check sequence
**************************/

#include "vlanstruct.h"

#include "commbase.h"
#include "win32-extensions.h"

class CNetMonitor:public CBaseComm
{
public:
	CNetMonitor();
	virtual ~CNetMonitor();
//	pcap_t *m_Interface;
	pcap_t* m_Interface;
	BYTE  m_LocalMac[6];
	BYTE  m_SourceMac[6];
	BYTE  m_DestinMac[6];
	static CWnd* m_pParentView;
	BOOL StartGooseIn();
public:
	BOOL InitSendQueue(int nQueBuf);
	pcap_send_queue *  m_queue ;
	int	m_nWaitTime;
	int m_nEthType;
	virtual BOOL IsMonitor();
	virtual BOOL CloseComm(BOOL bPost = false);
	virtual BOOL OpenComm();
	virtual BOOL OpenComm(CCommParam comParam);
	virtual BOOL IsConnected();
	virtual int WriteData(void* pBuf,int nLen);//返回写成功的字节数，-1表示写失败
	virtual int ReadData(void* pBuf,int nLen);//pBuf接收的缓冲区,由调用者负责分配,返回读到字节数，-1 表示读失败
	// Event function - override to get data
	virtual bool WatchComm();//接收数据线程	
	static UINT WINAPI WatchThreadProc(LPVOID pParam);
	void GetLocalMac(CString adapterName);
	static CString GetMACaddress(CString adapterName,BYTE* pMac); /* pMac 6字节长度*/ 
	
protected:
	static void PacketHandler(LPVOID param, const struct pcap_pkthdr *header, const u_char *pkt_data);
	// thread
	CWinThread*			m_Thread;
	struct bpf_program		m_Filter;
private:
	
	VLAN  m_vlan;
	BOOL IsBroadCast(const BYTE mac[]);
	BOOL IsLocalMac(const BYTE mac[]);
	void SendData(BYTE* ptr,  INT len);

};

#endif // !defined(AFX_MYETHERNET_H__DD06938E_4719_4446_B901_9704D4549731__INCLUDED_)
