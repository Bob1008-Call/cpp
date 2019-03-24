#include <stdio.h>
#include <malloc.h>
typedef int DataType;

typedef struct ListNode
{
  int _value;
  struct ListNode* _next;
}ListNode;

ListNode* Merge(ListNode* pHead1,ListNode* pHead2)
{
  if(NULL == pHead1)
    return pHead2;
  else if(NULL == pHead2)
    return pHead1;

  ListNode* newList = NULL;
  if(pHead1->_value < pHead2->_value)
  {
    newList = pHead1;
    newList->_next = Merge(pHead1->_next,pHead2);
  }
  else 
  {
    newList = pHead2;
    newList->_next = Merge(pHead1,pHead2->_next);
  }
  return newList;
}

ListNode* BuyNode(int data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->_next = NULL;
	node->_value = data;
	return node;
}

int main()
{
	ListNode* n1 = BuyNode(1);
	n1->_next = BuyNode(3);
	n1->_next->_next = BuyNode(5);
	ListNode* n2 = BuyNode(2);
	n2->_next = BuyNode(4);
	n2->_next->_next = BuyNode(6);
	ListNode* newList = Merge(n1, n2);
	while (newList != NULL)
	{
		printf("%d ", newList->_value);
		newList = newList->_next;
	}
	return 0;
}


