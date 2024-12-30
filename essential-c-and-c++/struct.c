#include <stdio.h>

typedef struct rectangle
{
    int length;
    int breadth;

} rectangle;

int main()
{
    rectangle r1;
    r1.length = 5;
    r1.breadth = 6;
    printf("Size of the rectangle structure: %zubytes\n", sizeof(rectangle));
}