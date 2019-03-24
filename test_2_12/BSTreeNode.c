#include "BSTreeNode.h"

int BSTreeSearch(BSTreeNode* root,KeyType key)
{
  assert(root);
  if(NULL == root)
  {
    return -1;
  }
  if(key == root->key)
  {
    return 0;
  }
  if(key<root->key)
  {
    return BSTreeSearch(root->left,key);
  }

  return BSTreeSearch(root->right,key);
}

int BSTreeSearchNor(BSTreeNode* root,KeyType key)
{
  assert(root);
  BSTreeNode* cur = root;
  if(NULL == root)
  {
    return -1;
  }

  while(cur)
  {
    if(cur->key == key)
    {
      return 0;
    }
    if(cur->key<key)
    {
      cur = cur->left;
    }
    if(cur->key>key)
    {
      cur = cur->right;
    }
  }
  return -1;
}

int BSTreeInsert(BSTreeSearch** root,KeyType key)
{
  if(NULL == root)
  {
    BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
  }
  if(key == (*root)->key)
  {
    return -1;
  }
  if(key<(*root)->key)
  {
    return BSTreeInsert(&(*root)->left,key);
  }

  return BSTreeInsert(&(*root)->right,key);
}

int BSTreeInsertNor(BSTreeNode** root,KeyType key)
{
  assert(root);
  BSTreeNode* cur = *root;
  BSTreeNode* parent = NULL;
  while(cur)
  {
    if(key == cur->key)
    {
      return -1;
    }
    parent = cur;
    if(key<cur->key)
    {
      cur = cur->left;
    }
    if(key>cur->right)
    {
      cur = cur->right;
    }
  }
  BSTreeNode* node = (BSTreeNode)malloc(sizeof(BSTreeNode));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  if(parent == NULL)
  {
    *root == node;
  }
  else if(key<parent->key)
  {
    parent->left = node;
  }
  else 
  {
    parent->right = node;
  }
  return 0;
}

int BSTreeRemove(BSTreeNode** root,KeyType key)
{
  assert(root);
  BSTreeNode* cur = *root;
  BSTreeNode* parent = NULL;
  while(cur)
  {
    if(key == cur->key)
    {
      if(NULL == cur->left)
      {
        if(NULL == parent)
        {
          *root = cur->right;
        }
        else if(cur->key<parent->key)
        {
          parent->left = cur->right;
        }
        else 
        {
          parent->right = cur->right;
        }
      }
      if(NULL == cur->right)
      {
        if(NULL == parent)
        {
          *root = cur->left;
        }
        else if(cur->key>parent->key)
        {
          parent->left = cur->left;
        }
        else 
        {
          parent->right = cur->left;
        }
      }
      else 
      {
        BSTreeNode* del = cur->right;  
        BSTreeNode* delparent = NULL;
        while(del->left)
        {
          delparent = del;
          del = del->left;
        }
        cur->key = del->key;
        if(delparent == cur)
        {
          delparent->right = del->right;
        }
        else
        {
          delparent->left = del->right;
        }
      }
    }
    parent = cur;
    if(key < cur->key)
    {
      cur = cur->left;
    }
    if(key > cur->key)
    {
      cur = cur->right;
    }
  }
  return -1;
}
