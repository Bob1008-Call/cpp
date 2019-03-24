#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int QDataType;

typedef struct QListNode
{
  struct QListNode* next;
  QDataType data;
}QListNode;

typedef struct Queue
{
  QListNode *front;
  QListNode *back;
  int sz;
}Queue;

typedef struct StackBy2Queue
{
  Queue q1;
  Queue q2;
}StackBy2Queue;

QListNode* BuyNewNode(QDataType data)
{
  QListNode* NewNode = (QListNode*)malloc(sizeof(QListNode));
  if(NULL == NewNode)
  {
    assert(0);
    return NULL;
  }
  NewNode->data = data;
  NewNode->next = NULL;
  return NewNode;
}

void QueueInit(Queue* q)
{
  assert(q);
  q->front = q->back = BuyNewNode(0);
  q->sz = 0;
}
void QueuePush(Queue* q,QDataType data)
{
  assert(q);
  q->back->next = BuyNewNode(data);
  q->back = q->back->next;
  q->sz++;
}
void QueuePop(Queue* q)
{
  assert(q);
  if(q->front != q->back)
  {
    QListNode* pDel = q->front->next;
    q->front->next = pDel->next;
    q->sz--;
    free(pDel);
    pDel = NULL;
  }
}

QDataType QueueFront(Queue* q)
{
  assert(q);
  return q->front->next->data;
}
QDataType QueueBack(Queue* q)
{
  assert(q);
  return q->back->data;
}
int QueueSize(Queue* q)
{
  return q->sz;
}
int QueueEmpty(Queue* q)
{
  assert(q);
  return 0 == QueueSize(q);
}
/////////////////////////////////////////////////////////
//两个队列实现一个栈
/////////////////////////////////////////////////////////
void StackBy2QueueInit(StackBy2Queue *s)
{
  assert(s);
  QueueInit(&s->q1);
  QueueInit(&s->q2);
}

void StackBy2QueuePush(StackBy2Queue *s,QDataType data)
{
  assert(s);
  if(QueueSize(&s->q1))
  {
    QueuePush(&s->q1,data);
  }
  else
  {
    QueuePush(&s->q2,data);
  }
}

void StackBy2QueuePop(StackBy2Queue *s)
{
  assert(s);
  if(QueueSize(&s->q1))
  {
    while(QueueSize(&s->q1)>1)
    {
      QueuePush(&s->q2,QueueFront(&s->q1));
      QueuePop(&s->q1);
    }
    QueuePop(&s->q1);
  }
  else
  {
    while(QueueSize(&s->q2)>1)
    {
      QueuePush(&s->q1,QueueFront(&s->q2));
      QueuePop(&s->q2);
    }
    QueuePop(&s->q2);
  }
}

QDataType StackBy2QueueTop(StackBy2Queue* s)
{
  assert(s);
  if(QueueSize(&s->q1))
  {
    return QueueBack(&s->q1);
  }
  else
  {
    return QueueBack(&s->q2);
  }
}


int main()
{
  StackBy2Queue s;
  StackBy2QueueInit(&s);
  StackBy2QueuePush(&s,1);
  StackBy2QueuePush(&s,2);
  StackBy2QueuePush(&s,3);
  int a = StackBy2QueueTop(&s);
  printf("%d",a);
  
  return 0;
}
//int main()
//{
//  Queue q;
//  QueueInit(&q);
//  QueuePush(&q,1);
//  QueuePush(&q,2);
//  QueuePush(&q,3);
//
//  printf("front = %d\n",QueueFront(&q));
//  printf("back = %d\n",QueueBack(&q));
//  printf("size = %d\n",QueueSize(&q));
//
//  QueuePop(&q);
//  QueuePop(&q);
//
//  printf("front = %d\n",QueueFront(&q));
//  printf("back = %d\n",QueueBack(&q));
//  printf("size = %d\n",QueueSize(&q));
//  return 0;
//}
