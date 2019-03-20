//删列造序
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int col = A[0].size();
        int count = 0;
        while(col--)
        {
            for(int i = 0;i<A.size()-1;++i)
            {
                if(A[i][col]>A[i+1][col])
                {
                    count++;
                    break;
                }
            }
        }
        return count;
    }
};

class Solution1 {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int j = 1;
        for(int i = 0;i<A.size();i+=2)
        {
            if(A[i]%2 == 1)
            {
                while(A[j]%2 == 1)
                {
                    j+=2;
                }
                swap(A[i],A[j]);
            }
        }
        return A;
    }
};
