// server_reverse.c
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {

    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024], result[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Server Waiting...\n");

    client_fd = accept(server_fd, NULL, NULL);

    recv(client_fd, buffer, sizeof(buffer), 0);

    int len = strlen(buffer);

    if(buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
        len--;
    }

    for(int i=0; i<len; i++) {
        result[i] = buffer[len-i-1];
    }

    result[len] = '\0';

    send(client_fd, result, strlen(result), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}