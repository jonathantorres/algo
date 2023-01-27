#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// An implementation of getnameinfo with a timeout
// it uses an alarm signal to detect the expiration of the timeout

#define HOST_LEN 512

int getnameinfo_timeo(const struct sockaddr *addr, socklen_t addrlen,
        char *host, socklen_t hostlen,
        char *serv, socklen_t servlen, int flags, int timeo);

int main(void)
{
    struct sockaddr_in addr;
    socklen_t addrlen, hostlen, servlen;
    char host[HOST_LEN];
    char serv[HOST_LEN];
    int rc;

    addrlen = sizeof(addr);
    hostlen = sizeof(host);
    servlen = sizeof(serv);

    memset(&addr, 0, sizeof(addr));
    memset(&host, 0, sizeof(host));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);

    if (inet_pton(addr.sin_family, "127.0.0.1", &addr.sin_addr) < 0) {
        perror("inet_pton() error");
        exit(1);
    }

    if ((rc = getnameinfo_timeo((struct sockaddr*)&addr, addrlen, host, hostlen, serv, servlen, 0, 10)) != 0) {
        if (rc == EAI_SYSTEM) {
            perror("getnameinfo_timeo() system error");
            exit(1);
        } else {
            printf("getnameinfo_timeo() error %s\n", gai_strerror(rc));
            exit(1);
        }
    }

    printf("Host: %s\n", host);
    printf("Service: %s\n", serv);

    return 0;
}

void handler(int signum)
{
    // do nothing
    if (signum) {}
    return;
}

int getnameinfo_timeo(const struct sockaddr *addr, socklen_t addrlen,
        char *host, socklen_t hostlen,
        char *serv, socklen_t servlen, int flags, int timeo)
{
    if (timeo > 0) {
        alarm(timeo);
        struct sigaction act, oldact;

        memset(&act, 0, sizeof(act));
        memset(&oldact, 0, sizeof(oldact));

        act.sa_handler = handler;

        if (sigaction(SIGALRM, &act, &oldact) < 0) {
            perror("sigaction() error");
            return EAI_SYSTEM;
        }
    }

    int rc = getnameinfo(addr, addrlen, host, hostlen, serv, servlen, flags);
    if (rc != 0) {
        // timeout
        if (rc == EAI_SYSTEM && errno == EINTR) {
            if (!(flags & NI_NAMEREQD)) {
                if (inet_ntop(addr->sa_family, addr->sa_data, host, hostlen) == NULL) {
                    return EAI_SYSTEM;
                }
            } else {
                return EAI_AGAIN;
            }
        }
    }
    return rc;
}
