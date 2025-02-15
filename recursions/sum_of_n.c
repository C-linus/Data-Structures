#include <stdio.h>
#include <stdlib.h>


size_t sum_of_N(size_t n)
{
	if (n == 1)
		return 1;
	else
		return n + sum_of_N(n - 1);
}




int main()
{
	size_t n = 10;
	printf("The sum of [1 ... %zu] natural numbers is:%zu\n",n,sum_of_N(n));
	return EXIT_SUCCESS;
}

