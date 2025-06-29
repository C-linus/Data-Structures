#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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


unsigned int precedence(char operator)
{
	if(operator == '+' || operator == '-')
		return 1;
	else if(operator == '*' || operator == '/')
		return 2;
	else if(operator == '^')
		return 3;
}


bool isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

bool isRightAssociative(char operator)
{
	return operator == '^';
}


char* infixToPostfix(const char* infix)
{
	Stack* st = __init__();

	size_t len = strlen(infix);

	char* postfix = (char *) malloc(len + 1);

	if(postfix == NULL)
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	unsigned int k = 0;
	char ch;

	for(unsigned int i = 0; i < len; i++)
	{
		ch = *(infix + i);

		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
			*(postfix + k++) = ch;
		else if(ch == '(')
			push(&st,ch);
		else if(ch == ')')
		{
			while(!isEmpty(st) && peek(st) != '(')
				*(postfix + k++) = pop(st);
			if(!isEmpty(st))
				pop(st);
			else
			{
				printf("Unmatching parantheses\n");
				exit(EXIT_FAILURE);
			}
		}
		else if(isOperator(ch))
		{
			while(!isEmpty(st) && isOperator(peek(st)) && (precedence(peek(st)) > precedence(ch) || precedence(ch) == precedence(peek(st)) && !isRightAssociative(ch)))
				*(postfix + k++) = pop(st);
			push(&st,ch);
		}
	}
	while(!isEmpty(st))
		*(postfix + k++) = pop(st);

	*(postfix + k) = '\0';
	__del__(&st);
	return postfix;
}



int main()
{
    const char* infix = "a+b*(c^d-e)^(f+g*h)-i";
    char* postfix = infixToPostfix(infix);

    printf("Infix:   %s\n", infix);
    printf("Postfix: %s\n", postfix);

    free(postfix);
    return 0;
}
