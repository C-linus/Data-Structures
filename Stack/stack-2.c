#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Type:Node
typedef struct Node
{
	int data;
	struct Node* next;
} Node;


//Type:Stack
typedef struct Stack
{
	Node* sp;
} Stack;

Stack* __init__()
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

void push(Stack** st,int element)
{
	if(*st == NULL)
		*st =	__init__();

	Node* newNode = (Node *)malloc(sizeof(Node));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->data = element;
	newNode->next =(*st)->sp;

	(*st)->sp = newNode;
}


int pop(Stack* st)
{
	if(st == NULL || st->sp == NULL)
	{
		printf("Stack UnderFlow: Cannot pop elements!\n");
		exit(EXIT_FAILURE);
	}

	Node* temp = st->sp;
	int element = temp->data;
	st->sp = temp->next;
	free(temp);
	return element;
}

bool isEmpty(Stack* st)
{
	return st->sp == NULL;
}

int peek(Stack* st)
{
	if(st == NULL || st->sp == NULL)
	{
		printf("Stack is Empty!\n");
		exit(EXIT_FAILURE);
	}

	return st->sp->data;
}

void __del__(Stack** st)
{
	if(*st == NULL)
		return;

	Node* curr = (*st)->sp;
	Node* temp;

	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*st);
	*st = NULL;
}

void display(Stack* st)
{
	if(st == NULL || st->sp == NULL)
	{
		printf("Stack is Empty!\n");
		return;
	}

	printf("%d -> (Stack Pointer)\n",st->sp->data);

	Node* curr = st->sp->next;

	while(curr != NULL)
	{
		printf("%d\n",curr->data);
		curr = curr->next;
	}

}


int main()
{
    Stack* myStack = NULL;
    int choice, element;

    while (1)
    {
        printf("\n---- Stack Menu ----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Is Empty?\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter element to push: ");
                scanf("%d", &element);
                push(&myStack, element);
                break;

            case 2:
                if (myStack == NULL || isEmpty(myStack))
                    printf("Stack Underflow!\n");
                else
                    printf("Popped element: %d\n", pop(myStack));
                break;

            case 3:
                if (myStack == NULL || isEmpty(myStack))
                    printf("Stack is Empty!\n");
                else
                    printf("Top element: %d\n", peek(myStack));
                break;

            case 4:
                if (myStack == NULL || isEmpty(myStack))
                    printf("Stack is Empty!\n");
                else
                    printf("Stack is NOT Empty.\n");
                break;

            case 5:
                display(myStack);
                break;

            case 6:
                __del__(&myStack);
                printf("Exiting and freeing memory...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
