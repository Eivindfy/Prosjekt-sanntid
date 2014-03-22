
#define MAIN_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "file_IO.h"
#include "global_variables.h"



int main(){
	int elevator_status[N_ELEVATORS];
	int elevator_floor[N_ELEVATORS];
	order_queue_initialize();
	
	for(int i=0; i<N_ELEVATORS; i++){
		elevator_status[i]=-1;	
		elevator_floor[i]=-1;
	}
	
	int k;
	for(int i=0; i<5; i++){
		k=40+i;
		order_queue_insert(i,k);
	}
	

	
	elevator_status[0]=1;
	elevator_floor[0]=3;
	
	elevator_status[1]=0;
	elevator_floor[1]=2;
	
	write_backup_master("/home/student/Prosjekt-sanntid/master/backup_test/master_backup.txt", elevator_status, elevator_floor, root);
	
	for(int i=0; i<N_ELEVATORS; i++){
		elevator_status[i]=-8;	
		elevator_floor[i]=-8;
	}
	order_queue_destroy();
	order_queue_initialize();
	
	retrieve_backup_master("/home/student/Prosjekt-sanntid/master/backup_test/master_backup.txt", elevator_status, elevator_floor, root);
	
	
	struct ORDER_QUEUE temp;
	for(int i=0; i<N_ELEVATORS; i++){
		printf("iteration: %i, elevator_status[i]: %i, elevator_floor[i]: %i\n", i,elevator_status[i],elevator_floor[i]);
	}
	
	int j=0;
	
	
	while(!order_queue_isempty()){
			temp=order_queue_pop();
			printf("%i :   temp.floor: %i  temp.direction: %i  \n",j,temp.floor,temp.direction);
			j++;
	}
	
	return 0;
	
}
