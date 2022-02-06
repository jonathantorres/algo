#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define NBUFF 4
#define MAXBUF 1024
#define SHMKEY ((key_t) 7890)
#define SEMKEY1 ((key_t) 7891)
#define SEMKEY2 ((key_t) 7892)
#define PERMS 0666
#define MAXMESGDATA (4096-16)
#define MESGHDRSIZE (sizeof(Mesg) - MAXMESGDATA)
#define BIGCOUNT 10000

typedef struct {
    int mesg_len;
    long mesg_type;
    char mesg_data[MAXMESGDATA];
} Mesg;

// Define the semaphore operation arrays for the semop() calls.
static struct sembuf op_lock[2] = {
    { 2, 0, 0 },
    { 2, 1, SEM_UNDO }
};

static struct sembuf op_endcreate[2] = {
    { 1, -1, SEM_UNDO },
    { 2, -1, SEM_UNDO }
};

static struct sembuf op_open[1] = {
    { 1, -1, SEM_UNDO }
};

static struct sembuf op_close[3] = {
    { 2, 0, 0 },
    { 2, 1, SEM_UNDO },
    { 1, 1, SEM_UNDO }
};

static struct sembuf op_unlock[1] = {
    { 2, -1, SEM_UNDO }
};

static struct sembuf op_op[1] = {
    { 0, 99, SEM_UNDO }
};

void sem_op(int id, int value);
void sem_rm(int id);

/****************************************************************************
 * Create a semaphore with a specified initial value.
 * If the semaphore already exists, we don't initialize it (of course).
 * We return the semaphore ID if all OK, else -1.
 */
int sem_create(key_t key, int initval)
{
    int id, semval;
    union semun {
        int     val;
        struct semid_ds *buf;
        ushort      *array;
    } semctl_arg;

    // not intended for private semaphores
    if (key == IPC_PRIVATE) {
        return -1;
    } else if (key == -1) {
        return -1;
    }

again:
    if ((id = semget(key, 3, 0666 | IPC_CREAT)) < 0) {
        // permission problem or tables full
        return -1;
    }

    /*
     * When the semaphore is created, we know that the value of all
     * 3 members is 0.
     * Get a lock on the semaphore by waiting for [2] to equal 0,
     * then increment it.
     *
     * There is a race condition here.  There is a possibility that
     * between the semget() above and the semop() below, another
     * process can call our sem_close() function which can remove
     * the semaphore if that process is the last one using it.
     * Therefore, we handle the error condition of an invalid
     * semaphore ID specially below, and if it does happen, we just
     * go back and create it again.
     */
    if (semop(id, &op_lock[0], 2) < 0) {
        if (errno == EINVAL) {
            goto again;
        }
        perror("can't lock");
        exit(EXIT_FAILURE);
    }

    /*
     * Get the value of the process counter.  If it equals 0,
     * then no one has initialized the semaphore yet.
     */
    if ((semval = semctl(id, 1, GETVAL, 0)) < 0) {
        perror("can't GETVAL");
        exit(EXIT_FAILURE);
    }

    if (semval == 0) {
        /*
         * We could initialize by doing a SETALL, but that
         * would clear the adjust value that we set when we
         * locked the semaphore above.  Instead, we'll do 2
         * system calls to initialize [0] and [1].
         */
        semctl_arg.val = initval;
        if (semctl(id, 0, SETVAL, semctl_arg) < 0) {
            perror("can SETVAL[0]");
            exit(EXIT_FAILURE);
        }

        semctl_arg.val = BIGCOUNT;
        if (semctl(id, 1, SETVAL, semctl_arg) < 0) {
            perror("can SETVAL[1]");
            exit(EXIT_FAILURE);
        }
    }

    // Decrement the process counter and then release the lock.
    if (semop(id, &op_endcreate[0], 2) < 0) {
        perror("can't end create");
        exit(EXIT_FAILURE);
    }

    return id;
}

/****************************************************************************
 * Open a semaphore that must already exist.
 * This function should be used, instead of sem_create(), if the caller
 * knows that the semaphore must already exist.  For example a client
 * from a client-server pair would use this, if its the server's
 * responsibility to create the semaphore.
 * We return the semaphore ID if all OK, else -1.
 */
int sem_open(key_t key)
{
    int id;

    // not intended for private semaphores
    if (key == IPC_PRIVATE) {
        return -1;
    } else if (key == -1) {
        return -1;
    }

    // doesn't exist, or tables full
    if ((id = semget(key, 3, 0)) < 0) {
        return -1;
    }

    // Decrement the process counter.  We don't need a lock to do this.
    if (semop(id, &op_open[0], 1) < 0) {
        perror("can't open");
        exit(EXIT_FAILURE);
    }

    return id;
}

/****************************************************************************
 * Remove a semaphore.
 * This call is intended to be called by a server, for example,
 * when it is being shut down, as we do an IPC_RMID on the semaphore,
 * regardless whether other processes may be using it or not.
 * Most other processes should use sem_close() below.
 */
void sem_rm(int id)
{
    if (semctl(id, 0, IPC_RMID, 0) < 0) {
        perror("can't IPC_RMID");
        exit(EXIT_FAILURE);
    }
}

/****************************************************************************
 * Close a semaphore.
 * Unlike the remove function above, this function is for a process
 * to call before it exits, when it is done with the semaphore.
 * We "decrement" the counter of processes using the semaphore, and
 * if this was the last one, we can remove the semaphore.
 */
void sem_close(int id)
{
    int semval;

    /*
     * The following semop() first gets a lock on the semaphore,
     * then increments [1] - the process counter.
     */
    if (semop(id, &op_close[0], 3) < 0) {
        perror("can't semop");
        exit(EXIT_FAILURE);
    }

    /*
     * Now that we have a lock, read the value of the process
     * counter to see if this is the last reference to the
     * semaphore.
     * There is a race condition here - see the comments in
     * sem_create().
     */
    if ((semval = semctl(id, 1, GETVAL, 0)) < 0) {
        perror("can't GETVAL");
        exit(EXIT_FAILURE);
    }

    if (semval > BIGCOUNT) {
        fprintf(stderr, "sem[1] > BIGCOUNT\n");
    } else if (semval == BIGCOUNT) {
        sem_rm(id);
    } else {
        if (semop(id, &op_unlock[0], 1) < 0) {
            // unlock
            perror("can't unlock");
            exit(EXIT_FAILURE);
        }
    }
}

/****************************************************************************
 * Wait until a semaphore's value is greater than 0, then decrement
 * it by 1 and return.
 * Dijkstra's P operation.  Tanenbaum's DOWN operation.
 */
void sem_wait(int id)
{
    sem_op(id, -1);
}

/****************************************************************************
 * Increment a semaphore by 1.
 * Dijkstra's V operation.  Tanenbaum's UP operation.
 */
void sem_signal(int id)
{
    sem_op(id, 1);
}

/****************************************************************************
 * General semaphore operation.  Increment or decrement by a user-specified
 * amount (positive or negative; amount can't be zero).
 */
void sem_op(int id, int value)
{
    if ((op_op[0].sem_op = value) == 0) {
        fprintf(stderr, "can't have value == 0\n");
    }

    if (semop(id, &op_op[0], 1) < 0) {
        perror("sem_op error");
        exit(EXIT_FAILURE);
    }
}

#endif
