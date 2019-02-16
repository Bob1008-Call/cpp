#include <assert.h>
#include <iostream>
#include <malloc.h>
#include <queue>
using namespace std;

typedef char BDataType;
typedef struct BTNode
{
  BDataType data;
  struct BTNode* LChild;
  struct BTNode* RChild;
}BTNode;

BTNode* BuyNode(BDataType data)
{
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  newNode->data = data;
  newNode->LChild = newNode->RChild = NULL;
  return newNode;
}

void CreatBinTree(BTNode** root,int size,int* index,char* str)
{
  assert(root);
  assert(index);
  if(*(index)<size && str[*index] != '#')
  {
    *root = BuyNode(str[*index]);
    ++(*index);
    CreatBinTree(&(*root)->LChild,size,index,str);
    ++(*index);
    CreatBinTree(&(*root)->RChild,size,index,str);
  }
}

void LevelOrder(BTNode* root)
{
  if(NULL == root)
    return;

  queue<BTNode*> q;
  q.push(root);
  while(!q.empty())
  {
    BTNode* cur = q.front();
    cout<<cur->data<<endl;
    if(cur->LChild)
      q.push(cur->LChild);
    if(cur->RChild)
      q.push(cur->RChild);

    q.pop();
  }
}

int main()
{
  char str[] = "ABD###CE##F";
  int size = sizeof(str)/sizeof(str[0]);
  int index = 0;
  BTNode* root = NULL;
  CreatBinTree(&root,size,&index,str);
  LevelOrder(root);
  return 0;
}
