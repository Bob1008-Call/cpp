#include <stdio.h>

void Swap(int* x,int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int GetMiddleIndex(int* array,int left,int right)
{
  int end = right-1;
  int mid = left+(right-left)/2;
  if(array[left]<array[end])
  {
    if(array[mid]<array[left])
      return left;
    else if(array[mid]>array[end])
      return end;
    else 
      return mid;
  }
  else 
  {
    if(array[mid]<array[end])
      return end;
    else if(array[mid]>array[left])
      return left;
    else 
      return mid;
  }
}
//交换法
int Partion1(int* array,int left,int right)
{
  int begin = left;
  int end = right-1;
  int index = GetMiddleIndex(array,left,right);
  if(index != end)
    Swap(&array[end],&array[index]);

  int key = array[end];
  while(begin<end)
  {
    while(begin<end && array[begin]<key)
      begin++;
    while(begin<end && array[end]>key)
      end--;
    if(begin<end)
      Swap(&array[begin],&array[end]);
  }
  if(begin != end)
    Swap(&array[begin],&array[end]);

  return begin;
}
//挖坑法
int Partion2(int* array,int left,int right)
{
  int end = right-1;
  int begin = left;
  int index = GetMiddleIndex(array,left,right);
  if(index != end)
    Swap(&array[index],&array[end]);

  int key = array[end];
  while(begin<end)
  {
    while(begin<end && array[begin]<key)
      begin++;
    if(begin<end)
    {
      array[end] = array[begin];
      end--;
    }
    while(begin<end && array[end]>key)
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
//前后指针法
int Partion3(int* array,int left,int right)
{
  int cur = left;
  int pre = left-1;
  int index = GetMiddleIndex(array,left,right);
  if(index != right-1)
  {
    Swap(&array[index],&array[right-1]);
  }
  int key = array[right-1];
  while(cur<right-1)
  {
    if(array[cur]<key)
    {
      pre++;
      Swap(&array[pre],&array[cur]);
    }
    cur++;
  }
  if(pre != cur)
    Swap(&array[++pre],&array[cur]); 
  
  return pre;
}
void _QuickSort(int* array,int left,int right)
{
  if(right-left>1)
  {
    int div = Partion3(array,left,right);
    _QuickSort(array,left,div);
    _QuickSort(array,div+1,right);
  }
}

void QuickSort(int* array,int size)
{
  _QuickSort(array,0,size);
}

int main()
{
  int array[] = {1,6,5,2,7,3,4};
  int size = sizeof(array)/sizeof(array[0]);
  QuickSort(array,size);
  int i = 0;
  for(i = 0;i<size;i++)
    printf("%d ",array[i]);
  return 0;
}
