#include <stdio.h>
#include <stdlib.h>

size_t lenOfStr(char* str)
{
	size_t len = 0;
	if(!str)
	{
		printf("Can't find the length of NULL object\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; *(str + i) != '\0';i++)
		len++;

	return len;
}


int main()
{
	char *str = "NALAN";
	printf("length of the string:%zu\n",lenOfStr(str));
	exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char* str)
{
    if(!str)
    {
        printf("Null object is not iterable.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t len;
    for(len = 0; *(str + len) != '\0'; len++);

    return len;
}


int main()
{
    char *str = "Nalan Pandi Kumar";
    printf("Length of the string is:%zu\n",strlen(str));
    return EXIT_SUCCESS;
}