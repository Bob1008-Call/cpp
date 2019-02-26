#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
  key_t key;
  key = ftok(".",2016);
  if(key == -1)
  {
    perror("ftok error");
  }
  
  system("ipcs -s");
  int semid;
  semid = semget(key,1,IPC_CREAT|0666);
  if(semid == -1)
  {
    perror("semget error");
  }

  system("ipcs -s");

  semctl(semid,0,IPC_RMID);

  system("ipcs -s");
  return 0;
}
