#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Item
{
	unsigned int profit;
	unsigned int weight;
} Item;


int compare(const void* a, const void* b)
{
	double r1 = (double)((Item *)a)->profit / ((Item *)a)->weight;
	double r2 = (double)((Item *)b)->profit / ((Item *)b)->weight;

	return (r2 > r1) - (r2 < r1);
}



Item* readItems(unsigned int* size)
{
	printf("Enter the no.of items: ");
	scanf("%u",size);

	Item* items = (Item *)malloc(sizeof(Item)*(*size));

	if(items == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < *size; i++)
	{
		printf("Enter item-%d\n",i+1);
		printf("Profit:");
		scanf("%u",&((items + i)->profit));
		printf("Weight:");
		scanf("%u",&((items + i)->weight));
	}

	return items;
}


double knapsack(Item* items,unsigned int size,unsigned int capacity)
{

	qsort(items,size,sizeof(Item),compare);

	double maxProfit = 0.0;

	for(unsigned int i = 0; i < size; i++)
	{
		if(capacity >= (items + i)->weight)
		{
			capacity -= (items + i)->weight;
			maxProfit += (items + i)->profit;
		}
		else
		{
			maxProfit += (items + i)->profit * capacity / (double) (items + i)->weight;
			break;
		}
	}
	return maxProfit;
}



int main() {
    unsigned int size;
    unsigned int capacity;

    // Read items
    Item* items = readItems(&size);

    // Read capacity
    printf("Enter the knapsack capacity: ");
    scanf("%u", &capacity);

    // Calculate max profit
    double result = knapsack(items, size, capacity);

    // Output result
    printf("\nMaximum Profit: %.2lf\n", result);

    // Free allocated memory
    free(items);

    return EXIT_SUCCESS;
}
