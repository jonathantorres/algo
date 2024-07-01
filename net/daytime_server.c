#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_fd, conn_fd;
    struct sockaddr_in socket_addr;

    // create the stream socket, TCP, it returns the descriptor
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() An error ocurred");
        exit(1);
    }

    // set default values to the address
    memset(&socket_addr, 0, sizeof(struct sockaddr_in));

    // now, set some settings to the address
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY); // server accepts IPv4 or IPv6
    socket_addr.sin_port = htons(9999); // port 9999

    // use bind to assign an address to the socket
    if (bind(socket_fd, (struct sockaddr *)&socket_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("bind() An error ocurred");
        close(socket_fd);
        exit(1);
    }

    // listen for socket connections
    if (listen(socket_fd, SOMAXCONN) < 0) {
        perror("listen() An error ocurred");
        close(socket_fd);
        exit(1);
    }

    // accept connections
    while (1) {
        conn_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);
        if (conn_fd < 0) {
            perror("accept() An error ocurred");
            close(conn_fd);
            continue;
        }

        // send something
        char *msg = "Daytime data\n";
        if (write(conn_fd, msg, strlen(msg)) < 0) {
            perror("write() An error ocurred");
            close(conn_fd);
            continue;
        }
        close(conn_fd);
    }

    close(socket_fd);
    return 0;
}
