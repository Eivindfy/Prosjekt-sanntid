#include <stdio.h>
#include <stdlib.h>
#include "tcpudpchannel.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>

void * master_backup(void * socketfd_void){

	int fd_max = 0;
	int tcpsocketfd = *(int*) socketfd_void;
	fd_max = fd_max > tcpsocketfd ? fd_max : tcpsocketfd;
	free(socketfd_void); 
	int udp_socketfd = tcpudpchannel_init();
	fd_max = fd_max > udp_socketfd ? fd_max : udp_socketfd;
	char send_buffer[1024];
	char recv_buffer[1024];
	
	int elevator_alive_status[N_ELEVATOR];

	for( int i = 0; i < N_ELEVATOR; i++){
		elevator_alive_status[i] = -1;
	}
	
	fds_set socket_fd_set;

	FD_ZERO(&socket_fd_set);

	struct timeval timeout;
	timeval.tv_sec = 3*60;
	timeval.tv_usec = 0;

	while(1){
		timeval.tv_sec = 3*60;
		timeval.tv_usec = 0;
		FD_SET(tcpsocketfd, &socket_fd_set);
		FD_SET(udp_socketfd, &socket_fd_set);
		select(fd_max + 1, &socket_fd_set, NULL, NULL, timeout);
		for(int i = 0; i < fd_max; i++){
			if(FD_ISSET(i,&socket_fd_set)){
				if( i == udp_socketfd){
					recv( udp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
					if(recv_buffer[0] = 'i'){
						for(int j = 0; j < N_ELEVATOR; j++){
							if(elevator_alive_status[j] == -1){
								elevator_alive_status[j] = 0;
								break;
							}
						}
						send_buffer[0] = 'm';
						send(udp_socket_fd, send_buffer, sizeof(send_buffer);
					}
				}
				else if(i == tcp_socketfd){
					if(recv_buffer[0] = 'a'){
						int elev_number = get_elevator_from_buffer(recv_buffer);
						elevator_alive_status[elev_number];
					}
				}
			}
		}
	}

}

void * master_backup_init(){
	
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
