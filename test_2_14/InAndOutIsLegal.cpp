#include <stack>
using namespace std;
#include <stdio.h>
void InAndOutIsLegal(int* in,int* out,int inSize,int outSize)
{
  if(inSize != outSize)
  {
    printf("不合法!");
  } 
  stack<int> s;
  int in_index = 0;
  int out_index = 0;
  for(;in_index<inSize;in_index++)
  {
    s.push(in[in_index]);
    while(s.size() && s.top() == out[out_index])
    {
      s.pop();
      out_index++;
    }
  }
  if(s.empty())
  {
    printf("合法!");
  }
  else 
  {
    printf("不合法!");
  }
}

int main()
{
  int in[] = {1,2,3,4,5};
  int out1[] = {2,1,5,4,3};
  int out2[] = {2,4,3,5,1};
  int out3[] = {5,4,3,1,2};
  int out4[] = {1,3,2,5,4};
  InAndOutIsLegal(in,out1,5,5);
  InAndOutIsLegal(in,out2,5,5);
  InAndOutIsLegal(in,out3,5,5);
  InAndOutIsLegal(in,out4,5,5);
  return 0;
}
