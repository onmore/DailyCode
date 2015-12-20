// ehcobylibevent.cpp : 定义控制台应用程序的入口点。
//

#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<winsock2.h>


#include "event2/event.h"
#include "event2/bufferevent.h"
#include "event2/event-config.h"
#include "event2/util.h"
#include "event2/buffer.h"

#define MAX_LINE 2048
event_base *base;



void onread(evutil_socket_t fd, short events, void *arg)
{
	if (fd == INVALID_SOCKET)
	{
		return;
	}
	char buff[MAX_LINE] = {0};
	recv(fd, buff, MAX_LINE, 0);
	printf(buff);
	send(fd, buff, strlen(buff) + 1, 0);
	closesocket(fd);
}

void onaccept(evutil_socket_t listener, short event, void *arg)
{
	event_base *loopbase = (event_base*)arg;
	sockaddr_storage ss;
	int slen = sizeof(ss);
	SOCKET fd = accept(listener, (struct sockaddr*)&ss, &slen);
	if (fd == INVALID_SOCKET)
	{
		closesocket(fd);
	}
	else
	{
		struct event* acceptevent;
		acceptevent = event_new(loopbase, fd, EV_READ | EV_PERSIST, onread, (void*)loopbase);
		event_add(acceptevent, NULL);
	}
}




int main()
{	
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		return -1;
	}


	SOCKET Server = socket(AF_INET , SOCK_STREAM , 0);
	if (Server == INVALID_SOCKET)
	{	
		WSACleanup();
		return -1;
	}

	sockaddr_in addr;
	memset(&addr , 0 , sizeof(sockaddr_in));
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if (bind(Server, (sockaddr*)&addr, (int)sizeof(sockaddr)) == SOCKET_ERROR)
	{	
		closesocket(Server);
		WSACleanup();
		return -1;
	}

	if (listen(Server, 5) == SOCKET_ERROR)
	{
		closesocket(Server);
		WSACleanup();
		return -1;
	}

	base = event_base_new();
	event* listenevent = event_new(base	, Server , EV_READ|EV_PERSIST, onaccept , (void*)base);
	event_add(listenevent , NULL);
	event_base_dispatch(base);

    return 0;
}

