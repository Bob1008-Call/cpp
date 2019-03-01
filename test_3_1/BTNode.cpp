#include <queue>
#include <malloc.h>
using namespace std;
typedef struct BTNode
{
  char data;
  struct BTNode* _left;
  struct BTNode* _right;
}BTNode;

BTNode* BuyNode(char data)
{
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  newNode->data = data;
  newNode->_left = NULL;
  newNode->_right = NULL;
  return newNode;
}

void CreatBinTree(BTNode** root,char* str,int size,int* index)
{
  if(*index<size && str[*index]!='#')
  {
    *root = BuyNode(str[*index]);
    ++(*index);
    CreatBinTree(&(*root)->_left,str,size,index);
    ++(*index);
    CreatBinTree(&(*root)->_right,str,size,index);
  }
}

void PrintLevel(BTNode* root)
{
  if(NULL == root)
    return;

  queue<BTNode*> q;
  q.push(root);
  while(!q.empty())
  {
    BTNode* cur = q.front();
    printf("%c ",cur->data);
    if(cur->_left)
      q.push(cur->_left);
    if(cur->_right)
      q.push(cur->_right);
    q.pop();
  }
}

int main()
{
  char str[] = "AB##C##";
  int size = sizeof(str)/sizeof(str[0]);
  BTNode*root;
  int index = 0;
  CreatBinTree(&root,str,size,&index);
  PrintLevel(root);
  return 0;
}
