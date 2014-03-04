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
	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);
	while(1){
		printf("Write floor you want the elevator to go to: ");
		scanf("%d", &go_to_floor);
		for( int i = 0; i < 3; i++){
			send_buffer[i] = (int)(go_to_floor/pow(10,2-i)) % 10 + '0';
		}
		for( int i = 0; i < 3; i++){
    		send_buffer[1021+i] = client_number/pow(10,2-i) + '0';
		}
		send_buffer[3] = '\0';
		send(socketfd, send_buffer, sizeof(send_buffer), 0);
	}
	sleep(1);
	return 0;
}
