#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSZ 512
int main()
{
  key_t key;
  int shmid;
  //创建key值
  key = ftok("/",2019);
  if(key == -1)
  {
    perror("ftok error");
  }

  //创建共享内存
  shmid = shmget(key,BUFSZ,IPC_CREAT|0666);
  if(shmid<0)
  {
    perror("shmget error");
    exit(-1);
  }

  //映射
  char* shmadd =(char*) shmat(shmid,NULL,0);
  if(shmadd <(char*)0)
  {
    perror("shmat error");
  }

  //拷贝数据到共享内存区
  printf("strcpy");
  bzero(shmadd,BUFSZ);
  strcpy(shmadd,"hello world");
  return 0;
}
