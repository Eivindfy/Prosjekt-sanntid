#include "global_variables.h"

int initialize_global_variables(){
	global_direction = 0;
	global_current_floor = -1;
	global_destination = -1; 

	for( int i = 0; i < N_FLOORS; i++){
		global_stop_array[i] = 0;
	} 
	return 0;
}
