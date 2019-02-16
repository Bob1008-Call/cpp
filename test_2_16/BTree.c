#include <assert.h>
#include <malloc.h>
typedef char BDataType;
typedef struct BTNode
{
  BDataType data;
  struct BTNode* LChild;
  struct BTNode* RChild;
}BTNode;

BTNode* BuyBTNode(BDataType data)
{
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  if(NULL == newNode)
  {
    assert(0);
    return NULL;
  }
  newNode->RChild = NULL;
  newNode->LChild = NULL;
  newNode->data = data;
  return newNode;
}

void CreateBinTree(BTNode** root,char* str,int size,int* index)
{
  assert(root);
  assert(index);
  if(*index<size && str[*index] != '#')
  {
    *root = BuyBTNode(str[*index]);
    ++(*index);
    CreateBinTree(&(*root)->LChild,str,size,index);
    ++(*index);
    CreateBinTree(&(*root)->RChild,str,size,index);
  }
}

void PreOrder(BTNode* root)
{
  if(root)
  {
    printf("%c ",root->data);
    PreOrder(root->LChild);
    PreOrder(root->RChild);
  }
}

void InOrder(BTNode* root)
{
  if(root)
  {
    InOrder(root->LChild);
    printf("%c ",root->data);
    InOrder(root->RChild);
  }
}

void PostOrder(BTNode* root)
{
  if(root)
  {
    PostOrder(root->LChild);
    PostOrder(root->RChild);
    printf("%c ",root->data);
  }
}

BTNode* rootCopy(BTNode* root)
{
  BTNode* newRoot = NULL;
  if(root)
  {
    newRoot = BuyBTNode(root->data);
    if(root->LChild)
      newRoot->LChild = rootCopy(root->LChild);
    if(root->RChild)
      newRoot->RChild = rootCopy(root->RChild);
  }
  return newRoot;
}

int GetBTNodeCount(BTNode* root)
{
  if(NULL == root)
  {
    return 0;
  }
  return GetBTNodeCount(root->LChild)+GetBTNodeCount(root->RChild)+1;
}

int GetLeafNodeCount(BTNode* root)
{
  if(NULL == root)
    return 0;
  if(NULL == root->LChild && NULL == root->RChild)
    return 1;

  return GetLeafNodeCount(root->LChild)+GetLeafNodeCount(root->RChild);
}

int GetBinTreeHeight(BTNode* root)
{
  if(NULL == root)
  {
    return 0;
  }
  int leftHeight = 0;
  int rightHeight = 0;
  leftHeight = GetBinTreeHeight(root->LChild);
  rightHeight = GetBinTreeHeight(root->RChild);
  return leftHeight>rightHeight?leftHeight:rightHeight;
}

void DestroyBinTree(BTNode** root)
{
  assert(root);
  if(NULL == *root)
  {
    return;
  }
  DestroyBinTree(&(*root)->LChild);
  DestroyBinTree(&(*root)->RChild);
  free(*root);
  *root = NULL;
}

int Max_distance(BTNode* root,int* m)
{
  if(NULL == root)
  {
    return 0;
  }
  int *max = m;
  int leftlength = Max_distance(root->LChild,max);
  int rightlength = Max_distance(root->RChild,max);
  if((leftlength+rightlength)>*max)
  {
    *max = leftlength+rightlength;
  }
  
  return leftlength>rightlength?leftlength+1:rightlength+1;
}

int MaxDistance(BTNode* root)
{
  if(NULL == root)
  {
    return 0;
  }
  int max = 0;
  Max_distance(root,&max);
  return max;
}

int IsBTNodeInBInTree(BTNode* root,BTNode* node)
{
  if(NULL == root || NULL == node)
  {
    return 0;
  }
  if(node == root)
  {
    return 1;
  }
  if(IsBTNodeInBInTree(root->LChild,node))
    return 1;

  return IsBTNodeInBInTree(root->RChild,node);
}

BTNode* GetBTNodeParent(BTNode* root,BTNode* node)
{
  if(NULL == root || NULL == node)
  {
    return 0;
  }

  if(root->LChild == node || root->RChild == node)
  {
    return root;
  }

  BTNode* parent = NULL;
  if(parent = GetBTNodeParent(root->LChild,node))
    return parent;

  return GetBTNodeParent(root->RChild,node);
}


void MirrorBinTree(BTNode* root)
{
  if(root)
  {
    Swap(&root->LChild,&root->RChild);
    MirrorBinTree(root->LChild);
    MirrorBinTree(root->RChild);
  }
}

  
