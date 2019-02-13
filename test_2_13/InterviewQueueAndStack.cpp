//1.使用同一个栈，采用多次入栈出栈法
//2.使用两个栈，一个存储最小值，一个存储所有元素
#include <stack>
using namespace std;
template<class T>
class MinStack
{
  public:
    MinStack()
    {}

    ~MinStack()
    {}

    void Push(const T& x)
    {
      if(s2.empty())
      {
        s1.push(x);
        s2.push(x);
      }
      else 
      {
        if(x < s2.top())
        {
          s2.push(x);
        }
        s1.push(x);
      }
    }

    void Pop()
    {
      if(s2.empty())
      {
        return;
      }
      else 
      {
        if(s1.top() == s2.top())
        {
          s2.pop();
        }
        s1.pop();
      }
    }

    T& Min()
    {
      if(!s2.empty())
      {
        return s2.top();
      }
    }

  private:
    stack<T> s1;
    stack<T> s2;
};
