#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 41234L
#define PERM 00666

int main() {


  int semid,rtn, semnum;

	union semun {
        	int              val;
        	struct semid_ds *buf;
        	unsigned short  *array;
        	struct seminfo  *__buf;
    	} arg;

	semid = semget (KEY, 0, PERM);
	if (semid < 0 ) {
		perror("Semget hiba!\n");
		exit(0);
	} else printf("A Semid: %d\n",semid);

	for(semnum=0; (rtn=semctl(semid, semnum , GETVAL, NULL))!=-1; semnum++){
		printf("A %d. szemafor erteke: %d\n", semnum+1, rtn);
	}
}
