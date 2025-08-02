#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

// Edge structure
typedef struct Edge {
    unsigned int src, dest, weight;
} Edge;

// Heap structure
typedef struct Heap {
    Edge* arr;
    unsigned int capacity;
    unsigned int size;
    bool isMaxHeap;
} Heap;

// Function declarations
Heap* __init__(unsigned int capacity, bool isMaxHeap);
void __del__(Heap* h);

void insert(Heap* h, Edge value);
Edge delete(Heap* h);

Heap* buildHeap(Edge* array, unsigned int size, bool isMaxHeap);
Edge* heapSort(Heap* h);

void printHeap(Heap* h);

#endif
