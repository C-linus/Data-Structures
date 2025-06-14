#include <stdio.h>
#include <stdlib.h>


int strcmp(const char* str1, const char* str2)
{

    if(!str1 || !str2)
    {
        printf("NULL object is not iterable.\n");
        exit(EXIT_FAILURE);
    }

    while(*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


int main()
{
    char* str1 = "nalan";
    char* str2 = "naman";

    printf("The both strings are %s\n",(!strcmp(str1,str2))?"same":"not same");
    return EXIT_SUCCESS;
}