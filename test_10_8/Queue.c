//顺序队列
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUESIZE 64
typedef int DataType;
typedef struct sequ
{
  DataType data[QUEUESIZE];
  int front;
  int rear;
}SeQueue,*pSeQueue;

pSeQueue SeQueueCreat()
{
  pSeQueue p = (pSeQueue)malloc(sizeof(SeQueue));
  if(NULL == p)
  {
    perror("SeQueueCreat malloc");
    return NULL;
  }
  memset(p,0,sizeof(SeQueue));
  p->front = -1;
  p->rear = -1;
  return p;
}

//入队
int SeQueueEnter(pSeQueue Q,DataType data)
{
  Q->rear++;
  if(Q->rear > QUEUESIZE)
    return -1;
  Q->data[Q->rear] = data;
  return 0;
}

int SeQueueExit(pSeQueue Q,DataType *data)
{
  if(Q->front == Q->rear)
    return -1;
  Q->front++;
  *data = Q->data[Q->front];
  return 0;
}

int SeQueueFree(pSeQueue Q)
{
  free(Q);
  return 0;
}

int QueuePrint(pSeQueue Q)
{
  int i = 0;
  for(i = Q->front+1;i<=Q->rear;i++)
  {
    printf("%4d",Q->data[i]);
  }
  printf("\r\n");
  return i;
}

int main()
{
  pSeQueue QQ = SeQueueCreat();
  SeQueueEnter(QQ,1);
  SeQueueEnter(QQ,2);
  SeQueueEnter(QQ,3);
  SeQueueEnter(QQ,4);
  QueuePrint(QQ);
  return 0;
}
