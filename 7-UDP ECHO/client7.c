#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 5671
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670
int main()
{
	int sd;
	struct sockaddr_in client, server;
	char str[512], msg[512];
	bzero((char *)&client, sizeof(client));
	int slen = sizeof(server);
	client.sin_family = AF_INET;
	client.sin_port = htons(CLIENT_PORT);
	client.sin_addr.s_addr = inet_addr(CLIENT_IP);
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sd, (struct sockaddr *)&client, sizeof(client));
	do
	{
		printf("\nEnter the message:");
		scanf("%s", str);
		sendto(sd, str, strlen(str) + 1, 0, (struct sockaddr *)&server, sizeof(server));
		memset(msg, 0x0, 512);
		recvfrom(sd, msg, 512, 0, (struct sockaddr *)&server, &slen);
		printf("The echoed message is %s", msg);
	} while (strcmp(str, "stop"));
	close(sd);
}
