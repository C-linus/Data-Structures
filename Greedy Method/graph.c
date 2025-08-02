#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph* createGraph(unsigned int V,unsigned int E)
{
	Graph* graph = (Graph *)malloc(sizeof(Graph));

    	if(graph == NULL)
    	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
    	}

    	graph->V = V;
	graph->E = E;

    	graph->array = (AdjNode**)malloc(V * sizeof(AdjNode*));

	if(graph->array == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

    	for (unsigned int i = 0; i < V; i++)
        	graph->array[i] = NULL;
    	return graph;
}


AdjNode* __initNode__()
{
	AdjNode* newNode = (AdjNode *)malloc(sizeof(AdjNode));

	if(newNode == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}
	return newNode;
}



void addEdge(Graph* graph, unsigned int src, unsigned int dest, unsigned int weight)
{
    	AdjNode* newNode = __initNode__();
    	newNode->dest = dest;
    	newNode->weight = weight;
    	newNode->next = graph->array[src];
    	graph->array[src] = newNode;

    	// Since undirected, add edge in both directions
    	newNode = __initNode__();
    	newNode->dest = src;
    	newNode->weight = weight;
    	newNode->next = graph->array[dest];
    	graph->array[dest] = newNode;
}

void readGraph(Graph* graph)
{


	unsigned int src,dest,weight;
	for(unsigned int i = 0; i < graph->E; i++)
	{
		printf("Enter Edge-%u:\n",i+1);
		printf("Enter src:");
		scanf("%u",&src);
		printf("Enter dest:");
		scanf("%u",&dest);
		printf("Enter cost:");
		scanf("%u",&weight);
		addEdge(graph,src,dest,weight);
	}
}


void freeGraph(Graph* graph)
{
    	for (unsigned int i = 0; i < graph->V; i++)
	{
        	AdjNode* current = graph->array[i];
        	while (current)
		{
            		AdjNode* temp = current;
            		current = current->next;
            		free(temp);
        	}
    	}
    	free(graph->array);
    	free(graph);
}
