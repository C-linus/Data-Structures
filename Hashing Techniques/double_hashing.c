#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SIZE 10  // initial request; will adjust to nearest lower prime

typedef struct HashSlot {
    int data;
    bool isOccupied;
    bool isDeleted;
} HashSlot;

typedef struct HashTable {
    HashSlot* table;
    unsigned int size;
} HashTable;

// Check if a number is prime
bool is_prime(unsigned int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (unsigned int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Get the nearest smaller prime less than or equal to given value
unsigned int get_nearest_prime_less_than(unsigned int n) {
    while (n >= 2) {
        if (is_prime(n)) return n;
        n--;
    }
    return 2;  // fallback
}

// Primary hash function
unsigned int h1(HashTable* ht, int key) {
    int index = key % (int)ht->size;
    return (index < 0) ? index + ht->size : index;
}

// Secondary hash function (must not be zero)
unsigned int h2(HashTable* ht, int key) {
    unsigned int prime = get_nearest_prime_less_than(ht->size);
    return prime - (key % prime);
}

// Create and initialize the hash table
HashTable* __init__(unsigned int size) {
    HashTable* ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    ht->size = size;
    ht->table = (HashSlot *)calloc(ht->size, sizeof(HashSlot));
    if (!ht->table) {
        printf("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    return ht;
}

// Insert using double hashing
bool insert(HashTable* ht, int key) {
    unsigned int init_index = h1(ht, key);
    unsigned int step = h2(ht, key);
    int tombStone = -1;
    unsigned int index;

    for (unsigned int i = 0; i < ht->size; i++) {
        index = (init_index + i * step) % ht->size;

        if (ht->table[index].isOccupied && ht->table[index].data == key) {
            printf("Error: Duplicate Key (%d) is not allowed\n", key);
            return false;
        }

        if (!ht->table[index].isOccupied) {
            if (ht->table[index].isDeleted) {
                if (tombStone == -1) tombStone = index;
            } else {
                if (tombStone != -1) index = tombStone;
                ht->table[index].data = key;
                ht->table[index].isOccupied = true;
                ht->table[index].isDeleted = false;
                return true;
            }
        }
    }

    if (tombStone != -1) {
        ht->table[tombStone].data = key;
        ht->table[tombStone].isOccupied = true;
        ht->table[tombStone].isDeleted = false;
        return true;
    }

    printf("Error: HashTable is Full, Cannot insert %d.\n", key);
    return false;
}

// Search using double hashing
bool search(HashTable* ht, int key) {
    unsigned int init_index = h1(ht, key);
    unsigned int step = h2(ht, key);
    unsigned int index;

    for (unsigned int i = 0; i < ht->size; i++) {
        index = (init_index + i * step) % ht->size;

        if (!ht->table[index].isOccupied && !ht->table[index].isDeleted)
            return false;

        if (ht->table[index].isOccupied && ht->table[index].data == key)
            return true;
    }

    return false;
}

// Delete using double hashing
bool delete(HashTable* ht, int key) {
    unsigned int init_index = h1(ht, key);
    unsigned int step = h2(ht, key);
    unsigned int index;

    for (unsigned int i = 0; i < ht->size; i++) {
        index = (init_index + i * step) % ht->size;

        if (!ht->table[index].isOccupied && !ht->table[index].isDeleted)
            return false;

        if (ht->table[index].isOccupied && ht->table[index].data == key) {
            ht->table[index].isOccupied = false;
            ht->table[index].isDeleted = true;
            return true;
        }
    }

    return false;
}

// Print the table
void printTable(HashTable* ht) {
    for (unsigned int i = 0; i < ht->size; i++) {
        printf("Slot[%u]: ", i);
        if (ht->table[i].isOccupied)
            printf("%d\n", ht->table[i].data);
        else if (ht->table[i].isDeleted)
            printf("Deleted\n");
        else
            printf("Empty\n");
    }
}

// Free memory
void freeTable(HashTable** ht) {
    free((*ht)->table);
    free(*ht);
    *ht = NULL;
}

// Main function
int main() {
    unsigned int prime_size = get_nearest_prime_less_than(SIZE);
    HashTable* table = __init__(prime_size);

    insert(table, -15);
    insert(table, 25);
    insert(table, 5);
    insert(table, 35);

    printTable(table);

    printf("Search 25: %s\n", search(table, 25) ? "Found" : "Not Found");

    delete(table, 25);
    printf("After deleting 25:\n");
    printTable(table);

    freeTable(&table);
    return EXIT_SUCCESS;
}
