#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

typedef struct MSG
{
  long mType;
  char mData[1024];
}MSG;

int main()
{
  key_t key;
  int msqid;
  key = ftok(".",2019);
  MSG msg;
  if(key == -1)
  {
    perror("ftok error");
  }

  memset(&msg,0,sizeof(msg));
  msqid = msgget(key,IPC_CREAT|0666);
  if(msqid<0)
  {
    perror("msgget error");
  }
  msgrcv(msqid,&msg,sizeof(msg)-sizeof(long),(long)10,0);

  printf("%s\n",msg.mData);
  
  msgctl(msqid,IPC_RMID,NULL);
  return 0;
}
