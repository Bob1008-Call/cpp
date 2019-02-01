#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;


typedef struct ListNode
{
  int data;
  struct ListNode *next;
}ListNode;

ListNode *CreatNode(DataType data)
{
  ListNode* Node = (ListNode*)malloc(sizeof(ListNode));
  assert(Node);
  Node->next = NULL;
  Node->data = data;
  return Node;
}

void PrintList(ListNode *Node)
{
  if(Node == NULL)
  {
    return;
  }
  ListNode *cur = Node;
  while(cur)
  {
    printf("%d ",cur->data);
    cur = cur->next;
  }
}

void PushBack(ListNode **Node,DataType data)
{
  ListNode *newNode = CreatNode(data);
  if(*Node == NULL)
  {
    *Node = newNode;
    return;
  }
  ListNode *cur = *Node;
  while(cur->next != NULL)
  {
    cur = cur->next;
  }
  cur->next = newNode;
}

void DelNotTailNode(ListNode *pos)
{
  ListNode *pDel = NULL;
  assert(pos);
  if(pos->next == NULL)
  {
    return;
  }
  else
  {
    int temp = 0;
    temp = pos->data;
    pos->data = pos->next->data;
    pos->next->data = temp;
    pDel = pos->next;
    pos->next = pos->next->next;
    free(pDel);
    pDel = NULL;
  }
}

ListNode* CombineList(ListNode* list1,ListNode* list2)
{
  if(list1&&list2)
  {
    ListNode* cur = NULL;
    ListNode* list = NULL;
    if(list1->data <= list2->data)
    {
      list = list1;
      list1 = list1->next;
    }
    else
    {
      list = list2;
      list2 = list2->next;
    }
    cur = list;
    while(list1 && list2)
    {
      if(list1->data <= list2->data)
      {
        cur->next = list1;
        cur = cur->next;
        list1 = list1->next;
      }
      else
      {
        cur->next = list2;
        cur = cur->next;
        list2 = list2->next;
      }
    }
    if(list1)
    {
      cur->next = list1;
    }
    if(list2)
    {
      cur->next = list2;
    }
    return list;
  }
  else if((list1 == NULL)&&(list2 != NULL))
  {
    return list2;
  }
  else if((list1 != NULL)&&(list2 ==NULL))
  {
    return list1;
  }
  else
  {
    return NULL;
  }
}

void InsertNoHead(ListNode* pos,DataType data)
{
  assert(pos);
  ListNode *tmp = CreatNode(pos->data);
  tmp->next = pos->next;
  pos->next = tmp;
  pos->data = data;
}

void PrintListFromTail2Head(ListNode *Node)
{
  if(Node)
  {
    PrintListFromTail2Head(Node->next);
    printf("%d ",Node->data);
  }
}

ListNode* Joseph(ListNode *Node,DataType k)
{
  ListNode *tail = Node;
  while(tail->next != NULL)
  {
    tail = tail->next;
  }
  tail->next = Node;
  ListNode* cur = Node;
  ListNode* pre = NULL;
  while(cur->next != cur)
  {
    k = 3;
    while(--k)
    {
      pre = cur;
      cur = cur->next;
    }
    pre->next = cur->next;
    free(cur);
    cur = pre->next;
  }
  return cur;
}

void RemoveLastK(ListNode** Node,int K)
{
  assert(*Node);
  if((*Node)->next == NULL)
  {
    return;
  }
  ListNode* fast = *Node;
  ListNode* slow = *Node;
  ListNode* cur = NULL;
  while(--K)
  {
    fast = fast->next;
  }
  while(fast->next != NULL)
  {
    cur = slow;
    slow = slow->next;
    fast = fast->next;
  }
  cur->next = slow->next;
  free(slow);
  slow = NULL;

}

void Reverse(ListNode **Node)
{
  if((*Node == NULL)||((*Node)->next ==NULL))
  {
    return;
  }
  ListNode* tmp = NULL;
  ListNode* cur = *Node;
  ListNode* newlist = NULL;
  while(cur)
  {
    tmp = cur;
    cur = cur->next;
    tmp->next = newlist;
    newlist = tmp;
  }
  *Node = newlist;
}

ListNode* FindMiddleNode(ListNode *List)
{
  if((List == NULL)||(List->next == NULL))
  {
    return NULL;
  }
  else if(List->next->next == NULL)
  {
    return List->next;
  }
  else
  {
    ListNode* fast = List;
    ListNode* slow = List;
    while((fast->next) != NULL)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }
}

ListNode* BubbleSort1(ListNode* Node)
{
  if((Node == NULL)||(Node->next == NULL))
  {
    return NULL;
  }
  ListNode *tail = NULL;
  while(tail != Node)
  {
    int flag = 0;
    ListNode *cur = Node;
    ListNode *next = cur->next;
    while(next != tail)
    {
      if(cur->data > next->data )
      {
        flag = 1;
        DataType tmp = cur->data;
        cur->data = next->data;
        next->data = tmp;
      }
      cur = cur->next;
      next = next->next;
      if(!flag)
        continue;
    }
    tail = cur;
  }
  return Node;
}
void BubbleSort(ListNode** Node)
{
  if((*Node == NULL)||((*Node)->next == NULL))
  {
    return;
  }
  ListNode *tail = NULL;
  while(tail != *Node)
  {
    ListNode *cur = *Node;
    ListNode *next = cur->next;
    while(next != tail)
    {
      if(cur->data > next->data )
      {
        DataType tmp = cur->data;
        cur->data = next->data;
        next->data = tmp;
      }
      cur = cur->next;
      next = next->next;
    }
    tail = cur;
  }
}

ListNode* EntryNodeLoop(ListNode *List)
{
  if(NULL == List)
  {
    return NULL;
  }
  ListNode* list1 = List;
  ListNode* list2 = List;
  DataType fastlength = 0;
  DataType slowlength = 0;

  ListNode* fast = List;
  ListNode* slow = List;
  while(1)//判断是否带环
  {
    if((NULL == fast)||(NULL == fast->next))
    {
      return NULL;
    }
    else
    {
      fast = fast->next->next;
      slow = slow->next;
    }
    if(fast == slow)
      break;
  }
  while(1)//求环的长度
  {
    fast = fast->next->next;
    fastlength += 2;

    slow = slow->next;
    slowlength += 1;

    if(fast == slow)
      break;
  }
  int length = 0;
  length = fastlength-slowlength;
  while(1)//求入口
  {
    int i = 0;
    for(;i<length;i++)
      list1 = list1->next;
    if(list1 == list2)
      return list1;

    while(1)
    {
      list1 = list1->next;
      list2 = list2->next;
    if(list1 == list2)
      return list1;
    }
  }
}

ListNode* EntryNodeLoop1(ListNode* List)
{
  if((List == NULL)||(List->next == NULL))
  { 
    return NULL;
  }
  ListNode* fast = List;
  ListNode* slow = List;
  while(fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
    if(slow == fast)
      break;
  }
  ListNode* cur = fast->next;
  int count = 1;
  while(cur != fast)
  {
    cur = cur->next;
    count++;
  }
  printf("%d",fast->data);
  while(List != fast)
  {
    fast = fast->next;
    List = List->next;
  }
  return List;
}
void BuildCircle(ListNode* List)
{
  if((NULL == List)||(NULL == List->next))
  {
    return;
  }
  ListNode* cur = List;
  ListNode* cur1 = cur;

  int i = 0;
  while(cur1->next != NULL)
  {
    cur1 = cur1->next;
  }
  for(;i<2;i++)
  {
    cur = cur->next;
  }
  cur1->next = cur;
}
void PrintFromRear2Head(ListNode* List)
{
  if(NULL == List)
  {
    return;
  }
  else
  {
    PrintFromRear2Head(List->next);
    printf("%d",List->data);
  }
}

int main()
{
  ListNode *first1 = NULL;
  PushBack(&first1,1);
  PushBack(&first1,4);
  PushBack(&first1,3);
  PushBack(&first1,5);
  PushBack(&first1,2);
  PushBack(&first1,6);
  PushBack(&first1,9);
  BuildCircle(first1);
  ListNode* Node = EntryNodeLoop1(first1);
  printf("%d",Node->data);

  //ListNode *Node = Joseph(first1,3);
  //printf("%d",Node->data);
  // printf("%d\n",FindMiddleNode(first1)->data);

  return 0;
}
