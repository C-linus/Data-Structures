#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




// TreeNode
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// QueueNode
typedef struct Node {
    TreeNode* data;
    struct Node* next;
} Node;

// Alias names for QueueNode & StackNode
typedef Node QueueNode;
typedef Node StackNode;

// Queue
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Stack
typedef struct Stack
{
	StackNode* sp;
} Stack;

void flushStdin() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


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

TreeNode* peek(Stack* st)
{
	if(st == NULL || isEmptyStack(st))
	{
		printf("Stack is empty\n");
		exit(EXIT_FAILURE);
	}

	return st->sp->data;
}

void push(Stack** st, TreeNode* element)
{
	if(st == NULL)
	{
		printf("Can't Push a NULL Object!\n");
		exit(EXIT_FAILURE);
	}

	if(*st == NULL)
	{
		printf("Warning: Stack is NULL! Allocating new Stack.\n");
		*st = initStack();
	}

	StackNode* newNode = (StackNode *) malloc(sizeof(StackNode));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = element;
	newNode->next = (*st)->sp;
	(*st)->sp = newNode;
}

TreeNode* pop(Stack* st)
{
	if(st == NULL || isEmptyStack(st))
	{
		printf("Stack Underflow! Cannot pop\n");
		exit(EXIT_FAILURE);
	}

	StackNode* temp = st->sp;
	TreeNode* removed = temp->data;
	st->sp = temp->next;
	free(temp);
	return removed;
}

// Queue functions
Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    return q;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

size_t QueueSize(Queue* q)
{
	size_t length = 0;
	for(QueueNode* curr = q->front; curr != NULL; curr = curr->next)
		length++;

	return length;
}

void enqueue(Queue** q, TreeNode* element) {
    if (q == NULL) {
        printf("Can't enqueue a NULL object\n");
        exit(EXIT_FAILURE);
    }
    if (*q == NULL) {
        printf("Warning: Queue is NULL! Allocating new Queue.\n");
        *q = initQueue();
    }

    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = element;
    newNode->next = NULL;

    if ((*q)->rear == NULL)
        (*q)->front = (*q)->rear = newNode;
    else {
        (*q)->rear->next = newNode;
        (*q)->rear = newNode;
    }
}

TreeNode* dequeue(Queue* q) {
    if (q == NULL || isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue\n");
        exit(EXIT_FAILURE);
    }

    QueueNode* temp = q->front;
    TreeNode* removed = temp->data;
    q->front = temp->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return removed;
}

void deleteQueue(Queue** q) {
    if (q == NULL || *q == NULL) {
        return;
    }

    QueueNode* curr = (*q)->front;
    while (curr != NULL) {
        QueueNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(*q);
    *q = NULL;
}

void deleteStack(Stack** st)
{
	if(st == NULL || *st == NULL)
		return;

	StackNode* curr = (*st)->sp;
	StackNode* temp;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(*st);
	*st = NULL;
}

// Iterative delete function for tree
void deleteTree(TreeNode* root) {

	if(root == NULL)
		return;

	Stack* st = initStack();
	push(&st,root);
	while(!isEmptyStack(st))
	{
		TreeNode* curr = pop(st);
		if(curr->left != NULL)
			push(&st,curr->left);
		if(curr->right != NULL)
			push(&st,curr->right);
		free(curr);
	}
	deleteStack(&st);
}

TreeNode* createTree() {
    int data;
    printf("Enter root value: ");
    while (scanf("%d", &data) != 1) {
        flushStdin();
        printf("Invalid Integer Input!\n");
        printf("Enter root value: ");
    }
    flushStdin();

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }
    root->data = data;
    root->left = root->right = NULL;

    Queue* q = initQueue();
    enqueue(&q, root);

    while (!isEmpty(q)) {
        TreeNode* curr = dequeue(q);
        char choice;

        // Left child
        while (true) {
            printf("Does %d have a left child? (Y/N): ", curr->data);
            if (scanf(" %c", &choice) == 1 && (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')) {
                break;
            }
            flushStdin();
            printf("Invalid Character Input!\n");
        }
        flushStdin();

        if (choice == 'Y' || choice == 'y') {
            printf("Enter value for left child of %d: ", curr->data);
            while (scanf("%d", &data) != 1) {
                flushStdin();
                printf("Invalid Integer Input!\n");
                printf("Enter value for left child of %d: ", curr->data);
            }
            flushStdin();
            TreeNode* leftChild = (TreeNode*)malloc(sizeof(TreeNode));
            if (leftChild == NULL) {
                printf("Memory Allocation Failed!\n");
                exit(EXIT_FAILURE);
            }
            leftChild->data = data;
            leftChild->left = leftChild->right = NULL;
            curr->left = leftChild;
            enqueue(&q, leftChild);
        }

        // Right child
        while (true) {
            printf("Does %d have a right child? (Y/N): ", curr->data);
            if (scanf(" %c", &choice) == 1 && (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')) {
                break;
            }
            flushStdin();
            printf("Invalid Character Input!\n");
        }
        flushStdin();

        if (choice == 'Y' || choice == 'y') {
            printf("Enter value for right child of %d: ", curr->data);
            while (scanf("%d", &data) != 1) {
                flushStdin();
                printf("Invalid Integer Input!\n");
                printf("Enter value for right child of %d: ", curr->data);
            }
            flushStdin();
            TreeNode* rightChild = (TreeNode*)malloc(sizeof(TreeNode));
            if (rightChild == NULL) {
                printf("Memory Allocation Failed!\n");
                exit(EXIT_FAILURE);
            }
            rightChild->data = data;
            rightChild->left = rightChild->right = NULL;
            curr->right = rightChild;
            enqueue(&q, rightChild);
        }
    }

    deleteQueue(&q);
    return root;
}

// Traversals
void preorder(TreeNode* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(TreeNode* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);

}

// Iterative Traversals

void preorder_iter(TreeNode* root)
{
	if(root == NULL)
		return;

	Stack *st = initStack();
	push(&st,root);
	TreeNode* temp;

	while(!isEmptyStack(st))
	{
		temp = pop(st);
		printf("%d ",temp->data);

		if(temp->right != NULL)
			push(&st,temp->right);

		if(temp->left != NULL)
			push(&st,temp->left);
	}
	deleteStack(&st);
}

void inorder_iter(TreeNode* root)
{
	if(root == NULL)
		return;

	Stack* st = initStack();

	while(root != NULL || !isEmptyStack(st))
	{
		if(root != NULL)
		{
			push(&st,root);
			root = root->left;
		}
		else
		{
			root = pop(st);
			printf("%d ",root->data);
			root = root->right;
		}
	}
	deleteStack(&st);
}

void postorder_iter(TreeNode* root)
{
	if(root == NULL)
		return;

	Stack* st = initStack();
	TreeNode* peekNode;
	TreeNode* lastVisited;

	while(root != NULL || !isEmptyStack(st))
	{
		if(root != NULL)
		{
			push(&st,root);
			root = root->left;
		}
		else
		{
			peekNode = peek(st);
			if(peekNode->right != NULL && lastVisited != peekNode->right)
				root = peekNode->right;
			else
			{
				printf("%d ",peekNode->data);
				lastVisited = pop(st);
			}
		}
	}
	deleteStack(&st);
}

void levelorder_iter(TreeNode* root)
{
	if(root == NULL)
		return;

	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* temp;

	while(!isEmpty(q))
	{
		temp = dequeue(q);
		printf("%d ",temp->data);

		if(temp->left != NULL)
			enqueue(&q,temp->left);
		if(temp->right != NULL)
			enqueue(&q,temp->right);
	}
	deleteQueue(&q);
}

// Counters

// Count the no.of nodes in the tree
size_t count_all(TreeNode* root)
{

	if(root == NULL)
		return 0;

	size_t length;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);
		length++;
		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

// Count the height of the tree
long int height(TreeNode* root)
{
	if(root == NULL)
		return -1;

	long int  height = -1;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;
	size_t length;

	while(!isEmpty(q))
	{
		length = QueueSize(q);

		for(size_t i = 1; i <= length; i++)
		{
			curr = dequeue(q);
			if(curr->left != NULL)
				enqueue(&q,curr->left);
			if(curr->right != NULL)
				enqueue(&q,curr->right);
		}
		height++;
	}
	deleteQueue(&q);
	return length;
}

// Count all the nodes with degree:0
size_t count_leaf(TreeNode* root)
{
	if(root == NULL)
		return 0;

	size_t length = 0;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);

		if(curr->left == NULL && curr->right == NULL)
			length++;
		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

// Count all the nodes with degree:2
size_t count_full(TreeNode* root)
{
	if(root == NULL)
		return 0;

	size_t length = 0;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);

		if(curr->left != NULL && curr->right != NULL)
			length++;

		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

// Count all the nodes with degree:1
size_t count_one(TreeNode* root)
{
	if(root == NULL)
		return 0;

	size_t length = 0;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);

		if(curr->left ^ curr->right)
			length++;

		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

// Count all the nodes with at least one children
size_t count_nonLeaf(TreeNode* root)
{

	if(root == NULL)
		return 0;

	size_t length = 0;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);

		if(curr->left != NULL || curr->right != NULL)
			length++;

		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

// Count all the nodes with Strict Degree either 0 or 2
size_t count_strict(TreeNode* root)
{

	if(root == NULL)
		return 0;

	size_t length = 0;
	Queue* q = initQueue();
	enqueue(&q,root);
	TreeNode* curr;

	while(!isEmpty(q))
	{
		curr = dequeue(q);

		if(!(curr->left ^ curr->right))
			length++;

		if(curr->left != NULL)
			enqueue(&q,curr->left);
		if(curr->right != NULL)
			enqueue(&q,curr->right);
	}
	deleteQueue(&q);
	return length;
}

int main() {
    TreeNode* root = createTree();

    printf("Recursive Traversals\n");

    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    printf("\nIterative Traversals\n");

    printf("\nPreorder Traversal: ");
    preorder_iter(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorder_iter(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder_iter(root);
    printf("\n");

    printf("Level Order Traversal: ");
    levelorder_iter(root);
    printf("\n");

    deleteTree(root);

    return 0;
}
