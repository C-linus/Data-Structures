#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char* str)
{

    if(!str)
    {
        printf("NULL object is not iterable.\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(str);
    for(int i = 0; i < len / 2; i++)
    {
        if(*(str + i) != *(str + len - i - 1))
            return false;
    }
    return true;
}


int main()
{
    char* word = "light";
    printf("The word:(%s) %s\n",word,(is_palindrome(word))? "is palindrome" : "is not palindrome");
    return EXIT_SUCCESS;
}