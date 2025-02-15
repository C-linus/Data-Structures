#include <stdio.h>
#include <stdlib.h>



int nCr(int n, int r)
{

	if ( r  == 0 || n == r)
		return 1;

	return nCr(n-1,r-1) + nCr(n - 1,r);

}



int main()
{
	printf("The nCr(%d,%d) is:%d\n",4,2,nCr(4,2));
	return EXIT_SUCCESS;

}
