#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 221706L

int main()
{
	int msgid, msgflg,retrn;
	key_t key;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;

	msgid = msgget(key, msgflg);

	retrn = msgctl(msgid, IPC_RMID, NULL);
	printf ("\n Visszatert: %d\n", retrn);

	exit(0);
}
