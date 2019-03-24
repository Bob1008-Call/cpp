#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
  fd = open("myfifo2",O_RDWR);
  if(fd<0)
  {
    perror("open error");
  }
  printf("after open\n");
  while(1)
  {
    char rec[1024] = {0};
    read(fd,rec,sizeof(rec));
    printf("read from myfifo2 buf = %s\n",rec);
    sleep(1);
  }
  return 0;
}
