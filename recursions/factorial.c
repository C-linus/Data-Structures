#include <stdio.h>
#include <stdlib.h>

size_t factorial(size_t n)
{

	if(n == 0)
		return 1;
	else
		return factorial(n - 1) * n;
}


int main()
{
	size_t n = 5;
	printf("The factorial (!%zu) is:%zu\n",n,factorial(n));
	return EXIT_SUCCESS;
}
