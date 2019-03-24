#include <stdio.h>
typedef struct BTNode
{
  int _value;
  struct BTNode* _left;
  struct BTNode* _right;
}BTNode;
template<class T>
void Swap(T& x,T& y)
{
  T temp = x;
  x = y;
  y = temp;
}

void Mirror(BTNode* root)
{
  if(NULL == root)
    return;
  if(NULL == root->_left && NULL ==root->_right)
    return;
  Swap(root->_left,root->_right);
  Mirror(root->_left);
  Mirror(root->_right);
}
