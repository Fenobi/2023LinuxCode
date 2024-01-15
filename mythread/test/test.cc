#include <iostream>
#include <unistd.h>
#include <functional>

using namespace std;

void func(int x, int y)
{
    cout << x + y << endl;
}

struct Functor
{
    void operator()(int x, int y)
    {
        cout << x + y << endl;
    }
};

int main()
{
    function<void(int, int)> f1;
    f1 = func;
    function<void(int, int)> f2(f1);
    f1(1, 2);
    f2(2, 3);
    f1 = Functor();
    function<void(int, int)> f3(f1);
    function<void(int, int)> f4(Functor());
    f3(4, 5);
    //f4(1, 2);
    return 0;
}