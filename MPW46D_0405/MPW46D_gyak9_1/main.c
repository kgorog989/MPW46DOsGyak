#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signAlarm(int alrm)
{
    printf("\nMPW46D\n");

}

int main()
{
    if(signal(SIGALRM, signAlarm) == SIG_ERR)
    {
        printf("Hiba");
    }
    else
    {

        alarm(3);
        kill(getpid(), SIGALRM);
        pause();
        printf("\nKilepes\n");

    }
    return 0;
}
