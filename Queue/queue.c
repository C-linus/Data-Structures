#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue
{
	int *data;
	int front;
	int rear;
	int size;
} Queue;

Queue* __init__(int size)
{
	Queue* q =(Queue *)malloc(sizeof(Queue));

	if(q == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->data = (int *)malloc(size * sizeof(int));

	if(q->data == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	q->front = q->rear = -1;
	q->size = size;
	return q;
}


bool isEmpty(Queue* q)
{
	return q->front == q->rear;
}

bool isFull(Queue* q)
{
	return q->rear == (q->size - 1);
}

void enqueue(Queue** q, int element)
{
	if(*q == NULL)
	{
		int size;
		printf("Warning:Queue is NULL \nAllocating new queue\nEnter size: ");
		scanf("%d",&size);
		*q = __init__(size);
	}


	if(isFull(*q))
	{
		printf("Queue Overflow! cannot enqueue %d\n",element);
		exit(EXIT_FAILURE);
	}

	(*q)->rear++;
	*((*q)->data + (*q)->rear) = element;
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
		printf("Queue Underflow!, Cannot dequeue\n");
		exit(EXIT_FAILURE);
	}

	int removed = *(q->data + ++q->front);

	if (q->front == q->rear)
        	q->front = q->rear = -1;
	return removed;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    for (int i = q->front + 1; i <= q->rear; i++) {
        printf("%d ", *(q->data + i));
    }
    printf("\n");
}

void __del__(Queue** q)
{
	free((*q)->data);
	free(*q);
	*q = NULL;
}


int main() {
    int size;
    printf("Enter size of queue: ");
    scanf("%d", &size);

    Queue *q = __init__(size);

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

    // Free memory
    __del__(&q);

    return 0;


}
