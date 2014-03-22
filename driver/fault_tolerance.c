#include <stdio.h>		//inkludet stdio og stdlib
#include <stdlib.h>
#include "tcpudpchannel.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include "fault_tolerance.h"

void * backup_module(void * socketfd_void){
	int tcpsocketfd = *(int*) socketfd_void;
	free(socketfd_void);									// endret fra 'tcp_socketfd_void' til 'socket_fd'
	int elevator_number;
	int udp_socketfd = tcpudpchannel_init();
	char send_buffer[1024]; 							// flyttet [1024]
	char recv_buffer[1024];
	send_buffer[0] = 'i';  // initialized 
	fd_set udp_fd_set;
	FD_ZERO(&udp_fd_set);
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	for(int i = 0; i <5; i++){
		send(udp_socketfd, send_buffer, sizeof(send_buffer), 0); //fylte ut argumenter
	}
	for(int i = 0; i < 5; i++){
		FD_SET(udp_socketfd,&udp_fd_set);
		select(udp_socketfd + 1, &udp_fd_set, NULL, NULL, timeout);
		if(FD_ISSET(udp_socketfd, &udp_fd_set)){
			recv(udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
			if(recv_buffer[0] = 'm'){
				elevator_number = get_elevator_from _buffer(recv_buffer);
				break;
			}
		}
		else if(i == 4){
				//this is master
		}
	}
	int number_of_misses = 0;
	while(1){
		FD_SET(udp_socketfd,&udp_fd_set);
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		select(2, &udp_fd_set, NULL, NULL, timeout);
		if(FD_ISSET(udp_socketfd, &udp_fd_set)){
			recv(udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
			if(recv_buffer[0] = 'A'){
				send_buffer[0] = 'a';
				insert_elevator_into_buffer(elevator_number, send_buffer);
				send(udp_socketfd, send_buffer, sizeof(send_buffer), 0);
				number_of_misses = 0;
			}
			else{
				number_of_misses++;
			}
		}
		if(number_of_misses == 5){
			// restart
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
