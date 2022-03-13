#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char	*env_init[] = {"USER=ismeretlen","PATH=/tmp","ENV=vége\n", NULL };

int
main(void)
{
	pid_t	pid;

	if ( (pid = fork()) < 0)
		perror("fork error");
	else if (pid == 0) {
		if (execle(strcat(getenv("BIN"),"/echoall"),
				   "echoall", "myarg1", "MY ARG2", (char *) 0,
				   env_init) < 0)
			perror("execle error");
	}
	if (waitpid(pid, NULL, 0) < 0)
		perror("wait error");

	if ( (pid = fork()) < 0)
		perror("fork error");
	else if (pid == 0) {
		if (execlp("echoall",
				   "echoall", "only 1 arg", (char *) 0) < 0)
			perror("execlp error");
	}
	exit(0);
}
