#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Heap
{
	int* arr;
	unsigned int capacity;
	unsigned int size;
	bool isMaxHeap;
} Heap;

// Utility
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


Heap* __init__(unsigned int capacity, bool isMaxHeap)
{
	Heap* h = (Heap *)malloc(sizeof(Heap));

	if(h == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	h->arr = (int *)calloc(capacity, sizeof(int));

	if(h->arr == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	h->capacity = capacity;
	h->size = 0;
	h->isMaxHeap = isMaxHeap;

	return h;
}

void heapifyUp(Heap* h, unsigned int index)
{
	int parent = (index - 1) / 2;

	while(index > 0 && ((h->isMaxHeap && *(h->arr + index) > *(h->arr + parent)) || (!h->isMaxHeap && *(h->arr + index) < *(h->arr + parent))))
	{
		swap(h->arr + index, h->arr + parent);
		index = parent;
		parent = (index - 1) / 2;
	}
}

void heapifyDown(Heap *h, unsigned int index){
    	unsigned int largest_or_smallest,left,right;
    	while (true)
	{
        	largest_or_smallest = index;
        	left = 2 * index + 1;
        	right = 2 * index + 2;

        	if (h->isMaxHeap)
		{
            		if (left < h->size && *(h->arr + left) > *(h->arr + largest_or_smallest))
                		largest_or_smallest = left;
            		if (right < h->size && *(h->arr + right) > *(h->arr + largest_or_smallest))
                		largest_or_smallest = right;
        	}
		else
		{
            		if (left < h->size && *(h->arr + left) < *(h->arr + largest_or_smallest))
                		largest_or_smallest = left;
            		if (right < h->size && *(h->arr + right) < *(h->arr + largest_or_smallest) )
                		largest_or_smallest = right;
        	}

        	if (largest_or_smallest != index)
		{
            		swap(h->arr + index, h->arr + largest_or_smallest);
            		index = largest_or_smallest;
       		}
		else
            		break;
    	}
}


void insert(Heap* h, int value)
{
	if(h->size == h->capacity)
	{
		h->capacity *= 2;
		h->arr = (int *)realloc(h->arr,sizeof(int) * h->capacity);

		if(h->arr == NULL)
		{
			printf("Memory Allocation Failed!\n");
			exit(EXIT_FAILURE);
		}
	}
	*(h->arr + h->size++) = value;
	heapifyUp(h,h->size - 1);
}

int delete(Heap *h)
{
	if (h->size == 0)
    	{
		printf("Can't delete heap is empty!\n");
		exit(EXIT_FAILURE);
    	}
    	int root = *h->arr;
	*h->arr = *(h->arr + --h->size);
    	heapifyDown(h, 0);
    	return root;
}

Heap* buildHeap(int* array, unsigned int size,bool isMaxHeap)
{
	Heap* h = __init__(size,isMaxHeap);

	for(unsigned int i = 0; i < size; i++)
		*(h->arr + i) = *(array + i);

	h->size = size;

	for(int j = (size / 2) - 1; j >= 0; j--)
		heapifyDown(h,j);

	return h;
}

int* heapSort(Heap* h)
{
	int* sorted = (int *)malloc(sizeof(int) * h->size);

	if(sorted == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for( int i = h->size - 1; i >= 0; i--)
		*(sorted + i) = delete(h);

	return sorted;
}

void printHeap(Heap *h) {
    for (int i = 0; i < h->size; i++)
        printf("%d ", h->arr[i]);
    printf("\n");
}


void __del__(Heap *h) {
    free(h->arr);
    free(h);
}


int main() {
    Heap *h = __init__(10, false);

    insert(h, 20);
    insert(h, 15);
    insert(h, 30);
    insert(h, 5);
    insert(h, 10);

    printf("Heap after inserts:\n");
    printHeap(h);

    printf("Deleted root: %d\n", delete(h));

    printf("Heap after deletion:\n");
    printHeap(h);


    unsigned int size = h->size;
    int *sorted = heapSort(h);

    printf("Sorted array:\n");
    for(unsigned int i = 0; i < size; i++)
        printf("%d ", sorted[i]);
    printf("\n");

    free(sorted);

    int arr[] = {4, 10, 3, 5, 1};
    Heap* h1 = buildHeap(arr, 5,false);
    printf("Heap after buildHeap from array:\n");
    printHeap(h1);

    size = h1->size;
    sorted = heapSort(h1);

    printf("Sorted array:\n");
    for(unsigned int i = 0; i < size; i++)
        printf("%d ", sorted[i]);
    printf("\n");

    free(sorted);

    __del__(h);
    __del__(h1);
    return EXIT_SUCCESS;
}

