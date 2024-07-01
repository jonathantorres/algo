// A simple multithreaded HTTP server, sends a 200 OK response

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef struct request_args_t {
    int fd;
    char *buff;
    int bufsize;
} request_args_t;

int handle_request(request_args_t *ra);

int main()
{
    int server_fd, client_fd;
    socklen_t addrlen;
    int bufsize = 1024;
    int port = 3490;
    int rc;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;

    if (!buffer) {
        fprintf(stderr, "No memory\n");
        exit(1);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("server: socket()");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("server: bind()");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        perror("server: listen()");
        close(server_fd);
        exit(1);
    }

    printf("Server running on port: %d\n", port);

    pthread_t t;

    while (1) {
        memset(buffer, 0, bufsize);
        client_fd = accept(server_fd, (struct sockaddr *) &address, &addrlen);

        if (client_fd < 0) {
            perror("server: accept");
            continue;
        }

        request_args_t *ra = malloc(sizeof(request_args_t));
        if (!ra) {
            puts("No memory!");
            close(client_fd);
            exit(1);
        }
        memset(ra, 0, sizeof(request_args_t));

        ra->fd = client_fd;
        ra->buff = buffer;
        ra->bufsize = bufsize;

        if ((rc = pthread_create(&t, NULL, (void*)handle_request, ra)) < 0) {
            perror("server: pthread_create");
            close(client_fd);
            free(ra);
            continue;
        }
    }
    close(server_fd);
    return 0;
}

int handle_request(request_args_t *ra)
{
    int client_fd = ra->fd;
    char *buffer = ra->buff;
    int bufsize = ra->bufsize;
    int bytes_r;
    if ((bytes_r = recv(client_fd, buffer, bufsize - 1, 0)) < 0) {
        perror("server: recv");
        return -1;
    }
    buffer[bytes_r] = '\0';

    printf("recv %d bytes\n", bytes_r);
    printf("str len: %ld\n", strlen(buffer));
    printf("%s\n", buffer);

    send(client_fd, "HTTP/1.1 200 OK\n", 16, 0);
    send(client_fd, "Content-length: 46\n", 19, 0);
    send(client_fd, "Content-Type: text/html\n\n", 25, 0);
    send(client_fd, "<html><body><h1>Hello world</h1></body></html>", 46, 0);
    close(client_fd);

    free(ra);

    return bytes_r;
}
