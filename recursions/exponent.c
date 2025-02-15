#include <stdio.h>
#include <stdlib.h>

double exponent(int base, int pow)
{
    if (pow == 0)
        return 1;
    if (pow == 1)
        return base;
    if (pow == -1)
        return 1.0 / base;
 
    if (pow > 0)
        return base * exponent(base, pow - 1);
    else
        return exponent(base, pow + 1) / base;
}

int main()
{
    int base = 2, pow = -3;
    printf("%d^%d = %lf\n", base, pow, exponent(base, pow));
    return 0;
}

