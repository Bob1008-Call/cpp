#include <stdio.h>

int Sum(int N)
{
  if (1 == N)
    return 1;
  return N+Sum(N-1);
}
