#include <stdio.h>
#include <string.h>
#include <malloc.h>

void PrintArray(int* array,int size)
{
  int i = 0;
  for(i = 0;i<size;i++)
  {
    printf("%d ",array[i]);
  }
  printf("\n");
}

void InsertSort(int* array,int size)
{
  int i = 0;
  for(i=1;i<size;++i)
  {
    int key = array[i];
    int end = i-1;
    while(end >= 0 && key<array[end])
    {
      array[end+1] = array[end];
      --end;
    }
    array[end+1] = key;
  }
}

void ShellSort1(int *array,int size)
{
  int gap = size;
  while(gap>1)
  {
    int i = 0;
    gap = gap/3+1;
    for(i=gap;i<size;i++)
    {
      int key = array[i];
      int end = i-gap;
      while(end>=0 && key<array[end])
      {
        array[end+gap] = array[end];
        end-=gap;
      }
      array[end+gap] = key;
    }
  }
}

void ShellSort(int* array,int size)
{
  int gap = size;
  while(gap>1)
  {
  int i = 0;
  gap = gap/3+1;
  for(i=gap;i<size;++i)
  {
    int key = array[i];
    int end = i-gap;
  while(end >= 0 && key<array[end])
  {
    array[end+gap] = array[end];
    end-=gap;
  }
  array[end+gap] = key;
  }
  } 
}

void Swap(int* x,int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void SelectSort(int* array,int size)
{
  int i;
  for(i = 0;i<size-1;++i)
  {
    int j = 1;
    int maxPos = 0;
    for(;j<size-i;++j)
    {
      if(array[j]>array[maxPos])
        maxPos = j;
    }
    if(maxPos != size-i-1)
      Swap(&array[size-i-1],&array[maxPos]);
  }
}

void SelectSort_O(int *array,int size)
{
  int begin = 0; 
  int end = size-1;
  while(begin<end)
  {
    int maxPos = begin;
    int minPos = begin;
    
    int i = begin+1;
    while(i<=end)
    {
      if(array[i]>array[maxPos])
        maxPos = i;
      if(array[i]<array[minPos])
        minPos = i;
      ++i;
    }
    if(maxPos != end)
    Swap(&array[maxPos],&array[end]);
    if(minPos == end)//最小的位置在最后面（end），需要把最小的位置换为最大的位置
      minPos = maxPos;
    if(minPos != begin)
    Swap(&array[minPos],&array[begin]);
    begin++;
    end--;
  }
}

void BubbleSort(int *array,int size)
{
  int i,j;
  for(i=0;i<size;i++)
  {
    int ischange = 0;
    for(j=1;j<size-i-1;j++)
    {
      if(array[j]>array[j+1])
      {
        ischange = 1;
        Swap(&array[j],&array[j+1]);
      }
    }
    if(!ischange)
      return;
  }
}

void HeapAdjust1(int *array,int size,int parent)
{
  int child = (parent<<1)+1;
  while(child<size)
  {
    if(child+1<size && array[child]<array[child+1])
    {
      child += 1;
    }
    if(array[child]>array[parent])
    {
      Swap(&array[child],&array[parent]);
      parent = child;
      child = (parent<<1)+1;
    }
    else
      return;
  }
}

void HeapSort1(int *array,int size)
{
  int end = size-1;
  int root = ((size-2)>>1);
  for(;root >= 0;--root)
  {
    HeapAdjust1(array,size,root);
  }
  //2.排序--删除
  while(end>0)
  {
    Swap(&array[0],&array[end]);
    HeapAdjust1(array,end,0);
    end--;
  }
}

int Partion2(int *array,int left,int right)
{
  int cur = left;
  int key = array[right-1];
  int prev = left-1;
  while(cur<right)
  {
  if(array[cur]<key && ++prev != cur)
    Swap(&array[prev],&array[cur]);
  ++cur;
  }
  if(++prev != right-1)
    Swap(&array[right],&array[prev]);

  return prev;
}

int Partion1(int *array,int left,int right)
{
  int key = array[right-1];
  int begin = left;
  int end = right-1;
  while(begin<end)
  {
    //从左往右找比基准值大的元素
    while(begin<end && array[begin]<=key)
      begin++;
    if(begin<end)
    {
      array[end] = array[begin];
      end--;
    }
    while(begin<end && array[end]>=key)
      end--;
    if(begin<end)
    {
      array[begin] = array[end];
      begin++;
    }
  }
  array[begin] = key;     
  return begin;
}

int GetMiddleIndex(int *array,int left,int right)//三数取中间
{
  int mid = left+((right-left)>>1);
  if(array[left]<array[right-1])
  {
    if(array[mid]<array[left])
      return left;
    else if(array[mid]>array[left])
      return mid;
    else
      return right-1;
  }
  else
  {
    if(array[mid]<array[left])
      return mid;
    else if(array[mid]>array[left])
      return left;
    else
      return right-1;
  }
}

int Partion(int *array,int left,int right)
{
  int index = GetMiddleIndex(array,left,right);
  int key;
  if(index != right)
    Swap(&array[index],&array[right-1]);
  key = array[right-1];
  int begin = left;
  int end = right-1;
    //end从right-1开始，反例是有序的序列
  while(begin<end)
  {
    while(begin<end && array[begin]<= key)
      begin++;
    //需要判断 begin 和 end 的关系，反例是有序的序列
      while(begin<end && array[end]>=key)
      end--;
    if(begin<end)
      Swap(&array[begin],&array[end]);
  }
  if(begin != right-1)
    Swap(&array[begin],&array[right-1]);
  return begin;
}

void QuickSort(int *array,int left,int right)
{
  if(right-left>1)
  {
    int boundary = Partion1(array,left,right);
    QuickSort(array,left,boundary);
    QuickSort(array,boundary+1,right);
  }
}

void MergeData(int *array,int left,int mid,int right,int *temp)
{
  int index = left;
  int begin1 = left;
  int end1 = mid;
  int begin2 = mid;
  int end2 = right;
  while(begin1<end1 && begin2<end2)
  {
    if(array[begin1]<=array[begin2])
      temp[index++] = array[begin1++]; 
    else
      temp[index++] = array[begin2++];
  }
  while(begin1<end1) 
  {
    temp[index++] = array[begin1++];
  }
  while(begin2<end2)
  {
    temp[index++] = array[begin2++];
  }
}

//归并排序
void _MergeSort(int *array,int left,int right,int *temp)
{
  if(right-left>1)
  {
    int mid = left+((right-left)>>1);
    _MergeSort(array,left,mid,temp);
    _MergeSort(array,mid,right,temp);
    MergeData(array,left,mid,right,temp);
    memcpy(array+left,temp+left,(right-left)*sizeof(int));
  }
}

void MergeSort(int *array,int size)
{
  int* temp = (int *)malloc(sizeof(int)*size);
  if(NULL == temp)
  {
    return;
  }
  _MergeSort(array,0,size,temp);
  free(temp);
}

int main()
{
  int array[] = {2,4,7,3,8,5,2,5,7};
  PrintArray(array,sizeof(array)/sizeof(array[0]));
  //BubbleSort(array,sizeof(array)/sizeof(array[0]));
  MergeSort(array,sizeof(array)/sizeof(array[0]));
  PrintArray(array,sizeof(array)/sizeof(array[0]));
  return 0;
}
