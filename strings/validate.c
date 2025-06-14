#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid(const char* str)
{
    if(!str)
    {
        printf("Null object is not iterable.\n");
        exit(EXIT_FAILURE);
    }


    char ch;
    for(size_t i = 0; *(str + i) != '\0'; i++)
    {
        ch = *(str + i);
        if(!(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122) && !(ch >= 48 && ch <= 57))
            return false;

    }
    return true;
}

int main()
{
    char* usrname = "Nalan123";
    printf("Username:(%s) is %s\n",usrname,(is_valid(usrname))? "valid" : "not valid");
}