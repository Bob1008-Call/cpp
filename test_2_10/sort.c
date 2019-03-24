#include <stdio.h>

void Swap(int* x,int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void InsertSort(int* array,int size)
{
  int i = 0;
  for(i = 1;i<size;i++)
  {
    int key = array[i];
    int end = i-1;
    while(end>=0 && key<array[end])
    {
      array[end+1] = array[end];
      --end;
    }
    array[end+1] = key;
  }
}

void InsertSort_OP(int* array,int size)
{
  int i = 0;
  for(i = 1;i<size;i++)
  {
    int key = array[i];
    int end = i-1;
    int left = 0;
    int right = end;
    while(left<=right)
    {
      int mid = left+(right-left)/2;
      if(key<array[mid])
      {
        right = mid-1;
      }
      else 
      {
        left = mid+1;
      }
    }
    while(left<=end)
    {
      array[end+1] = array[end];
      --end;
    }
    array[end+1] = key;
  }
}

void ShellSort(int* array,int size)
{
  int i = 0;
  int gap = size;
  while(gap>1)
  {
    for(i = gap;i<size;i++)
    {
      gap = gap/3+1;
      int key = array[i];
      int end = i-gap;
      while(end>=0 && key<array[end])
      {
        array[end+gap] = array[end];
        gap -= end;
      }
      array[end+gap] = key;
    }
  }
}

void SelectSort(int* array,int size)
{
  int i = 0;
  for(i = 0;i<size-1;i++)
  {
    int j = 1;
    int maxPos = 0;
    for(;j<size-i;j++)
    {
      if(array[maxPos]<array[j])
        maxPos = j;
    }
    if(maxPos != size-i)
    {
      Swap(&array[maxPos],&array[size-i-1]);
    }
  }
}

void SelectSort_OP(int* array,int size)
{
  int start = 0;
  int end = size-1;
  while(start<=end)
  {
    int maxPos = start;
    int minPos = start;
    int j = start+1;
    while(j<=end)
    {
      if(array[maxPos]<array[j])
        maxPos = j;
      if(array[minPos]>array[j])
        minPos = j;
      ++j;
    }
    if(maxPos != end)
      Swap(&array[maxPos],&array[end]);

    if(minPos == end)
      minPos = maxPos;

    if(minPos != start)
      Swap(&array[minPos],&array[start]);
    ++start;
    --end;
  }
}

void AdjustDown(int* array,int parent,int size)
{
  int child = (parent<<1)+1;
  while(child<size)
  {
    if(child+1<size && array[child]<array[child+1])
      child += 1;

    if(array[parent]<array[child])
      Swap(&array[parent],&array[child]);

    parent = child;
    child = (parent<<1)+1;
  }
}

void HeapSort(int* array,int size)
{
  int i = 0;
  int end = size-1;
  int root = (size-1-1)/2;
  for(i = root;i>=0;i--)
  {
    AdjustDown(array,i,size);
  }
  while(end)
  {
    Swap(array,array+end);
    AdjustDown(array,0,end);
    --end;
  }
}

int main()
{
  int array[] = {3,4,2,5,6,1,7};
  int size = sizeof(array)/sizeof(array[0]);
  HeapSort(array,size);
  int i = 0;
  for(;i<size;i++)
  {
    printf("%d ",array[i]);
  }
  return 0;
}
