#include "StdAfx.h"
#include "get_json.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <winsock2.h>
#include "mysock.h"

#pragma comment( lib, "ws2_32.lib"  )

void p(char *msg)
{
#if 0

#endif
}

void get_json(char* recv_buf, char* key)
{
	int ret;
	WSAData		m_wsadata;
	char *p_buf;

	if((ret = WSAStartup(MAKEWORD(2,2), &m_wsadata)) != 0)
		return;
	HOSTENT *site;
	char send_buf[100] =  "GET https://api.douban.com/v2/book/search";
	char *host = "api.douban.com";
	struct sockaddr_in me;
	
	site = gethostbyname(host);
	if (site == NULL)
	{
		AfxMessageBox("gethostbyname");
		exit(1);
	}

	memcpy(&me.sin_addr, site-> h_addr_list[0], site-> h_length);
	p("memcpy");
	me.sin_family = AF_INET;
	me.sin_port = htons(80);
	int socket_des = socket(AF_INET,SOCK_STREAM,0);

	if (connect(socket_des, (struct sockaddr *)&me,sizeof(struct sockaddr)) == -1)
	{
		AfxMessageBox("connect error!!!");
		return ;
	}
			
	sprintf(send_buf, "%s?q=%s\n", send_buf, key);//print to send_buf
	send(socket_des,send_buf,strlen(send_buf),0);
//	send(socket_des,"\n",strlen("\n"),0);

	char buf[256] = {0};//below recv from host

	p_buf = recv_buf;


	while ((ret =::recv(socket_des, (char *)buf, 256, 0)) > 0)
	{
		memcpy(p_buf, buf, ret);
		p_buf += ret;
	}

	closesocket(socket_des);
}
