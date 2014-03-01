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
	char recv_buffer[1024];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	socketfd = fd[1];
	pthread_t server;
	pthread_create(&server,NULL, servermodule, (void *) &fd[0]);
 	sleep(2);
	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);

	printf("Recived message: %s \n", recv_buffer);
//	printf("Write the message you want to send: ");
//	scanf("%s",send_buffer);
	sleep(2);
	strcpy(send_buffer,"hei");
	for( int i = 0; i < 3; i++){
		send_buffer[1024-3+i] = '0';
	}
	printf("TCPTEST: Sending to socketfd: %s , %d\n", send_buffer,socketfd);
	if(send(socketfd, send_buffer, sizeof(send_buffer), 0) <=0){
		perror("TCPTEST: error sending");
	}
	printf("TCPTEST: Sendt to socketfd, %d \n", socketfd);
	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);
	printf("Message recieved: %s\n", recv_buffer);
	return 0;
}
