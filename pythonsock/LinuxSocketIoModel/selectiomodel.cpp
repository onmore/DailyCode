#include"stdio.h"
#include "sys/select.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/socket.h"
#include "sys/inet.h"
#include "sys/in.h"
#include "fcntl.h"
#include "unistd.h"

#define PORT 10086
#define BACKLOG 5
#define BUFFSIZE
int fdarr[BACKLOG] = { 0 };
int conncount = 0;


void showclient()
{
	int i;
	printf("client amount is  %d\n", conncount);
	for (i = 0; i<conncount; i++)
	{
		printf("[%d]:%d\n", i, fdarr[i]);
	}

	printf("\n\n", );

}


int main()
{
	int sock_fd, new_fd;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	int yes = 1;
	socklen_t sin_size;
	char buf[BUFFSIZE];
	int ret;
	int i;
	fd_set  readset;
	struct timeval timeout;


	if (sock_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
	{
		perror("socket");
		exit(0);
	}

	if (setsockrtopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("setsockrtopt");
		exit(0);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = INADDR_ANY; R_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

	if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sock_fd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("listen port %d\n", PORT);

	fd_set  readset;
	int maxsock;
	struct timeval tv;

	conncount = 0;
	sin_size = sizeof(clientaddr);
	maxsock = sock_fd;
	while (ture)
	{
		/* code */
		FD_ZERO(readset);
		FD_SET(sock_fd, &readset);

		tv.tv_sec = 30;
		tv.tv_usec = 0;

		for (i = 0; i < BACKLOG; i++)
		{
			if (fd_A[i] != 0)
			{
				FD_SET(fd_A[i], &fdsr);
			}

		}

		ret = select(maxsock + 1, &readset, NULL, NULL, &tv);
		if (ret < 0)
		{
			perror("select");
			break;
		}
		else if (ret == 0)
		{
			printf("timeout\n");
			continue;
		}

		for (i = 0; i <conncount; i++)
		{
			if (FD_ISSET(fdarr[i], &readfd))
			{
				ret = recv(fdarr[i], buf, sizeof(buf), 0);
				if (ret < BUF_SIZE)
					memset(&buf[ret], '\0', 1);
				printf("client[%d] send:%s\n", i, buf);
			}
		}

		if (FD_ISSET(sock_fd, &fdsr))
		{
			new_fd = accept(sock_fd, (struct sockaddr *)&clientaddr, &sin_size);
			if (new_fd <= 0)
			{
				perror("accept");
				continue;
			}

			if (conncount < BACKLOG)
			{
				fdarr[conn_amount++] = new_fd;
				printf("new connection client[%d] %s:%d\n", conn_amount,
					inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				if (new_fd > maxsock)
					maxsock = new_fd;
			}
			else
			{
				printf("max connections arrive, exit\n");
				send(new_fd, "bye", 4, 0);
				close(new_fd);
				break;
			}
		}

		showclient();

	}

	// close other connections
	for (i = 0; i < BACKLOG; i++)
	{
		if (fdarr[i] != 0)
		{
			close(fdarr[i]);
		}
	}
	exit(0);
}
