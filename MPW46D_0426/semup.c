#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 41234L
#define PERM 00666

int main()
{
	int semid,semnum,rtn;
	struct sembuf sembuf;

	semid = semget (KEY, 0, PERM);
	if (semid < 0 ) {
		perror("Semget hiba!\n");
		exit(0);
	} else printf("A Semid: %d\n",semid);

	for(semnum=0; (rtn=semctl(semid, semnum , GETVAL, NULL))!=-1; semnum++){
		sembuf.sem_num = semnum;
		sembuf.sem_op = 1;
		sembuf.sem_flg = PERM;
		rtn = semop(semid, &sembuf, 1);
		printf("A Semop visszateresi erteke: %d\n",rtn);
	}

}
