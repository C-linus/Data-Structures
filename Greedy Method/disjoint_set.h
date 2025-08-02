#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

typedef struct Subset
{
	unsigned int parent;
	unsigned int rank;
} Subset;

typedef struct DisjointSet
{
	Subset* subsets;
	unsigned int size;
} DisjointSet;

DisjointSet* __initDS__(unsigned int size);
void __delDS__(DisjointSet** ds);
void unionDS(DisjointSet* ds,unsigned int x, unsigned int y);
unsigned int find(DisjointSet* ds, unsigned int x);

#endif
