#include "elev.h"
#include <stdio.h>
/*
 *	This function makes the elevator go from one floor to a destination
 *	floor and stopping on intetmidiate floors if the it is ordered so.
 */


int go_to_floor(int socketfd){
		int current_floor = get_current_floor(); //placeholder
		int destination_floor = get_destination_floor() //placeholder
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
			if (sensor_signal == -1){
			
			}
			else{
				current_floor = sensor_signal;
				elev_set_floor_indicator(current_floor);
			}
			if(stop_array[current_floor]){ //placeholder
				elev_set_speed(0);
				sleep(1);
				if(direction == UP){
					elev_set_speed(300);
				}
				else if(direction == DOWN){
					elev_set_speed(-300);
				}
				//sending "floor visited" to main
				//set buffer acordingly
				send(socketfd,send_buffer,sizeof(send_buffer),0);
			}
			if(current_floor == destination_floor){
				elev_set_speed(0);
				return 0;
				//sending "destination reached" to main
				//set buffer acordingly
				send(socketfd,send_buffer,sizeof(send_buffer),0);
			}
			if(current_floor < destination_floor && direction == DOWN){
				return -1;
			}
			else if (current_floor > destination_floor && direction == UP){
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
		if(recv(socketfd,recv_buffer,sizeof(recv_buffer),0) < 0){
			perror("Error recieving in elevator_control");
		}
		// check if someting is recieved
		// set variable destination
		while(!idle){
			if(go_to_floor(socketfd)<0){
				perror("Error in go_to_floor elevator_control"); 
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
