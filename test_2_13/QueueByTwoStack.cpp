#include <stack>
using namespace std;
template<class T>
class QueueByTwoStack
{
  public:
    QueueByTwoStack()
    {}

    ~QueueByTwoStack()
    {}

    void Push(const T& x)
    {
      s1.push(x);
    }

    void Pop()
    {
      if(s2.empty())
      {
        while(!s1.empty())
        {
          s2.push(s1.top());
          s1.pop();
        }
      }
      s2.pop();
    }

    const T& Front()
    {
      if(!s2.empty())
      {
        return s2.top();
      }
      if(!s1.empty() && s2.empty())
      {
        T tmp = 0;
        while(!s1.empty())
        {
          if(s1.size() == 1)
          {
            tmp = s1.top();
          }
          s2.push(s1.top());
          s1.pop();
        }
        return tmp;
      }
    }
  private:
    stack<T> s1;
    stack<T> s2;
};
