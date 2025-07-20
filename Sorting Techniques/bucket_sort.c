#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a,b)((a>b)?a:b)
#define MIN(a,b)((a<b)?a:b)

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

void __del__(Node** head) {
    Node* curr = *head;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    *head = NULL;
}



void sortedInsertAsc(Node** head, int data)
{
	Node* node = __init__(data);

	if(*head == NULL || (*head)->data > data)
	{
		node->next = *head;
		*head = node;
	}

	else
	{
		Node* curr = *head;
		while(curr->next  != NULL && curr->next->data <= data)
			curr = curr->next;


		node->next = curr->next;
		curr->next = node;
	}
}


void sortedInsertDesc(Node** head, int data)
{

	Node* node = __init__(data);

	if(*head == NULL || (*head)->data < data)
	{
		node->next = *head;
		*head = node;
	}

	else
	{
		Node* curr = *head;
		while(curr->next != NULL && curr->next->data >= data)
			curr = curr->next;

		node->next = curr->next;
		curr->next = node;
	}
}

void bucket_sort(int* arr, unsigned int size, bool isAsc)
{
	if(size < 2) return;

	int max = *arr;
	int min = *arr;

	for(unsigned int i = 1; i < size; i++)
	{
		max = MAX(max,*(arr + i));
		min = MIN(min,*(arr + i));
	}

	unsigned int range = max - min + 1;

	unsigned int bucket_count = size;

	Node** buckets = (Node **)calloc(bucket_count,sizeof(Node*));

	if(buckets == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < size; i++)
	{
		unsigned int index = (*(arr + i) - min) * bucket_count / range;
		if(index == bucket_count)
			index--;
		if(isAsc)
			sortedInsertAsc(buckets + index,*(arr + i));
		else
			sortedInsertDesc(buckets + index,*(arr + i));
	}


	unsigned int pos = 0;
	Node* node;
	if(isAsc)
	{
		for(unsigned int i = 0; i < bucket_count; i++)
		{
			node = *(buckets + i);
			while(node != NULL)
			{
				*(arr + pos++) = node->data;
				node = node->next;
			}
			__del__(buckets + i);
		}
	}

	else
	{
		for(int i = bucket_count - 1; i >= 0; i--)
		{
			node = *(buckets + i);
			while(node != NULL)
			{
				*(arr + pos++) = node->data;
				node = node->next;
			}
			__del__(buckets + i);
		}
	}


	free(buckets);
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main(void) {
    int arr[] = {42, 32, 33, 52, 37, 47, 51};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original:   ");
    printArray(arr, n);

    bucket_sort(arr, n, false); // Assuming 'true' is defined or you use 1

    printf("Sorted:     ");
    printArray(arr, n);

    return 0;
}

