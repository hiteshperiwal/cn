#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
int main()
{
    struct sockaddr_in client, server;

    int sd, clen = sizeof(client);
    char str[512];
    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sd, (struct sockaddr *)&server, sizeof(server));

    while (1)
    {
        do
        {
            memset(str, 0x0, 512);
            recvfrom(sd, str1, 512, 0, (struct sockaddr *)&client, &clen);
            sendto(sd, str, strlen(str) + 1, 0, (struct sockaddr *)&client, &clen);
        } while (strcmp(str, "stop"));
    }
}