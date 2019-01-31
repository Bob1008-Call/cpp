#include <stdio.h>
#include <stdlib.h>
/*-------------冒泡排序-------------*/
void BubbleSort(int data[],int n)
{
  int i,j,temp;
  for(j=0;j<n-1;j++)
  {
    for(i=0;i<n-j-1;i++)
    {
      if(data[i]>data[i+1])
      {
        temp = data[i];
        data[i] = data[i+1];
        data[i+1] = temp;
      }
    }
  }
}

/*-------------快速排序-------------*/
int findPos(int data[],int low,int high)
{
  int t= data[low];
  while(low<high)
  {
    while(low<high && data[high] >= t)
    {
      high--;
    }
    data[low] = data[high];
    while(low<high && data[low] <= t)
    {
      low++;
    }
    data[high] = data[low];
  }
  data[low] = t;
  return low;
}

void QuickSort(int data[],int low,int high)
{
  if(low>high)
  {
    return;
  }
  int pos = findPos(data,low,high);
  QuickSort(data,low,pos-1);
  QuickSort(data,pos+1,high);
}

/*-------------插入排序-------------*/
void BInsertSort(int data[],int n)
{
  int temp,i,j;
  for(i=1;i<n;i++)
  {
    for(j=i;j>0;j--)
    {
      if(data[j]<data[j-1])
      {
        temp = data[j];
        data[j] = data[j-1];
        data[j-1] = temp;
      }
      else
      {
        break;
      }
    }
  }
  return;
}

void printData(int data[],int n)
{
  int i;
  for(i=0;i<n;i++)
  {
    printf("%d ",data[i]);
  }
  printf("\n");
  return;
}

void ShellSort(int data[],int n)
{
  int i,j,elem;
  int k = n/2;
  while(k>=1)
  {
    for(i=k;i<n;i++)
    {
      elem = data[i];
      for(j=i;j>=k;j-=k)
      {
        if(elem<data[j-k])
        {
          data[j] = data[j-k];
        }
        else
        {
          break;
        }
      }
      data[j] = elem;
    }
    k = k/2;
  }
}

int main()
{
  int data[] = {1,5,3,6,8,3,7};
  int n = sizeof(data)/sizeof(data[0]);
  BInsertSort(data,n);
  printData(data,n);
  return 0;
}
