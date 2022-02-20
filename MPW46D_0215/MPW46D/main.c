#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *gorog;
    gorog = fopen("gorog.txt", "w");
    fprintf(gorog, "Gorog Krisztina Erzsebet, MPW46D, programtervezo informatikus Bsc");
    fclose(gorog);
    return 0;
}
