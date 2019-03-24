#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int KeyType;

typedef struct BSTreeNode
{
  BSTreeNode* left;
  BSTreeNode* right;
  KeyType key;
}BSTreeNode;

int BSTreeSearch(BSTreeNode* root,KeyType key);
int BSTreeSearchNor(BSTreeNode* root,KeyType key);

int BSTreeInsert(BSTreeNode* root,KeyType key);
int BSTreeInsertNor(BSTreeNode* root,KeyType key);

int BSTreeRemove(BSTreeNode* root,KeyType key);

