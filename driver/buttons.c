#include "elev.c"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>



int button_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);
	
	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
   	*dynamic_int_pointer = fd[0];
	 void* dynamic_void_pointer;
   	dynamic_void_pointer = (void*)dynamic_int_pointer;
	
	pthread_t button_thread;

	pthread_create(&button_thread,NULL, button_return, dynamic_voidpointer);
	return fd[2];
}


void* button_return(void * socket_fd_void){
	int socket_fd = * (int *) socket_fd_void;
	char send_buffer[1024];
	while(1){
		for (i = 1; i < 3; ++i){
			if (elev_get_button_signal(BUTTON_CALL_DOWN, i)){
				send_buffer[0]='d';
				send_buffer[1]= '0'+i;
				send_buffer[2]= '\0';
				send(socket_fd, send_buffer, sizeof(send_buffer),0);
			}

		}
		for (i = 0; i < 2; ++i){
			if (elev_get_button_signal(BUTTON_CALL_UP, i)){
				send_buffer[0] = 'u';
				send_buffer[1] = '0'+i;
				send_buffer[2] = '\0';
				send(socket_fd, send_buffer, sizeof(send_buffer), 0);
			}


		}
		for (i = 0; i < 3; ++i){
			if(elev_get_button_signal(BUTTON_COMMAND, i)){
				send_buffer[0] = 'c';
				send_buffer[1] = '0'+i;
				send_buffer[2] = '\0';
				send(socket_fd, send_buffer, sizeof(send_buffer), 0);
			}
		if(elev_get_stop_signal()){
				send_buffer[0] = 's';
				send_buffer[1] = '0';
				send_buffer[2] = '\0';
				send socket_fd, send_buffer, sizeof(send_buffer), 0);
		}


		}
	}
}
