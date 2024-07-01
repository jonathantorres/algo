#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// program that will descend the provided directory
// hierarchy counting the types of files that are found

/* function type that is called for each filename */
typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
    int ret;

    if (argc != 2) {
        puts("usage: ftw <starting-pathname>");
        exit(EXIT_FAILURE);
    }

    ret = myftw(argv[1], myfunc);       /* does it all */
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

    if (ntot == 0) {
        ntot = 1;       /* avoid divide by 0; print 0 for all counts */
    }

    printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);

    exit(ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F   1 /* file other than directory */
#define FTW_D   2 /* directory */
#define FTW_DNR 3 /* directory that can't be read */
#define FTW_NS  4 /* file that we can't stat */

static char *fullpath; /* contains full pathname for every file */

/* we return whatever func() returns */
static int myftw(char *pathname, Myfunc *func)
{
    int len = BUFF_SIZE;
    fullpath = malloc(len);

    if (!fullpath) {
        fprintf(stderr, "No memory!");
        exit(EXIT_FAILURE);
    }
    strncpy(fullpath, pathname, len);   /* protect against */
    fullpath[len-1] = 0;                /* buffer overrun */

    return(dopath(func));
}

/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 */
/* we return whatever func() returns */
static int dopath(Myfunc* func)
{
    struct stat   statbuf;
    struct dirent *dirp;
    DIR           *dp;
    int           ret;
    char          *ptr;

    if (lstat(fullpath, &statbuf) < 0) {
        // stat error
        return(func(fullpath, &statbuf, FTW_NS));
    }
    if (S_ISDIR(statbuf.st_mode) == 0) {
        // not a directory
        return(func(fullpath, &statbuf, FTW_F));
    }

    /*
     * It's a directory.  First call func() for the directory,
     * then process each filename in the directory.
     */
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
        return(ret);
    }

    ptr = fullpath + strlen(fullpath);  /* point to end of fullpath */
    *ptr++ = '/';
    *ptr = 0;

    if ((dp = opendir(fullpath)) == NULL) {
        // can't read the directory
        return(func(fullpath, &statbuf, FTW_DNR));
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue; /* ignore dot and dot-dot */
        }

        strcpy(ptr, dirp->d_name);  /* append name after slash */

        // recursive
        if ((ret = dopath(func)) != 0) {
            break;  /* time to leave */
        }
    }

    ptr[-1] = 0;    /* erase everything from slash onwards */

    if (closedir(dp) < 0) {
        printf("can't close directory %s\n", fullpath);
    }

    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type) {
    case FTW_F:
        switch (statptr->st_mode & S_IFMT) {
        case S_IFREG:   nreg++;   break;
        case S_IFBLK:   nblk++;   break;
        case S_IFCHR:   nchr++;   break;
        case S_IFIFO:   nfifo++;  break;
        case S_IFLNK:   nslink++; break;
        case S_IFSOCK:  nsock++;  break;
        case S_IFDIR:
            /* directories should have type = FTW_D */
            printf("for S_IFDIR for %s\n", pathname);
        }
        break;

    case FTW_D:
        ndir++;
        break;

    case FTW_DNR:
        printf("can't read directory %s\n", pathname);
        break;

    case FTW_NS:
        printf("stat error for %s\n", pathname);
        break;

    default:
        printf("unknown type %d for pathname %s\n", type, pathname);
        exit(EXIT_FAILURE);
    }

    return 0;
}
