#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>

#include "elev.h"
#include "buttons.h"
#include "utility_functions.h"

int button_initialize(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);
	

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
   *dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
   dynamic_void_pointer = (void*)dynamic_int_pointer;
	
	pthread_t button_thread;

	pthread_create(&button_thread,NULL, button_return, dynamic_voidpointer);
	return fd[1];
}


void* button_return(void * socket_fd_void){
	int socket_fd = * (int *) socket_fd_void;
	free(socket_fd_void);
	
	
	char send_buffer[1024];
	send_buffer[5]='\0';
	while(1){
		for (int i = 1; i < N_FLOORS; i++){
			if (elev_get_button_signal(BUTTON_CALL_DOWN, i)){
				send_buffer[0]='d';
				insert_floor_into_buffer(i,send_buffer);
				send(socket_fd, send_buffer, sizeof(send_buffer),0);
			}

		}
		for (int i = 0; i < N_FLOORS-1; i++){
			if (elev_get_button_signal(BUTTON_CALL_UP, i)){
				send_buffer[0] = 'u';
				insert_floor_into_buffer(i,send_buffer);
				send(socket_fd, send_buffer, sizeof(send_buffer), 0);
			}


		}
		for (int i = 0; i < N_FLOORS; i++){
			if(elev_get_button_signal(BUTTON_COMMAND, i)){
				send_buffer[0] = 'c';
				insert_floor_into_buffer(i,send_buffer);
				send(socket_fd, send_buffer, sizeof(send_buffer), 0);
			}
		if(elev_get_stop_signal()){
				send_buffer[0] = 's';
				send_buffer[1] = '-';
				send_buffer[2] = '-';
				send_buffer[3] = '-';
				send_buffer[4] = '-';
				send(socket_fd, send_buffer, sizeof(send_buffer), 0);
		}


		}
	}
}
