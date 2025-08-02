#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "disjoint_set.h"
#include "heap.h"


typedef struct Graph
{
	unsigned int vertices;
	unsigned int edges_c;
	Edge* edges;
} Graph;



Graph* initGraph()
{
	unsigned int vertices,edges;

	Graph* graph = (Graph *)malloc(sizeof(Graph));

	printf("Enter no of vertices:");
        scanf("%u",&vertices);

        printf("Enter no of edges:");
        scanf("%u",&edges);

	if(graph == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	graph->edges_c = edges;
	graph->vertices = vertices;

	graph->edges = (Edge *)malloc(sizeof(Edge) * edges);

	if(graph->edges == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < edges; i++)
	{
		printf("Edge-%d:\n",i+1);
		printf("Enter the src:");
		scanf("%u",&((graph->edges + i)->src));
		printf("Enter the dest:");
		scanf("%u",&((graph->edges + i)->dest));
		printf("Enter the cost:");
		scanf("%u",&((graph->edges + i)->weight));
	}

	return graph;
}

void __delGraph__(Graph** graph)
{
	free((*graph)->edges);
	free(*graph);
	*graph = NULL;
}

size_t kruskal(Graph* graph)
{
	Heap* heap = __init__(graph->edges_c,true);

	for(unsigned int i = 0; i < graph->edges_c; i++)
		insert(heap,*(graph->edges + i));

	DisjointSet* ds = __initDS__(graph->vertices);

	size_t minCost = 0;
	unsigned int edgeCount = 0;
	unsigned int x,y;

	Edge* sorted = heapSort(heap);

	for (unsigned int i = 0; i < graph->edges_c && edgeCount < graph->vertices - 1; i++)
	{
		x = find(ds, (sorted + i)->src);
		y = find(ds, (sorted + i)->dest);

    		// Cycle check
    		if (x != y)
    		{
        		minCost += (sorted + i)->weight;
        		unionDS(ds, x, y);
        		edgeCount++;
    		}
	}

	__del__(heap);
	__delDS__(&ds);
	return minCost;
}


int main()
{
	Graph* graph = initGraph();

	size_t minCost = kruskal(graph);
	printf("Minimum Cost:%zu\n",minCost);
	__delGraph__(&graph);
	return EXIT_SUCCESS;
}
