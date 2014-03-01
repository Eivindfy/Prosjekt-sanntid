#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "client.h"



int main(){
	printf("CLIENTTEST: starta programmet\n");
	
	char send_buffer[1024];
	strcpy(send_buffer,"melding");
	char recv_buffer[1024];
	printf("CLIENTTEST: creating client\n");
	int socketfd = create_client();
	printf("CLIENTTEST: client created\n");
	sleep(2);
	printf("CLIENTTEST: Sending to socketfd: %s \n", send_buffer);
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	printf("CLIENTTEST: Recieving from socketfd \n");
	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);
	printf("CLIENTTEST: Recieved from socketfd \n");
	printf("Message from server: %s", recv_buffer);

	printf("CLIENTTEST: Sending to socketfd\n");
	send(socketfd, send_buffer, sizeof(send_buffer), 0);
	return 0;
}

