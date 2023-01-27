// two processes sending data to each other using shared memory
// this client reads a filename from standard input
// and writes it to the shared memory segment, then it reads the file contents
// shared memory segment when the server is done writing it
// and writes these contents back to standard output

#include "shared_mem.h"

void client(void);

int shmid, clisem, servsem;
Mesg *mesgptr;

int main(void)
{
    // get the shared memory segment and attach it
    // the server must have already created it
    if ((shmid = shmget(SHMKEY, sizeof(Mesg), 0)) < 0) {
        perror("client: can't get shared memory segment");
        exit(EXIT_FAILURE);
    }

    if ((mesgptr = (Mesg *) shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("client: can't attach shared memory segment");
        exit(EXIT_FAILURE);
    }

    // open the two semaphores, the server must have created them already
    if ((clisem = sem_open(SEMKEY1)) < 0) {
        perror("server: can't opem client semaphore");
        exit(EXIT_FAILURE);
    }

    if ((servsem = sem_open(SEMKEY2)) < 0) {
        perror("server: can't open server semaphore");
        exit(EXIT_FAILURE);
    }

    client();

    // detach and remove the shared memory segment and close the semaphores
    if (shmdt(mesgptr) < 0) {
        perror("client: can't detach shared memory");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("client: can't remove shared memory");
        exit(EXIT_FAILURE);
    }

    sem_close(clisem);
    sem_close(servsem);

    return 0;
}

void client(void)
{
    int n;

    // read the filename from standard input, write it to shared memory
    sem_wait(clisem);
    if (fgets(mesgptr->mesg_data, MAXMESGDATA, stdin) == NULL) {
        perror("client: filename read error");
        exit(EXIT_FAILURE);
    }

    // ignore newline from fgets
    n = strlen(mesgptr->mesg_data);
    if (mesgptr->mesg_data[n-1] == '\n') {
        n--;
    }

    mesgptr->mesg_len = n;
    sem_signal(servsem);

    // wait for the server to place something in shared memory
    sem_wait(clisem);
    while ((n = mesgptr->mesg_len) > 0) {
        if (write(1, mesgptr->mesg_data, n) != n) {
            perror("client: data write error");
            exit(EXIT_FAILURE);
        }
        sem_signal(servsem);
        sem_wait(clisem);
    }

    if (n < 0) {
        perror("client: data read error");
        exit(EXIT_FAILURE);
    }
}
