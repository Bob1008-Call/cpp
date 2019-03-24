#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{
		int count = 0;
		sort(numbers.begin(), numbers.end());
		for (int i = 0; i<numbers.size(); ++i)
		{
			if (numbers[i] == numbers[numbers.size() / 2])
			{
				count++;
			}
		}
		if (count >= numbers.size() - 1)
		{
			return numbers[numbers.size() / 2];
		}
		return 0;
	}
};

int main()
{
  Solution s;

  return 0;
}
