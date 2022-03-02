#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int inet_pton_loose(int family, const char *strptr, void *addrptr);

int main(void)
{
    char *str = "127.0.0.1";
    struct sockaddr_in s_addr;

    memset(&s_addr, 0, sizeof(struct sockaddr_in));

    int rc = inet_pton_loose(AF_INET, str, &s_addr);
    printf("status = %d\n", rc);
}

int inet_pton_loose(int family, const char *strptr, void *addrptr)
{
    int rc = inet_pton(family, strptr, addrptr);
    if (rc == 0) {
        rc = inet_aton(strptr, addrptr);

        if (rc == 0) {
            return 1;
        }
        return rc;
    }

    return rc;
}
