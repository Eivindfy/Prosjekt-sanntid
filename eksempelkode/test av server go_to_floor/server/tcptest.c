#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "serverclient.h"

int main(){
	int fd[2];
	int socketfd;
	char send_buffer[1024];
	char recv_buffer[1024];
	int go_to_floor = 2;
	int client_number = 0;
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	socketfd = fd[1];
	pthread_t server;
	pthread_create(&server,NULL, servermodule, (void *) &fd[0]);
 	sleep(2);
	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);
	printf("Recieved: %s \n", recv_buffer);	
	sleep(2);
	for( int i = 0; i < 3; i++){
		send_buffer[i] = go_to_floor/pow(10,2-i) + '0';
	}
	for( int i = 1024-3; i < 3; i++){
    	send_buffer[i] = client_number/pow(10,2-i) + '0';
	}
	send_buffer[3] = '\0';
	printf("Sending: %s \n", send_buffer);
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	return 0;
}
