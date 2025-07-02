#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node
{
	int data;
	int priority;
	struct Node* next;
} Node;


typedef struct PriorityQueue
{
	Node* front;
} PriorityQueue;

PriorityQueue* __init__()
{
	PriorityQueue* pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

	if(pq == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	pq->front = NULL;
	return pq;
}

bool isEmpty(PriorityQueue* pq)
{
	return pq->front == NULL;
}

void enqueue(PriorityQueue** pq, int data, int priority)
{
	if(pq == NULL)
	{
		printf("Error: NuLL pointer(*) is parsed!\n");
		exit(EXIT_FAILURE);
	}

	if(*pq == NULL)
	{
		printf("Warning: Priority Queue is NULL\n Allocating new PriorityQueue.\n");
		*pq = __init__();
	}

	Node* newNode = (Node *) malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->priority = priority;
	newNode->data = data;
	newNode->next = NULL;

	if((*pq)->front == NULL || priority < (*pq)->front->priority)
	{
		newNode->next = (*pq)->front;
		(*pq)->front = newNode;
	}
	else
	{
		Node* temp = (*pq)->front;
		while(temp->next != NULL && priority >= temp->next->priority)
			temp = temp->next;

		newNode->next = temp->next;
		temp->next = newNode;
	}
}


int dequeue(PriorityQueue* pq)
{
	if(pq == NULL)
	{
		printf("Can't dequeue a NULL Object!\n");
		exit(EXIT_FAILURE);
	}


	if(isEmpty(pq))
	{
		printf("PriorityQueue Underflow! Cannot dequeue\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = pq->front;
	int removed = temp->data;
	pq->front = temp->next;

	free(temp);
	return removed;
}


void display(PriorityQueue* pq)
{
	if(pq == NULL || isEmpty(pq))
	{
		printf("PriorityQueue is Empty!\n");
		exit(EXIT_FAILURE);
	}

	printf("PriorityQueue Elements (Data:Priority): ");
	Node* temp = pq->front;
	while(temp != NULL)
	{
		printf("(%d:%d) ",temp->data,temp->priority);
		temp = temp->next;
	}
	printf("\n");
}

void __del__(PriorityQueue** pq)
{
	if(pq == NULL || *pq == NULL)
	{
		printf("Can't free a NULL Object!\n");
		exit(EXIT_FAILURE);
	}


	Node* temp;
	Node* curr = (*pq)->front;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*pq);
	*pq = NULL;
}


int main()
{
    PriorityQueue* pq = __init__();

    enqueue(&pq, 10, 2);
    enqueue(&pq, 20, 1);
    enqueue(&pq, 30, 3);
    display(pq);

    dequeue(pq);
    display(pq);

    enqueue(&pq, 40, 0);
    enqueue(&pq, 50, 2);
    display(pq);

    dequeue(pq);
    dequeue(pq);
    dequeue(pq);

    display(pq);

    __del__(&pq);

    return EXIT_SUCCESS;
}
