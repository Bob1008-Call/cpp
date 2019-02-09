void InsertSort(int* array,int size)
{
  int i = 0;
  for(int i = 1;i<size;i++)
  {
    int key = array[i];
    int end = i - 1;
    while(end>=0&&key<array[end])
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
  for(int i = 1;i<size;i++)
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
    while(end>=left)
    {
      array[end+1] = array[end];
      --end;
    }
    array[left] = key;
  }
}
