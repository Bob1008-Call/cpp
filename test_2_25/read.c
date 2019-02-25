#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd;
  int ret;
  ret = mkfifo("myfifo1",0666);
  if(ret == -1)
  {
    perror("mkfifo error");
  }

  printf("before open\n");
  fd = open("myfifo1",O_RDWR);
  if(fd<0)
  {
    perror("open error");
  }
  printf("after open\n");
  return 0;
}
