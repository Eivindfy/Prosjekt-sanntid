#include "channels.h"
#include "elev.h"
#include "io.h"
#include "global_variables.h"
#include "utility_functions.h"


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>

#include <assert.h>


// global variable direction= 1 for up and -1 for down, 0 for IDLE/stopped




void* floor_control(void* socketfd_void){

int socketfd = *((int*)socketfd_void);
free(socketfd_void);

int floor_request = 0;
char receive_buffer[1024];
char send_buffer[1024];


while(1){
	if(0 > recv(socketfd,receive_buffer,sizeof(receive_buffer),0)){
		perror("Error receiving from main in floor_control\n");
	}
	char control_character = receive_buffer[0];
	// IF GETS SOMETHING FROM TASK MANAGER
	if(control_character=='R'){
		floor_request = get_floor_from_buffer(receive_buffer);
		if(floor_request < 0){
			perror("could not get proper floor from buffer from main in floor_control\n");
		}
		else{
			if(global_direction==0){
				set_global_stop_array(floor_request,1);
				set_global_destination(floor_request);
				printf("FLOOR_CONTROL: global_destination= %i\n",get_global_destination());
				send_buffer[0]='Y';
				insert_floor_into_buffer(get_global_destination(),send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
				printf("FLOOR_CONTROL: sent to main: %s\n",send_buffer);
			}
			else if( (global_direction==DIRECTION_UP && (floor_request>global_current_floor && floor_request<get_global_destination())) || (global_direction==DIRECTION_DOWN && (floor_request<global_current_floor && floor_request > get_global_destination()))){
				set_global_stop_array(floor_request,1);
				send_buffer[0]='Y';
				insert_floor_into_buffer(9999,send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
			}
			else{
				send_buffer[0]='N';
				send(socketfd,send_buffer,sizeof(send_buffer),0);
			}
								
		}
								
	}// IF GETS SOMETHING FROM BUTTON
	else if(control_character == 'c'){
		floor_request = get_floor_from_buffer(receive_buffer);
		if (global_current_floor == get_global_destination()){
			set_global_destination(floor_request);
			set_global_stop_array(floor_request,1);
			send_buffer[0] = 'g';
			insert_floor_into_buffer(get_global_destination(), send_buffer);
			send(socketfd,send_buffer,sizeof(send_buffer),0);
		}
		else if((global_direction==1 && floor_request > get_global_destination()) || (global_direction==-1 && floor_request < get_global_destination()) ){
			set_global_stop_array(floor_request,1);
			set_global_destination(floor_request);
			printf("FLOOR_CONTROL: global_destination= %i\n",get_global_destination());
		}
		else{
			set_global_stop_array(floor_request,1);
		}
								
	}
	else if(control_character == 'r'){
		int stop_array_is_empty = 1;
		if (global_direction == DIRECTION_UP){
			for(int i = 0; i < N_FLOORS; i ++){
				if (get_global_stop_array(i)){
					set_global_destination(i);
					stop_array_is_empty = 0;
					send_buffer[0] = 'g';
					insert_floor_into_buffer(get_global_destination(), send_buffer);
					send(socketfd,send_buffer,sizeof(send_buffer),0);
					break;
				}
			}
		}
		else if (global_direction == DIRECTION_DOWN){
			for(int i = N_FLOORS-1; i > 0; i--){
				if (get_global_stop_array(i)){
					set_global_destination(i);
					stop_array_is_empty = 0;
					send_buffer[0] = 'g';
					insert_floor_into_buffer(get_global_destination(), send_buffer);
					send(socketfd,send_buffer,sizeof(send_buffer),0);
					break;
				}
			}
		}
		if(stop_array_is_empty){
			global_direction = 0;
			send_buffer[0]='I';
			insert_floor_into_buffer(9999,send_buffer);
			send(socketfd,send_buffer,sizeof(send_buffer),0);
		}
						
	}
	else if(control_character == 'D'){
		int floor_number = get_floor_from_buffer(receive_buffer);
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor_number,1);
	}
	else if(control_character == 'U'){
		int floor_number = get_floor_from_buffer(receive_buffer);
		elev_set_button_lamp(BUTTON_CALL_UP,floor_number,1);
	}
	else if(control_character == 'B'){
		int floor_number = get_floor_from_buffer(receive_buffer);
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor_number,0);
	}
	else if(control_character == 'A'){
		int floor_number = get_floor_from_buffer(receive_buffer);
		elev_set_button_lamp(BUTTON_CALL_UP,floor_number,0);
	}
				
}
			
}


int floor_control_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
 	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t floor_control_thread;
                                                                 
	pthread_create(&floor_control_thread,NULL, floor_control, dynamic_void_pointer);
	return fd[1];
}
