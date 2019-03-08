#include <stdio.h>

int _check()
{
  int a = 1;
  return *((char*)&a);
}

int main()
{
  if(_check() == 1)
  { 
    printf("小端\n");
  }
  else 
  {
    printf("大端\n");
  }
  return 0;
}
