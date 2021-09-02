#ifndef INET_PTON_LOOSE_H
#define INET_PTON_LOOSE_H
#include <arpa/inet.h>

int inet_pton_loose(int family, const char *strptr, void *addrptr);
#endif
