#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSGKEY 221732L

struct msgbuf1 {
long mtype;
char mtext[512];
} sendbuf, *msgp;


struct msqid_ds ds, *buf;

int main()
{
pid_t p;


if((p = fork()) < 0){
        printf("A fork nem sikerult!\n");
}
else if(p == 0){

        int msgid;
        key_t key;
        int msgflg;
        int ret, msgsz;

        key = MSGKEY;
        msgflg = 00666 | IPC_CREAT;
        msgid = msgget(key, msgflg);
        if (msgid == -1) {
                    perror(": msgget() nem sikerult!");
                    exit(-1);
            }

        msgp        = &sendbuf;
        msgp->mtype = 1;
        strcpy(msgp->mtext,"Elso uzenet");
        msgsz       = strlen(msgp->mtext) + 1;

            ret = msgsnd(msgid,(struct msgbuf *)msgp, msgsz, msgflg);


        strcpy(msgp->mtext,"Masodik uzenet");
        msgsz       = strlen(msgp->mtext) + 1;
        ret = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);



}
else{
        int msgid;
        key_t key;
        int mtype, msgflg;
        int ret, msgsz;

        key = MSGKEY;
        msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

        msgid = msgget(key, msgflg);
        if (msgid == -1) {
                    perror("msgget() nem sikerult");
                    exit(-1);
            }


        msgp = &sendbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;



        int command = -1;

    while(command != 4){
            printf("\n Mit szeretne?");
            printf("\n 0: uzenet db szamanak a kiirasa");
            printf("\n 1: 1 uzenet kiolvasasa");
            printf("\n 2: osszes uzenet kiirasa");
            printf("\n 3: uzenetsor megszuntetese");
            printf("\n 4: kilepes\n");

            scanf("%d", &command);

            switch(command)
          {
            case 0:
                ret = msgctl(msgid, IPC_STAT, buf);
                printf("Az uzenetek szama az uzenetsorban: %d\n", (int)(buf->msg_qnum));

                break;

            case 1:
                ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
                printf("\n Egy uzenet az uzenetsorbol: %s\n", msgp->mtext);
                break;

            case 2:
                	ret = msgctl(msgid, IPC_STAT, buf);

                	printf("Osszes uzenet kiirasa:\n");
                	while (buf->msg_qnum) {

                    ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
                    printf("Uzenet: %s\n", msgp->mtext);
                    ret = msgctl(msgid, IPC_STAT, buf);
                }
                break;

            case 3:

                printf("\nUzenetsor megszuntetve!\n");
                ret = msgctl(msgid, IPC_RMID, NULL);
                printf ("\n Visszatert: %d\n", ret);

                break;

            case 4:
                exit(0);

            default:
                printf("Nincs ilyen parancs!\n");
                break;
            }
}
    }
}


