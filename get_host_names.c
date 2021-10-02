#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char **argv)
{
    char *ptr, **pptr;
    char str[INET6_ADDRSTRLEN];
    struct hostent *hptr;

    while (--argc > 0) {
        ptr = *++argv;
        if ((hptr = gethostbyname(ptr)) == NULL) {
            herror("gethostbyname() error");
            continue;
        }
        printf("official hostname: %s\n", hptr->h_name);

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++) {
            printf("\talias: %s\n", *pptr);
        }

        switch (hptr->h_addrtype) {
            case AF_INET:
            case AF_INET6:
                pptr = hptr->h_addr_list;
                for (; *pptr != NULL; pptr++) {
                    if (inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)) == NULL) {
                        perror("inet_ntop() error");
                        continue;
                    }
                    printf("\taddress: %s\n", str);
                }
                break;
        }
    }

    return 0;
}
