#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) 
    {
        int MaxRes = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int Temp = 0;
            while(i<nums.size()&&nums[i++]==1)Temp++;
            MaxRes = max(Temp, MaxRes);
            i--;
        }
        return MaxRes;
    }
};
