#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   / 
  returr 0;
   r("bind error");
               return -1;
                       
}
        //3.接收数据
        //        //ssize_t recvfrom(int sockfd,void *buf,size_t len,int flags,struct sockaddr* src_addr,socklen_t *addrlen);
        //                //sockfd:套接字描述符--确定从哪里获取数据
        //                        //buf：用于接收数据
        //                                //len：接收的数据长度
        //                                        //flags：默认赋0--阻塞接收（没接受就一直等待）
        //                                                      //src_addr:数据从哪里，对端地址信息
        //                                                              //addrlen：地址信息长度（输入输出复合参数）
        //                                                                      //返回值：实际接受的数据长度  失败：-1
        //                                                                              char buff[1024] = {0};
        //                                                                                      struct sockaddr_in cliaddr;
        //                                                                                              recvfrom(sockfd,buff,1023,0(struct sockaddr*)&cli_addr,&len);
        //                                                                                                      printf("client say:%s\b",buff);
        //                                                                                                              //4.发送数据
        //                                                                                                                      //memset(buff.0x00,1024);
        //                                                                                                                              scanf("%s",buff);
        //                                                                                                                                      //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
        //                                                                                                                                                            const struct sockaddr *dest_addr, socklen_t addrlen);
        //                                                                                                                                                                    //dest_addr:目的端地址信息
        //                                                                                                                                                                            //addrlen:地址信息长度
        //                                                                                                                                                                                    ``
