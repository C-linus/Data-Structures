#include <stdio.h>
#include <stdlib.h>


int fib[10];

int fibonacci(int num)
{
	if(num <= 1)
		return num;
	else
		return fibonacci(num - 2) + fibonacci(num - 1);
}

/// Memoization
int memfib(int num)
{
	if (num <= 1)
	{
		fib[num] = num;
		return num;
	}
	else
	{
		if(fib[num - 2] == -1)
			fib[num - 2] = memfib(num - 2);
		if(fib[num - 1] == -1)
			fib[num - 1] = memfib(num - 1);
		fib[num] = fib[num - 2] + fib[num - 1];
		return fib[num - 2] + fib[num - 1];
	}
}

int main()
{
	int num = 7;

	for(int i = 0; i < 10; i++)
		fib[i] = -1;

	printf("The fibonacci number at %d in sequence is:%d\n",num,memfib(num));
	return EXIT_SUCCESS;
}
