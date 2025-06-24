#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define INSERT_AT_BEGIN 0
#define INSERT_AT_END -1
#define MAX(a,b)((a>=b)?a:b)
#define MIN(a,b)((a<=b)?a:b)


bool isAsc(int a, int b){return a <= b;}
bool isDesc(int a, int b){return a >= b;}


// Define the node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* __init__(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data)
{
	Node* newNode = __init__(data);

	if(*head == NULL)
	{
		*head = newNode;
		return;
	}

	Node* temp = *head;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = newNode;
}

// Removes all the duplicate element from the linked list
void removedup(Node* head)
{
	Node* curr = head;
	Node* temp;
	while (curr != NULL && curr->next != NULL)
	{
		if(curr->data == curr->next->data)
		{
			temp = curr->next;
			curr->next = curr->next->next;
			free(temp);
		}
		else
		{
			curr = curr->next;
		}
	}
}

void reverse(Node** head)
{
	if(*head == NULL || (*head)->next == NULL)
		return;

	Node* prev = NULL;
	Node* curr = NULL;
	Node* next = *head;

	while(next != NULL)
	{
		prev = curr;
		curr = next;
		next = next->next;
		curr->next = prev;
	}
	*head = curr;
}

bool isSorted(Node* head,bool dir)
{
	bool (*check)(int,int) = (dir)?isDesc:isAsc;
	bool sorted = true;

	Node* prev = head;
	Node* curr = prev->next;
	while(curr != NULL)
	{
		if(!check(prev->data,curr->data))
		{
			sorted = false;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	return sorted;
}

bool hasLoop(Node* head)
{
	Node *fast,*slow;
	fast = slow = head;

	do
	{
		slow = slow->next;
		fast = fast->next;
		fast = (fast != NULL)?fast->next:NULL;
	}while(slow && fast && fast != slow);

	return fast == slow;
}

Node* concat(Node** head1, Node* head2)
{
	if(*head1 == NULL)
	{
		*head1 = head2;
		return *head1;
	}

	Node* temp = *head1;
	while(temp->next != NULL)
		temp = temp->next;

	temp->next = head2;
	return *head1;
}

// Merge Two Sorted Linked List
Node* merge(Node* head1, Node* head2,bool dir)
{
	if(head1 == NULL) return head2;
	if(head2 == NULL) return head1;

	bool (*check)(int,int) = (dir)?isDesc:isAsc;
	Node dummy = (Node) {.data = INT32_MIN,.next = NULL};
	Node* tail = &dummy;

	while(head1 != NULL && head2 != NULL)
	{
		if(check(head1->data,head2->data))
		{
			tail->next = head1;
			head1 = head1->next;
		}
		else
		{
			tail->next = head2;
			head2 = head2->next;
		}
		tail = tail->next;
	}

	tail->next = (head1 != NULL)?head1:head2;
	return dummy.next;
}

void insert(Node** head,int data,int pos)
{
	if(pos < INSERT_AT_END)
	{
		printf("IndexOutOfBoundError: %d, Must be -1 (end) or >=0.\n",pos);
		return;
	}

	Node* newNode = __init__(data);

	// Insertion at begining
	if(pos == INSERT_AT_BEGIN || *head == NULL)
	{
		newNode->next = *head;
		*head = newNode;
		return;
	}

	// Insertion at end
	if(pos == INSERT_AT_END)
	{
		Node* temp = *head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		return;
	}

	// Insertion at specific position
	Node* temp = *head;
	for(unsigned int i = 0; i < pos - 1 && temp != NULL; i++)
		temp = temp->next;

	if(!temp)
	{
		printf("IndexOutOfBoundError: Can't insert a node outside the bound.\n");
		free(newNode);
		return;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

// Insertion at Sorted Linked List
void insertSorted(Node** head,bool dir,int data)
{
	bool (*check)(int,int) = (dir)?isDesc:isAsc;

	Node* newNode = __init__(data);

	// Insert at begining
	if(*head == NULL || !check((*head)->data , data))
	{
		newNode->next = *head;
		*head = newNode;
		return;
	}

	// Insert at any position in sorted order
	while((*head)->next != NULL && check((*head)->next->data,data))
		head = &((*head)->next);

	newNode->next =(*head)->next;
	(*head)->next = newNode;
}

void delete(Node** head,unsigned int pos)
{
	if(*head == NULL)
		return;

	Node* temp = *head;

	// Delete the head
	if(pos == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	// Delete at any position
	for(unsigned int i=0; i < pos-1 && temp != NULL; i++)
		temp = temp->next;

	if(temp == NULL || temp->next == NULL)
		return;

	Node* nodeToDelete = temp->next;
	temp->next = nodeToDelete->next;
	free(nodeToDelete);
}

//
//	1.dir (true) sorts in descending
//	2.dir (false) sorts in ascending

void sort(Node** head,bool dir)
{
	if(*head == NULL || (*head)->next == NULL)
		return;


	bool (*check)(int,int) = (dir)?isDesc:isAsc;
	bool swapped;

	Node **ptr;
	Node *prev;
	Node *curr;

	do
	{
		swapped = false;
		ptr = head;

		while((*ptr)->next != NULL)
		{
			prev = *ptr;
			curr = (*ptr)->next;

			if(!check(prev->data,curr->data))
			{
				prev->next = curr->next;
				curr->next = prev;
				*ptr = curr;
				swapped = true;
			}
			ptr = &((*ptr)->next);
		}
	}while(swapped);
}

void display(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

unsigned int __len__(Node* head)
{
	unsigned int cnt = 0;
	while(head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}

int sum(Node* head)
{
	int total = 0;
	while(head != NULL)
	{
		total += head->data;
		head = head->next;
	}
	return total;
}

int max(Node* head)
{
	int max = INT32_MIN;
	while(head != NULL)
	{
		max = MAX(max,head->data);
		head = head->next;
	}
	return max;
}

int min(Node* head)
{
	int min = INT32_MAX;
	while(head != NULL)
	{
		min = MIN(min,head->data);
		head = head->next;
	}
	return min;
}

Node* search(Node* head,int value)
{
	while(head != NULL)
	{
		if(value == head->data)
			break;
		head = head->next;
	}
	return head;
}

// Improved Linear Search
//	1. Transposition
// 	2. Move To Head


//	1. Transposition
Node* t_search(Node** head, int value)
{
	if(*head == NULL)
		return NULL;

	if((*head)->data == value)
		return *head;

	Node* p1 = NULL;
	Node* p2 = *head;
	Node* curr = (*head)->next;
	while(curr != NULL)
	{
		if(curr->data == value)
		{
			p2->next = curr->next;
			curr->next = p2;

			if(p1 != NULL)
				p1->next = curr;
			else
				*head = curr;
			return curr;
		}
		p1 = p2;
		p2 = curr;
		curr = curr->next;
	}
	return NULL;
}



//	2. Move To Head
Node* h_search(Node** head,int value)
{
	Node* prev = NULL;
	Node* curr = *head;
	while(curr != NULL)
	{
		if(curr->data == value)
		{
			if(prev != NULL)
			{
				prev->next = curr->next;
				curr->next = *head;
				*head = curr;
			}
			return curr;
		}
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

void __del__(Node** head)
{
	Node* curr;
	while(*head != NULL)
	{
		curr = *head;
		*head = (*head)->next;
		free(curr);
	}
	*head = NULL;
}

int main() {
    Node* head = NULL;
    bool dir = true;

    append(&head, 10);
    append(&head, 25);
    append(&head, 3);
    append(&head, -40);
    append(&head, 5);

    display(head);
    printf("Maximum value:%d\n",max(head));
    printf("Minimum value:%d\n",min(head));
    Node* n = t_search(&head,-10);
    display(head);
    if(n != NULL)
    	printf("Search of %d at %p\n",n->data,n);
    else
	printf("Not found\n");
    insert(&head,60,2);
    display(head);
    sort(&head,dir);
    printf("Sorted List:\n");
    display(head);
    insertSorted(&head,dir,25);
    display(head);
    delete(&head,6);
    display(head);
    printf("List is %s in %s\n",(isSorted(head,dir))?"Sorted":"Not Sorted",(dir)?"Descending Order": "Ascending Order");
    removedup(head);
    display(head);
    reverse(&head);
    display(head);

    Node* head2 = NULL;


    append(&head2,21);
    append(&head2,33);
    append(&head2,14);
    append(&head2,41);
    append(&head2,77);

    sort(&head,dir);
    sort(&head2,dir);

    printf("Node-1: ");
    display(head);
    printf("Node-2: ");
    display(head2);


    Node* head3 = merge(head,head2,dir);
    printf("Node-3: ");
    display(head3);

    Node* head4 = __init__(10);
    append(&head4,34);
    append(&head4,33);

//    head4->next->next->next = head4;
    printf("Node4 %s Loop.\n",(hasLoop(head4))?"has":"has no");

    __del__(&head3);
   return EXIT_SUCCESS;
}
