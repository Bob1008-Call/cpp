#include <iostream>
using namespace std;
class Base
{
  public:
    virtual void Testfunc1()
    {
      cout<<"Base::Testfunc2()"<<endl;
    }

    virtual void Testfunc2()
    {
      cout<<"Base::Testfunc2()"<<endl;
    }
    int _b;
    int _c;
};

class Derived:public Base
{
  public:
    ~Derived()
    {}
};

int main()
{
  Derived d;
  cout<<sizeof(d)<<endl;
}
