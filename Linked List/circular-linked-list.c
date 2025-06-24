#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;


Node* __init__()
{
	Node* dummy = (Node*)malloc(sizeof(Node));

	if(!dummy)
	{
		printf("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	dummy->next = dummy;
	return dummy;
}

size_t __len__(Node* head)
{
	size_t length = 0;
	Node* temp = head->next;

	while(temp != head)
	{
		length++;
		temp = temp->next;
	}
	return length;
}

void append(Node** head, int data)
{
	if(head == NULL)
		*head = __init__();

	Node* newNode = (Node*)malloc(sizeof(Node));

	if(!newNode)
	{
		printf("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->data = data;
	newNode->next = *head;

	Node* temp = *head;
	while(temp->next != *head)
		temp = temp->next;

	temp->next = newNode;
}

// wrap(true)  : wrap around the indices, which are out of bound.
// wrap(false) : follows strict indexing with exceptions
void insert(Node** head,unsigned int pos,int data,bool wrap)
{
	if(*head == NULL)
		*head = __init__();

	size_t length = __len__(*head);

	if(wrap)
		pos = (length == 0)? 0:(pos % (length + 1));

	else{
		if(pos > length)
		{
			printf("Error(IndexOutOfBound): Invalid position %u.\n",pos);
			exit(EXIT_FAILURE);
		}
	}

	Node* newNode = (Node*)malloc(sizeof(Node));

	if(!newNode)
	{
		printf("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->data = data;

	Node* temp = *head;

	for(unsigned int i = 0;i < pos;i++)
		temp = temp->next;


	newNode->next = temp->next;
	temp->next = newNode;
}

void delete(Node** head, unsigned int pos, bool wrap)
{
    if (*head == NULL || (*head)->next == *head) {
        printf("Error: List is empty. Cannot delete.\n");
        return;
    }

    size_t length = __len__(*head);

    if (wrap)
        pos = (length == 0) ? 0 : (pos % (length + 1));
    else {
        if (pos >= length) {
            printf("Error(IndexOutOfBound): Invalid position %u.\n", pos);
            exit(EXIT_FAILURE);
        }
    }

    Node* temp = *head;
    for (unsigned int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    Node* to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
}


void display(Node* head)
{
	if(head->next == head)
	{
		printf("List is empty.\n");
		return;
	}

	Node* temp = head->next;
	while(temp != head)
	{
		printf("%d -> ",temp->data);
		temp = temp->next;
	}
	printf("(HEAD)\n");
}

void __del__(Node** head)
{
	Node* curr = (*head)->next;
	Node* temp;
	while(curr != *head)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(curr);
	*head = NULL;
}


int main()
{
	Node* head1 = __init__();
	append(&head1,20);
	append(&head1,30);
	append(&head1,40);
	append(&head1,50);

	display(head1);

	insert(&head1,9,100,true);
	display(head1);

	delete(&head1,10,true);
	display(head1);
	__del__(&head1);
	return EXIT_SUCCESS;
}
