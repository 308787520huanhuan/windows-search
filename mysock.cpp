#include "stdafx.h"
#include "mysock.h"
#include "mmsystem.h"
#include "afxmt.h"

CString			g_passwd	  = _T("hello,world!!!");			//password 
CStringArray    g_ipAllowArr;	//ip
int				gNowConnect	  = 0;

//g_overThisConnect 当这个为true时，关闭当前连接
BOOL			g_overThisConnect = FALSE;


#pragma comment(lib, "winmm.lib")

MySock::MySock()
{
	if((m_Ret = WSAStartup(MAKEWORD(2,2), &m_wsadata)) != 0)
		return;

	m_port 		 = DEFAUTPORT;
	m_offset	 = 0;
	memset(m_ip, 0, MAXLENGTH);
	memset(m_fileName, 0, MAXLENGTH);
	memset(m_block.buf, 0, LEN);
}

MySock::MySock(int port)
{
	if((m_Ret = WSAStartup(MAKEWORD(2,2), &m_wsadata)) != 0)
		return;
	
	m_port		 = port;
	m_offset	 = 0;
	memset(m_ip, 0, MAXLENGTH);
	memset(m_fileName, 0, MAXLENGTH);
	memset(&m_block, 0, sizeof(m_block));
}

MySock::~MySock()
{
	if(WSACleanup() == SOCKET_ERROR)
	{
		return;
	}
}

__int64 MySock::getThisFileLength(const char * filePath)
{
	WIN32_FIND_DATA FindFileData ;
	__int64 fileLength = 0;
	__int64 i64_temp   = 0;

	FindFirstFile(filePath, &FindFileData); 
	i64_temp = FindFileData.nFileSizeHigh;
	i64_temp = i64_temp * MAXDWORD + i64_temp;
	
	fileLength = i64_temp + FindFileData.nFileSizeLow;
	
	return fileLength;
}


//**************************************************客户端实现**************************************************************
ClientSock::ClientSock()
{
	m_cSpeedLimit = 100*KB;
	m_pwd = _T("");
	m_flag  = TRUE;
}

ClientSock::ClientSock(ClientSock& cli)
{
	memcpy(m_fileName, cli.m_fileName, sizeof(m_fileName));
	memcpy(m_ip, cli.m_ip, sizeof(m_ip));
	m_port		= cli.m_port;
	m_pwd		= cli.m_pwd;
	m_cSpeedLimit  = cli.m_cSpeedLimit;
	m_flag  = cli.m_flag;
}

ClientSock::ClientSock(int port):MySock(port)
{
	m_cSpeedLimit = 100*KB;
	m_pwd = _T("");
	m_flag  = TRUE;
}

ClientSock::~ClientSock()
{
	if(m_connectSocket  != INVALID_SOCKET)
		closesocket(m_connectSocket);
}

void ClientSock::WriteLog(const CString& context)
{

}

void ClientSock::CreSocket(int proType, const char FAR* cp)
{
	if(proType == TCPSOCKET)
	{
		m_connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(m_connectSocket == INVALID_SOCKET)
			return;

		int nNetTimeout = 5000;
		setsockopt(m_connectSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout,sizeof(int));
		m_clientConnectAddr.sin_family		  = AF_INET;
		m_clientConnectAddr.sin_port		  = htons(m_port);
		m_clientConnectAddr.sin_addr.s_addr   = inet_addr(cp);
	}
	else if(proType == UDPSOCKET)
	{
		
	}
}

bool ClientSock::Connect()
{
	if(::connect(m_connectSocket, (SOCKADDR *)&m_clientConnectAddr, sizeof(m_clientConnectAddr)) == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		return false;
	}
	return true;
}


void ClientSock::SendFile(const char* fileName)
{

}

DWORD WINAPI ClientSock::ClientInterFaceThread(LPVOID lpParam)
{
	return 1;
}

void ClientSock::TransFer(int port, char* fileName, char* ip)
{
	
}

void ClientSock::TransFer(int port, int speed, char* fileName, char* pwd, char* ip)
{
	DWORD		processId;
	HANDLE		handle;
	m_port		=	port;
	memset(m_fileName, 0, sizeof(m_fileName));
	memset(m_ip, 0, sizeof(m_ip));
	m_pwd = pwd;
	m_cSpeedLimit = speed * KB;
	
	memcpy(m_fileName, fileName, strlen(fileName));
	memcpy(m_ip, ip, strlen(ip));
	handle = ::CreateThread(NULL, 0, ClientInterFaceThread, this, 0, &processId);	
	WaitForSingleObject(handle, INFINITE);
}


DWORD WINAPI ClientSock::WatchSpeed(LPVOID lpParam)
{
	BLOCK conf;
	ClientSock *pc = static_cast<ClientSock*>(lpParam);
	
	while(1)
	{
		::recv(pc->m_connectSocket, (char *)&conf, sizeof(conf), 0);
		
		if(conf.type == SPEEDLIMIT)
		{
			if(pc->m_cSpeedLimit > (long)conf.offset && (long)conf.offset > 0)
				pc->m_cSpeedLimit = (long)conf.offset;	
		}
		else if( conf.type == OVER ) 
		{
			g_overThisConnect = TRUE;
		}

		memset(&conf, 0, sizeof(conf));
		Sleep(1);
	}
	
	return TRUE;
}



// void ClientSock::writeClientLog(const CString & con)
// {
// 	
// }