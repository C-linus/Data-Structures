#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"


unsigned int* dijkstra(Graph* graph,unsigned int start)
{
	unsigned int V = graph->V;
	unsigned int* dist = (unsigned int *)malloc(V * sizeof(unsigned int));
	bool* visited = (bool *)malloc(V * sizeof(bool));

	if(dist == NULL || visited == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}


	for(unsigned int i = 0; i < V; i++)
	{
		*(dist + i) = UINT_MAX;
		*(visited + i) = false;
	}

	*(dist + start) = 0;
	int u;

	for(unsigned int count = 1; count < V;count++)
	{

		u = -1;
		for(unsigned int v = 0; v < V; v++)
		{
			if(!(*(visited + v)) && (u == -1 || *(dist + v) < *(dist + u)))
				u = v;
		}


		*(visited + u) = true;
		unsigned int v;
		for(AdjNode* adjacent = *(graph->array + u);adjacent != NULL;adjacent = adjacent->next)
		{

			v = adjacent->dest;
			if(!(*(visited + v)) && *(dist + u) != UINT_MAX && *(dist + u) + adjacent->weight < *(dist + v))
				*(dist + v) = *(dist + u) + adjacent->weight;
		}
	}
	free(visited);
	return dist;
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

    unsigned int src;
    printf("Enter source vertex: ");
    scanf("%u", &src);

    unsigned int* distances = dijkstra(graph, src);

    printf("Minimum distances from vertex %u:\n", src);
    for (unsigned int i = 0; i < V; i++)
    {
        if (distances[i] == UINT_MAX)
            printf("To %u: INF (unreachable)\n", i);
        else
            printf("To %u: %u\n", i, distances[i]);
    }

    free(distances);
    freeGraph(graph);
    return 0;
}
