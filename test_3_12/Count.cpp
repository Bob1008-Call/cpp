#include <string>
using namespace std;
class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        int count = 0;
        for(int i = 0;i<n;++i)
        {
            if(A[i] == '(')
            {
                count++;
            }
            if(A[i] == ')')
            {
                count--;
            }
        }
        if(count == 0)
        {
            return true;
        }
        return false;
    }
};
