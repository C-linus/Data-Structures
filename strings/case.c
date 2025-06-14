#include <stdio.h>
#include <stdlib.h>


char* lower(char* str)
{
	if(!str)
	{
		printf("Can't change the case of NULL\n");
		exit(EXIT_FAILURE);
	}

	char letter;
	for(int i = 0; *(str + i) != '\0' ; i++)
	{
		letter = *(str + i);
		*(str + i) += ((letter >= 65 && letter <= 90) ? 32 : 0);
	}
	return str;
}

char* upper(char* str)
{
	if(!str)
	{
		printf("Can't change the case of NULL\n");
		exit(EXIT_FAILURE);
	}

	char letter;
	for(int i = 0; *(str + i) != '\0' ; i++)
	{
		letter = *(str + i);
		*(str + i) += ((letter >= 97 && letter <= 122) ? -32 : 0);
	}
	return str;
}

char* swap(char* str)
{
	if(!str)
	{
		printf("Can't change the case of NULL\n");
		exit(EXIT_FAILURE);
	}

	char letter;
	for(int i = 0; *(str + i) != '\0' ; i++)
	{
		letter = *(str + i);
		*(str + i) += ((letter >= 65 && letter <= 90) ? 32 : (letter >= 97 && letter <= 122) ? -32 : 0);
	}
	return str;
}

int main()
{
	char str[] = "n4lAN";
	printf("swap case:%s\n",swap(str));
	return EXIT_SUCCESS;
}

