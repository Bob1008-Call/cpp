#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc,char** argv)
{

  if(argc != 3)//更改服务器的ip地址
  {
    printf("Usage:%s [ip][port]\n",argv[0]);
    return 0;
  }

  int sockfd;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
  {
    perror("socket error");
    return -1;
  }
  
  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET; //IPv4
  server_addr.sin_port = htons(atoi(argv[2]));//端口
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  //inet_pton(AF_INET,server_ip,&server_addr.sin_addr);
  
  int err_log = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  if(err_log != 0)
  {
    perror("connect error");
    close(sockfd);
    exit(-1);
  }
  
  char buf[512];
  while(1)
  {
    printf("send###");
    fflush(stdout);
    ssize_t _s = read(0,buf,sizeof(buf)-1);
    buf[_s] = 0;
    write(sockfd,buf,_s);
  }
  close(sockfd);
  return 0;
}
