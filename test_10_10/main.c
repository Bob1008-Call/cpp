#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  pid_t ret = fork();
  if(ret > 0)
  {
    printf("father = %d\n",getpid());
    int status;
    wait(&status);
    printf("status = %d\n",status);
    while(1)
    {
      sleep(1);
    }
  }
  else if(ret == 0)
  {
    printf("child = %d\n",getpid());
    exit(1);
  }
  else
  {
    perror("fork");
  }
  return 0;
}
