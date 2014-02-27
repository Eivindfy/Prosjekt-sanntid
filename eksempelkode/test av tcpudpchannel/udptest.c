#include<stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "tcpudpchannel.h"

#define UDPADDRESS "127.0.0.1"
#define UDPPORT 12345
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 12435
#define BUFFERLENGTH 1024

int main(){

	printf("UDPTEST: starta programmet\n");
	
	char send_buffer[1024];
	strcpy(send_buffer,"melding\n");
	char recv_buffer[1024];
	
	int socketfd = initializetcpudpchannel();
	int socketfd2 = initializetcpudpchannel();
	
	
	sleep(2);
	printf("UDPTEST: Sending to socketfd\n");
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	
	//sleep(1);
	printf("UDPTEST: Receiving from socketfd2 \n");
	recv(socketfd2, recv_buffer, sizeof(send_buffer), 0);
	
	printf("her skal melding komme: %s \n", recv_buffer);
	return 0;
}
