#include <stdlib.h>
typedef struct RandomListNode
{
  int _val;
  struct RandomListNode* _next;
  struct RandomListNode* _random;
};

class solution
{
  public:

    RandomListNode* Clone(RandomListNode* pHead)
    {
      if(nullptr == pHead)
        return NULL;
      RandomListNode* pCur = pHead;
      while(pCur)
      {
        RandomListNode* Node = pCur->_next;
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
