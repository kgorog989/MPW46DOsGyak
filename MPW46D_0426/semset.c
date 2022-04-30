#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define KEY 41234L
#define PERM 00666

int main( ) {
    int 	id;
    int n;
    int def_value = 0;

	printf("Adja meg a szemaforok szamat!\n");
	scanf("%d", &n);

	if ((id = semget(KEY, 5, 0)) < 0) {
		if ((id = semget(KEY, 5, PERM | IPC_CREAT)) < 0) {
		 	perror(" A szemafor nem nyitható meg. ");
			exit(-1);
		}
	}
	else    {
		perror(" Már létezik a szemafor. ");
		exit(0);
	}

int i;
    for(i = 0; i < n; i++){
        if (semctl(id, i, SETVAL, def_value) < 0) {
            perror(" Nem lehetett inicializálni. ");
        } else {
            printf(" \nKész és inicializált a(z) %d. szemafor. ", i+1);
        }
    }

	exit(0);
}
