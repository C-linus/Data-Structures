#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a,b)((a > b) ? a : b)
#define MIN(a,b)((a < b) ? a : b)


void count_sort(int* arr,unsigned int size, bool isAsc)
{
	int max = arr[0];
	int min = arr[0];

	for(unsigned int i = 1; i < size; i++)
	{
		max = MAX(max,*(arr + i));
		min = MIN(min,*(arr + i));
	}


	unsigned int range = max - min + 1;

	int* count = (int *)calloc(range,sizeof(int));
	int* output = (int *)malloc(size * sizeof(int));

	if(count == NULL || output == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < size; i++)
		*(count + *(arr + i) - min) += 1;

	// Cummulative Sum

	if(isAsc)
	{
		for(unsigned int i = 1; i < range; i++)
			*(count + i) += *(count + i - 1);
	}
	else
	{
		for(int i = range - 2; i >= 0; i--)
			*(count + i) += *(count + i + 1);
	}



	for(int i = size - 1; i >= 0; i--)
	{
		*(output + *(count + *(arr + i) - min) - 1) = *(arr + i);
		*(count + *(arr + i) - min) -= 1;
	}

	for(unsigned int i = 0; i < size; i++)
		*(arr + i) = *(output + i);

	free(count);
	free(output);

}

int main() {
    int arr[] = {23,4,21, 2,18, 2,17, 8, 3,9, 34,3,88,1,15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    count_sort(arr, n, true); // Ascending

    printf("\nSorted array (Ascending):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    count_sort(arr, n, false); // Descending

    printf("\nSorted array (Descending):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return EXIT_SUCCESS;
}
