#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int startup(int _port,const char* _ip)
{
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
  {
    perror("socket error");
    exit(1);
  }

  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(_port);
  local.sin_addr.s_addr = inet_addr(_ip);

  int err_log = bind(sockfd,(struct sockaddr*)&local,sizeof(sockaddr_in));
  if(err_log < 0)
  {
    perror("bind");
    exit(2);
  }

  if(listen(sockfd,5) < 0)
  {
    perror("listen");
    exit(3);
  }
  return sockfd;
}

int main(int argc,char** argv)
{
  if(argc != 3)
  {
    printf("Usage:%s[local_ip][local_port]\n",argv[0]);
    return 1;
  }
  int listen_sockfd = startup(atoi(argv[2]),argv[1]);
  
  struct sockaddr_in remote;
  socklen_t len = sizeof(struct sockaddr_in);
  while(1)
  {
    int sockfd = accept(listen_sockfd,(struct sockaddr*)&remote,&len);
    if(sockfd < 0)
    {
      perror("accept");
      continue;
    }
    printf("get a client,ip:%s,port:%d\n",inet_ntoa(remote.sin_addr),htons(remote.sin_port));

    char buf[512];
    while(1)
    {
      ssize_t _s = read(sockfd,buf,sizeof(buf)-1);
      if(_s > 0)
      {
        buf[_s] = 0;
        printf("client:%s\n",buf);
      }
      else 
      {
        printf("client is quit!\n");
        break;
      }
    }
  }
  return 0;
}

