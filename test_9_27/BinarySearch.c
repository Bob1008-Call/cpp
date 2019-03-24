
int BinarySearch(int *array,int size,int data)
{
  int left = 0;
  int right = size-1;//size;
  while(left<=right) //left<right;
  {
    int mid = (left+right)/2;//(left+(right-1eft)>>1)
    if(data == array[mid])
    {
      return mid;
    }
    else if(data<array[mid])
    {
      right = mid-1;//right = mid;
    }
    else
    {
      left = mid+1;
    }
  }
  return -1;
}
