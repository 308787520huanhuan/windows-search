#ifndef MYSOCK_H
#define MYSOCK_H
#include <afx.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define		LOGNAME			"transfer.log"
#define     KB				1024
#define		MB				(1024*KB)
#define		LEN				(1*KB)
#define     DEFAUTPORT      5000
#define		PWDLENGTH		40
#define		DEFAULTSPEED	(10*KB)


#define     TCPSOCKET       0x0001
#define     UDPSOCKET       0x0002
#define		FILENAME		0x0004
#define		FILETEXT		0x0008

#define		FINISH			0x0010
#define		FAILE			0x0020
#define		BUZY			0x0040
#define		BADPWD			0x0080

#define		FORBID			0x0100
#define		SPEEDLIMIT		0x0200
#define     OVER			0x0800

#define		MAXLENGTH		200

typedef struct block
{
	int			type;
	__int64		offset;		//type == FILENAME:offset为文件长度；否则为文件偏移量
	char        buf[LEN];
	char		pwd[PWDLENGTH];
	block(int _type = FAILE, __int64 _offset = 0):type(_type), offset(_offset)
	{
		memset(buf, 0, sizeof(buf));
		memset(pwd, 0, sizeof(pwd));
	}
}BLOCK;




//*************************************************BASECLASS*************************************************
class MySock
{
public:
	MySock();
	~MySock();
	MySock(int port);
	virtual void TransFer(int port, char* fileName, char* ip) = 0;
	__int64 getFileOffset(){return m_offset;}
	__int64 getThisFileLength(const char* filePath);

private:
	WSAData		m_wsadata;
	int			m_Ret;
public:
	int			m_port;
	char		m_fileName[MAXLENGTH];
	char		m_ip[MAXLENGTH];
	BLOCK		m_block;
	CString		m_pwd;
	__int64		m_offset;
};

//*************************************************CLIENT*************************************************
class ClientSock :public MySock
{
public:
	ClientSock();
	ClientSock(int port);
	ClientSock(ClientSock& cli);
	~ClientSock();
	void TransFer(int port, char* fileName, char* ip);
	void TransFer(int port, int speed, char* fileName, char* pwd, char* ip = "127.0.0.1");
	void WriteLog(const CString& context);



public:
	static DWORD WINAPI ClientInterFaceThread(LPVOID lpParam);
	void CreSocket(int proType, const char FAR* cp = "127.0.0.1");
	bool Connect();
	void SendFile(const char* filaName);
	static DWORD WINAPI WatchSpeed(LPVOID lpParam);
	//void writeClientLog(const CString& context);

public:
	//是否继续不停发送
	int m_flag;
	long m_cSpeedLimit;
public:
	SOCKET		m_connectSocket;
	SOCKADDR_IN m_clientConnectAddr;
	
};
#endif 