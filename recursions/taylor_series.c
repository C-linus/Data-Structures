#include <stdio.h>
#include <stdlib.h>

double e(double x, double n)
{
	static double p = 1, f = 1;
	double result;
	if(n == 0)
		return 1;
	else
	{
 		result = e(x,n-1);
		p *= x;
		f *= n;
		return result +  (p / f);
	}
}



//// Taylor Series Using horner's rule
double e1(double x, double n)
{
	static double result = 1;
	if (n == 0)
		return result;
	result = 1 + ( x / n ) * result;
	return e1(x,n-1);
}


int main()
{
	double x = 1;
	double n = 40;
	printf("The taylor series of e^%.0lf is : %lf\n",x,e1(x,n));
	return EXIT_SUCCESS;
}
