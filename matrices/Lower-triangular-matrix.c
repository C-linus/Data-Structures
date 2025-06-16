#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
    int *arr;
    unsigned int n;
} Matrix;

Matrix* __init__(unsigned int n)
{
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    if (!m)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    m->n = n;
    int non_zero_elements = n * (n + 1) / 2;
    m->arr = (int *)malloc(non_zero_elements * sizeof(int));

    if (!(m->arr))
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return m;
}

// Row major mapping
void Set_r(Matrix* m, unsigned int row, unsigned int col, int element)
{
    if (row >= col && row >= 1 && row <= m->n && col >= 1)
    {
        int index = (row * (row - 1)) / 2 + (col - 1);
        m->arr[index] = element;
    }
}


int Get_r(Matrix *m, unsigned int row, unsigned int col)
{
    if (row >= col && row >= 1 && row <= m->n && col >= 1)
    {
        int index = (row * (row - 1)) / 2 + (col - 1);
        return m->arr[index];
    }
    else
        return 0;  
}

void Display_r(Matrix *m)
{
    for (unsigned int row = 1; row <= m->n; row++)
    {
        for (unsigned int col = 1; col <= m->n; col++)
        {
            if (row >= col)
            {
                int index = (row * (row - 1)) / 2 + (col - 1);
                printf("%6d ", m->arr[index]);
            }
            else
                printf("%6d",0);
        }
        printf("\n");
    }
}

void input_r(Matrix* m)
{
    printf("Enter all elements (row-wise):\n");
    for (unsigned int i = 1; i <= m->n; i++)
    {
        for (unsigned int j = 1; j <= m->n; j++)
        {
            int x;
            if (i >= j)
            {
                printf("Element [%u][%u]: ", i, j);
                scanf("%d", &x);
                Set_r(m, i, j, x);
            }
        }
    }
}

// Column major mapping
void Set_c(Matrix* m, unsigned int row, unsigned int col, int element)
{
    if (row >= col && row >= 1 && row <= m->n && col >= 1)
    {
        int index = m->n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
        m->arr[index] = element;
    }
}


int Get_c(Matrix *m, unsigned int row, unsigned int col)
{
    if (row >= col && row >= 1 && row <= m->n && col >= 1)
    {
        int index = m->n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
        return m->arr[index];
    }
    else
        return 0;  
}

void Display_c(Matrix *m)
{
    for (unsigned int row = 1; row <= m->n; row++)
    {
        for (unsigned int col = 1; col <= m->n; col++)
        {
            if (row >= col)
            {
                int index = m->n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
                printf("%6d ", m->arr[index]);
            }
            else
                printf("%6d",0);
        }
        printf("\n");
    }
}


void input_c(Matrix* m)
{
    printf("Enter all elements (col-wise):\n");
    for (unsigned int i = 1; i <= m->n; i++)
    {
        for (unsigned int j = 1; j <= m->n; j++)
        {
            int x;
            if (j >= i)
            {
                printf("Element [%u][%u]: ", j, i);
                scanf("%d", &x);
                Set_c(m, j, i, x);
            }
        }
    }
}

int main()
{
    Matrix* m;
    unsigned int size;

    printf("Enter Lower Triangular Matrix Dimension: ");
    scanf("%u", &size); 

    m = __init__(size);

    input_r(m);

    printf("\nMatrix:\n");
    Display_r(m);

    printf("\nElement at (3,1): %d\n", Get_r(m, 3, 1));
    return EXIT_SUCCESS;
}
