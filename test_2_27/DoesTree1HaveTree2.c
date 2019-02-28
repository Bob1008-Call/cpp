#include <stdio.h>

typedef struct BTNode 
{
  int _value;
  struct BTNode* _left;
  struct BTNode* _right;
}BTNode;

bool DoesTree1HaveTree2(BTNode* root1,BTNode* root2)
{
  if(root2 == NULL)
    return true;
  if(root1 == NULL)
    return false;
  if(root1->_value != root2->_value)
    return false;
  return DoesTree1HaveTree2(root1->_left,root2->_left) && DoesTree1HaveTree2(root1->_right,root2->_right);
}

bool HasSubTree(BTNode* root1,BTNode* root2)
{
  bool result = false;
  if(root1 != NULL && root2 != NULL)
    result = DoesTree1HaveTree2(root1,root2);
  if(!result)
    result = DoesTree1HaveTree2(root1->_left,root2);
  if(!result)
    result = DoesTree1HaveTree2(root1->_right,root2);

  return result;
}


