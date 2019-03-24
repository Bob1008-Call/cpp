#include <stdio.h>

int Find(int array[],int size,int data)
{
  int i = 0;
  for(i = 0;i<size;i++)
  {
    if(data == array[i])
      printf("%d",i);
  }
  return -1;
}

int main()
{
  int array[] = {1,2,3,4,5,6,7};
  int size = sizeof(array)/sizeof(array[0]);
  Find(array,size,5);
  return 0;
}
