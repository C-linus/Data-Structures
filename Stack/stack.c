#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
    int size;
    int sp;
    int *arr;
} Stack;

Stack* __init__(int size)
{
    Stack* st = (Stack *)malloc(sizeof(Stack));

    if(!st)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    st->size = size;
    st->sp = -1;
    st->arr = (int *)malloc(sizeof(int) * size);

    if(!(st->arr))
    {
        printf("Memory allocation failed!\n");
        free(st);
        exit(EXIT_FAILURE);
    }

    return st;
}

void __del__(Stack** st)
{
    if (st == NULL || *st == NULL) {
        printf("Can't free a NULL object!\n");
        return;
    }

    if ((*st)->arr != NULL) {
        free((*st)->arr);
    }

    free(*st);
    *st = NULL; 
}

bool isFull(Stack* st)
{
    if(st == NULL)
    {
        printf("Stack is NULL!\n");
        exit(EXIT_FAILURE);
    }

    return (st->sp == st->size - 1);
}

bool isEmpty(Stack* st)
{
    if(st == NULL)
    {
        printf("Stack is NULL!\n");
        exit(EXIT_FAILURE);
    }

    return (st->sp == -1);
}

void push(Stack *st, int element)
{

    if(isFull(st))
    {
        printf("Stack Overflow! Cannot push %d\n",element);
        exit(EXIT_FAILURE);
    }


    *(st->arr + ++st->sp) = element;
}

int pop(Stack* st)
{

    if(isEmpty(st))
    {
        printf("Stack Underflow! Cannot pop \n");
        exit(EXIT_FAILURE);
    }

    return *(st->arr + st->sp--);
     
}

int peek(Stack* st)
{
    if(isEmpty(st))
    {
        printf("Stack is Empty\n");
        exit(EXIT_FAILURE);
    }

    return *(st->arr + st->sp);
}

void display(Stack* st)
{
    if(isEmpty(st)) return;

    printf("\nStack (Top to Bottom): \n");
    printf("%d -> (Stack pointer)\n",*(st->arr + st->sp));
    for(int i = st->sp - 1; i > -1; i--)
    {
        printf("%d\n",*(st->arr + i));
    }
}

int main() {
    int size;

    do {
        printf("Enter the size of the stack: ");
        scanf("%d", &size);
    } while (size <= 0);

    Stack* st = __init__(size);

    int choice, value;

    do {
        printf("\n------ STACK MENU ------\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(st, value);
                break;
            case 2:
                value = pop(st);
                printf("Popped: %d\n", value);
                break;
            case 3:
                value = peek(st);
                printf("Top element: %d\n", value);
                break;
            case 4:
                display(st);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    __del__(&st);
    return EXIT_SUCCESS;
}