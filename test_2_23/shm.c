#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFSZ 1024

int main()
{
  int shmid;
  key_t key;

  key = ftok("./",2019);
  if(key == -1)
  {
    perror("ftok error");
  }
  
  shmid = shmget(key,BUFSZ,IPC_CREAT|0666);
  if(shmid<0)
  {
    perror("shmget error");
    exit(-1);
  }
  return 0;
}

