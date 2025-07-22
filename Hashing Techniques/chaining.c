#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define SIZE 10

typedef struct Node
{
	int data;
	struct Node* next;
} Node;


typedef struct HashTable
{
	Node** buckets;
	unsigned int size;
	bool ascending;
} HashTable;

// Comparator utilities
bool isAsc(int a, int b){ return (a <= b); }
bool isDesc(int a, int b){ return (a >= b); }


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



HashTable* initTable(unsigned int size, bool ascending)
{
	HashTable* table = (HashTable *)malloc(sizeof(HashTable));

	if(table == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	table->buckets = (Node **)calloc(size,sizeof(Node*));

	if(table->buckets == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	table->size = size;
	table->ascending = ascending;

	return table;
}


// Hash Function (Mapper)
unsigned int hash(HashTable* table, int key)
{
	return key % table->size;
}


void insertSorted(Node** head, int data, bool ascending)
{
	Node* newNode = __init__(data);

	bool (*cmp)(int,int) = (ascending) ? isAsc : isDesc;

	if(*head == NULL || cmp(data,(*head)->data))
	{
		newNode->next = *head;
		*head = newNode;
		return;
	}

	Node* current = *head;
	while(current->next != NULL && cmp(current->next->data,data))
		current = current->next;

	newNode->next = current->next;
	current->next = newNode;
}

void insert(HashTable* table, int key)
{
	unsigned int index = hash(table,key);
	insertSorted(table->buckets + index, key, table->ascending);
}


bool search(HashTable* table, int key)
{
	unsigned int index = hash(table,key);
	Node* current = *(table->buckets + index);
	bool (*cmp)(int,int) = (table->ascending) ? isAsc : isDesc;

	while(current != NULL && cmp(current->data, key))
	{
		if(current->data == key)
			return true;
		current = current->next;
	}
	return false;
}

bool delete(HashTable* table, int key)
{
	unsigned int index = hash(table,key);
	Node** current = table->buckets + index;
	bool (*cmp)(int,int) = (table->ascending) ? isAsc : isDesc;
	Node* temp;

	while(*current != NULL && cmp((*current)->data,key))
	{
		if((*current)->data == key)
		{
			temp = *current;
			*current = (*current)->next;
			free(temp);
			return true;
		}
		current = &((*current)->next);
	}
	return false;
}

void printTable(HashTable* table)
{
	Node* current;
	for(unsigned int i = 0; i < table->size; i++)
	{
		printf("Bucket[%u]: ",i+1);
		current = *(table->buckets + i);
		while(current != NULL)
		{
			printf("%d -> ",current->data);
			current = current->next;
		}
		printf("(NULL)\n");
	}
}

void freeHashTable(HashTable** table)
{
	Node *temp, *current;

	for(unsigned int i = 0; i < (*table)->size; i++)
	{
		current = *((*table)->buckets + i);
		while(current != NULL)
		{
			temp = current;
			current = current->next;
			free(temp);
		}
	}
	free((*table)->buckets);
	free(*table);
	*table = NULL;
}

int main() {
    HashTable* table = initTable(SIZE, true);

    insert(table, 15);
    insert(table, 25);
    insert(table, 5);
    insert(table, 20);
    insert(table, 35);

    printTable(table);

    int target = 25;
    printf("Search %d: %s\n", target, search(table, target) ? "Found" : "Not Found");

    delete(table, 25);
    printf("After deleting %d:\n", target);
    printTable(table);

    freeHashTable(&table);
    return EXIT_SUCCESS;
}

