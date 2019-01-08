// SerialComm.h: interface for the CSerialComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALCOMM_H__6B6EDACD_D4F5_471B_B60C_349594EBE91E__INCLUDED_)
#define AFX_SERIALCOMM_H__6B6EDACD_D4F5_471B_B60C_349594EBE91E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommBase.h"

#define WM_COMM_BREAK_DETECTED		WM_USER+1	// A break was detected on input. 
#define WM_COMM_CTS_DETECTED		WM_USER+2	// The CTS (clear-to-send) signal changed state.  
#define WM_COMM_DSR_DETECTED		WM_USER+3	// The DSR (data-set-ready) signal changed state.  
#define WM_COMM_ERR_DETECTED		WM_USER+4	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY.  
#define WM_COMM_RING_DETECTED		WM_USER+5	// A ring indicator was detected.  
#define WM_COMM_RLSD_DETECTED		WM_USER+6	// The RLSD (receive-line-signal-detect) signal changed state.  
#define WM_COMM_RXCHAR				WM_USER+7	// A character was received and placed in the input buffer.  
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8	// The event character was received and placed in the input buffer.   
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9	// The last character in the output buffer was sent.   

//#include "comcontrol.h"
//class CSerial;
#ifndef WIN32
//namespace Serial {
	enum BaudRateEnum {
		BAUD_50    = B50,         //!< 50 baud.
		BAUD_75    = B75,         //!< 75 baud.
		BAUD_110   = B110,        //!< 110 baud.
		BAUD_134   = B134,        //!< 134.5 baud. Yes 134.5. I did not mistype that.
		BAUD_150   = B150,        //!< 150 baud.
		BAUD_200   = B200,        //!< 200 baud.
		BAUD_300   = B300,        //!< 300 baud.
		BAUD_600   = B600,        //!< 600 baud.
		BAUD_1200  = B1200,       //!< 1200 baud.
		BAUD_1800  = B1800,       //!< 1800 baud.
		BAUD_2400  = B2400,       //!< 2400 baud.
		BAUD_4800  = B4800,       //!< 4800 baud.
		BAUD_9600  = B9600,       //!< 9600 baud.
		BAUD_19200 = B19200,      //!< 19200 baud.
		BAUD_38400 = B38400,      //!< 38400 baud.
		BAUD_57600  = B57600,       //!< 1200 baud.
		BAUD_115200  = B115200,       //!< 1800 baud.
		BAUD_230400  = B230400,       //!< 2400 baud.
		BAUD_460800  = B460800,       //!< 4800 baud.
		BAUD_500000  = B500000,       //!< 9600 baud.
		BAUD_576000 = B576000,      //!< 19200 baud.
		BAUD_INVALID              //!< Invalid baud rate.
	} ;

	      /** The allowed values of character sizes that can be used
		  during the serial communication.

	       */
	enum CharSizeEnum {
		CHAR_SIZE_5 = CS5, //!< 5 bit characters.
		CHAR_SIZE_6 = CS6, //!< 6 bit characters.
		CHAR_SIZE_7 = CS7, //!< 7 bit characters.
		CHAR_SIZE_8 = CS8, //!< 8 bit characters.
		CHAR_SIZE_INVALID  //!< Invalid character size.
	} ;

	      /** The allowed values of the parity associated with the serial
		  port communications.
		
	      */
	enum ParityEnum {
		PARITY_EVEN,     //!< Even parity.
		PARITY_ODD,      //!< Odd parity.
		PARITY_NONE,     //!< No parity i.e. parity checking disabled.
		PARITY_INVALID   //!< Invalid parity value.
	} ;

	      /** The values of the flow control settings for a serial
		  port.

	       */
	enum FlowControlEnum {
		FLOW_CONTROL_HARD,   //!< Hardware flow control.
		FLOW_CONTROL_SOFT,   //!< Software flow control.
		FLOW_CONTROL_INVALID //!< Invalid flow control setting.
	} ;
//}
#endif

#ifndef WIN32
	#ifndef INVALID_HANDLE_VALUE
		#define INVALID_HANDLE_VALUE 0
	#endif
#endif
class CSerialComm : public CBaseComm  
{
public:
	CSerialComm();
	virtual ~CSerialComm();
//	CComControl m_comCtrol;
public:
	void ResetBytes();
	virtual BOOL OpenComm();
	virtual BOOL OpenComm(CCommParam comParam);
	virtual BOOL CloseComm(BOOL bPost = false/* *10 ms */);
	virtual void ClosePort();
	virtual BOOL IsConnected();
	virtual int  WriteData(void* pBuf,int nLen,BOOL bRefreshTime=TRUE);
	virtual int	 ReadData(void* pBuf,int nLen);
#ifdef WIN32
	void GetTimeOuts(COMMTIMEOUTS & cts);
#endif
	void SetTimeOuts(int nTimeOut);
	virtual bool WatchComm();
// Event function - override to get data
	virtual void Run();
	BOOL m_bOpenExist;
//	CSerial* m_pSerial;
	HANDLE m_hCom;

	// Event array.  
	// One element is used for each event. There are two event handles for each port. 
	// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent). 
	// There is a general shutdown when the port is closed.  
 #ifdef WIN32
public:
	BOOL Config();
	void ClearInOut();
	DWORD	m_cbInQue;			//输入缓冲字节数
	DWORD	m_cbOutQue;			//输出缓冲字节数
protected:
	OVERLAPPED	m_ovRead;		//用于接收的数据OVERLAPPED结构	
	OVERLAPPED	m_ovWrite;		//用于发送的数据OVERLAPPED结构
	static UINT WINAPI SerialThreadProc(LPVOID pParam);
	// handles 
	HANDLE				m_hShutdownEvent; 
	HANDLE				m_hWriteEvent; 
	HANDLE				m_hEventArray[3]; 

	// structures 
//	OVERLAPPED			m_ov; 
	COMMTIMEOUTS		m_CommTimeouts; 
	DCB					m_dcb; 
	DWORD				m_dwCommEvents; 
// synchronisation objects 
	CRITICAL_SECTION	m_csCommunicationSync; 
#else
protected:
	static void* SerialThreadProc(void * pParam);
		bool SetParameters();
		const BaudRateEnum SetBaudRate(const BaudRateEnum baud_rate);
		const BaudRateEnum BaudRate() const;	
		const CharSizeEnum SetCharSize(const CharSizeEnum char_size);
		const CharSizeEnum CharSize() const;
		
		short SetNumOfStopBits(short stop_bits);		
		short NumOfStopBits() const;
		const ParityEnum SetParity(const ParityEnum parity);
		const ParityEnum Parity() const;
		const FlowControlEnum SetFlowControl(const FlowControlEnum flow_c);
		const FlowControlEnum FlowControl() const;
#endif
};

#endif // !defined(AFX_SERIALCOMM_H__6B6EDACD_D4F5_471B_B60C_349594EBE91E__INCLUDED_)
