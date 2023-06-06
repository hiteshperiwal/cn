#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"

#define SERVER_PORT 5670
int main()
{
	struct  sockaddr_in client,server;
	time_t ti;
	char * res;
        int sd,nsd;
        char str[512],msg1[512]="invalid";
        bzero((char*)&server,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_port=htons(SERVER_PORT);
        server.sin_addr.s_addr=inet_addr(SERVER_IP);
        sd=socket(AF_INET,SOCK_DGRAM,0);
        bind(sd,(struct sockaddr*)&server,sizeof(server));
        int clen=sizeof(client);
	while(1)
	{
        do{
        memset(str,0x0,512);
	recvfrom(sd,str,512,0,(struct sockaddr*)&client,&clen);
	printf("%s",str);
	if(!strcmp(str,"time"))
	{
        ti=time(NULL);
	res=ctime(&ti);
	sendto(sd,res,strlen(res)+1,0,(struct sockaddr*)&client,clen);;
	}
	else
	{
	sendto(sd,msg1,strlen(msg1)+1,0,(struct sockaddr*)&client,clen);
        }
	}
        while(strcmp(str,"stop"));
}
return 0;
}
