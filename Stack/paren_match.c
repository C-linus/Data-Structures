#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Type:Node
typedef struct Node
{
        char data;
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

void push(Stack** st,char element)
{
        if(*st == NULL)
                *st =   __init__();

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


char pop(Stack* st)
{
        if(st == NULL || st->sp == NULL)
        {
                printf("Stack UnderFlow: Cannot pop elements!\n");
                exit(EXIT_FAILURE);
        }

        Node* temp = st->sp;
        char element = temp->data;
        st->sp = temp->next;
        free(temp);
        return element;
}

bool isEmpty(Stack* st)
{
        return st->sp == NULL;
}

char peek(Stack* st)
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


bool isMatch(char open, char close)
{
	return (open == '(' && close == ')') || (open == '{' && close == '}' ) || (open == '[' && close == ']');
}


bool isValidParen(const char* exp)
{
	Stack* st = __init__();
	char open;
	for(int i = 0; *(exp + i) != '\0'; i++)
	{
		char ch = *(exp + i);

		if(ch == '(' || ch == '{' || ch == '[')
			push(&st,ch);

		else if(ch == ')' || ch == '}' || ch == ']')
		{
			if(isEmpty(st))
			{
				__del__(&st);
				return false;
			}
			open = pop(st);

			if(!isMatch(open,ch))
			{
				__del__(&st);
				return false;
			}
		}
	}
	bool valid = isEmpty(st);
	__del__(&st);
	return valid;
}


int main() {
    const char* expr = "{[()]}";

    if (isValidParen(expr))
        printf("Valid Parentheses!\n");
    else
        printf("Invalid Parentheses!\n");

    return 0;
}
