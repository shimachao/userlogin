#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "access_to_mysql.h"

#define PORT 0
int main(int argc,char *argv[])
{
	if(init_connect_mysql() != 0)
		return -1;

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == sockfd)
	{
		perror("scoket failed!");
		return -1;
	}
	
	struct sockaddr_in myaddr;
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(PORT);
	if(bind(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr)) != 0)
	{
		perror("bind error!");
		close(sockfd);
		return -1;
	}

	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	socklen_t addrlen = sizeof(clientaddr);
	while(1)
	{
		char buff[1024] ={'\0'};
		ssize_t len = recvfrom(sockfd,(void*)buff,1024,0,(struct sockaddr*)&clientaddr,&addrlen);
		if (len < 0) continue;
	
		size_t emailen = (size_t)buff[0];
		char *email = (char*)malloc(emailen+1);
		bzero(email,emailen+1);
		strncpy(email,(char*)&buff[1],emailen);
		size_t passwordlen = (size_t)buff[1+emailen];
		char *password = (char*)malloc(passwordlen+1);
		bzero(password,passwordlen+1);
		strncpy(password,(char*)&buff[2+emailen],passwordlen);
		//varigy
		signed char reply = 0;
		if(0 != user_verify(email,password))
		{
			reply = -1;
		}
		sendto(sockfd,(void*)&reply,1,0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
		
		free(email);
		free(password);
	}//while
	return 0;
}
