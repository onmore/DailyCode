#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <poll.h>

#define PORT 10086
#define BACKLOG 5
#define BUFFSIZE 1024

int main()
{
  printf(" server have start！\n");

  int serverfd = socket(AF_INET,SOCK_STREAM,0);
  sockaddr_in serveraddr;
  bzero(&serveraddr , sizeof(serveraddr));
  serveraddr.family = AF_INET;
  serveraddr.sin_port   = htons(PORT);
  serveraddr.sin_addr.s_addr = INADDR_ANY;

  int ret = bind(serverfd , (sockaddr*)&serveraddr , sizeof(serveraddr));
  if (ret == -1)
  {
    printf("bind erro");
    return -1;
  }

  ret = listen(serverfd , BACKLOG);
  if (ret == -1)
  {
    printf("bind erro");
    return -1;
  }

  //客户端地址信息
  sockaddr_in clientaddr;
  socklen_t client_addr_len = sizeof(sockaddr_in);

  pollfd pollarr[BACKLOG] = {0};
  pollarr[0] = serverfd;
  pollfdArry[0].events = POLLIN;

  int cur_fd_num = 1;
  char buf[BUFFSIZE]={0};

  while (1)
  {
      int nready = poll(pollarr , cur_fd_num , -1);
      if (pollarr[0].revents & POLLIN)
      {
          if (cur_fd_num > BACKLOG)
          {
            printf("socket is too much！\n");
          }
          else
          {
            int client_sockfd = accept(server_sockfd,(struct sockaddr*)&client_addr,&client_addr_len);

                if(client_sockfd < 0)
                {
                   perror("accept");
                }
                else
                {
                    //inet_ntoa(struct addr_in) 将IP地址转换为字符串并返回
                    printf("accept client_addr %s\n",inet_ntoa(client_addr.sin_addr));

                    for(int i=0;i<MAX_FD_NUM;++i)
                    {
                        if(pollfdarr[i].fd == 0)
                        {
                            pollfdarr[i].fd = client_sockfd;
                            pollfdarr[i].events = POLLIN;
                            cur_fd_num++;
                            break;
                        }

                    }
                }
          }

          if(--nready <= 0)
          {
              continue;
          }
      }

      for(int i=0;i<MAX_FD_NUM;++i)
      {
        if(pollfdArry[i].fd < 0)
        {
            continue;
        }

        if(pollfdarr[i].revents & (POLLIN |POLLERR))
        {

          int n = recv(pollfdArry[i].fd,buf,MAXLEN,0);

          if(n < 0)
          {
              if(ECONNRESET == errno)
              {
                  close(pollfdArry[i].fd);
                  pollfdArry[i].fd = -1;
                  cur_fd_num--;
              }
              else
              {
                  perror("recv");
              }
          }
          else if(n == 0)
          {
              close(pollfdArry[i].fd);
              pollfdArry[i].fd = -1;
              cur_fd_num--;
          }
          else
          {
              printf("recived:%s\n",buf);
          }

      }

      if(--nready)
      {
          break;
      }
    }

    //关闭连接，实际只是socket的引用-1,必须引用为0才会真正关闭
    for(int i=0;i<MAX_FD_NUM;++i)
    {
      if(pollfdArry[i].fd != -1)
      {
        close(pollfdArry[i].fd);
      }
    }

    return 0;

 }


















}
