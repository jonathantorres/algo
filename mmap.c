#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// program to demonstrate the use of mmap
// to copy a file use memory-mapped I/O

#define COPYINCR (1024*1024*1024) // 1GB
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <fromfile> <tofile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "can't open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
        fprintf(stderr, "can't create %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    if (fstat(fdin, &sbuf) < 0) {
        perror("fstat error");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fdout, sbuf.st_size) < 0) {
        perror("ftruncate error");
        exit(EXIT_FAILURE);
    }

    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) > COPYINCR) {
            copysz = COPYINCR;
        } else {
            copysz = sbuf.st_size - fsz;
        }
        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED) {
            perror("mmap error for input");
            exit(EXIT_FAILURE);
        }
        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED) {
            perror("mmap error for output");
            exit(EXIT_FAILURE);
        }

        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
    return 0;
}
