#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_fd, bytes_read;
    struct sockaddr_in socket_addr;
    char buffer[100];

    // create the stream socket, TCP, it returns the descriptor
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket: An error ocurred!\n");
    }

    // set default values to the address
    memset(&socket_addr, 0, sizeof(struct sockaddr_in));

    // now, set some settings to the address
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(9999); // port 9999

    // convert ip address to network (something that the computer understands)
    if (inet_pton(AF_INET, "127.0.0.1", &socket_addr.sin_addr) <= 0) {
        perror("inet_pton() An error ocurred");
        close(socket_fd);
        exit(1);
    }

    // attempt to connect to the socket
    if (connect(socket_fd, (struct sockaddr *)&socket_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("connect() An error ocurred");
        close(socket_fd);
        exit(1);
    }

    // read data from the socket
    while ((bytes_read = read(socket_fd, buffer, 100)) > 0) {
        buffer[bytes_read] = '\0'; // terminate the received string

        // write data to stdout
        if (fputs(buffer, stdout) == EOF) {
            perror("fputs() An error ocurred");
            close(socket_fd);
            exit(1);
        }
    }

    // failed to read data
    if (bytes_read < 0) {
        fputs("Error reading the data", stderr);
        close(socket_fd);
        exit(1);
    }

    exit(0);

    return 0;
}
