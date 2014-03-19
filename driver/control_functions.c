#include "elev.h"
#include <stdio.h>
#include "global_variables.h"
#include "utility_functions.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
/*
 *	This function makes the elevator go from one floor to a destination
 *	floor and stopping on intetmidiate floors if the it is ordered so.
 */


int go_to_floor(int socketfd){
		char send_buffer[1024];
		if(global_current_floor < get_global_destination()){ // Sets the direction the elevator is travelling
			elev_set_speed(300);
			global_direction = DIRECTION_UP;
			printf("GO_TO_FLOOR: elev_set_speed(300)\n");
		}
		else if (global_current_floor > get_global_destination()){
			elev_set_speed(-300);
			global_direction = DIRECTION_DOWN;
			printf("GO_TO_FLOOR: elev_set_speed(300)\n");
		}
		else
			return -1;
		printf("GO_TO_FLOOR: global_destination = %i\n",get_global_destination());
		printf("GO_TO_FLOOR: global_current_floor = %i\n", global_current_floor);
		for(int i = 0; i < 4; i++){
			printf("GO_TO_FLOOR: global_stop_array[%i] = %i\n", i, global_stop_array[i]);
		}
		// In each iteration the code checks if it has arived on a new floor.
		// If it has it checks the order queue if it whould stop on this floor 
		// evetualy if this is the destination floor it stops and the function returns
		while(1){
			int sensor_signal = elev_get_floor_sensor_signal();
			if (sensor_signal != -1 && global_current_floor != sensor_signal)
			{
				global_current_floor = sensor_signal;
				elev_set_floor_indicator(global_current_floor);
				send_buffer[0] = 'f';
				insert_floor_into_buffer(global_current_floor, send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
			}
			if(global_current_floor == get_global_destination()){
				elev_set_speed(0);
        send_buffer[0] = 'r';
        insert_floor_into_buffer(global_current_floor, send_buffer);
        send(socketfd,send_buffer,sizeof(send_buffer),0);
        global_stop_array[global_current_floor] = 0;
				//global_direction = 0;
				elev_set_button_lamp(BUTTON_COMMAND,global_current_floor,0);
				return 0;
			}
			else if(global_stop_array[sensor_signal]){
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
				elev_set_button_lamp(BUTTON_COMMAND,global_current_floor,0);
			}
			if(global_current_floor < get_global_destination() && global_direction == DIRECTION_DOWN){
				return -1;
			}
			else if (global_current_floor > get_global_destination() && global_direction == DIRECTION_UP){
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
	if (!elev_init()) {
		printf(__FILE__ ": Unable to initialize elevator hardware\n");
	}
	int socketfd = * (int* ) socketfd_void;
	char send_buffer[1024];
	elev_set_speed(0);
	if(global_current_floor == -1){
		elev_set_speed(-300);
		printf("ELEVATOR_CONTROL: elev_set_speed(-300)\n");
		while(elev_get_floor_sensor_signal()!=0){
			
		}
		printf("ELEVATOR_CONTROL: elev_set_speed(0)\n");
		elev_set_speed(0);
		global_current_floor = elev_get_floor_sensor_signal();
	}
	set_global_destination(global_current_floor);

	// delete socketfd_void
	printf("ELEVATOR_CONTROL: global_current_floor is %d\n",global_current_floor);
	printf("ELEVATOR_CONTROL: global_direction is %d\n",global_direction);
  while(1){	
		// check if someting is recieved
		// set variable destination
		usleep(100000);
//		printf("ELEVATOR_CONTROL: global_destination != global_current_floor = %i\n",global_destination != global_current_floor); 
		while(get_global_destination() != global_current_floor || global_stop_array[global_current_floor]){
			printf("ELEVATOR_CONTROL: going to floor %d\n",get_global_destination());
			assert(get_global_destination()<4);
			if(go_to_floor(socketfd)<0){
				global_stop_array[global_current_floor] = 0;
				send_buffer[0] = 'r';
				insert_floor_into_buffer(global_current_floor, send_buffer);
				send(socketfd,send_buffer,sizeof(send_buffer),0);
				global_stop_array[global_current_floor] = 0;
			}
			sleep(1);
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
