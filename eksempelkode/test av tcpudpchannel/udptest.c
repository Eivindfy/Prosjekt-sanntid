#include<stdio.h>
#include <sys/socket.h>
#include <string.h>

#include "tcpudpchannel.h"

#define UDPADDRESS "127.0.0.1"
#define UDPPORT 1234
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 1243
#define BUFFERLENGTH 1024

int main(){

	printf("starta programmet\n");
	char send_buffer[1024];
	strcpy(send_buffer,"melding\n");
	printf("starta programmet 2\n");
	char recv_buffer[1024];
	int socketfd = initializetcpudpchannel();
	printf("starta programmet 3\n");
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	printf("starta programmet 4\n");
	recv(socketfd, recv_buffer, sizeof(send_buffer), 0);
	printf("starta programmet 5\n");
	printf("%s \n", recv_buffer);
	return 0;
}


