#include <stdio.h>
#include <stdlib.h>


void tower_of_hanoi(int n, int A, int B, int C)
{
	if(n > 0)
	{
		tower_of_hanoi(n-1,A,C,B);
		printf("(%d,%d)\n",A,C);
		tower_of_hanoi(n-1,B,A,C);
	}

}



int main()
{

	tower_of_hanoi(3,1,2,3);
	return EXIT_SUCCESS;

}
