#include <stdio.h>

int main()
{
    int a = 10;
    int *p;
    p = &a;
    printf("The value of a:%d\n", p);
    printf("The 8-byte address:%zu\n", p);
    return 0;
}
