#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void shell_sort(int* arr, unsigned int size, bool isAsc)
{
	int temp;
	for(unsigned int gap = size / 2; gap > 0; gap /= 2)
	{
		for(unsigned int i = gap; i < size; i++)
		{
			temp = *(arr + i);
			 int j;

			if(isAsc)
			{
				for(j = i; j >= gap && *(arr + j - gap) > temp; j -= gap)
					*(arr + j) = *(arr + j - gap);
			}
			else
			{
				for(j = i; j >= gap && *(arr + j - gap) < temp; j -= gap)
					*(arr + j) = *(arr + j - gap);
			}
			*(arr + j) = temp;
		}
	}
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main driver
int main() {
    int arr[] = {12, 34, 54, 2, 3, 90, -20, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original:   ");
    printArray(arr, n);

    shell_sort(arr, n, true);  // 1 for ascending
    printf("Ascending:  ");
    printArray(arr, n);

    shell_sort(arr, n, false);  // 0 for descending
    printf("Descending: ");
    printArray(arr, n);

    return 0;
}
