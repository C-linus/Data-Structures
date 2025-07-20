#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int* a,int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort(int* arr, unsigned int n, bool isAsc)
{
	bool swapped;
	for(unsigned int i = 0; i < n - 1; i++)
	{
		swapped = false;
		for(unsigned int j = 0; j < n - i - 1; j++)
		{
			if((isAsc) ? (*(arr + j) > *(arr + j + 1)) : (*(arr + j) < *(arr + j + 1)))
			{

				swap(arr + j, arr + j + 1);
				swapped = true;
			}
		}
		if(!swapped)
			break;
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Sort ascending
    bubble_sort(arr, n, true);
    printf("Sorted array in ascending order:\n");
    printArray(arr, n);

    // Sort descending
    bubble_sort(arr, n, false);
    printf("Sorted array in descending order:\n");
    printArray(arr, n);

    return EXIT_SUCCESS;
}

