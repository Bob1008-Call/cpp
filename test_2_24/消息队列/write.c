#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
typedef struct MSG
{
  long mType;
  char mData[1024];
}MSG;

int main()
{
  MSG msg;
  key_t key;
  int msqid;
  key = ftok(".",2019);
  if(key == -1)
  {
    perror("ftok error");
  }
  msqid = msgget(key,IPC_CREAT|0666);
  if(msqid<0)
  {
    perror("msget error");
  }
  msg.mType = 10;
  strcpy(msg.mData,"hello world");
  msgsnd(msqid,&msg,sizeof(MSG)-sizeof(long),0);
  return 0;
}
