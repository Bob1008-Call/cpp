#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd;
  int ret;
  ret = mkfifo("myfifo2",0666);
  if(ret == -1)
  {
    perror("mkfifo error");
  }

  printf("before open\n");
  fd = open("myfifo2",O_WRONLY);
  if(fd<0)
  {
    perror("open error");
  }
  printf("after open\n");
  char send[1024] = "hello world";
  write(fd,send,strlen(send));
  while(1);
  return 0;
}

