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
int fdarr[BACKLOG] = {0};
int conncount = 0;


void showclient()
{
  int i;
  printf("client amount is  %d\n", conncount);
  for(i=0 ; i<conncount;i++)
  {
    printf("[%d]:%d\n", i , fdarr[i]);
  }

  printf("\n\n", );

}


int main()
{
    int sock_fd , new_fd;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int yes =1;
    socklen_t sin_size;
    char buf[BUFFSIZE];
    int ret;
    int i;
    fd_set  readset;
    struct timeval timeout;


    if(sock_fd = socket(AF_INET , SOCK_STREAM , 0 ) == -1)
    {
        perror("socket");
        exit(0);
    }

    if(setsockrtopt(sock_fd , SOL_SOCKET , SO_REUSEADDR , &yes, sizeof(int)) == -1)
    {
      perror("setsockrtopt");
      exit(0);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;R_ANY;
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
     FD_SET(sock_fd , &readset);

     tv.tv_sec = 30;
     tv.tv_usec= 0;

     for (i = 0; i < BACKLOG; i++)
     {
        if (fd_A[i] != 0) {
        FD_SET(fd_A[i], &fdsr);
      }

    }
   }








}
