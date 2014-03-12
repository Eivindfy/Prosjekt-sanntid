#include "elev.h"
#include <stdio.h>
#include "global_variables.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
/*
 *	This function makes the elevator go from one floor to a destination
 *	floor and stopping on intetmidiate floors if the it is ordered so.
 */


int go_to_floor(int socketfd){
		char send_buffer[1024];
		if(global_current_floor < global_destination){ // Sets the direction the elevator is travelling
			elev_set_speed(300);
			global_direction = DIRECTION_UP;
		}
		else if (global_current_floor > global_destination){
			elev_set_speed(-300);
			global_direction = DIRECTION_DOWN;
		}
		else
			return -1;
		// In each iteration the code checks if it has arived on a new floor.
		// If it has it checks the order queue if it whould stop on this floor 
		// evetualy if this is the destination floor it stops and the function returns
		while(1){
			int sensor_signal = elev_get_floor_sensor_signal();
			if (sensor_signal != -1)
			{
				global_current_floor = sensor_signal;
				elev_set_floor_indicator(global_current_floor);
			}
			if(global_current_floor == global_destination){
				elev_set_speed(0);
        send_buffer[0] = 'r';
        insert_floor_into_buffer(global_current_floor, send_buffer);
        send(socketfd,send_buffer,sizeof(send_buffer),0);
        global_stop_array[global_current_floor] = 0;
				return 0;
			}
			else if(global_stop_array[global_current_floor]){
				elev_set_speed(0);
				sleep(1);
				if(global_direction == DIRECTION_UP){
					elev_set_speed(300);
				}
				else if(global_direction == DIRECTION_DOWN){
					elev_set_speed(-300);
				}
				send_buffer[0] = 'v';
				insert_floor_into_buffer(global_current_floor, send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
				global_stop_array[global_current_floor] = 0;
			}
			if(global_current_floor < global_destination && global_direction == DIRECTION_DOWN){
				return -1;
			}
			else if (global_current_floor > global_destination && global_direction == DIRECTION_UP){
				return -1;
			}
		}
}

/*
 *	controll for elevator 
 *	when order are recieved from main
 *	start a loop for the elevator until there are no longer any orders left for the elevator to do 
 *
 *
 */

void * elevator_control(void* socketfd_void){

	int socketfd = * (int* ) socketfd_void;
	char send_buffer[1024];
	if(global_current_floor == -1){
		elev_set_speed(-300);
		while(elev_get_floor_sensor_signal()<0){
			
		}
		elev_set_speed(0);
		global_current_floor = elev_get_floor_sensor_signal();
	}
	global_destination = global_current_floor;

	// delete socketfd_void
	printf("ELEVATOR_CONTROL: global_current_floor is %d\n",global_current_floor);
	printf("ELEVATOR_CONTROL: global_direction is %d\n",global_direction);
  while(1){	
		// check if someting is recieved
		// set variable destination
		usleep(100000);
//		printf("ELEVATOR_CONTROL: global_destination != global_current_floor = %i\n",global_destination != global_current_floor); 
		while(global_destination != global_current_floor || global_stop_array[global_current_floor]){
			printf("ELEVATOR_CONTROL: going to floor %d\n",global_destination);
			if(go_to_floor(socketfd)<0){
				global_stop_array[global_current_floor] = 0;
				send_buffer[0] = 'r';
				insert_floor_into_buffer(global_current_floor, send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
				global_stop_array[global_current_floor] = 0;
			}
		}
	}
	return 0;
}


int elevator_control_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t control_thread;
	
	pthread_create(&control_thread,NULL, elevator_control, dynamic_void_pointer);
	return fd[1];
}
