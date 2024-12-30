#include <stdio.h>

int main()
{
    int A[] = {2, 4, 6, 8, 10};

    printf("size of array:%zubytes\n", sizeof(A));

    // Printing array values
    for (int i = 0; i < 5; i++)
    {
        printf("arr[%d] = %d\n", i, *(A + i));
    }
}