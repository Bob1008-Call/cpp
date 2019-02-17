#include <stack>
#include <queue>
#include <malloc.h>
#include <assert.h>
using namespace std;

typedef char BDataType;
typedef struct BTNode
{
  struct BTNode* LChild;
  struct BTNode* RChild;
  BDataType data;
}BTNode;

BTNode* BuyNode(BDataType data)
{
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  if(newNode != NULL)
  {
    newNode->data = data;
    newNode->LChild = NULL;
    newNode->RChild = NULL;
  }

  return newNode;
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
    printf("%c ",cur->data);
    if(cur->LChild)
      q.push(cur->LChild);

    if(cur->RChild)
      q.push(cur->RChild);

    q.pop();
  }
}

void CreateBinTree(BTNode** root,char* str,int size,int* index)
{
  assert(root);
  assert(index);
  if(*index<size && str[*index] != '#')
  {
    *root = BuyNode(str[*index]);
    ++(*index);
    CreateBinTree(&(*root)->LChild,str,size,index);
    ++(*index);
    CreateBinTree(&(*root)->RChild,str,size,index);
  }
}

int IsCompleteBinTree(BTNode* root)
{
  if(NULL == root)
    return 0;

  int flag = 0;
  queue<BTNode*> q;
  q.push(root);
  while(!q.empty())
  {
    BTNode* cur = q.front();
    if(flag == 1)
    {
      if(cur->LChild || cur->RChild)
        return 0;
    }
    else 
    {
      if(cur->LChild && cur->RChild)
      {
        q.push(cur->LChild);
        q.push(cur->RChild);
      }
      else if(cur->LChild)
      {
        q.push(cur->LChild);
        flag = 1;
      }
      else if(cur->RChild)
      {
        return 0;
      }
      else 
      {
        flag = 1;
      }
    }
    q.pop();
  }
  return 1;
}

void PreOrderNor_1(BTNode* root)
{
  if(NULL == root)
  {
    return;
  }
  stack<BTNode*> s;
  s.push(root);
  while(!s.empty())
  {
    BTNode* cur = s.top();
    printf("%c ",cur->data);
    s.pop();
    if(cur->RChild)
      s.push(cur->RChild);
    if(cur->LChild)
      s.push(cur->LChild);
  }
}

void PreOrderNor_2(BTNode* root)
{
  if(NULL == root)
  {
    return;
  }
  stack<BTNode*> s;
  s.push(root);
  while(!s.empty())
  {
    BTNode* cur = s.top();
    s.pop();
    while(cur)
    {
      printf("%c ",cur->data);
      if(cur->RChild)
        s.push(cur->RChild);

      cur = cur->LChild;
    }
  }
}

void InOrder(BTNode* root)
{
  if(NULL == root)
    return;

  stack<BTNode*> s;
  BTNode* cur = root;
  while(cur || !s.empty())
  {
    while(cur)
    {
      s.push(cur);
      cur = cur->LChild;
    }
    cur = s.top();
    printf("%c ",cur->data);
    s.pop();
    cur = cur->RChild;
  }
}

void PostOrderNor(BTNode* root)
{
  if(NULL == root)
    return;

  stack<BTNode*> s;
  BTNode* visitNode = NULL;
  BTNode* cur = root;
  while(cur || !s.empty())
  {
    while(cur)
    {
      s.push(cur);
      cur = cur->LChild;
    }
    cur = s.top();
    if(NULL == cur->RChild || visitNode == cur->RChild)
    {
      printf("%c ",cur->data);
      visitNode = cur;
      s.pop();
      cur = NULL;
    }
    else 
    {
      cur = cur->RChild;
    }
  }
}

int main()
{
  char str[]= "ABD##E##CF###";
  int size = sizeof(str)/sizeof(str[0]);
  int index = 0;
  BTNode* root = NULL;
  CreateBinTree(&root,str,size,&index);
  //printf("%d", IsCompleteBinTree(root));
  //InOrder(root);
  //PostOrderNor(root);
  PreOrderNor_2(root);
  //LevelOrder(root);  
  return 0;
}
