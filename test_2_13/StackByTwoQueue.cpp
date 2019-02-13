#include <queue>
using namespace std;
template<class T>
class StackByTwoQueue
{
  StackByTwoQueue()
  {}

  ~StackByTwoQueue()
  {}

  void Push(const T& x)
  {
    if(q1.empty())
    {
      q2.push(x);
    }
    else 
    {
      q1.push(x);
    }
  }

  void Pop()
  {
    assert(!q1.empty() || !q2.empty());
    if(q1.empty())
    {
      while(q2.size()>1)
      {
        q1.push(q2.front());
        q2.pop();
      }
      q2.pop;
    }
    else 
    {
      while(q1.size()>1)
      {
        q2.push(q1.front());
        q1.pop();
      }
      q1.pop();
    }
  }

  const int& Top()
  {
    assert(!q1.empty() || !q2.empty());
    int tmp = 0;
    if(q1.empty())
    {
      while(q2.size()>1)
      {
        q1.push(q2.front());
        q2.pop();
      }
      tmp = q2.front();
      q1.push(tmp);
      q2.pop();
    }
    else 
    {
      while(q1.size()>1)
      {
        q2.push(q1.front());
        q1.pop();
      }
      tmp = q1.front();
      q2.push(tmp);
      q1.pop();
    }
    return tmp;
  }

  private:
  queue<T> q1;
  queue<T> q2;
};
