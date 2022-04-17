#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHMKEY 55905L

int main()
{
	pid_t p;

	if((p = fork()) < 0){
        printf("A fork nem sikerult!\n");
    }
    else if(p == 0){
        int shmid;
        key_t key;
        int size=512;
        int shmflg;

        key = SHMKEY;

        shmflg = 0;
        if ((shmid=shmget(key, size, shmflg)) < 0) {

           shmflg = 00666 | IPC_CREAT;
           if ((shmid=shmget(key, size, shmflg)) < 0) {
              perror("Az shmget() system-call sikertelen!\n");
              exit(-1);
           }
        }


    }
    else{
        int shmid;
        key_t key;
        int size=512;
        int shmflg;
        struct vmi {
            int  hossz;
            char szoveg[512-sizeof(int)];
        } *segm;

        key = SHMKEY;

        shmflg = 0;

        if ((shmid=shmget(key, size, shmflg)) < 0) {
            perror("Az shmget system-call sikertelen!\n");
            exit(-1);
        }



        shmflg = 00666 | SHM_RND;
        segm = (struct vmi *)shmat(shmid, NULL, shmflg);

        if (segm == (void *)-1) {
            perror("Sikertelen attach!\n");
            exit(-1);
        }



        if (strlen(segm->szoveg) > 0)
            printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);

        printf("\nUj szoveget kerek!\n");
        scanf("%[^\n]", segm->szoveg);
        printf("Az uj szoveg: %s\n",segm->szoveg);
        segm->hossz=strlen(segm->szoveg);


        shmdt(segm);




        int rtn;
        int cmd = -1;
        struct shmid_ds shmid_ds, *buf;

        buf = &shmid_ds;

        key = SHMKEY;

        shmflg = 0;
        if ((shmid=shmget(key, size, shmflg)) < 0) {
            perror("Az shmget() system-call sikertelen!\n");
            exit(-1);
        }


        while(cmd != 2){
            printf("\nAdd meg a parancs szamat:\n");
            printf("0. IPC_STAT (status)\n");
            printf("1. IPC_RMID (torles)\n");
            printf("2. EXIT (kilepes)\n> ");
            scanf("%d",&cmd);


        switch (cmd)
        {
            case 0:
            rtn = shmctl(shmid, IPC_STAT, buf);
            printf("Szegmens merete: %d\n",(int)(buf->shm_segsz));
            printf("Utolso shmop()-os processz pid-je: %d\n",buf->shm_lpid);
            break;
            case 1:
            rtn = shmctl(shmid, IPC_RMID, NULL);
            printf("Szegmens torolve. Hibakod: %d\n", rtn);
            break;
            case 2:
            exit(0);
            default:
            printf("Nincs ilyen parancs!\n");
            break;
        }

    }

}
}
