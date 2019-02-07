#include <stdio.h>
void ShellSort(int* array,int size)
{
  int i = 0;
  int gap = size;
  while(gap>1)
  {
     gap = gap/3+1;
     for(i = gap;i<size;i++)
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

int main()
{
  int array[] = {1,6,2,4,5,2};
  int len = sizeof(array)/sizeof(array[0]);
  ShellSort(array,len);
  for(int i = 0;i<len;i++)
    printf("%d ",array[i]);
  return 0;
}
