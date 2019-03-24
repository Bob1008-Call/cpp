#include <stdio.h>
#include <stdlib.h>

typedef int QueuedataType;

typedef struct qlNode
{
  QueuedataType data;
  struct qlNode *next;
}QueueNode,*pQueueNode;

typedef struct
{
  pQueueNode front;
  pQueueNode rear;
  int count;
}LinkQueue,*pLinkQueue;

pQueueNode LinkQueueCreatNode(QueuedataType data)
{
  pQueueNode s = (pQueueNode)malloc(sizeof(QueueNode));
  if(NULL == s)
  {
    perror("LinkQueueCreatNode malloc");
    return NULL;
  }
  s->data = data;
  s->next = NULL;
  return s;
}
