#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


// Linear Search
int search(int *arr, int len,int element)
{
	for(int i = 0; i < len; i++)
	{
		if(*(arr + i) == element)
			return i;
	}
	return -1;
}


// Improved Linear Search

// Transposition Linear Search -> Slow Reduction Of Searching Time
int search_1(int *arr,int len,int element)
{
	for(int i = 0; i < len; i++)
	{
		if(*(arr + i) == element)
		{
			swap((arr + i),(arr + i - 1));
			return i - 1;
		}
	}
	return -1;
}

// Move To Fromt / Move To Head -> Sudden Reduction Of Searching Time
int search_2(int *arr,int len,int element)
{
	for(int i = 0; i < len; i++)
	{
		if(*(arr + i) == element)
		{
			swap((arr + i),arr);
			return 0;
		}
	}
	return -1;
}
