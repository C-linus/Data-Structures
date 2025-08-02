#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"

unsigned int prim(Graph* graph)
{
	unsigned int V = graph->V;
	unsigned int* dist = (unsigned int *)malloc(sizeof(unsigned int) * V);
	bool* inMST =(bool *)calloc(V,sizeof(bool));
	unsigned int minCost = 0;

	for(unsigned int i = 0;i < V;i++)
		*(dist + i) = UINT_MAX;

	*dist = 0;
	int u;

	for(unsigned int count = 0; count < V; count++)
	{
		u = -1;
		for(unsigned int v = 0; v < V; v++)
		{
			if(!(*(inMST + v)) && (u == -1 || *(dist + v) < *(dist + u)))
				u = v;
		}

		*(inMST + u) = true;
		minCost += *(dist + u);
		unsigned int v;

		for(AdjNode* adjacent = *(graph->array + u); adjacent != NULL; adjacent = adjacent->next)
		{
			v = adjacent->dest;
			if(!(*(inMST + v)) && adjacent->weight < *(dist + v))
				*(dist + v) = adjacent->weight;

		}
	}
	free(dist);
	free(inMST);
	return minCost;
}


int main()
{
   	unsigned int V,E;
    	printf("Enter number of vertices: ");
    	scanf("%u", &V);

    	printf("Enter number of edges: ");
        scanf("%u", &E);

    	Graph* graph = createGraph(V,E);

    	readGraph(graph);

    	unsigned int cost = prim(graph);
    	printf("Minimum Spanning Tree Cost: %u\n", cost);

    	freeGraph(graph);

    	return EXIT_SUCCESS;
}
