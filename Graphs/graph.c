#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ---------- Node Structure (for Stack and Queue) ----------
typedef struct Node {
    unsigned int data;
    struct Node* next;
} Node;

// ---------- Queue (Linked List Implementation) ----------
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

Queue* initQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

bool isEmptyQueue(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q,unsigned int element) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = NULL;

    if (q->rear == NULL)
        q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

unsigned int dequeue(Queue* q) {
    if (isEmptyQueue(q)) {
        printf("Queue Underflow!\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = q->front;
    unsigned int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return data;
}

void freeQueue(Queue* q) {
    Node* curr = q->front;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);
}

// ---------- Stack (Linked List Implementation) ----------
typedef struct Stack {
    Node* sp;
} Stack;

Stack* initStack() {
    Stack* st = (Stack*) malloc(sizeof(Stack));
    st->sp = NULL;
    return st;
}

bool isEmptyStack(Stack* st) {
    return st->sp == NULL;
}

void push(Stack* st, unsigned int element) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = st->sp;
    st->sp = newNode;
}

unsigned int pop(Stack* st) {
    if (isEmptyStack(st)) {
        printf("Stack Underflow!\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = st->sp;
    unsigned int data = temp->data;
    st->sp = st->sp->next;
    free(temp);
    return data;
}

unsigned int peek(Stack* st) {
    if (isEmptyStack(st)) {
        printf("Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return st->sp->data;
}

void freeStack(Stack* st) {
    Node* curr = st->sp;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(st);
}


typedef struct AdjNode
{
	unsigned int vertex;
	struct AdjNode* next;
} AdjNode;

typedef struct Graph
{
	unsigned int numVertices;
	AdjNode** adjLists;
	bool* visited;
} Graph;


AdjNode* createAdjNode(unsigned int vertex)
{
	AdjNode* node = (AdjNode *)malloc(sizeof(AdjNode));

	if(node == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	node->vertex = vertex;
	node->next = NULL;

	return node;
}

Graph* createGraph(unsigned int numVertices)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));

	if(graph == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	graph->adjLists = (AdjNode **)malloc(numVertices * sizeof(AdjNode *));

	if(graph->adjLists == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	graph->numVertices = numVertices;

	graph->visited = (bool *)malloc(numVertices * sizeof(bool));

	if(graph->visited == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < numVertices; i++)
	{
		*(graph->adjLists + i) = NULL;
		*(graph->visited + i) = false;
	}

	return graph;
}

void addEdge(Graph* graph, unsigned int src, unsigned int dest)
{
	AdjNode* node = createAdjNode(dest);
	node->next = *(graph->adjLists + src);
	*(graph->adjLists + src) = node;

	node = createAdjNode(src);
	node->next = *(graph->adjLists + dest);
	*(graph->adjLists + dest) = node;
}

void resetVisited(Graph* graph)
{
	for(unsigned int i = 0; i < graph->numVertices; i++)
		*(graph->visited + i) = false;
}


void BFS(Graph* graph, unsigned int startVertex)
{
	Queue* q = initQueue();
	*(graph->visited + startVertex) = true;
	enqueue(q,startVertex);


	while(!isEmptyQueue(q))
	{
		unsigned int curr = dequeue(q);
		printf("%u ",curr);
		AdjNode* node = *(graph->adjLists + curr);
		while(node != NULL)
		{
			unsigned int vertex = node->vertex;
			if(*(graph->visited + vertex) == false)
			{
				*(graph->visited + vertex) = true;
				enqueue(q, vertex);
			}
			node = node->next;
		}
	}

	freeQueue(q);
}

void DFS(Graph* graph, unsigned int startVertex)
{
	Stack* st = initStack();
	push(st,startVertex);

	while(!isEmptyStack(st))
	{
		unsigned int curr = pop(st);

		if(*(graph->visited + curr) == false)
		{
			printf("%u ",curr);
			*(graph->visited + curr) = true;

			AdjNode* node = *(graph->adjLists + curr);
			while(node != NULL)
			{
				unsigned int vertex = node->vertex;
				if(*(graph->visited + vertex) == false)
					push(st,vertex);
				node = node->next;
			}

		}
	}
	freeStack(st);
}


void freeGraph(Graph* graph)
{
    for (int i = 0; i < graph->numVertices; i++) {
        AdjNode* curr = graph->adjLists[i];
        while (curr) {
            AdjNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}


int main() {
    unsigned int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%u", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Enter number of edges: ");
    scanf("%u", &edges);

    printf("Enter edges (u v):\n");
    for (unsigned int i = 0; i < edges; i++) {
        unsigned int u, v;
        scanf("%u %u", &u, &v);

        if (u >= vertices || v >= vertices) {
            printf("Invalid edge (%u, %u). Vertex out of bounds. Try again.\n", u, v);
            i--; // Repeat this iteration
            continue;
        }

        addEdge(graph, u, v);
    }

    unsigned int start;
    printf("\nEnter starting vertex for DFS: ");
    scanf("%u", &start);
    if (start >= vertices) {
        printf("Invalid start vertex for DFS.\n");
        freeGraph(graph);
        return EXIT_FAILURE;
    }

    printf("DFS traversal: ");
    DFS(graph, start);

    resetVisited(graph);

    printf("\nEnter starting vertex for BFS: ");
    scanf("%u", &start);
    if (start >= vertices) {
        printf("Invalid start vertex for BFS.\n");
        freeGraph(graph);
        return EXIT_FAILURE;
    }

    printf("BFS traversal: ");
    BFS(graph, start);
    printf("\n");
    freeGraph(graph);
    return EXIT_SUCCESS;
}



