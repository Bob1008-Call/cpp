#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  close(1);
  int fd = open("file",O_WRONLY|O_CREAT,0777);
  if(fd<0)
  {
    perror("open");
  }

  printf("fd: %d\n",fd);

  close(fd);
  return 0;
}
