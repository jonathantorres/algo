#include "msg_queue.h"

void client(int ipcreadfd, int ipcwritefd);

Mesg mesg;

int main(void)
{
    int writeid, readid;

    // open the message queues, the server must have
    // already created them
    if ((writeid = msgget(MKEY1, 0)) < 0) {
        perror("client: can't msgget message queue 1");
        exit(EXIT_FAILURE);
    }

    if ((readid = msgget(MKEY2, 0)) < 0) {
        perror("client: can't msgget message queue 2");
        exit(EXIT_FAILURE);
    }

    client(readid, writeid);

    // now we can delete the message queues
    if (msgctl(readid, IPC_RMID, NULL) < 0) {
        perror("client: can't RMID message queue 1");
        exit(EXIT_FAILURE);
    }

    if (msgctl(writeid, IPC_RMID, NULL) < 0) {
        perror("client: can't RMID message queue 2");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return 0;
}

void client(int ipcreadfd, int ipcwritefd)
{
    int n;

    // read message from standard input, write as a message to IPC descriptor
    if (fgets(mesg.mesg_data, MAXMESGDATA, stdin) == NULL) {
        perror("client: filename read error");
        exit(EXIT_FAILURE);
    }

    // ignore newline from fgets
    n = strlen(mesg.mesg_data);
    if (mesg.mesg_data[n-1] == '\n') {
        n--;
    }

    mesg.mesg_len = n;
    mesg.mesg_type = 1L;
    msg_send(ipcwritefd, &mesg);

    // receive the message from the IPC descriptor
    // and write the data to standard output
    while ((n = msg_recv(ipcreadfd, &mesg)) > 0) {
        if (write(1, mesg.mesg_data, n) != n) {
            perror("client: data write error");
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0) {
        perror("client: data read error");
        exit(EXIT_FAILURE);
    }
}
