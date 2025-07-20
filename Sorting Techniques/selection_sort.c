#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void selection_sort(int* arr, unsigned int size, bool isAsc)
{
	unsigned int i, selected_index;

	for(i = 0; i < size - 1; i++)
	{
		selected_index = i;

		for(unsigned int j = i + 1;j < size;j++)
		{
			if((isAsc) ? (*(arr + j) < *(arr + selected_index)) : (*(arr + j) > *(arr + selected_index)))
			{
				selected_index = j;
			}
		}

		if(selected_index != i)
			swap(arr + i, arr + selected_index);

	}
}


void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");
}

int main()
{
    int arr[] = {20, 12, 10, 15, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Sort in ascending order
    selection_sort(arr, n, true);
    printf("Sorted array in ascending order:\n");
    printArray(arr, n);

    // Sort in descending order
    selection_sort(arr, n, false);
    printf("Sorted array in descending order:\n");
    printArray(arr, n);

    return EXIT_SUCCESS;
}
