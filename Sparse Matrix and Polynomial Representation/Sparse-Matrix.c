#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 


#define DEFAULT_SPARSITY_THRESHOLD 0.5f

// Coordinates(row,col,value)
typedef struct Coordinates
{
    unsigned int row;
    unsigned int col;
    int value; 
} Coordinates;

// Matrix[m][n]
typedef struct SparseMatrix
{
    unsigned int m;
    unsigned int n;
    unsigned int count;
    Coordinates* coordinates;
} SparseMatrix;



bool isSparse(SparseMatrix* matrix, float threshold) {
    unsigned int total = matrix->m * matrix->n;
    float ratio = (float)matrix->count / total;
    return ratio < threshold;
}



bool isValidCoordinate(SparseMatrix* matrix, unsigned int row, unsigned int col, int value, unsigned int index) {
    // 1. Check value is not zero
    if (value == 0) {
        printf("\nValue cannot be zero in a sparse matrix.\n");
        return false;
    }

    // 2. Check bounds
    if (row >= matrix->m || col >= matrix->n) {
        printf("\nInvalid row/column index. Must be within matrix bounds.\n");
        return false;
    }

    // 3. Check for duplicate coordinate
    for (unsigned int i = 0; i < index; i++) {
        if (matrix->coordinates[i].row == row && matrix->coordinates[i].col == col) {
            printf("\nDuplicate position (%u,%u) is not allowed.\n", row, col);
            return false;
        }
    }

    return true;
}


// Constructor
SparseMatrix* __init__()
{
    SparseMatrix* matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));

    if(!matrix)
    {
        printf("Couldn't alloacte the memory!\n");
        exit(EXIT_FAILURE);
    }
    

    // Dimensions
    matrix->m = 0;
    matrix->n = 0;

    while(!(matrix->m)){
        printf("Enter the Dimension(m): ");
        scanf("%u",&(matrix->m));
    }

    while(!(matrix->n)){
        printf("Enter the Dimension(n): ");
        scanf("%u",&(matrix->n));
    }

    printf("Enter number of non-zero elements: ");
    scanf("%u", &(matrix->count));

    while (!isSparse(matrix, DEFAULT_SPARSITY_THRESHOLD)) {
        printf("Sparsity Error: (Minimum sparsity should be %.0f%%)\n", DEFAULT_SPARSITY_THRESHOLD * 100);
        printf("Enter number of non-zero elements: ");
        scanf("%u", &(matrix->count));
    }

    // Matrix allocation using 3-column representation
    matrix->coordinates = (Coordinates *)malloc(sizeof(Coordinates) * matrix->count);

    if(!(matrix->coordinates))
    {
        printf("Couldn't alloacte the memory!\n");
        free(matrix);
        exit(EXIT_FAILURE);
    }

    printf("Enter all non-zero elements:\n");
    unsigned int row, col;
    int value;
    for(unsigned int i = 0; i < matrix->count; i++)
    {

        while (true) {
            printf("Enter the row of element-%u: ", i+1);
            scanf("%u", &row);
            printf("Enter the col of element-%u: ", i+1);
            scanf("%u", &col);
            printf("Enter the value of element-%u: ", i+1);
            scanf("%d", &value);

            if (isValidCoordinate(matrix, row, col, value, i)) {
                matrix->coordinates[i].row = row;
                matrix->coordinates[i].col = col;
                matrix->coordinates[i].value = value;
                break;
            } else {
                printf("Invalid entry. Please re-enter element-%u.\n", i+1);
            }
        }
    }

    return matrix;

}

// Destructor
void __del__(SparseMatrix* matrix)
{
    free(matrix->coordinates);
    free(matrix);
}

// Sort Coordinates
void sortCoordinates(Coordinates* coordinates, unsigned int count)
{
    Coordinates temp;
    for(unsigned int i = 0; i < count - 1; i++)
    {
        for(unsigned int j = 0; j < count - i - 1; j++)
        {
            if((*(coordinates + j)).row > (*(coordinates + j + 1)).row || (*(coordinates + j)).col > (*(coordinates + j + 1)).col)
            {
                temp = *(coordinates + j);
                *(coordinates + j) = *(coordinates + j + 1);
                *(coordinates + j + 1) = temp;
            }
        }
    }
}

SparseMatrix* addSparseMatrix(SparseMatrix* matrix1 , SparseMatrix* matrix2)
{
    if(!(matrix1) || !(matrix2) || !(matrix1->coordinates) || !(matrix2->coordinates))
    {
        printf("Null object can't be used to perform sparse matrix addition!\n");
        exit(EXIT_FAILURE);
    }

    if(matrix1->m != matrix2->m || matrix1->n != matrix2->n)
    {
        printf("Addition Error: Matrices with different dimensions(m * n) can't be add together!\n");
        exit(EXIT_FAILURE);
    }

    SparseMatrix* result = (SparseMatrix *)malloc(sizeof(SparseMatrix));

    if(!result)
    {
        printf("Couldn't alloacte the memory!\n");
        exit(EXIT_FAILURE);    
    }

    result->m = matrix1->m;
    result->n = matrix1->n;


    result->coordinates = (Coordinates *)malloc(sizeof(Coordinates) * (matrix1->count + matrix2->count));

    if(!(result->coordinates))
    {
        printf("Couldn't alloacte the memory!\n");
        free(result);
        exit(EXIT_FAILURE);    
    }

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    while(i < matrix1->count && j < matrix2->count)
    {
        
        if(((*(matrix1->coordinates + i)).row < (*(matrix2->coordinates + j)).row) || (((*(matrix1->coordinates + i)).row == (*(matrix2->coordinates + j)).row) && (*(matrix1->coordinates + i)).col < (*(matrix2->coordinates + j)).col))
        {
            (*(result->coordinates + k)).row = (*(matrix1->coordinates + i)).row;
            (*(result->coordinates + k)).col = (*(matrix1->coordinates + i)).col;
            (*(result->coordinates + k)).value = (*(matrix1->coordinates + i)).value;
            i++;
            k++;
        }
        else if(((*(matrix1->coordinates + i)).row > (*(matrix2->coordinates + j)).row) || (((*(matrix1->coordinates + i)).row == (*(matrix2->coordinates + j)).row) && (*(matrix1->coordinates + i)).col > (*(matrix2->coordinates + j)).col))
        {
            (*(result->coordinates + k)).row = (*(matrix2->coordinates + j)).row;
            (*(result->coordinates + k)).col = (*(matrix2->coordinates + j)).col;
            (*(result->coordinates + k)).value = (*(matrix2->coordinates + j)).value;
            j++;
            k++;
        }
        else
        {
            int sum = (*(matrix1->coordinates + i)).value + (*(matrix2->coordinates + j)).value;
            if(sum != 0)
            {
                (*(result->coordinates + k)).row = (*(matrix1->coordinates + i)).row;
                (*(result->coordinates + k)).col = (*(matrix1->coordinates + i)).col;
                (*(result->coordinates + k)).value = sum;
                k++;
            }
            i++;
            j++;
        }
        
    }

    for(; i < matrix1->count; i++)
    {
        (*(result->coordinates + k)).row = (*(matrix1->coordinates + i)).row;
        (*(result->coordinates + k)).col = (*(matrix1->coordinates + i)).col;
        (*(result->coordinates + k)).value = (*(matrix1->coordinates + i)).value;
        k++;
    }
    for(; j < matrix2->count; j++)
    {
        (*(result->coordinates + k)).row = (*(matrix2->coordinates + j)).row;
        (*(result->coordinates + k)).col = (*(matrix2->coordinates + j)).col;
        (*(result->coordinates + k)).value = (*(matrix2->coordinates + j)).value;
        k++;
    }

    result->count = k;
    result->coordinates = (Coordinates*)realloc(result->coordinates,sizeof(Coordinates)* result->count);

    if(!(result->coordinates))
    {
        printf("Couldn't alloacte the memory!\n");
        free(result);
        exit(EXIT_FAILURE);    
    }
    return result;

}

void display(SparseMatrix* matrix)
{
    int k=0;

    for(int i = 0; i < matrix->m; i++)
    {
        for(int j = 0; j < matrix->n; j++)
        {
            if(i == (*(matrix->coordinates + k)).row && j == (*(matrix->coordinates + k)).col)
                printf("%6d ",matrix->coordinates[k++].value);
            else
                printf("%6d",0);
        }
        printf("\n");
    }
}

int main()
{
    SparseMatrix* matrix1 = __init__();
    display(matrix1);
    SparseMatrix* matrix2 = __init__();
    display(matrix2);
    SparseMatrix* result = addSparseMatrix(matrix1,matrix2);
    printf("\nresult:\n");
    display(result);
    __del__(matrix1);
    __del__(matrix2);
    __del__(result);
    return EXIT_SUCCESS;
}