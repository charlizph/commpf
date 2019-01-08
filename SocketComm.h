///////////////////////////////////////////////////////////////////////////////
// FILE : SocketComm.h
// Header file for CSocketComm class
// CSocketComm
//     Generic class for Socket Communication
///////////////////////////////////////////////////////////////////////////////

#ifndef _SOCKETCOMM_H_
#define _SOCKETCOMM_H_
#ifdef WIN32
#include <list>

#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

#define WSA_VERSION  MAKEWORD(2,0)
#define HOSTNAME_SIZE	MAX_PATH
#else
#define HOSTNAME_SIZE	128
#define SOCKADDR_IN sockaddr_in
#endif
#include "CommBase.h"

#define STRING_LENGTH	40
#define IPADR_LEN		16

struct SockAddrIn : public SOCKADDR_IN {
public:
	SockAddrIn() { Clear(); }
	SockAddrIn(const SockAddrIn& sin) { Copy( sin ); }
	~SockAddrIn() { }
	SockAddrIn& Copy(const SockAddrIn& sin);
	void	Clear() { memset(this, 0, sizeof(SOCKADDR_IN)); }
	bool	IsEqual(const SockAddrIn& sin);
	bool	IsGreater(const SockAddrIn& sin);
	bool	IsLower(const SockAddrIn& pm);
	bool	IsNull() const { return ((sin_addr.s_addr==0L)&&(sin_port==0)); }
	ULONG	GetIPAddr() const { return sin_addr.s_addr; }
	short	GetPort() const { return sin_port; }
	bool	CreateFrom(LPCTSTR sAddr, int nPort, BOOL bServer,int nFamily = AF_INET);
	SockAddrIn& operator=(const SockAddrIn& sin) { return Copy( sin ); }
	bool	operator==(const SockAddrIn& sin) { return IsEqual( sin ); }
	bool	operator!=(const SockAddrIn& sin) { return !IsEqual( sin ); }
	bool	operator<(const SockAddrIn& sin)  { return IsLower( sin ); }
	bool	operator>(const SockAddrIn& sin)  { return IsGreater( sin ); }
	bool	operator<=(const SockAddrIn& sin) { return !IsGreater( sin ); }
	bool	operator>=(const SockAddrIn& sin) { return !IsLower( sin ); }
	operator LPSOCKADDR() { return (LPSOCKADDR)(this); }
	size_t	Size() const { return sizeof(SOCKADDR_IN); }
	void	SetAddr(SOCKADDR_IN* psin) { memcpy(this, psin, Size()); }
};

struct stMessageProxy
{
  SockAddrIn	address;
  BYTE			byData[BUFFER_SIZE];
};
#ifdef WIN32
#include <afxtempl.h>

typedef CArray<SockAddrIn,SockAddrIn> CSockAddrList;
#else
#include <vector>
typedef std::list<SockAddrIn> CSockAddrList;

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE 0
#endif

#endif
class CSocketComm;

//Net Message Type - NMT
//心跳信号
#define NM_HEARTBEAT	1
//握手信号
#define NM_SHAKEHAND	2
//关闭udp连接
#define NM_CLOSEUDP	3

struct NetHeader
{
	NetHeader()
	{
		Init();
	}
	void Init()
	{
	//	memcpy(szHeader,"dvlt",4);
		memset(szHeader,0,8);
		memset(szCheck,0,8);
		szHeader[0] = 'h';
		szHeader[1] = 'r';
		szHeader[2] = 'x';
		szHeader[3] = 't';
		szHeader[5] = '\0';

		szCheck[0] = 'z';
		szCheck[1] = 'h';
		szCheck[2] = 'p';
		szCheck[3] = 'h';
		szCheck[4] = '\0';
		bIsValid = TRUE;
		bMsgType = NM_SHAKEHAND;
		nDataLen = 0;
		bDoubleNet=0;//是否为双网；
		bDoubleCp=0;//是否为双机
		bMasterCp=0;//是否为主机
		bMore = FALSE;
//		sDstHost[0]='\0';
//		sSrcHost[0] = '\0';
//		memset(szReserve,0,2);
		memset(sDstHost,0,IPADR_LEN);
		memset(sDstHost,0,IPADR_LEN);
	}

	BOOL IsOwnNetData()
	{
	//	CString strTmp;
	//	strTmp.Format("%s",szHeader);
		BOOL bOwn = strcmp(szHeader,("hrxt"));
		if(bOwn == 0)
			return TRUE;
		return FALSE;
	}

	BOOL IsValid()
	{
		if(strcmp(szCheck,"zhph")!=0)
			return FALSE;
		return bIsValid==TRUE?TRUE:FALSE;
	}

	char		szHeader[8];
	char		sSrcHost[16];
	char		sDstHost[16];
	BYTE		bIsValid;//数据是否有效
	BYTE		bMsgType;//报文类型
	BOOL		bDoubleNet;//是否为双网；
	BOOL		bDoubleCp;//是否为双机
	int			nDataLen;//
	BOOL		bMasterCp;//是否为主机
	BOOL		bMore;//
	char		szCheck[8];
//	BYTE	szReserve[16];
};
         
//typedef CTypedPtrArray<CPtrArray , CSocketComm*>  CAClientSocket;

class CSocketComm : public CBaseComm
{
public:
	HANDLE m_hOpenCommEvent;
	int nIndex;
	CSocketComm();
	CSocketComm(int nComType);
	virtual ~CSocketComm();
public:
	virtual void ForceClose();
	virtual BOOL CloseComm(BOOL bPost = false);
	virtual BOOL OpenComm();
	virtual BOOL OpenComm(CCommParam comParam);
	virtual BOOL InnerOpenComm();
	virtual BOOL IsConnected();
	virtual int WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);//返回写成功的字节数，-1表示写失败
	virtual int ReadData(void* pBuf,int nLen);//pBuf接收的缓冲区,由调用者负责分配,返回读到字节数，-1 表示读失败
#ifdef WIN32
	virtual void SetParentWnd(CWnd* pWnd);
#endif
public:
	void SetComm(HANDLE hCom);
//	bool IsOpen() const;	// Is Socket valid?
	bool IsStart() const;	// Is Thread started?
	bool IsServer() const;	// Is running in server mode
	bool IsBroadcast() const; // Is UDP Broadcast active
	bool IsSmartAddressing() const;	// Is Smart Addressing mode support
	SOCKET GetSocket() const;	// return socket handle
	void SetServerState(bool bServer);	// Run as server mode if true
	void SetSmartAddressing(bool bSmartAddressing);	// Set Smart addressing mode
	bool GetSockName(SockAddrIn& saddr_in);	// Get Socket name - address
	bool GetPeerName(SockAddrIn& saddr_in);	// Get Peer Socket name - address
	void AddToList( SockAddrIn saddr_in);	// Add an address to the list
	void RemoveFromList( SockAddrIn saddr_in);	// Remove an address from the list
//	void CloseComm();		// Close Socket
	virtual bool WatchComm();		// Start Socket thread
//	virtual void StopComm();		// Stop Socket thread

	// Create a Socket - Server side
	//LPCTSTR strServiceName: Service name or port number
	//nFamily :AF_INET
	//nType:SOCK_STREAM, SOCK_DGRAM
	//strDestination: hostname or address to connect (in .dot format)
	bool CreateSocket(int nType);//LPCTSTR strServiceName, int nFamily, int nType, UINT uOptions = 0);
	// Create a socket, connect to (Client side)
	bool ConnectTo(int nType);//LPCTSTR strDestination, LPCTSTR strServiceName, int nFamily, int nType);
	bool CreateSocketUdp(int nType);//LPCTSTR strServiceName, int nFamily, int nType, UINT uOptions = 0);
	// Create a socket, connect to (Client side)
	bool ConnectToUdp(int nType);//LPCTSTR strDestination, LPCTSTR strServiceName, int nFamily, int nType);

// Event function - override to get data
//	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
//	virtual void OnEvent(UINT uEvent);
// Run function - override to implement a new behaviour
	virtual void Run();
	bool ShutdownConnection(SOCKET sock);  // Shutdown a connection


	// Utility functions
//	static 
	SOCKET WaitForConnection(SOCKET sock,SOCKADDR_IN & nRemoteSockInfo); // Wait For a new connection (Server side)
	static USHORT GetPortNumber( LPCTSTR strServiceName );	// Get service port number
	static ULONG GetIPAddress( LPCTSTR strHostName,BOOL bServer );	// Get IP address of a host
	static bool GetLocalName(LPTSTR strName, UINT nSize);	// GetLocalName
	static bool GetLocalAddress(LPTSTR strAddress, UINT nSize);	// GetLocalAddress
// SocketComm - data
public:
	void ClosePort();
	BOOL m_bWsaStart;
	void SetSockOpt(SOCKET sock);
	BOOL SetDstAddr();
	BOOL m_bShakeSuc;
	int SendShakeHand();
	int SendHeartBeat();
	int SendShakeHand(NetHeader ndHead);
	int SendHeartBeat(NetHeader ndHead);
//	CAClientSocket m_aClientList;
	void*	m_pSocketSrv;//CSocketServer;
	int		m_nLocalPort;
	SOCKADDR_IN	m_remoteinaddr;//clien info for connect to server
protected:
	SockAddrIn	m_sockBroadAddr;
	SockAddrIn	m_sockBroadAddr2;
	SockAddrIn	m_sockBroadAddr3;
	HANDLE		m_hComm;		// Serial Comm handle
	bool		m_bServer;		// Server mode (true)
	bool		m_bSmartAddressing;	// Smart Addressing mode (true) - many listeners
	bool		m_bBroadcast;	// Broadcast mode
	CSockAddrList m_AddrList;	// Connection address list for broadcast
	SockAddrIn m_curiter;
// SocketComm - function


//private:
// Data function
	virtual int ReadComm(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout);
	virtual int WriteComm(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
};
#ifdef WIN32
extern void SocketThreadProc(LPVOID pParam);
#else
extern void* SocketThreadProc(LPVOID pParam);
#endif
#endif // _SOCKETCOMM_H_
