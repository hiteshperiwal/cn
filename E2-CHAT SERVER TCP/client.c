#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 7000
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
int main()
{
    int sd;
    struct sockaddr_in client, server;
    char str[512], str1[512];
    bzero((char *)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr *)&client, sizeof(client));
    connect(sd, (struct sockaddr *)&server, sizeof(server));
    memset(str1, 0x0, 512, 0);
    recv(sd, str1, 512, 0);
    printf("\n%s\n",str1);
    do
    {

        printf("\nEnter a message to send to server:");
        scanf("%s", str);
        send(sd, str, strlen(str) + 1, 0);
        memset(str1, 0x0, 512);
        recv(sd, str1, 512, 0);
        printf("message from server is %s \n", str1);
    } while (strcmp(str, "stop"));
    close(sd);
}
