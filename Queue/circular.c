#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Queue
{
	int* data;
	int front;
	int rear;
	int size;
} Queue;


Queue* __init__(int size)
{
	Queue* q = (Queue *)malloc(sizeof(Queue));

	if(q == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->data = (int *)malloc(sizeof(int)*size);

	if(q->data == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->front = q->rear = 0;
	q->size = size;
	return q;
}

bool isEmpty(Queue* q)
{
	return q->rear == q->front;
}

bool isFull(Queue* q)
{
	return (q->rear + 1) % q->size == q->front;
}

void enqueue(Queue** q, int element)
{
	if(*q == NULL)
	{
		int size;
		printf("Warning: Queue is NULL\nAllocating new queue\nEnter size: ");
		scanf("%d",&size);
		*q = __init__(size + 1);
	}

	if(isFull(*q))
	{
		printf("Queue Overflow! Cannot enqueue %d\n",element);
		exit(EXIT_FAILURE);
	}

	*((*q)->data + (*q)->rear) = element;
	(*q)->rear = ((*q)->rear + 1) % (*q)->size;
}

int dequeue(Queue* q)
{
	if(q == NULL)
	{
		printf("Can't dequeue from a NULL object!\n");
		exit(EXIT_FAILURE);
	}

	if(isEmpty(q))
	{
		printf("Queue Underflow! Cannot dequeue\n");
		exit(EXIT_FAILURE);
	}

	int removed = *(q->data + q->front);
	q->front = (q->front + 1) % q->size;
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
	int i = q->front;
	while(i != q->rear)
	{
		printf("%d ",*(q->data + i));
		i = (i + 1) % q->size;
	}
	printf("\n");
}

void __del__(Queue** q)
{
	if(*q == NULL || q == NULL)
	{
		printf("Can't free NULL object\n");
		exit(EXIT_FAILURE);
	}
	free((*q)->data);
	free(*q);
	*q = NULL;
}

int main() {
    int size;
    printf("Enter size of queue: ");
    scanf("%d", &size);

    Queue *q = __init__(size + 1);

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


