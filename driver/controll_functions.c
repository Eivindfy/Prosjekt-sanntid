#include "elev.h"
#include <stdio.h>
/*
 *	This function makes the elevator go from one floor to a destination
 *	floor and stopping on intetmidiate floors if the it is ordered so.
 */


int go_to_floor(){
		int current_floor = get_current_floor(); //placeholder
		int destination_floor = get_destination_floor() //placeholder
		int direction;
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
			if(stop_order(current_floor)){ //placeholder
				elev_set_speed(0);
				sleep(1);
				if(direction == UP){
					elev_set_speed(300);
				}
				else if(direction == DOWN){
					elev_set_speed(-300);
				}
			}
			if(current_floor == destination_floor){
				elev_set_speed(0);
				return 0;
			}
			if(current_floor < destination_floor && direction == DOWN){
				return -1;
			}
			else if (current_floor > destination_floor && direction == UP){
				return -1;
			}
		}
}
