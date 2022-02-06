// two processes sending data to each other using shared memory
// this server reads the filename from the shared memory segment
// opens and reads the file and then sends the file contents
// back to the shared memory segment
#include "shared_mem.h"

void server(void);

int shmid, clisem, servsem;
Mesg *mesgptr;

int main(void)
{
    if ((shmid = shmget(SHMKEY, sizeof(Mesg), PERMS | IPC_CREAT)) < 0) {
        perror("server: can't get shared memory");
        exit(EXIT_FAILURE);
    }

    if ((mesgptr = (Mesg *) shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("server: can't attach shared memory");
        exit(EXIT_FAILURE);
    }

    if ((clisem = sem_create(SEMKEY1, 1)) < 0) {
        perror("server: can't create client semaphore");
        exit(EXIT_FAILURE);
    }

    if ((servsem = sem_create(SEMKEY2, 0)) < 0) {
        perror("server: can't create server semaphore");
        exit(EXIT_FAILURE);
    }

    server();

    if (shmdt(mesgptr) < 0) {
        perror("server: can't detach shared memory");
        exit(EXIT_FAILURE);
    }

    sem_close(clisem);
    sem_close(servsem);

    return 0;
}

void server(void)
{
    char errmessg[256];
    int n, filefd;

    sem_wait(servsem);

    mesgptr->mesg_data[mesgptr->mesg_len] = '\0';

    if ((filefd = open(mesgptr->mesg_data, 0)) < 0) {
        sprintf(errmessg, ": can't open, %s\n", strerror(errno));
        strcat(mesgptr->mesg_data, errmessg);
        mesgptr->mesg_len = strlen(mesgptr->mesg_data);
        sem_signal(clisem);
        sem_wait(servsem);
    } else {
        // read the data from the file into shared memory
        while ((n = read(filefd, mesgptr->mesg_data, MAXMESGDATA-1)) > 0) {
            mesgptr->mesg_len = n;
            sem_signal(clisem);
            sem_wait(servsem);
        }
        close(filefd);

        if (n < 0) {
            perror("server: read error");
            exit(EXIT_FAILURE);
        }
    }

    // send message with length 0 to signify the end
    mesgptr->mesg_len = 0;
    sem_signal(clisem);
}
