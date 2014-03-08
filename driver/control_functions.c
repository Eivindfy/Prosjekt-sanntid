#include "elev.h"
#include <stdio.h>
#include "global_variables.h"
/*
 *	This function makes the elevator go from one floor to a destination
 *	floor and stopping on intetmidiate floors if the it is ordered so.
 */


int go_to_floor(int socketfd){
		int direction;
		char send_buffer[1024]
		if current_floor < destination_floor{ // Sets the direction the elevator is travelling
			elev_set_speed(300);
			direction = UP;
		}
		else if current_floor > destination_floor{
			elev_set_speed(-300);
			direction = DOWN;
		}
		else
			return -1;
		// In each iteration the code checks if it has arived on a new floor.
		// If it has it checks the order queue if it whould stop on this floor 
		// evetualy if this is the destination floor it stops and the function returns
		while(1){
			int sensor_signal = elev_get_sensor_signal()
			if (sensor_signal != -1){
			{
				global_current_floor = sensor_signal;
				elev_set_floor_indicator(global_current_floor);
			}
			if(global_current_floor == global_destination_floor){
				elev_set_speed(0);
				return 0;
				send_buffer[0] = 'r';
				insert_floor_into_buffer(global_current_floor, send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
				global_stop_array[global_current_floor] = 0;
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
			if(global_current_floor < global_destination_floor && global_direction == DIRECTION_DOWN){
				return -1;
			}
			else if (global_current_floor > global_destination_floor && global_direction == DIRECTION_UP){
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
	
	// delete socketfd_void

	char recv_buffer[1024];
  while(1){	
		// check if someting is recieved
		// set variable destination
		while(!global_direction){
			if(go_to_floor(socketfd)<0){
				perror("Error in go_to_floor elevator_control\n"); 
			}
		}
	}
}


int elevator_control_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t control_thread;
	
	pthread_create(&control_thread,NULL, elevatro_control, dynamic_voidpointer);
	return fd[2];
}
