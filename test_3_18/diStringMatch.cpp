#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    vector<int> diStringMatch(string S) {
        int length = S.size();
        int small = 0;
        int big = length;
        vector<int> res;
        for(int i = 0;i<S.size();++i)
        {
            if(S[i] == 'I')
            {
                res.push_back(small);
                small++;
            }
            else
            {
                res.push_back(big);
                big--;
            }
        }
        res.push_back(big);
        return res;
    }
};
