#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main() {
    int server_fd, client_fd;
    socklen_t addrlen;
    int bufsize = 1024;
    int port = 3490;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("server: socket()");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // re-use the address when stopping and restarting the server
    int reuse_addr = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)) < 0) {
        perror("server: setsockopt()");
        close(server_fd);
        exit(1);
    }

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

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *) &address, &addrlen);

        if (client_fd < 0) {
            perror("server: accept");
            continue;
        }

        // set non-blocking socket
        int s_flags;
        if ((s_flags = fcntl(client_fd, F_GETFL, 0)) < 0) {
            perror("server: fcntl");
            continue;
        }
        s_flags |= O_NONBLOCK;
        if (fcntl(client_fd, F_SETFL, s_flags) < 0) {
            perror("server: fcntl");
            continue;
        }

        char *buffer = NULL;
        int bytes_r = 0;
        int total_bytes_r = 0;
        fd_set r_set;

        FD_ZERO(&r_set);
        FD_SET(client_fd, &r_set);
        select(client_fd + 1, &r_set, NULL, NULL, NULL);

        while (1) {
            if (FD_ISSET(client_fd, &r_set)) { // ready to read
                do {
                    if (buffer == NULL) {
                        buffer = malloc(bufsize);
                        if (!buffer) {
                            fprintf(stderr, "No memory\n");
                            exit(1);
                        }
                        memset(buffer, 0, bufsize);
                    } else if (bytes_r > 0) {
                        total_bytes_r += bytes_r;
                        buffer = realloc(buffer, bufsize - 1);
                    }
                } while ((bytes_r = recv(client_fd, buffer + total_bytes_r, bufsize - 1, 0)) > 0);
                break;
            }
        }

        if (errno != EWOULDBLOCK && bytes_r < 0) {
            perror("server: recv");
            close(client_fd);
            continue;
        }

        buffer[total_bytes_r] = '\0';

        free(buffer);

        int fd = open("bowling.jpg", O_RDONLY);
        if (fd == -1) {
            perror("file opening failed");
            close(client_fd);
            continue;
        }

        // get the length (in bytes) of the image
        size_t contents_len = (size_t)lseek(fd, (off_t)0, SEEK_END);
        lseek(fd, (off_t)0, SEEK_SET);
        printf("content length: %ld\n", contents_len);

        char *contents = NULL;
        long read_bytes;
        contents = malloc(contents_len + 1);
        if (!contents) {
            puts("no memory!");
            exit(1);
        }
        memset(contents, 0, contents_len + 1);
        read_bytes = read(fd, contents, contents_len);
        printf("bytes read from image: %ld\n", read_bytes);

        send(client_fd, "HTTP/1.1 200 OK\n", 16, 0);
        send(client_fd, "Content-length: 28616\n", 22, 0);
        send(client_fd, "Content-Type: image/jpeg\n\n", 26, 0);
        send(client_fd, contents, contents_len, 0);
        close(client_fd);
    }
    close(server_fd);
    return 0;
}
