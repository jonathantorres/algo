// Implementation of the access system call but using the
// effective user id and the effective group id
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int _access(char *path, int mode);

int main(void)
{
    int rc = _access("Makefile", F_OK);
    printf("%d\n", rc);
    return 0;
}

int _access(char *path, int mode)
{
    struct stat stats;
    int granted;

    uid_t uid = getuid();
    gid_t gid = getgid();
    uid_t euid = geteuid();
    gid_t egid = getegid();

    if (uid == euid && gid == egid) {
        return access(path, mode);
    }

    if (stat(path, &stats)) {
        return -1;
    }

    mode &= (X_OK | W_OK | R_OK);

    if (mode == F_OK) {
        return 0;
    }

    if (euid == 0 && ((mode & X_OK) == 0 || (stats.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))) {
        return 0;
    }

    if (euid == stats.st_uid) {
        granted = (unsigned int) (stats.st_mode & (mode << 6)) >> 6;
    } else if (egid == stats.st_gid) {
        granted = (unsigned int) (stats.st_mode & (mode << 3)) >> 3;
    } else {
        granted = (stats.st_mode & mode);
    }
    if (granted == mode) {
        return 0;
    }

    return -1;
}
