#include <stdio.h>
#include "global_variables.h"
#include "utility_functions.h"
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t destination_lock;

int mutex_init(){
	pthread_mutex_init(&destination_lock, NULL);
	return 1;
}

int set_global_stop_array(int floor, int value){
	//her kan mutexer og sånn komme   return 0 eller -1 if fail
	global_stop_array[floor]=value;

	return 1;
}

int get_global_stop_array(int floor){
	// MUTEX OG GREIER, RETURNER -1 om det failer
	
	return global_stop_array[floor];	
}

int set_global_destination(int value){
	pthread_mutex_lock(&destination_lock);
	global_destination = value;
	pthread_mutex_unlock(&destination_lock);
	return 1;
}


int get_global_destination(){
	pthread_mutex_lock(&destination_lock);
	int temp = global_destination;
	pthread_mutex_unlock(&destination_lock);
	return temp;
}




int floor_to_string(int floor, char* floor_string){
// antar floors mellom 0 og 9999
	if(floor>=0 && floor <= 9999){
		if(floor<10){
			sprintf(floor_string, "000%d", floor);
		}
		else if(floor<100){
			sprintf(floor_string, "00%d",floor);
		}
		else if(floor<1000){
			sprintf(floor_string, "0%d",floor);
		}
		else{
			sprintf(floor_string, "%d",floor);
		}
		return 1;
	}
	else{
		perror("Invalid floor in floor_to_string\n");
		sprintf(floor_string,"%d",-1);
		return 0;
	}
	
}

int insert_floor_into_buffer(int floor, char* buffer){
	if(sizeof(buffer)<5){
		printf("Invalid buffer size in insert_floor_into_buffer\n");
		return 0;
	}
	char floor_string[5];
	floor_to_string(floor,floor_string);
	for(int i=0; i<4; i++){
		buffer[i+1]=floor_string[i];
	}
	return 1;
}

int get_floor_from_buffer(char* buffer){
	if(sizeof(buffer)<5){
		printf("Invalid buffer size in get_floor_from_buffer\n");
		return -1;
	}
	char floor_string[5];
	floor_string[4]='\0';
	for(int i=0; i<4; i++){
		floor_string[i]=buffer[i+1];
	}
		
	int floor = atoi(floor_string);
	
	return floor;
}


int get_elevator_from_buffer(char* buffer){
	if(sizeof(buffer)<8){
		printf("Invalid buffer size in get_elevato_from_buffer: %lu\n",sizeof(buffer));
		return -1;
	}
	char elevator_string[5];
	elevator_string[4]='\0';
	for(int i=0; i<4; i++){
		elevator_string[i]=buffer[i+5];
	}
	int elevator = atoi(elevator_string);
	return elevator;
}

int insert_elevator_into_buffer(int elevator, char* buffer){
	if(sizeof(buffer)<8){
		printf("Invalid buffer size in insert_elevator_into_buffer: %lu\n", sizeof(buffer));
		return -1;
	}
	char elevator_string[5];
	floor_to_string(elevator,elevator_string);
	for(int i=0; i<4; i++){
		buffer[i+5]=elevator_string[i];
	}
	return 1;
}
