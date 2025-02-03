#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool is_duplicate(const char *arr,size_t length)
{
	unsigned int CFLAGS= 0x0;
	unsigned int MASK;
	for (size_t i = 0;i < length;i++)
	{
		MASK = 0x1;

		if (arr[i] >= 65 && arr[i] <= 90)
			MASK = MASK << (arr[i]  -  65);
                else if(arr[i] >= 97 && arr[i] <= 122)
 			MASK = MASK << (arr[i]  -  97);
		else
		{
			printf("Invalid Symbols found:(\n");
			exit(EXIT_FAILURE);
		}


		if((CFLAGS & MASK) != 0)
			return true;
		else
			CFLAGS = CFLAGS | MASK;

	}
	return false;

}






int main()
{
	char* str = "Nalan";
	printf("The string:(%s) is %s dulpicate\n",str,(is_duplicate(str,strlen(str)))? "" : "not");
	return EXIT_SUCCESS;
}

