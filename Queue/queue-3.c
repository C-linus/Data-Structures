#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;


typedef struct Stack
{
	Node* sp;
}Stack;

Stack* initStack()
{
	Stack* st = (Stack *)malloc(sizeof(Stack));

	if(st == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	st->sp = NULL;
	return st;
}


bool isEmptyStack(Stack* st)
{
	return st->sp == NULL;
}

void push(Stack* st,int element)
{
	Node* newNode = (Node *) malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->next = st->sp;
	newNode->data = element;
	st->sp = newNode;
}

int pop(Stack* st)
{
	if(isEmptyStack(st))
	{
		printf("Stack Underflow! Cannot pop anything!\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = st->sp;
	int popped = temp->data;
	st->sp = temp->next;
	free(temp);
	return popped;
}

int peek(Stack* st)
{
	if(isEmptyStack(st))
	{
		printf("Stack is Empty!\n");
		exit(EXIT_FAILURE);
	}
	return st->sp->data;
}

void freeStack(Stack* st)
{
	if(st == NULL)
	{
		printf("Cannot Deallocate a NULL Object!\n");
		exit(EXIT_FAILURE);
	}

	Node* temp;
	while(st->sp != NULL)
	{
		temp = st->sp;
		st->sp = temp->next;
		free(temp);
	}
	free(st);
}

typedef struct Queue
{
	Stack* s1;
	Stack* s2;
} Queue;


Queue* initQueue()
{
	Queue* q = (Queue *)malloc(sizeof(Queue));

	if(q == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->s1 = initStack();
	q->s2 = initStack();
	return q;
}

bool isEmptyQueue(Queue* q)
{
	return isEmptyStack(q->s1) && isEmptyStack(q->s2);
}


void enqueue(Queue* q,int element)
{

	if(q == NULL)
	{
		printf("Cannot enqueue a NULL Object!\n");
		exit(EXIT_FAILURE);
	}
	push(q->s1,element);
}


int dequeue(Queue* q)
{
	if(isEmptyQueue(q))
	{
		printf("Queue Underflow! Cannot dequeue\n");
		exit(EXIT_FAILURE);
	}


	if(isEmptyStack(q->s2))
	{
		while(!isEmptyStack(q->s1))
			push(q->s2,pop(q->s1));
	}

	return pop(q->s2);
}

void display(Queue* q)
{
	if(q == NULL)
	{
		printf("Queue is Empty!\n");
		return;
	}


	printf("Queue Elements: ");
	Node* temp = q->s2->sp;
	while(temp != NULL)
	{
		printf("%d ",temp->data);
		temp = temp->next;
	}



	Stack* tempStack = initStack();

	while(!isEmptyStack(q->s1))
		push(tempStack,pop(q->s1));

	int popped;
	while(!isEmptyStack(tempStack))
	{
		popped = pop(tempStack);
		printf("%d ",popped);
		push(q->s1,popped);
	}
	printf("\n");
	freeStack(tempStack);
}


void freeQueue(Queue** q)
{
	if(q == NULL || *q == NULL)
	{
		printf("Cannot Deallocate a NULL Object!\n");
		return;
	}

	free((*q)->s1);
	free((*q)->s2);
	free(*q);
	*q = NULL;
}


int main()
{
    Queue* q = initQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);

    dequeue(q);
    display(q);

    enqueue(q, 40);
    enqueue(q, 50);
    display(q);

    dequeue(q);
    dequeue(q);
    dequeue(q);

    display(q);

    freeQueue(&q);

    return EXIT_SUCCESS;
}

