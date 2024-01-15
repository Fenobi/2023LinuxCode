#include <iostream>

using namespace std;

class Base
{
public:
  virtual void Fun1()
  {
    cout<<"Base:Fun1()"<<endl;
  }
private:
  int _b=1;
  char _ch;
};

class Derive:public Base 
{
public:
  void Fun1()
  {
    cout<<"Derive Fun"<<endl;
  }
private:
  int _d=2;
};


// int main()
// {
//   cout<<sizeof(Base)<<endl;
//   cout<<sizeof(Derive)<<endl;
//   return 0;
// }

int main()
{
  int a = 2;
  cout << "栈：" << &a << endl;

  int *p1 = new int;
  cout << "堆：" << p1 << endl;

  const char *str = "hello!";
  cout << "常量区：" << (void *)str << endl;

  static int b = 0;
  cout << "静态区：" << &b << endl;

  Base bs;
  cout << "虚表:" << (void *)*((int *)&bs) << endl;

  return 0;
}