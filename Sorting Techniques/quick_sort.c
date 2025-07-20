#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// Lomato partition

unsigned int lomato_partition(int* arr, unsigned int low, unsigned int high,bool isAsc)
{

	int pivot = *(arr + high);
	int i = low - 1;

	for(int j = low; j < high;j++)
	{
		if((isAsc) ? *(arr + j) < pivot : *(arr + j) > pivot)
		{
			i++;
			swap(arr + i, arr + j);
		}
	}

	swap(arr + i + 1, arr + high);
	return i + 1;

}

// Hoare partition

unsigned int hoare_partition(int* arr, unsigned int low, unsigned int high, bool isAsc)
{
	int pivot = *(arr + low);
	int i = low - 1;
	int j = high + 1;

	while(true)
	{
		do{i++;}while((isAsc) ? *(arr + i) < pivot : *(arr + i) > pivot);
		do{j--;}while((isAsc) ? *(arr + j) > pivot : *(arr + j) < pivot);

		if( i >= j )
			return j;

		swap(arr + i, arr + j);
	}

}

void quickSort(int* arr, int low, int high, bool isAsc)
{
    if (low < high)
    {
        int pi = lomato_partition(arr, low, high, isAsc);

        quickSort(arr, low, pi - 1, isAsc);
        quickSort(arr, pi + 1, high, isAsc);
    }
}

void printArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");
}


int main()
{
    int arr[] = {33, 21, 45, 64, 22, 11, 89};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Sort ascending
    quickSort(arr, 0, n - 1, true);
    printf("Sorted in ascending order:\n");
    printArray(arr, n);

    // Sort descending
    quickSort(arr, 0, n - 1, false);
    printf("Sorted in descending order:\n");
    printArray(arr, n);

    return EXIT_SUCCESS;
}
