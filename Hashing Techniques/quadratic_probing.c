#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct HashSlot
{
	int data;
	bool isOccupied;
	bool isDeleted;
} HashSlot;


typedef struct HashTable
{
	HashSlot* table;
	unsigned int size;
} HashTable;


unsigned int hash(HashTable* ht, int key)
{
	int  index = key % (int)ht->size;
	return (index < 0) ? index + ht->size : index;
}


HashTable* __init__(unsigned int size)
{
	HashTable* ht = (HashTable *)malloc(sizeof(HashTable));

	if(ht == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	ht->table = (HashSlot *)calloc(size,sizeof(HashSlot));

	if(ht->table == NULL)
	{
		printf("Memory Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}

	ht->size = size;

	return ht;
}


bool insert(HashTable* ht, int key)
{
	unsigned int init_index = hash(ht,key);
	int tombStone = -1;
	unsigned int index;

	for(unsigned int i = 0; i < ht->size; i++)
	{
		index = (init_index + i * i) % ht->size;

		if((*(ht->table + index)).isOccupied && (*(ht->table + index)).data == key)
		{
			printf("Error: Duplicate Key (%d) is not allowed\n",key);
			return false;
		}

		if(!(*(ht->table + index)).isOccupied)
		{
			if((*(ht->table + index)).isDeleted)
			{
				if(tombStone == -1)
					tombStone = index;
			}
			else
			{
				if(tombStone != -1)
					index = tombStone;
				(*(ht->table + index)).data = key;
				(*(ht->table + index)).isOccupied = true;
				(*(ht->table + index)).isDeleted = false;
				return true;
			}

		}

	}

	if(tombStone != -1)
	{
		   (*(ht->table + tombStone)).data = key;
                   (*(ht->table + tombStone)).isOccupied = true;
                   (*(ht->table + tombStone)).isDeleted = false;
                   return true;
	}

	printf("Error: HashTable is Full, Cannot insert %d.\n",key);
	return false;
}


bool search(HashTable* ht, int key)
{
	unsigned int init_index = hash(ht,key);
	unsigned int index;

	for(unsigned int i = 0; i < ht->size; i++)
	{
		index = (init_index + i * i) % ht->size;

		if(!(*(ht->table + index)).isOccupied && !(*(ht->table + index)).isDeleted)
			return false;

		if((*(ht->table + index)).isOccupied && (*(ht->table + index)).data == key)
			return true;
	}

	return false;
}



bool delete(HashTable* ht, int key)
{
        unsigned int init_index = hash(ht,key);
        unsigned int index;

        for(unsigned int i = 0; i < ht->size; i++)
        {
                index = (init_index + i * i) % ht->size;

                if(!(*(ht->table + index)).isOccupied && !(*(ht->table + index)).isDeleted)
                        return false;

                if((*(ht->table + index)).isOccupied && (*(ht->table + index)).data == key)
                {
			(*(ht->table + index)).isOccupied = false;
			(*(ht->table + index)).isDeleted = true;
			return true;
		}
        }

        return false;
}

void printTable(HashTable* ht) {
    for (unsigned int i = 0; i < ht->size; i++) {
        printf("Slot[%d]: ", i);
        if (ht->table[i].isOccupied)
            printf("%d\n", ht->table[i].data);
        else if (ht->table[i].isDeleted)
            printf("Deleted\n");
        else
            printf("Empty\n");
    }
}


void freeTable(HashTable** ht) {
    free((*ht)->table);
    free(*ht);
    *ht = NULL;
}


int main() {
    HashTable* table = __init__(SIZE);

    insert(table, -15);
    insert(table, 25);
    insert(table, 5);
    insert(table, 35); // Will cause collision with 15 and 25 if SIZE is small

    printTable(table);

    printf("Search 25: %s\n", search(table, 25) ? "Found" : "Not Found");

    delete(table, 25);
    printf("After deleting 25:\n");
    printTable(table);

    freeTable(&table);
    return EXIT_SUCCESS;
}
