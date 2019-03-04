#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
class Solution
{
  public:
    vector<int> GetLeastNumbers_Solution(vector<int> array,size_t k)
    {
      vector<int> result;
      if(array.size()<k || k<1)
        return result;

      sort(array.begin(),array.end());
      for(size_t i = 0;i<k;++i)
      {
        result.push_back(array[i]);
      }
      return result;
    }
};
