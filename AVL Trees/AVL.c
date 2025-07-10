#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



// ---------- TreeNode ----------
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
} TreeNode;

// ---------- StackNode ----------
typedef struct Node {
    TreeNode* data;
    struct Node* next;
} Node;

typedef Node StackNode;

typedef struct Stack {
    StackNode* sp;
} Stack;

Stack* initStack() {
    Stack* st = (Stack*)malloc(sizeof(Stack));
    if (!st) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }
    st->sp = NULL;
    return st;
}

bool isEmptyStack(Stack* st) {
    return st->sp == NULL;
}

TreeNode* peek(Stack* st)
{
        if(isEmptyStack(st))
        {
                printf("Stack is Empty!\n");
                exit(EXIT_FAILURE);
        }
        return st->sp->data;
}

void push(Stack** st, TreeNode* element) {
    if (*st == NULL)
        *st = initStack();

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = element;
    newNode->next = (*st)->sp;
    (*st)->sp = newNode;
}

TreeNode* pop(Stack* st) {
    if (st == NULL || isEmptyStack(st)) {
        printf("Stack Underflow! Cannot pop\n");
        exit(EXIT_FAILURE);
    }

    StackNode* temp = st->sp;
    TreeNode* removed = temp->data;
    st->sp = temp->next;
    free(temp);
    return removed;
}

void deleteStack(Stack** st) {
    if (!st || !*st)
        return;

    StackNode* curr = (*st)->sp;
    while (curr) {
        StackNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(*st);
    *st = NULL;
}



// ------------- AVL Helpers -------------

int max(int a, int b)
{
	return (a > b)? a : b;
}

int height(TreeNode* node)
{
	if(node == NULL)
		return 0;
	return node->height;
}

TreeNode* rightRotate(TreeNode* y)
{
	TreeNode* x = y->left;
	TreeNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left) , height(y->right)) + 1;
	x->height = max(height(x->left) , height(x->right)) + 1;

	return x;

}

TreeNode* leftRotate(TreeNode* x)
{

	TreeNode* y = x->right;
	TreeNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left) , height(x->right)) + 1;
	y->height = max(height(y->left) , height(y->right)) + 1;

	return y;
}


int getBalance(TreeNode* node)
{
	if(node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}


TreeNode* newNode(int data)
{
	TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));

	if(node == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	node->data = data;
	node->left = node->right = NULL;
	return node;
}

TreeNode* insert(TreeNode* root, int data)
{
	if(root == NULL)
		return newNode(data);

	Stack* st = initStack();
	TreeNode* parent = NULL;
	TreeNode* current = root;

	while(current != NULL)
	{
		push(&st,current);
		parent = current;

		if(current->data > data)
			current = current->left;
		else if(current->data < data)
			current = current->right;
		else
		{
			printf("Error: BST Property Violated Insertion Failed (Duplicate Value %d)\n",data);
			return root;
		}
	}



	TreeNode* newnode = newNode(data);

	if(data < parent->data)
		parent->left = newnode;
	else
		parent->right = newnode;


	while(!isEmptyStack(st))
	{
		TreeNode* node = pop(st);
		node->height = max(height(node->left) , height(node->right)) + 1;
		int balance = getBalance(node);

		// LL Imbalance
		if(balance > 1 && data < node->left->data)
		{
			if(!isEmptyStack(st))
			{
				TreeNode* top = peek(st);
				if(top->left == node)
					top->left = rightRotate(node);
				else
					top->right = rightRotate(node);
			}
			else
				root = rightRotate(node);

		}

		// LR Imbalance
		else if(balance > 1 && data > node->left->data)
		{
			node->left = leftRotate(node->left);
			if(!isEmptyStack(st))
			{
				TreeNode* top = peek(st);
				if(top->left == node)
					top->left = rightRotate(node);
				else
					top->right = rightRotate(node);
			}
			else
				root = rightRotate(node);
		}

		// RR Imbalance
		else if(balance < -1 && data > node->right->data)
		{
			if(!isEmptyStack(st))
			{
				TreeNode* top = peek(st);
				if(top->left == node)
					top->left = leftRotate(node);
				else
					top->right = leftRotate(node);
			}
			else
				root = leftRotate(node);
		}

		//RL Imbalance
		else if(balance < -1 && data < node->right->data)
		{
			node->right = rightRotate(node->right);
			if(!isEmptyStack(st))
			{
				TreeNode* top = peek(st);
				if(top->left == node)
					top->left = leftRotate(node);
				else
					top->right = leftRotate(node);
			}
			else
				root = leftRotate(node);
		}


	}
	deleteStack(&st);
	return root;
}


void inOrder(TreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
	printf("%d ",root->data);
        inOrder(root->right);
    }
}

// ---------- Main ----------
int main() {
    TreeNode* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal of AVL tree:\n");
    inOrder(root);
    printf("\n");

    return 0;
}

