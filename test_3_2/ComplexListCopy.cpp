#include <stdlib.h>
#include <stdio.h>

typedef struct RandomListNode
{
  int _val;
  struct RandomListNode* _next;
  struct RandomListNode* _random;
}RandomListNode;

class solution
{
  public:
    
    RandomListNode* BuyNode(int val)
    {
      RandomListNode* newNode = (RandomListNode*)malloc(sizeof(RandomListNode));
      newNode->_next = NULL;
      newNode->_random = NULL;
      newNode->_val = val;
      return newNode;
    }

    RandomListNode* Clone(RandomListNode* pHead)
    {
      if(NULL == pHead)
        return NULL;
      RandomListNode* pCur = pHead;
      while(pCur)
      {
        RandomListNode* Node = BuyNode(pCur->_val);
        Node->_next = pCur->_next;
        pCur->_next = Node;
        pCur = Node->_next;
      }
      pCur = pHead;
      while(pCur)
      {
        RandomListNode* Node = pCur->_next;
        if(pCur->_random)
        {
          Node->_random = pCur->_random->_next;
        }
        pCur = Node->_next;
      }
      RandomListNode* pCloneHead = pHead->_next;
      RandomListNode* tmp;
      pCur = pHead;
      while(pCur->_next)
      {
        tmp = pCur->_next;
        pCur->_next = tmp->_next;
        pCur = tmp;
      }
      return pCloneHead;
    }
};

//////////////////////////// 
//第二种写法
//////////////////////////// 
int main()
{
  solution s;
  RandomListNode* node1 = s.BuyNode(1);
  RandomListNode* node2 = s.BuyNode(2);
  RandomListNode* node3 = s.BuyNode(3);
  
  node1->_next = node2;
  node1->_random = node3;
  node2->_next = node3;
  node2->_random = node2;
  node3->_next = NULL;
  node3->_random = node1;
  RandomListNode* newNode = s.Clone(node1);
  while(newNode)
  {
    printf("%d ",newNode->_val);
    newNode = newNode->_next;
  }
  return 0;
}
