#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INSERT_AT_BEGIN 0

typedef struct Node
{
	struct Node* prev;
	int data;
	struct Node* next;
} Node;



Node* __init__(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if(!newNode)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->prev = newNode->next = NULL;
	newNode->data = data;

	return newNode;
}

size_t __len__(Node* head)
{
	size_t len = 0;
	while(head)
	{
		len++;
		head = head->next;
	}
	return len;
}

void append(Node** head,int data)
{

	if(*head == NULL)
	{
		*head = __init__(data);
		return;
	}

	Node* newNode = __init__(data);
	Node* curr = *head;
	while(curr->next != NULL)
		curr = curr->next;

	curr->next = newNode;
	newNode->prev = curr;
}



void insert(Node** head,int data, unsigned int position)
{

	size_t len = __len__(*head);
	if(position >  len)
	{
		printf("IndexOutOfBoundError: Invalid position (%u).\n",position);
		exit(EXIT_FAILURE);
	}

	Node* newNode = __init__(data);

	// Insertion at Begining
	if(*head == NULL || position == INSERT_AT_BEGIN)
	{
		newNode->next = *head;
		if(*head != NULL)
			(*head)->prev = newNode;
		*head = newNode;
		return;
	}

	unsigned int index = 0;
	Node* curr = *head;

	while(index < position - 1)
	{
		index++;
		curr = curr->next;
	}


	newNode->next = curr->next;
	newNode->prev = curr;

	if(curr->next != NULL)
		curr->next->prev = newNode;

	curr->next = newNode;
}

void delete(Node** head,unsigned int position)
{

	if(*head == NULL)
	{
		printf("List is Empty!\n");
		return;
	}

	size_t len = __len__(*head);

	if(position >= len)
	{
		printf("IndexOutOfBoundError: Invalid position (%u).\n",position);
                exit(EXIT_FAILURE);
	}

	Node* curr = *head;
	unsigned int index = 0;

	if(position == 0)
	{
		*head = curr->next;
		if(curr->next != NULL)
			curr->next->prev = NULL;
		free(curr);
		return;
	}

	while(index < position)
	{
		curr = curr->next;
		index++;
	}

	curr->prev->next = curr->next;

	if(curr->next)
		curr->next->prev = curr->prev;

	free(curr);
}

void reverse(Node** head)
{
	if(*head == NULL || (*head)->next == NULL)
		return;

	Node* curr = *head;
	Node* temp;

	while(curr != NULL)
	{
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}

	if(temp != NULL)
		*head = temp->prev;
}

void display(Node* head, bool forward)
{

	if(head == NULL)
	{
		printf("List is Empty!\n");
		return;
	}

	Node* curr = head;

	if(!forward)
	{
		while(curr->next != NULL)
			curr = curr->next;
	}

	printf("List: (NULL) ");
	while(curr != NULL)
	{
		printf("<->  |%d| ",curr->data);
		curr = (forward)?curr->next:curr->prev;
	}
	printf("<-> (NULL)\n");
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

int main()
{
	Node* head = __init__(5);
	append(&head,10);
	append(&head,15);
	append(&head,20);
	append(&head,25);

	display(head,true);

	reverse(&head);
	display(head,true);

	__del__(&head);
	return EXIT_SUCCESS;
}
