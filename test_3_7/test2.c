#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
  pid_t pid;
  pid = fork();
  if(pid<0)
  {
    perror("fork error");
    exit(0);
  }
  else if(pid == 0)
  {
    //子进程
    int i;
    for(i = 0;i<5;++i)
    {
      printf("this is son process\n");
      sleep(1);
    }

    _exit(2);
  }
  else 
  {
    //父进程
    int status = 0;
    wait(&status);
    if(WIFEXITED(status) != 0)
    {
      printf("son process return %d\n",WEXITSTATUS(status));
    }
    printf("this is father process\n");
  }
  return 0;
}
