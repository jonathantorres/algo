#include "msg_queue.h"

void server(int ipcreadfd, int ipcwritefd);

Mesg mesg;

int main(void)
{
    int readid, writeid;

    // create message queues
    if ((readid = msgget(MKEY1, PERMS | IPC_CREAT)) < 0) {
        perror("server: can't get message queue 1");
        exit(EXIT_FAILURE);
    }

    if ((writeid = msgget(MKEY2, PERMS | IPC_CREAT)) < 0) {
        perror("server: can't get message queue 2");
        exit(EXIT_FAILURE);
    }

    server(readid, writeid);

    return 0;
}

void server(int ipcreadfd, int ipcwritefd)
{
    char errmessg[256];
    int n, filefd;

    // read the filename from the IPC descriptor
    mesg.mesg_type = 1L;
    if ((n = msg_recv(ipcreadfd, &mesg)) <= 0) {
        perror("server: filename read error");
        exit(EXIT_FAILURE);
    }
    mesg.mesg_data[n] = '\0';

    if ((filefd = open(mesg.mesg_data, 0)) < 0) {
        sprintf(errmessg, ": can't open, %s\n", strerror(errno));
        strcat(mesg.mesg_data, errmessg);
        mesg.mesg_len = strlen(mesg.mesg_data);
        msg_send(ipcwritefd, &mesg);
    } else {
        // read the data from the file and send a message to
        // the IPC file descriptor
        while ((n = read(filefd, mesg.mesg_data, MAXMESGDATA)) > 0) {
            mesg.mesg_len = n;
            msg_send(ipcwritefd, &mesg);
        }
        close(filefd);

        if (n < 0) {
            perror("server: read error");
            exit(EXIT_FAILURE);
        }
    }

    // send message with length 0 to signify the end
    mesg.mesg_len = 0;
    msg_send(ipcwritefd, &mesg);
}
