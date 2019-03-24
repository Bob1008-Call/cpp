#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
  int fd[2] = {0};
  pid_t pid;
  if(pipe(fd)<0)
  {
    printf("pipe error");
  }
  pid = fork();
  if(pid<0)
  {
    printf("fork error");
  }
  else if(pid == 0)//子进程
  {
    
  }
  else 
  {
    fcntl(fd[0],F_SETFL,O_NONBLOCK);
    char str[50];
    printf("before read\n");
    read(fd[0],str,sizeof(str));
    printf("after read\n");
    printf("str = %s\n",str);
  }
  return 0;
}
