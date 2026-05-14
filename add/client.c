// client_add.c
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in server_addr;

    char msg[1024], buffer[1024];

    int a, b;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    connect(sock,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    printf("Enter Two Numbers: ");
    scanf("%d %d", &a, &b);

    sprintf(msg, "%d %d", a, b);

    send(sock, msg, strlen(msg), 0);

    recv(sock, buffer, sizeof(buffer), 0);

    printf("Sum = %s\n", buffer);

    close(sock);

    return 0;
}