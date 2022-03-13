#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    if ((pid = fork())<0)
        perror("fork error");
    else if(pid == 0){
        if(execl("./child","child",(char*)NULL)<0)
            perror("execl error");
    }

    if(waitpid(pid, NULL, 0) < 0)
        perror("wait error");
    else{
        printf("wait the child");
    }

    return 0;
}

