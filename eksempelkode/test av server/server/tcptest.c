#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "serverclient.h"

int main(){
	int fd[2];
	int socketfd;
	char send_buffer[1024];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	socketfd = fd[1];
	pthread_t server;
	pthread_create(&server,NULL, servermodule, (void *) &fd[0]);
 	sleep(2);
	recv(socketfd, send_buffer, sizeof(send_buffer), 0);

	printf("Recived message: %s \n", send_buffer);
	printf("Write the message you want to send: ");
  scanf("%s",send_buffer);

	for( int i = 0; i < 3; i++){
		send_buffer[1024-3+1] = '0';
	}
	printf("TCPTEST: Sending to socketfd: %s\n", send_buffer);
	if(send(socketfd, send_buffer, sizeof(send_buffer), 0) <0){
		perror("TCPTEST: error sending");
	}
	printf("TCPTEST: Sendt to socketfd\n");
	recv(socketfd, send_buffer, sizeof(send_buffer), 0);
	return 0;
}
