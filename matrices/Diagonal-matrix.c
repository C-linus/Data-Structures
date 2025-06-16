#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
    int arr[10];
    unsigned int n;
} Matrix;

void Set(Matrix* m, unsigned int row, unsigned int col,int element)
{
    if(row == col && row <= m->n && row >= 1)
        *(m->arr + row - 1) = element;
}

int Get(Matrix m, int row, int col)
{
    return (row == col && row <= m.n && row >= 1 )? *(m.arr + row - 1) : 0;
}

void Display(Matrix m)
{
    for(int i = 0; i < m.n; i++)
    {
        for(int j = 0; j < m.n; j++)
        {
            if(i == j)
                printf("%d ",*(m.arr + i));
            else
                printf("0 ");
        }
        printf("\n");
    }
}

int main()
{
    Matrix m;
    m.n = 4;
    Set(&m,1,1,5);
    Set(&m,2,2,8);
    Set(&m,3,3,9);
    Set(&m,4,4,12);
    Display(m);
    printf("Matrix(2,2):%d\n",Get(m,2,2));
    return EXIT_SUCCESS;

}