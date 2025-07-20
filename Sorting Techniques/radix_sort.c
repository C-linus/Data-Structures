#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct Node
{
	int data;
	struct Node* next;
} Node;


Node* __init__(int data)
{
	Node* node = (Node *)malloc(sizeof(Node));

	if(node == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	node->data = data;
	node->next = NULL;

	return node;
}


void append(Node** head, int data)
{
	Node* node = __init__(data);

	if(*head == NULL)
		*head = node;
	else
	{
		Node* curr = *head;
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = node;
	}
}

void __del__(Node** head)
{
	Node* curr = *head;
	Node* temp;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	*head = NULL;
}


unsigned int getMaxAbs(int* arr, unsigned int size)
{
	unsigned int max = abs(*arr);
	unsigned int absVal;

	for(int i = 1; i < size; i++)
	{
		absVal = abs(*(arr + i));
		if(max < absVal)
			max = absVal;
	}
	return max;
}


void radix_sort(int* arr, unsigned int size, bool isAsc)
{
	unsigned int max = getMaxAbs(arr,size);

	Node** pos_buckets;
	Node** neg_buckets;

	for(unsigned int exp = 1; max / exp > 0; exp *= 10)
	{
		pos_buckets = (Node **)calloc(10,sizeof(Node*));
		neg_buckets = (Node **)calloc(10,sizeof(Node*));

		if(pos_buckets == NULL || neg_buckets == NULL)
		{
			printf("Memory Allocation Failed!\n");
			exit(EXIT_FAILURE);
		}

		// Bucket Assignment
		unsigned int index;
		for(unsigned int i = 0; i < size;i++)
		{

			index = ( abs(*(arr + i)) / exp ) % 10;

			if(*(arr + i) < 0)
				append(neg_buckets + index,*(arr + i));
			else
				append(pos_buckets + index,*(arr + i));
		}


		index = 0;
		Node* bucket;

		for(int i = 9; i >= 0; i--)
		{
			bucket = (isAsc) ? *(neg_buckets + i): *(pos_buckets + i);
			while(bucket != NULL)
			{
				*(arr + index++) = bucket->data;
				bucket = bucket->next;
			}
		}

		for(unsigned int i = 0; i < 10; i++)
		{
			bucket = (isAsc) ? *(pos_buckets + i) : *(neg_buckets + i);
			while(bucket != NULL)
			{
				*(arr + index++) = bucket->data;
				bucket = bucket->next;
			}
		}

		for(unsigned int i = 0; i < 10; i++)
		{
			__del__(pos_buckets + i);
			__del__(neg_buckets + i);
		}


		free(pos_buckets);
		free(neg_buckets);

	}
}

void printArray(int* arr, unsigned int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void) {
    int arr[] = {170, -45, 75, -90, -802, 24, 2, 66};
    unsigned int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original:   ");
    printArray(arr, n);

    radix_sort(arr, n, true);  // true for ascending
    printf("Ascending:  ");
    printArray(arr, n);

    radix_sort(arr, n, false); // false for descending
    printf("Descending: ");
    printArray(arr, n);

    return EXIT_SUCCESS;
}
