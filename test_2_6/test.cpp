#include <stdio.h>

int main()
{
  int array[] = {8,9,1,2,3,4,5,6};
  int size = (sizeof(array)/sizeof(array[0]));
  for(int i = 0;i<size-1;i++)
  {
    for(int j=size-2;j>=i;j--)
    {
      if(array[j]<array[j+1])
      {
        int temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
  for(int i = 0;i<8;i++)
  printf("%d ",array[i]);
  return 0;
}
