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
    int sd, w, i, j, count = 0;
    struct sockaddr_in client, server;
    char str[512], buff[512], ack[512];
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
    do
    {

        printf("\nEnter a message ");
        scanf("%s", str);
        printf("\n enter winfow size");
        scanf("%d", &w);
        j = 0;
        count = 0;
        for (i = 0; i < strlen(str); i++)
        {
            if (j < w)
            {
                buff[j] = str[i];
                j++;
            }
            if (j == w || i == strlen(str) - 1)
            {
                buff[j] = '\0';
                send(sd, buff, strlen(buff) + 1, 0);
                memset(ack, 0x0, 512);
                recv(sd, ack .512, 0);
                printf("%s%d\n", ack, count++);
                j = 0;
            }
        }
    } while (strcmp(str, "stop"));
    close(sd);
}