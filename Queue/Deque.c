#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node
{
	int data;
	struct Node* prev;
	struct Node* next;
} Node;


typedef struct Deque
{
	Node* front;
	Node* rear;
} Deque;



Deque* __init__()
{
	Deque* dq = (Deque *) malloc(sizeof(Deque));

	if(dq == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	dq->front = dq->rear = NULL;
	return dq;
}


bool isEmpty(Deque* dq)
{
	return dq->front == NULL;
}

void insertFront(Deque** dq,int element)
{

	if(*dq == NULL)
	{
		printf("Warning: Deque is NULL \n Allocating New Deque\n");
		*dq = __init__();
	}


	Node* newNode = (Node *) malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->prev = NULL;
	newNode->data = element;
	newNode->next = (*dq)->front;

	if(isEmpty(*dq))
	{
		(*dq)->front = (*dq)->rear = newNode;
	}
	else
	{
		(*dq)->front->prev = newNode;
		(*dq)->front = newNode;
	}
}


int insertRear(Deque** dq,int element)
{
	if(*dq == NULL)
	{
		printf("Warning: Deque is NULL \n Allocating New Deque\n");
		*dq = __init__();
	}

	Node* newNode = (Node *) malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->prev = (*dq)->rear;
	newNode->data = element;
	newNode->next = NULL;

	if(isEmpty(*dq))
	{
		(*dq)->front = (*dq)->rear = newNode;
	}
	else
	{
		(*dq)->rear->next = newNode;
		(*dq)->rear = newNode;
	}
}


int deleteFront(Deque* dq)
{
	if(dq == NULL || isEmpty(dq))
	{
		printf("Deque Underflow! Cannot delete NULL Object\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = dq->front;
	int removed = temp->data;
	dq->front = temp->next;

	if(isEmpty(dq))
	{
		dq->rear = NULL;
	}
	else
	{
		dq->front->prev = NULL;
	}

	free(temp);
	return removed;
}


int deleteRear(Deque* dq)
{
	if(dq == NULL || isEmpty(dq))
	{
		printf("Deque Underflow! Cannot delete NULL Object\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = dq->rear;
	int removed = temp->data;
	dq->rear = temp->prev;

	if(dq->rear == NULL)
	{
		dq->front = NULL;
	}
	else
	{
		dq->rear->next = NULL;
	}

	free(temp);
	return removed;
}


void display(Deque* dq)
{
	if(isEmpty(dq))
	{
		printf("Deque is Empty!\n");
		return;
	}

	printf("Deque Elements: ");
	Node* curr = dq->front;
	while(curr != NULL)
	{
		printf("%d ",curr->data);
		curr = curr->next;
	}
	printf("\n");
}

void __del__(Deque** dq)
{
	if(dq == NULL || *dq == NULL)
	{
		printf("Cannot Deallocate the NULL Object!\n");
		return;
	}

	Node* temp;
	Node* curr = (*dq)->front;

	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*dq);
	*dq = NULL;
}


int main()
{
    Deque* dq = __init__();

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertFront(&dq, 1);
    display(dq);

    deleteFront(dq);
    display(dq);

    deleteRear(dq);
    display(dq);

    insertRear(&dq, 30);
    insertFront(&dq, 0);
    display(dq);

    // Free memory
    __del__(&dq);

    return EXIT_SUCCESS;
}
