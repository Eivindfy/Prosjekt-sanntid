#include<stdio.h>
#include <sys/socket.h>
#include <string.h>


int initializetcpudpchannel();
void *tcpudpchannel(void * tcp_socketfdvoid);

int main(){
	char send_buffer[1024];
	strcpy(send_buffer,"melding");
	char recv_buffer[1024];
	int socketfd = initializetcpudpchannel();
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	recv(socketfd, recv_buffer, sizeof(send_buffer), 0);
	printf("%s \n", recv_buffer);
	return 0;
}
