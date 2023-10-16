#include "my_add.h"
#include "my_sub.h"

int main()
{
    int a = 10;
    int b = 20;
    printf("result:%d\n", Sub(b, a));
    printf("result:%d\n", Add(b, a));
    return 0;
}