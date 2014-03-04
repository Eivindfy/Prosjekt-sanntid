#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "client.h"
#include <math.h>



int main(){
	printf("CLIENTTEST: starta programmet\n");
	
	char send_buffer[1024];

	char recv_buffer[1024];
	int floor = 0;
	int socketfd = create_client();
	strcpy(send_buffer,"Initialized\n");
	strcpy(recv_buffer,"0");

	send(socketfd, send_buffer, sizeof(send_buffer), 0);

	recv(socketfd, recv_buffer, sizeof(recv_buffer), 0);
	printf("Recieved: %s\n",recv_buffer); 
	for(int i = 0; i < 3; i++){
		printf("floor : %d\n", floor);
		floor = floor + (recv_buffer[i]-'0') * pow(10.0,(double)(2-i));
	}
	printf("Comand: Go to floor %d \n",floor); 
	sleep(1);
	return 0;
}

