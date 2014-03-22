#include <stdio.h>
#include <stdlib.h>
#include "tcpudpchannel.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include "global_variables.h"
#include "fault_tolerance_master.h"
#include <string.h>
#include <unistd.h>

struct alive_pack{
	int udp_socket;
	int * elevator_alive;
};

void * master_backup(void * socketfd_void){

	int fd_max = 0;
	int tcpsocketfd = *(int*) socketfd_void;
	fd_max = fd_max > tcpsocketfd ? fd_max : tcpsocketfd;
	free(socketfd_void); 
	int udp_socketfd = tcpudpchannel_init();

	char recv_buffer[1024];
	
	int elevator_alive_status[N_ELEVATORS];

	for( int i = 0; i < N_ELEVATORS; i++){
		elevator_alive_status[i] = -1;
	}

	struct alive_pack my_ap;

	my_ap.udp_socket = udp_socketfd;
	my_ap.elevator_alive =elevator_alive_status;
	
	pthread_t as;
	pthread_create(&as,NULL, alivespam, (void*) &my_ap);
	fd_set socket_fd_set;

	FD_ZERO(&socket_fd_set);

	struct timeval timeout;

	while(1){
		timeout.tv_sec = 0;
		timeout.tv_usec = 500000;
		FD_SET(tcpsocketfd, &socket_fd_set);
//		printf("FAULT_TOLERANCE_MASTER: tcpsocketfd: %d udp_socketfd: %d fd_max: %d \n", tcpsocketfd,udp_socketfd,fd_max);
		select(fd_max + 1, &socket_fd_set, NULL, NULL, &timeout);
		for(int i = 0; i <= fd_max; i++){
			if(FD_ISSET(i,&socket_fd_set)){;
				if( i == tcpsocketfd){
					recv( udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
					printf("FAULT_TOLERANCE_MASTER: recieved message on udp: %c \n", recv_buffer[0]);
					if(recv_buffer[0] == 'i'){
						for(int j = 0; j < N_ELEVATORS; j++){
							if(elevator_alive_status[j] == -1){
								elevator_alive_status[j] = 0;
//								break;
							}
						}
					}
					if(recv_buffer[0] == 'a'){
						int elev_number = get_elevator_from_buffer(recv_buffer);
						elevator_alive_status[elev_number] = 0;
					}
				}
			}
		}
	}
}

int master_backup_init(){
	
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

	int* dynamic_int_pointer = malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t backup;

	pthread_create(&backup,NULL, master_backup, dynamic_void_pointer);

	return fd[1];
}

void * alivespam(void * ap){
	struct alive_pack my_ap = * (struct alive_pack *) ap;
	int * elevator_alive_status = my_ap.elevator_alive;
	int udp_socketfd = my_ap.udp_socket;
	char send_buffer[1024];
	while(1){
		send_buffer[0] = 'A';
		send(udp_socketfd, send_buffer, sizeof(send_buffer), 0);
		for( int i = 0; i < N_ELEVATORS; i++){
			if(elevator_alive_status[i] != -1){
				elevator_alive_status[i]++;
				printf("%d\n",elevator_alive_status[i]);
			}
			if( elevator_alive_status[i] == 5){
				exit(0);
			}
			send_buffer[0] = 'm';
			send_buffer[1] = '\0';
			char * temp = MY_IP;
			usleep(1000000);
			strcat(send_buffer, temp);
			for(int j = 0; j<5; j++){
				send(udp_socketfd, send_buffer, sizeof(send_buffer), 0);
				printf("FAULT_TOLERANCE_MASTER: Sent %s \n", send_buffer);
			}
		}
		usleep(100000);
	}
}
