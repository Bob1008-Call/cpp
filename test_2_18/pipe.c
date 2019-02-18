#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  int fd[2];
  pid_t pid;

  if(pipe(fd)<0)
  {
    perror("pipe error");
  }
  pid = fork();
  if(pid<0)
  {
    perror("fork error");
  }
  else if(pid == 0)//子进程
  {
    char buf[] = "I am a dog";
    write(fd[1],buf,strlen(buf));
  }
  else if(pid>0)//父进程
  {
    wait(NULL);
    char str[50] = {0};
    read(fd[0],str,sizeof(str));
    printf("str = %s\n",str);
  }
  return 0;
}
