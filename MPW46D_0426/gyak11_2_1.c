#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define KEY 11234L
#define PERM 00666

int main( ) {
    int 	id;
    int def_value = 1;


	if ((id = semget(KEY, 1, 0)) < 0) {
		if ((id = semget(KEY, 1, PERM | IPC_CREAT)) < 0) {
		 	perror(" A szemafor nem nyitható meg. ");
			exit(-1);
		}
	}
	else    {
		perror(" Már létezik a szemafor. ");
		exit(0);
	}


        if (semctl(id, 0, SETVAL, def_value) < 0) {
            perror(" Nem lehetett inicializálni. ");
        } else {
            printf(" \nKész és inicializált a szemafor. ");
        }


	exit(0);
}
