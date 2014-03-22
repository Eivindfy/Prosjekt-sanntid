#define MAIN_FILE

#include "global_variables.h"
#include <stdio.h>
#include "client_backup.h"
//#include "utility_functions.h"
#include <string.h>




int main(){
	
	initialize_global_variables();
	
	global_direction = 20;
	global_idle = 30;
	global_destination = 40;
	global_current_floor = 50;
	
	global_stop_array[0]=-5;
	global_stop_array[1]=2;
	global_stop_array[2]=3;
	global_stop_array[3]=-4;
	char buffer[1024];
	
	
	write_backup_client("/home/student/Prosjekt-sanntid/driver/testmappe/hei.txt");
	
	
	backup_tostring_client("/home/student/Prosjekt-sanntid/driver/testmappe/hei.txt",buffer,sizeof(buffer));
	
	printf("dette er etter tostring: %s  \n",buffer);
	
	
	
	initialize_global_variables();
	global_direction = -8;
	global_idle = -8;
	global_destination = -8;
	global_current_floor = -8;
	
	
	retrieve_backup_client("/home/student/Prosjekt-sanntid/driver/testmappe/hei.txt");
	
	printf("global_direction: %i, global_idle: %i, global_destination: %i, global_current_floor: %i\n", global_direction, global_idle, global_destination, global_current_floor);
	
	for(int i = 0 ; i < N_FLOORS ; i++){
    	printf("%i: %i\n",i,global_stop_array[i]);
    }
    
	
	
	
	
	return 0;
}
