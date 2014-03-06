#include "utility_functions.h"
#include <stdio.h>




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
		perror("Invalid buffer size in insert_floor_into_buffer\n");
		return 0;
	}
	char floor_string[5];
	floor_to_string(floor,floor_string);
	printf("dette er floor_string i insert_into_buffer: %s \n",floor_string);
	for(int i=0; i<4; i++){
		buffer[i+1]=floor_string[i];
	}
	return 1;
}
