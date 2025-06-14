#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 26



bool is_anagram(const char* str1, const char* str2)
{
    long int* hash_map = (long int *)calloc(SIZE,sizeof(long int));

    if(!hash_map)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }


    if(strlen(str1) != strlen(str2))
    {
        free(hash_map);
        return false;
    }

    char ch;
    for(int i = 0; *(str1 + i) != '\0';  i++)
    {
        ch = *(str1 + i);
        if(ch >= 65 && ch <= 90)
            *(hash_map + ch - 65) += 1;
        else if(ch >= 97 && ch <= 122)
            *(hash_map + ch - 97) += 1;
        else
        {
            printf("Invalid character found :(\n");
            free(hash_map);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; *(str2 + i) != '\0'; i++)
    {
        ch = *(str2 + i);
        if(ch >= 65 && ch <= 90)
            *(hash_map + ch - 65) -= 1;
        else if(ch >= 97 && ch <= 122)
            *(hash_map + ch - 97) -= 1;
        else
        {
            printf("Invalid character found :(\n");
            free(hash_map);
            exit(EXIT_FAILURE);
        }
    }

    bool flag = true;
    for(int i = 0; i < SIZE; i++)
    {
        if(*(hash_map + i) != 0)
        {
            flag = false;
            break;
        }
    }
    free(hash_map);
    return flag;
}

int main()
{
    char* str1 = "decImal";
    char* str2 = "meDicoL";

    printf("Both strings are %s\n",(is_anagram(str1,str2))? "anagram" : "not anagram");
    return EXIT_SUCCESS;
}