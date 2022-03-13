#include <stdio.h>
#include <stdlib.h>

int main()
{
    char command[30];
    do{
        scanf("%s", command);
        system(command);
    }while(1);
    return 0;
}
