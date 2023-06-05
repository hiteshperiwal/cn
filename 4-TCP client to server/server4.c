#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670
int main()
{
        struct sockaddr_in client, server;

        int sd, nsd, clen = sizeof(client);
        char str[512];
        bzero((char *)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        sd = socket(AF_INET, SOCK_STREAM, 0);
        bind(sd, (struct sockaddr *)&server, sizeof(server));
        listen(sd, 5);
        while (1)
        {
                nsd = accept(sd, (struct sockaddr *)&client, &clen);
                do
                {
                        memset(str, 0x0, 512);
                        recv(nsd, str, 512, 0);
                        printf("\nMessage received from client:%s", str);
                        printf("\nClient's IP:%s", inet_ntoa(client.sin_addr));
                        printf("\nClient's Port:%u", ntohs(client.sin_port));
                } while (strcmp(str, "stop"));
                close(nsd);
        }
}
