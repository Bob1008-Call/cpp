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
  int ret;
  //创建key值
  
  key = ftok(".",2019);
  if(key == -1)
  {
    perror("ftok error");
  }
  
  //查看共享内存
  system("ipcs -m");

  //打开共享内存
  shmid = shmget(key,BUFSZ,IPC_CREAT|0666);
  if(shmid<0)
  {
    perror("shmget error");
    exit(1);
  }

  //映射
  char* shmadd =(char*)shmat(shmid,NULL,0);

  //读共享内存区数据
  printf("%s\n",shmadd);

  //分离共享内存和当前进程
  ret = shmdt(shmadd);
  if(ret<0)
  {
    perror("delete false");
  }
  else 
  {
    printf("delete success");
  }

  //删除共享内存
  shmctl(shmid,IPC_RMID,NULL);

  //查看共享内存
  system("ipcs -m");
  return 0;
}
