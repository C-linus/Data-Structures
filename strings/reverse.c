#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* rev_str(char* str)
{

    if(!str)
    {
        printf("NULL object is not iterable.\n");
        exit(EXIT_FAILURE);
    }

    char temp;
    size_t len = strlen(str);
    for(int i = 0; i < len / 2; i++)
    {
        temp = *(str + i);
        *(str + i) = *(str + len - i - 1);
        *(str + len - i - 1) = temp;
    }
    return str;
}

int main()
{
    char name[] = "nalan";
    printf("Reverse string: %s\n",rev_str(name));
    return EXIT_SUCCESS;
}

