#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjNode {
    unsigned int dest, weight;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    unsigned int V,E;
    AdjNode** array;  // Array of adjacency lists
} Graph;

AdjNode* __initNode__();
Graph* createGraph(unsigned int V,unsigned int E);
void addEdge(Graph* graph, unsigned int src, unsigned int dest, unsigned int weight);
void freeGraph(Graph* graph);
void readGraph(Graph* graph);
#endif
