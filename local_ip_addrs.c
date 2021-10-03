#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define NAMELEN 512

char **my_addrs(int *addrtype);

int main(void)
{
    int addrtype;
    char **addrs = my_addrs(&addrtype);
    char **addr_ptr;
    char ipaddr[NAMELEN];

    memset(ipaddr, 0, NAMELEN);

    if (addrs == NULL) {
        perror("error getting addresses");
        return 1;
    }

    for (addr_ptr = addrs; *addr_ptr != NULL; addr_ptr++) {
        if (inet_ntop(addrtype, *addr_ptr, ipaddr, NAMELEN) == NULL) {
            perror("inet_ntop() error");
            continue;
        }

        printf("IP address: %s\n", ipaddr);
    }

    return 0;
}

char **my_addrs(int *addrtype)
{
    struct hostent *hptr;
    char myname[NAMELEN];

    memset(myname, 0, NAMELEN);

    if (gethostname(myname, NAMELEN) < 0) {
        return NULL;
    }

    if ((hptr = gethostbyname(myname)) == NULL) {
        return NULL;
    }

    *addrtype = hptr->h_addrtype;

    return hptr->h_addr_list;
}
