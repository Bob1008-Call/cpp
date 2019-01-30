#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main()
{
  int fd[2] = {0};
  int ret = pipe(fd);
  if(ret<0)
  {
    perror("pipe");
    return 1;
  }
  const char* msg = "hehe";
  write(fd[1],msg,strlen(msg));

  char buf[1024] = {0};
  read(fd[0],buf,sizeof(buf)-1);

  printf("buf = %s\n",buf);
  return 0;
}
