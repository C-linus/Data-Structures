#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ---------- TreeNode ----------
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
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


bool isLeafNode(TreeNode* node)
{
	return (node->left == NULL && node->right == NULL);
}

TreeNode* predecessor(TreeNode* node)
{
	while(node && node->right)
		node = node->right;
	return node;
}

TreeNode* successor(TreeNode* node)
{
	while(node && node->left)
		node = node->left;
	return node;
}

TreeNode* insert(TreeNode* root,int key)
{
	TreeNode* newNode = (TreeNode *)malloc(sizeof(TreeNode));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	newNode->left = newNode->right = NULL;
	newNode->data = key;

	if(root == NULL)
		return newNode;

	TreeNode* parent = NULL;
	TreeNode* current = root;

	while(current != NULL)
	{
		parent = current;

		if(current->data > key)
			current = current->left;

		else if(current->data < key)
			current = current->right;

		else
		{
			printf("BSTPropertyViolated: Binary Search Tree Doesn't allow duplicate values!\n");
			printf("Duplicate:%d is ignored!\n",key);
			free(newNode);
			return root;
		}
	}
	if(parent->data > key)
		parent->left = newNode;
	else
		parent->right = newNode;

	return root;
}


TreeNode* search(TreeNode* root, int key)
{
	TreeNode* current = root;
	while(current != NULL)
	{
		if(current->data == key)
			return current;
		else if(current->data > key)
			current = current->left;
		else
			current = current->right;
	}
	return NULL;
}

void inorder(TreeNode* root)
{
	if(root == NULL)
	{
		printf("BST is Empty!\n");
		return;
	}

	Stack *st = initStack();
	TreeNode* current = root;
	TreeNode* temp;

	while(current != NULL || !isEmptyStack(st))
	{
		if(current != NULL)
		{
			push(&st,current);
			current = current->left;
		}
		else
		{
			temp = pop(st);
			printf("%d ",temp->data);
			current = temp->right;
		}
	}
	deleteStack(&st);
}

TreeNode* delete(TreeNode* root, int key)
{
    if(root == NULL)
        return NULL;

    // Special case: root is the leaf and needs to be deleted
    if(key == root->data && isLeafNode(root))
    {
        free(root);
        return NULL;
    }

    TreeNode* parentNode = NULL;
    TreeNode* deleteNode = root;

    // Find node to delete
    while(deleteNode != NULL && deleteNode->data != key)
    {
        parentNode = deleteNode;

        if(deleteNode->data > key)
            deleteNode = deleteNode->left;
        else if(deleteNode->data < key)
            deleteNode = deleteNode->right;
    }

    if(deleteNode == NULL)
    {
        printf("DeletionError: Node with value %d not found!\n", key);
        exit(EXIT_FAILURE);
    }

    // If it's a leaf node
    if(isLeafNode(deleteNode))
    {
        if (parentNode->left == deleteNode)
            parentNode->left = NULL;
        else if (parentNode->right == deleteNode)
            parentNode->right = NULL;

        free(deleteNode);
        return root;
    }
    bool isLastPredecessor = true;

    // Otherwise, keep replacing until it becomes a leaf
    while(!isLeafNode(deleteNode))
    {
        parentNode = deleteNode;

        if(deleteNode->left != NULL)
        {
            deleteNode = predecessor(deleteNode->left);
            parentNode->data = deleteNode->data;
            isLastPredecessor = true;
        }
        else if(deleteNode->right != NULL)
        {
            deleteNode = successor(deleteNode->right);
            parentNode->data = deleteNode->data;
	    isLastPredecessor = false;
        }

    }

    // Adjust parentNode to point before deleteNode
    if(parentNode->left != deleteNode && parentNode->right != deleteNode)
    {
		parentNode = (isLastPredecessor)?parentNode->left:parentNode->right;
		while(parentNode->left != deleteNode && parentNode->right != deleteNode)
		{
			parentNode = (!isLastPredecessor)?parentNode->left:parentNode->right;
		}
    }

    if (parentNode->left == deleteNode)
        parentNode->left = NULL;
    else if (parentNode->right == deleteNode)
        parentNode->right = NULL;

    free(deleteNode);
    return root;
}

void freeTree(TreeNode* root) {
    if (root == NULL)
        return;

    Stack* st = initStack();
    push(&st, root);

    while (!isEmptyStack(st)) {
        TreeNode* curr = pop(st);
        if (curr->left)
            push(&st, curr->left);
        if (curr->right)
            push(&st, curr->right);
        free(curr);
    }
    deleteStack(&st);
}


TreeNode* createBST(int* preorder, size_t length)
{
	Stack* st = initStack();
	TreeNode *t,*p,*root;
	size_t i = 0;

	p = (TreeNode *) malloc(sizeof(TreeNode));

	if(p == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}
	root = p;
	p->data = *(preorder + i++);
	p->left = p->right = NULL;

	while(i < length)
	{
		if(*(preorder + i) < p->data)
		{
			t = (TreeNode *)malloc(sizeof(TreeNode));
			if(t == NULL)
			{
				printf("Memory Allocation Failed!\n");
				exit(EXIT_FAILURE);
			}
			t->data = *(preorder + i++);
			t->left = t->right = NULL;
			p->left = t;
			push(&st,p);
			p = t;
		}
		else
		{
			if(*(preorder + i) > p->data && (isEmptyStack(st) || peek(st)->data > *(preorder + i)))
			{
				t = (TreeNode*)malloc(sizeof(TreeNode));
				if(t == NULL)
				{
					printf("Memory Allocation Failed!\n");
					exit(EXIT_FAILURE);
				}
				t->data = *(preorder + i++);
				t->left = t->right = NULL;
				p->right = t;
				p = t;
			}
			else
				p = pop(st);
		}
	}
	deleteStack(&st);
	return root;
}


int main() {
    TreeNode* root = NULL;

    printf("\n========= Case 1: Skewed tree (all right children) =========\n");
    int values1[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int n1 = sizeof(values1) / sizeof(values1[0]);
    for (int i = 0; i < n1; i++)
        root = insert(root, values1[i]);
    printf("Original inorder: ");
    inorder(root);
    printf("\n");

    root = delete(root, 10);
    inorder(root); printf(" ← After deleting 10\n");

    root = delete(root, 20);
    inorder(root); printf(" ← After deleting 20\n");

    root = delete(root, 40);
    inorder(root); printf(" ← After deleting 40\n");

    root = delete(root, 80);
    inorder(root); printf(" ← After deleting 80\n");

    // Free tree
    while(root != NULL)
        root = delete(root, root->data);


    printf("\n========= Case 2: Skewed tree (all left children) =========\n");
    root = NULL;
    int values2[] = {80, 70, 60, 50, 40, 30, 20, 10};
    int n2 = sizeof(values2) / sizeof(values2[0]);
    for (int i = 0; i < n2; i++)
        root = insert(root, values2[i]);
    printf("Original inorder: ");
    inorder(root);
    printf("\n");

    root = delete(root, 10);
    inorder(root); printf(" ← After deleting 10\n");

    root = delete(root, 70);
    inorder(root); printf(" ← After deleting 70\n");

    root = delete(root, 50);
    inorder(root); printf(" ← After deleting 50\n");

    root = delete(root, 80);
    inorder(root); printf(" ← After deleting 80\n");

    while(root != NULL)
        root = delete(root, root->data);


    printf("\n========= Case 3: Duplicate deletion attempts =========\n");
    root = NULL;
    int values3[] = {50, 30, 70, 20, 40, 60, 80};
    int n3 = sizeof(values3) / sizeof(values3[0]);
    for (int i = 0; i < n3; i++)
        root = insert(root, values3[i]);
    printf("Original inorder: ");
    inorder(root);
    printf("\n");

    root = delete(root, 20);
    inorder(root); printf(" ← After deleting 20\n");


    printf("\n========= Case 4: Complex replacements =========\n");
    root = NULL;
    int values4[] = {50, 30, 70, 10, 40, 35, 45, 65, 90, 85, 100, 95, 110};
    int n4 = sizeof(values4) / sizeof(values4[0]);
    for (int i = 0; i < n4; i++)
        root = insert(root, values4[i]);
    printf("Original inorder: ");
    inorder(root);
    printf("\n");

    root = delete(root, 70);
    inorder(root); printf(" ← After deleting 70\n");

    root = delete(root, 50);
    inorder(root); printf(" ← After deleting 50\n");

    root = delete(root, 100);
    inorder(root); printf(" ← After deleting 100\n");

    while(root != NULL)
        root = delete(root, root->data);


    printf("\n========= Case 5: Remove all nodes one by one =========\n");
    root = NULL;
    int values5[] = {55, 20, 70, 10, 35, 60, 80, 5, 15, 30, 40, 58, 65, 75, 90};
    int n5 = sizeof(values5) / sizeof(values5[0]);
    for (int i = 0; i < n5; i++)
        root = insert(root, values5[i]);
    printf("Original inorder: ");
    inorder(root);
    printf("\n");

    int deletions[] = {5, 10, 15, 20, 30, 35, 40, 55, 58, 60, 65, 70, 75, 80, 90};
    int d = sizeof(deletions) / sizeof(deletions[0]);

    for (int i = 0; i < d; i++) {
        root = delete(root, deletions[i]);
        inorder(root);
        printf(" ← After deleting %d\n", deletions[i]);
    }

    return 0;
}

