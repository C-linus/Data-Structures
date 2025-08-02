#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set.h"


DisjointSet* __initDS__(unsigned int size)
{
	DisjointSet* ds = (DisjointSet *)malloc(sizeof(DisjointSet));

	if(ds == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	ds->size = size;

	ds->subsets = (Subset *)malloc(sizeof(Subset)*size);

	if(ds->subsets == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < size; i++)
	{
		(ds->subsets + i)->parent = i;
		(ds->subsets + i)->rank = 0;
	}

	return ds;
}



void __delDS__(DisjointSet** ds)
{
	free((*ds)->subsets);
	free(*ds);
	*ds = NULL;
}


void unionDS(DisjointSet* ds,unsigned int x, unsigned int y)
{
	unsigned int rootX = find(ds,x);
	unsigned int rootY = find(ds,y);


	if(rootX == rootY) return;

	if((ds->subsets + rootX)->rank > (ds->subsets + rootY)->rank)
		(ds->subsets + rootY)->parent = rootX;
	else if((ds->subsets + rootX)->rank < (ds->subsets + rootY)->rank)
		(ds->subsets + rootX)->parent = rootY;
	else
	{
		(ds->subsets + rootY)->parent = rootX;
		(ds->subsets + rootX)->rank++;
	}

}



unsigned int find(DisjointSet* ds, unsigned int x)
{
	unsigned int root = x;
	unsigned int parent;

	while((ds->subsets + root)->parent != root)
		root = (ds->subsets + root)->parent;


	// Path Compresion for O(1) searching
	while(x != root)
	{
		parent = (ds->subsets + x)->parent;
		(ds->subsets + x)->parent = root;
		x = parent;
	}

	return root;
}

