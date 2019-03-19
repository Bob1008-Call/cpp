class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int count = 0;
        for(int j = 0;j<J.length();++j)
        {
            for(int s = 0;s<S.length();++s)
            {
                if(S[s] == J[j])
                {
                    count++;
                }
            }
        }
       return count;
    }
};

class Solution {
public:
    string toLowerCase(string str) {
        for(int i = 0;i<str.size();++i)
        {
            if(str[i]<='Z' && str[i]>= 'A')
               str[i] = str[i]+32;
        }
        return str;
    }
};

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
