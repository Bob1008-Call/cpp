#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main()
{
  key_t key;
  int msgid;
  key = ftok(".",2019);
  if(key == -1)
  {
    perror("ftok error");
  }
  msgid = msgget(key,IPC_CREAT);
  if(msgid<0)
  {
    perror("msgget error");
  }
  return 0;
}
