#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node
{
	int data;
	struct Node* next;
}Node;

typedef struct Queue
{
	Node* front;
	Node* rear;
} Queue;

Queue* __init__()
{
	Queue* q = (Queue *) malloc(sizeof(Queue));

	if(q == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->front = q->rear = NULL;
	return q;
}

bool isEmpty(Queue* q)
{
	return q->front == NULL;
}

void enqueue(Queue** q, int element)
{

	if(*q == NULL)
	{
		printf("Warning: Queue is NULL.\n Allocating new Queue. \n");
		*q = __init__();
	}

	Node* newNode = (Node *)malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->next = NULL;
	newNode->data = element;

	if((*q)->rear == NULL)
	{
		(*q)->front = (*q)->rear = newNode;
	}
	else
	{
		(*q)->rear->next = newNode;
		(*q)->rear = newNode;
	}
}

int dequeue(Queue* q)
{
	if(q == NULL)
	{
		printf("Can't dequeue a NULL Object!\n");
		exit(EXIT_FAILURE);
	}

	if(isEmpty(q))
	{
		printf("Queue Underflow! Cannot dequeue\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = q->front;
	int removed = temp->data;
	q->front = temp->next;

	if(q->front == NULL)
	{
		q->rear = NULL;
	}

	free(temp);
	return removed;
}

void display(Queue* q)
{
	if(isEmpty(q))
	{
		printf("Queue is Empty!\n");
		return;
	}

	printf("Queue Elements: ");
	Node* temp = q->front;
	while(temp != NULL)
	{
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void __del__(Queue** q)
{

	if(*q == NULL || q == NULL)
	{
		printf("Can't free a NULL Object!\n");
		exit(EXIT_FAILURE);
	}

	Node* temp;
	Node* curr = (*q)->front;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*q);
	*q = NULL;
}

int main()
{
    Queue* q = __init__();

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(q);

    dequeue(q);
    display(q);

    enqueue(&q, 40);
    enqueue(&q, 50);
    display(q);

    dequeue(q);
    dequeue(q);
    dequeue(q);

    display(q);

    __del__(&q);

    return EXIT_SUCCESS;
}
