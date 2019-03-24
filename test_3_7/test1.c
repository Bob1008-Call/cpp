#include <stdio.h>
#include <unistd.h>
int main()
{
  printf("hello world!");
  _exit(0);
  while(1);
  return 0;
}
