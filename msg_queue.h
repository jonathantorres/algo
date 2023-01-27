#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAXBUF 1024
#define MKEY1 1234L
#define MKEY2 2345L
#define PERMS 0666
#define MAXMESGDATA (4096-16)
#define MESGHDRSIZE (sizeof(Mesg) - MAXMESGDATA)

typedef struct {
    int mesg_len;
    long mesg_type;
    char mesg_data[MAXMESGDATA];
} Mesg;

void msg_send(int id, Mesg *mesgptr)
{
    if (msgsnd(id, (char *) &(mesgptr->mesg_type), mesgptr->mesg_len, 0) != 0) {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }
}

int msg_recv(int id, Mesg *mesgptr)
{
    int n;

    n = msgrcv(id, (char *) &(mesgptr->mesg_type),
               MAXMESGDATA, mesgptr->mesg_type, 0);

    if ((mesgptr->mesg_len = n) < 0) {
        fprintf(stderr, "msgrcv error\n");
        exit(EXIT_FAILURE);
    }

    return n;
}

#endif
