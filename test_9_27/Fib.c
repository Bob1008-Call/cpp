#include <stdio.h>

int Fib(int N)
{
  if (N<3)
  return 1;
  return Fib(N-1)+Fib(N-2);
}


//int main()
//{
//  printf("%d,%d",60,Fib(60));
//  return 0;
//}

long int NFib(int first,int second,int N)
{
  if(N<3)
    return 1;
  if(3 == N)
    return first+second;
  return NFib(second,first+second,N-1);
}

int Fib1(int N)
{
  int first = 1;
  int second = 1;
  int ret = 0;
  int i = 3;
  for(;i<=N;i++)
  {
    ret = first+second;
    first = second;
    second = ret;
  }
  return ret;
}

int main()
{

  printf("%d",Fib1(10));
  return 0;
}
