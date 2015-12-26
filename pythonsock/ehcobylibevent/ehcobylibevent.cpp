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
#include <event2/listener.h>


#include "stdio.h"
#include "stdlib.h"

#define MAX_LINE 2048
event_base *base;
evconnlistener *listener;



void onread(evutil_socket_t fd, short events, void *arg)
{
	if (fd == INVALID_SOCKET)
	{
		return;
	}
	char buff[MAX_LINE] = {0};
	event* ev = (event*)arg;
	recv(fd, buff, MAX_LINE, 0);
	printf(buff);
	send(fd, buff, strlen(buff) + 1, 0);
	event_del(ev);
	free(ev);
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
		acceptevent = event_new(loopbase, fd, EV_READ|EV_PERSIST, onread, (void*)loopbase);
		evutil_make_socket_nonblocking(fd);
		event_add(acceptevent, NULL);
	}
}


void listener_cb(evconnlistener *listener, evutil_socket_t fd , sockaddr *sa, int socklen, void *user_data)
{
	event_base *loopbase = (event_base*)user_data;
	//sockaddr_storage ss;
	//int slen = sizeof(ss);
	//SOCKET fd = accept(fd1, (struct sockaddr*)&ss, &slen);
	evutil_make_socket_nonblocking(fd);
	if (fd == INVALID_SOCKET)
	{
		closesocket(fd);
	}
	else
	{
		event* acceptevent;
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
	//evutil_make_socket_nonblocking(Server);
	

	sockaddr_in addr;
	memset(&addr , 0 , sizeof(sockaddr_in));
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//if (bind(Server, (sockaddr*)&addr, (int)sizeof(sockaddr)) == SOCKET_ERROR)
	//{	
	//	closesocket(Server);
	//	WSACleanup();
	//	return -1;
	//}


	base = event_base_new();
	//event* listenevent = event_new(base	, Server , EV_READ|EV_PERSIST, onaccept , (void*)base);
	//event_add(listenevent , NULL);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
				LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
				(struct sockaddr*)&addr,
				sizeof(addr));
		
	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
				return 1;
		}


    return 	event_base_loop(base, 0);
}

/*
This exmple program provides a trivial server program that listens for TCP
connections on port 9995.  When they arrive, it writes a short message to
each client connection, and closes each connection once it is flushed.

Where possible, it exits cleanly in response to a SIGINT (ctrl-c).
*/


//#include <string.h>
//#include <errno.h>
//#include <stdio.h>
//#include <signal.h>
//#ifndef WIN32
//#include <netinet/in.h>
//# ifdef _XOPEN_SOURCE_EXTENDED
//#  include <arpa/inet.h>
//# endif
//#include <sys/socket.h>
//#endif
//
//#include <event2/bufferevent.h>
//#include <event2/buffer.h>
//#include <event2/listener.h>
//#include <event2/util.h>
//#include <event2/event.h>
//
//static const char MESSAGE[] = "Hello, World!\n";
//
//static const int PORT = 12345;
//
//static void listener_cb(struct evconnlistener *, evutil_socket_t,
//struct sockaddr *, int socklen, void *);
//static void conn_writecb(struct bufferevent *, void *);
//static void conn_eventcb(struct bufferevent *, short, void *);
//static void signal_cb(evutil_socket_t, short, void *);
//
//int
//main(int argc, char **argv)
//{
//	struct event_base *base;
//	struct evconnlistener *listener;
//	struct event *signal_event;
//
//	struct sockaddr_in sin;
//#ifdef WIN32
//	WSADATA wsa_data;
//	WSAStartup(0x0201, &wsa_data);
//#endif
//
//	base = event_base_new();
//	if (!base) {
//		fprintf(stderr, "Could not initialize libevent!\n");
//		return 1;
//	}
//
//	memset(&sin, 0, sizeof(sin));
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(PORT);
//
//	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
//		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
//		(struct sockaddr*)&sin,
//		sizeof(sin));
//
//	if (!listener) {
//		fprintf(stderr, "Could not create a listener!\n");
//		return 1;
//	}
//
//	//signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);
//
//	//if (!signal_event || event_add(signal_event, NULL)<0) {
//	//	fprintf(stderr, "Could not create/add a signal event!\n");
//	//	return 1;
//	//}
//
//	event_base_dispatch(base);
//
//	evconnlistener_free(listener);
//	//event_free(signal_event);
//	event_base_free(base);
//
//	printf("done\n");
//	return 0;
//}
//
//static void
//listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
//struct sockaddr *sa, int socklen, void *user_data)
//{
//	struct event_base *base = (event_base*)user_data;
//	struct bufferevent *bev;
//
//	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
//	if (!bev) {
//		fprintf(stderr, "Error constructing bufferevent!");
//		event_base_loopbreak(base);
//		return;
//	}
//	bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
//	bufferevent_enable(bev, EV_WRITE);
//	bufferevent_disable(bev, EV_READ);
//
//	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
//}
//
//static void
//conn_writecb(struct bufferevent *bev, void *user_data)
//{
//	struct evbuffer *output = bufferevent_get_output(bev);
//	if (evbuffer_get_length(output) == 0) {
//		printf("flushed answer\n");
//		bufferevent_free(bev);
//	}
//}
//
//static void
//conn_eventcb(struct bufferevent *bev, short events, void *user_data)
//{
//	if (events & BEV_EVENT_EOF) {
//		printf("Connection closed.\n");
//	}
//	else if (events & BEV_EVENT_ERROR) {
//		printf("Got an error on the connection: %s\n",
//			strerror(errno));/*XXX win32*/
//	}
//	/* None of the other events can happen here, since we haven't enabled
//	* timeouts */
//	bufferevent_free(bev);
//}
//
//static void
//signal_cb(evutil_socket_t sig, short events, void *user_data)
//{
//	struct event_base *base = (event_base*)user_data;
//	struct timeval delay = { 2, 0 };
//
//	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");
//
//	event_base_loopexit(base, &delay);
//}
