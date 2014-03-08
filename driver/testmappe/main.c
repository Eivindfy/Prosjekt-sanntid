#define MAIN_FILE

#include "global_variables.h"
#include <stdio.h>
#include "utility_functions.h"
#include <string.h>




int main(){
	global_stop_array[1]=1;
	printf("før funk: %i\n", global_stop_array[1]);
	set_global_stop_array(1,0);
	printf("etter funk: %i\n", global_stop_array[1]);
	char buffer[1024];
	strcpy(buffer,"d0104");
	int floor = 0;
	floor = get_floor_from_buffer(buffer);
	printf("%i \n", floor);	
	insert_floor_into_buffer(floor, buffer);
	printf("buffer : %s \n", buffer);
	
	
	
	return 0;
}
