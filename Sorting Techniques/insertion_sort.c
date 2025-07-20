#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void insertion_sort(int* arr, int n, bool isAsc)
{
	int j,key;
	for(unsigned int i = 1; i < n; i++)
	{
		j = i - 1;
		key = *(arr + i);

		while( j > -1 && ((isAsc) ? (*(arr + j) > key) : (*(arr + j) < key)))
		{
			*(arr + j + 1) = *(arr + j);
			j--;
		}

		*(arr + j + 1) = key;
	}
}


void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {29, 10, 14, 37, 13};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);


    insertion_sort(arr, n, true);
    printf("Sorted array in ascending order:\n");
    printArray(arr, n);


    insertion_sort(arr, n, false);
    printf("Sorted array in descending order:\n");
    printArray(arr, n);

    return 0;
}
