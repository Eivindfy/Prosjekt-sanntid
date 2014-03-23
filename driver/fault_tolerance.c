#include <stdio.h>		//inkludet stdio og stdlib
#include <stdlib.h>
#include "tcpudpchannel.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include "fault_tolerance.h"
#include <unistd.h>

void * backup_module(void * socketfd_void){
	int tcpsocketfd = *(int*) socketfd_void;
	free(socketfd_void);									// endret fra 'tcp_socketfd_void' til 'socket_fd'
	int udp_socketfd = tcpudpchannel_init();
	char send_buffer[1024]; 							// flyttet [1024]
	char recv_buffer[1024];
	send_buffer[0] = 'i';  // initialized 
	fd_set udp_fd_set;
	FD_ZERO(&udp_fd_set);
	struct timeval timeout;
	for(int i = 0; i <10; i++){
		timeout.tv_sec = 0;
		timeout.tv_usec = 500000;
//		printf("FAULT_TOLERANCE: waiting on master \n");
		FD_SET(udp_socketfd,&udp_fd_set);
		select(udp_socketfd + 1, &udp_fd_set, NULL, NULL, &timeout);
		if(FD_ISSET(udp_socketfd, &udp_fd_set)){
			recv(udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
//			printf("FAULT_TOLERANCE: recieved message: %s\n", recv_buffer);
			if(recv_buffer[0] == 'm'){
				printf("FAULT_TOLERANCE: master found\n");
				break;
			}
		}
		else if(i == 4){
			printf("FAULT_TOLERANCE: No answer from master\n");
			exit(0);
				//this is master
		}
	}
	sleep(1);
	send(tcpsocketfd, send_buffer, sizeof(send_buffer), 0); //fylte
	int number_of_misses = 0;
	while(1){
		FD_SET(udp_socketfd,&udp_fd_set);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
//		printf("FAULT_TOLERANCE: waiting on master \n");
		select(udp_socketfd+1, &udp_fd_set, NULL, NULL, &timeout);
		if(FD_ISSET(udp_socketfd, &udp_fd_set)){
			recv(udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
			if(recv_buffer[0] == 'm'){
				send_buffer[0] = 'a';
				send(tcpsocketfd, send_buffer, sizeof(send_buffer), 0);
				number_of_misses = 0;
//				printf("FAULT_TOLERANCE: sent %s \n", send_buffer);
			}
		}
		else{
				number_of_misses++;

		}
		
		if(number_of_misses == 5){
			printf("FAUOLT_TOLERANCE: Master is dead\n");
			exit(0);
		}
	}
}


int backup_module_init(){

	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);


	int* dynamic_int_pointer = malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;


	pthread_t backup;

	pthread_create(&backup,NULL, backup_module, dynamic_void_pointer);

	return fd[1];

}
