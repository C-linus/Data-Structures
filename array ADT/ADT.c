#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a,b)((a < b) ? a : b)
#define MAX(a,b)((a > b) ? a : b)

// Array ADT
typedef struct array{
	int *arr;
	int size;
	int length;
} Array;

// Function Declarations
void get_length(Array* arr);
void get_size(Array* arr);

void __init__(Array* arr)
{
	get_size(arr);
	arr->arr = (int *) malloc(sizeof(int) * arr->size);

	if(!(arr->arr))
	{
		printf("Memory Allocation failed\n");
		exit(EXIT_FAILURE);
	}

	get_length(arr);
	for(int i = 0; i < arr->length; i++)
	{
		printf("Enter element-%d: ",i + 1);
		scanf("%d",(arr->arr + i));
	}
}

void  get_length(Array* arr)
{
	int length;
	do
	{
		printf("Enter the number of elements: ");
		scanf("%d",&length);
	}while(length < 1 || length > arr->size);

	arr->length = length;
}

void get_size(Array* arr)
{
	int size;
	do
	{
		printf("Enter the size of array: ");
		scanf("%d",&size);
	}while(size < 1);

	arr->size = size;
}

// Getter Method
int get(Array arr,unsigned int index)
{
	if(index >= arr.length)
	{
		printf("IndexOutOfRangeError: Array index(%d) out of range\n",index);
		exit(EXIT_FAILURE);
	}
	return *(arr.arr + index);
}

// Setter Method
void set(Array arr,unsigned int index, int element)
{
	if(index >= arr.length)
	{
		printf("IndexOutOfRangeError: Array index(%d) out of range\n",index);
		exit(EXIT_FAILURE);
	}
	*(arr.arr + index) = element;
}

// Returns the maximum element
int max(Array arr)
{
	int max = *(arr.arr);
	int curr;
	for(int i = 1; i < arr.length; i++)
	{
		curr = *(arr.arr + i);
		if(curr > max)
			max = curr;
	}
	return max;
}

// Returns the minimum element
int min(Array arr)
{
	int min = *(arr.arr);
	int curr;
	for(int i = 1; i < arr.length; i++)
	{
		curr = *(arr.arr + i);
		if(curr < min)
			min = curr;
	}
	return min;
}

// Returns the sum
int sum(Array arr)
{
	int sum = 0;
	for(int i = 0; i < arr.length; i++)
		sum += *(arr.arr + i);
	return sum;
}

// Returns the average
double average(Array arr)
{
	return sum(arr) / (double) arr.length;
}

void append(Array* arr,int element)
{
	if(arr->length < arr->size)
	{
		*(arr->arr + arr->length) = element;
		arr->length++;
	}

}

void insert(Array* arr,int index,int element)
{
	if(arr->length >= arr->size)
	{
		printf("Memory is full\n");
		return;
	}

	if(index < 0 || index > arr->length)
	{
		printf("Invalid Index for insertion\n");
		return;
	}

	for(int i = arr->length; i > index; i--)
	{
		*(arr->arr + i) = *(arr->arr + i - 1);
	}
	*(arr->arr + index) = element;
	arr->length++;
}

// Insertion in sorted array
void insert_at_sorted(Array* arr, int element)
{
	if(arr->length >= arr->size)
	{
		printf("Memory is full\n");
		return;
	}

	int index = arr->length - 1;

	while(index >= 0 && *(arr->arr + index) > element)
	{
		*(arr->arr + index + 1) = *(arr->arr + index);
		index--;
	}
	*(arr->arr + index + 1) = element;
	arr->length++;
}

// Merge function
Array* merge(Array* arr1,Array* arr2)
{
	int i,j,k;
	i=j=k=0;

	Array* arr3 = (Array*) malloc(sizeof(Array));

	if(!arr3)
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}


	int size = arr1->length + arr2->length;
	arr3->length = size;
	arr3->size = size;

	arr3->arr = (int *)malloc(sizeof(int)*size);

	if(!(arr3->arr))
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int num1;
	int num2;
	while(i < arr1->length && j < arr2->length)
	{

		num1 = *(arr1->arr + i);
		num2 = *(arr2->arr + j);

		if(num1 < num2)
		{
			*(arr3->arr + k) = num1;
			k++;
			i++;
		}
		else
		{
			*(arr3->arr + k) = num2;
			k++;
			j++;
		}
	}

	// Copying Remaining elements of Array-1
	for(;i < arr1->length; i++)
	{
		*(arr3->arr + k) = *(arr1->arr + i);
		k++;
	}

	// Copying Remaining elements of Array-2
	for(; j < arr2->length; j++)
	{
		*(arr3->arr + k) = *(arr2->arr + j);
		k++;
	}

	return arr3;
}

// Union Operation for Sorted Array
Array* union_sorted(Array* arr1, Array* arr2)
{
	int i,j,k;
	i=j=k=0;

	Array* arr3 = (Array*)malloc(sizeof(Array));

	if(!arr3)
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int size = arr1->length + arr2->length;
	arr3->size = size;

	arr3->arr = (int *) malloc(sizeof(int)*size);

	if(!(arr3->arr))
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int num1;
	int num2;
	while(i < arr1->length && j < arr2->length)
	{
		num1 = *(arr1->arr + i);
		num2 = *(arr2->arr + j);

		if(num1 < num2)
		{
			if (k == 0 || *(arr3->arr + k - 1) != num1)
			{
				*(arr3->arr + k) = num1;
				k++;
			}
			i++;
		}
		else if(num2 < num1)
		{
			if (k == 0 || *(arr3->arr + k - 1) != num2)
			{
				*(arr3->arr + k) = num2;
				k++;
			}
			j++;
		}
		else
		{
			if (k == 0 || *(arr3->arr + k - 1) != num1)
			{
				*(arr3->arr + k) = num1;
				k++;
			}
			i++;
			j++;
		}
	}


	while(i < arr1->length)
	{
		num1 = *(arr1->arr + i);
		if(k == 0 || *(arr3->arr + k - 1) != num1)
		{
			*(arr3->arr + k) = num1;
			k++;
		}
		i++;
	}

	while(j < arr2->length)
	{
		num2 = *(arr2->arr + j);
		if(k == 0 || *(arr3->arr + k - 1) != num2)
		{
			*(arr3->arr + k) = num2;
			k++;
		}
		j++;
	}

	arr3->length = k;
	if(k < arr3->size)
	{
		arr3->arr = (int *) realloc(arr3->arr, sizeof(int) * k);
		if(!(arr3->arr))
		{
			printf("Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		arr3->size = k;
	}
	return arr3;
}

// Intersection Operation for Sorted Array

Array* intersection_sorted(Array* arr1, Array* arr2)
{
	int i,j,k;
	i=j=k=0;

	Array* arr3 = (Array*)malloc(sizeof(Array));

	if(!arr3)
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int size = MIN(arr1->length,arr2->length);
	arr3->size = size;

	arr3->arr = (int *) malloc(sizeof(int) * size);

	if(!(arr3->arr))
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int num1;
	int num2;

	while(i < arr1->length && j < arr2->length)
	{
		num1 = *(arr1->arr + i);
		num2 = *(arr2->arr + j);

		if(num1 < num2)
			i++;
		else if(num2 < num1)
			j++;
		else
		{
			if(k == 0 || *(arr3->arr + k - 1) != num1)
			{
				*(arr3->arr + k) = num1;
				k++;
			}
			i++;
			j++;
		}
	}

	arr3->length = k;
	if(k < arr3->size)
	{
		arr3->arr = (int*) realloc(arr3->arr, sizeof(int) * k);
		if(!(arr3->arr))
		{
			printf("Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		arr3->size = k;
	}
	return arr3;
}

// Difference Operation for Sorted Array

Array* difference_sorted(Array* arr1, Array* arr2)
{
	int i,j,k;
	i=j=k=0;

	Array* arr3 = (Array*) malloc(sizeof(Array));

	if(!arr3)
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int size = arr1->length;
	arr3->size = size;

	arr3->arr = (int*) malloc(sizeof(int) * size);

	if(!(arr3->arr))
	{
		printf("Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}

	int num1;
	int num2;

	while(i < arr1->length && j < arr2->length)
	{
		num1 = *(arr1->arr + i);
		num2 = *(arr2->arr + j);

		if(num1 < num2)
		{
			*(arr3->arr + k) = num1;
			i++;
			k++;
		}
		else if(num2 < num1)
			j++;
		else
		{
			while(i < arr1->length && *(arr1->arr + i) == num1)
				i++;
			while(j < arr2->length && *(arr2->arr + j) == num2)
				j++;
		}
	}

	while(i < arr1->length)
	{
		*(arr3->arr + k) = *(arr1->arr + i);;
		i++;
		k++;
	}

	arr3->length = k;
	if(k < arr3->size)
	{
		arr3->arr = (int*) realloc(arr3->arr, sizeof(int)*k);
		if(!(arr3->arr))
		{
			printf("Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		arr3->size = k;
	}
	return arr3;

}
int delete(Array* arr,int index)
{

	if(arr->length == 0)
	{
		printf("Deletion can't be done at empty array\n");
	}

	if(index < 0 || index >= arr->length)
	{
		printf("Invalid Index for deletion\n");
		exit(EXIT_FAILURE);
	}

	int element = *(arr->arr + index);

	for(int i = index; i < arr->length; i++)
	{
		*(arr->arr + i) = *(arr->arr + i + 1);
	}
	arr->length--;
	return element;
}

void display(Array arr)
{
	printf("Array elements are:\n ");
	for(int i = 0; i < arr.length; i++)
		printf("|%8d| ",*(arr.arr + i));
	printf("\n");
}

int linear_search(Array arr,int element)
{
	for(int i = 0; i < arr.length; i++)
	{
		if(*(arr.arr + i) == element)
			return i;
	}
	return -1;
}

int binary_search(Array arr, int element)
{
	int low = 0;
	int high = arr.length - 1;
	int mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(*(arr.arr + mid) == element)
			return mid;
		else if(*(arr.arr + mid) > element)
			high = mid - 1;
		else if(*(arr.arr + mid) < element)
			low = mid + 1;
	}
	return -1;
}

// Reverse
void reverse(Array arr)
{
	int temp;
	for(int i = 0; i < (arr.length / 2) ; i++)
	{
		temp = *(arr.arr + i);
		*(arr.arr + i) = *(arr.arr + arr.length - i - 1);
		*(arr.arr + arr.length - i - 1) = temp;
	}
}

// Shifts
void left_shift(Array arr, int position)
{
	if(position >= arr.length)
	{
		for(int i = 0; i < arr.length; i++)
			*(arr.arr + i) = 0;
		return;
	}

	for(int i = 0; i < (arr.length - position); i++)
	{
		*(arr.arr + i) = *(arr.arr + i + position);
	}

	for(int i = (arr.length - position); i < arr.length; i++)
	{
		*(arr.arr + i) = 0;
	}
}

void right_shift(Array arr, int position)
{
	if(position >= arr.length)
	{
		for(int i = 0; i < arr.length; i++)
			*(arr.arr + i) = 0;
		return;
	}

	for(int i = arr.length - 1; i >= position; i--)
	{
		*(arr.arr + i) = *(arr.arr + i - position);
	}

	for(int i = 0; i < position; i++)
	{
		*(arr.arr + i) = 0;
	}
}

// Rotation
void left_rotate(Array arr, int position)
{
	position = position % arr.length;
	int temp;

	while(position--)
	{
		temp = *(arr.arr);
		for(int i = 0; i < arr.length - 1; i++)
		{
			*(arr.arr + i) = *(arr.arr + i + 1);
		}
		*(arr.arr + arr.length - 1) = temp;
	}
}

void right_rotate(Array arr, int position)
{
	position = position % arr.length;
	int temp;

	while(position--)
	{
		temp = *(arr.arr + arr.length - 1);
		for(int i = arr.length - 1; i > 0; i--)
		{
			*(arr.arr + i) = *(arr.arr + i - 1);
		}
		*(arr.arr) = temp;
	}
}

bool is_sorted(Array arr)
{
	for(int i = 0; i < arr.length - 1; i++)
	{
		if(*(arr.arr + i) > *(arr.arr + i + 1))
			return false;
	}
	return true;
}

void separate_polarity(Array arr)
{
	int i = 0;
	int j = arr.length - 1;
	int temp;

	while(i < j)
	{
		while(i < j && *(arr.arr + i) < 0) i++;
		while(i < j && *(arr.arr + j) >= 0) j--;

		if(i < j)
		{
			temp = *(arr.arr + i);
			*(arr.arr + i ) = *(arr.arr + j);
			*(arr.arr + j ) = temp;
		}
	}
}

int main()
{
	Array arr1;
	__init__(&arr1);
	Array arr2;
	__init__(&arr2);
	display(arr1);
	display(arr2);
	Array* arr3 = difference_sorted(&arr1,&arr2);
	printf("The sizeof array:%d\n",arr3->size);
	display(*arr3);
	return EXIT_SUCCESS;
}
