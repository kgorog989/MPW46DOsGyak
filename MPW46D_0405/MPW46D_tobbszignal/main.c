#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

void handleSignals();

int countSigint = 0;

int main()
{
    //these if statement catch errors
    if (signal(SIGINT, handleSignals) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    if (signal(SIGQUIT, handleSignals) == SIG_ERR)
        printf("\ncan't catch SIGQUIT\n");
    //Runs the program infinitely
    while(1)
        sleep(1);


    return 0;
}

void handleSignals(int signo){

    //looks for ctrl-c
    if (signo == SIGINT){
        printf("\nreceived SIGINT\n");
        countSigint++;

        if(countSigint == 1){
            printf("\nAlapertelmezett muvelet: %d\n", SIG_DFL);
        }
        else if (countSigint == 2){
            printf("\nkilepes\n");
            exit(0);
        }


        }
    //looks for ctrl-\ and prints value
    else if (signo == SIGQUIT){
        printf("\nreceived SIGQUIT, value: %d\n", signo);
    }
}
