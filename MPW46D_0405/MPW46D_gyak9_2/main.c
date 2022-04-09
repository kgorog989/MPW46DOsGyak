#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigterm(int sig)
{
    printf("\n%d\n", sig);
}

int main()
{
    if(signal(SIGTERM, sigterm) == SIG_ERR)
    {
        printf("hiba");
        exit(1);
    }
    while(1)
    {
        sleep(3);
    }
    return 0;

}
