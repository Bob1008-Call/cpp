#include <stdlib.h>
#include <malloc.h>
int Merge(int* array1,int size1,int* array2,int size2)
{
  int index1 = 0,index2 = 0,index = 0;
  int *temp = (int*)malloc(sizeof(int)*(size1+size2));
  if(NULL == temp)
  {
    return NULL;
  }
  while(index1<size1 && index2<size2)
  {
    if(array1[index1]<array2[index2])
      temp[index++] = array1[index1];
    else
      temp[index++] = array2[index2];
  }   
}
