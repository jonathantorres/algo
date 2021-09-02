#include "inet_pton_loose.h"

int inet_pton_loose(int family, const char *strptr, void *addrptr)
{
    int rc = inet_pton(family, strptr, addrptr);
    if (rc == 0) {
        int rc2 = inet_aton(strptr, addrptr);
        if (rc2 == 0) {
            return 1;
        }
        return rc2;
    }
    return rc;
}
