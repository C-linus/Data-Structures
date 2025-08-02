#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

// Utility
void swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

Heap* __init__(unsigned int capacity, bool isMaxHeap)
{
    Heap* h = (Heap *)malloc(sizeof(Heap));
    if(h == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    h->arr = (Edge *)calloc(capacity, sizeof(Edge));
    if(h->arr == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    h->capacity = capacity;
    h->size = 0;
    h->isMaxHeap = isMaxHeap;

    return h;
}

void heapifyUp(Heap* h, unsigned int index)
{
    int parent = (index - 1) / 2;

    while(index > 0 &&
        ((h->isMaxHeap && h->arr[index].weight > h->arr[parent].weight) ||
         (!h->isMaxHeap && h->arr[index].weight < h->arr[parent].weight)))
    {
        swap(&h->arr[index], &h->arr[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(Heap *h, unsigned int index)
{
    unsigned int target, left, right;
    while (true)
    {
        target = index;
        left = 2 * index + 1;
        right = 2 * index + 2;

        if (h->isMaxHeap)
        {
            if (left < h->size && h->arr[left].weight > h->arr[target].weight)
                target = left;
            if (right < h->size && h->arr[right].weight > h->arr[target].weight)
                target = right;
        }
        else
        {
            if (left < h->size && h->arr[left].weight < h->arr[target].weight)
                target = left;
            if (right < h->size && h->arr[right].weight < h->arr[target].weight)
                target = right;
        }

        if (target != index)
        {
            swap(&h->arr[index], &h->arr[target]);
            index = target;
        }
        else
            break;
    }
}

void insert(Heap* h, Edge value)
{
    if(h->size == h->capacity)
    {
        h->capacity *= 2;
        h->arr = (Edge *)realloc(h->arr, sizeof(Edge) * h->capacity);
        if(h->arr == NULL) {
            printf("Memory Allocation Failed!\n");
            exit(EXIT_FAILURE);
        }
    }
    h->arr[h->size++] = value;
    heapifyUp(h, h->size - 1);
}

Edge delete(Heap *h)
{
    if (h->size == 0)
    {
        printf("Can't delete, heap is empty!\n");
        exit(EXIT_FAILURE);
    }
    Edge root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapifyDown(h, 0);
    return root;
}

Heap* buildHeap(Edge* array, unsigned int size, bool isMaxHeap)
{
    Heap* h = __init__(size, isMaxHeap);
    for(unsigned int i = 0; i < size; i++)
        h->arr[i] = array[i];

    h->size = size;

    for(int j = (size / 2) - 1; j >= 0; j--)
        heapifyDown(h, j);

    return h;
}

Edge* heapSort(Heap* h)
{
    Edge* sorted = (Edge *)malloc(sizeof(Edge) * h->size);
    if(sorted == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    unsigned int originalSize = h->size;
    for(int i = h->size - 1; i >= 0; i--)
        sorted[i] = delete(h);

    h->size = originalSize; // Restore if needed
    return sorted;
}

void printHeap(Heap *h)
{
    for (int i = 0; i < h->size; i++)
        printf("(%u, %u, %u) ", h->arr[i].src, h->arr[i].dest, h->arr[i].weight);
    printf("\n");
}

void __del__(Heap *h)
{
    free(h->arr);
    free(h);
}
