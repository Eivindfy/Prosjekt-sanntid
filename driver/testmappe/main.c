//#define MAIN_FILE

//#include "global_variables.h"
#include <stdio.h>
#include "queue.h"
//#include "utility_functions.h"
//#include <string.h>




int main(){
	
	struct ORDER_QUEUE temp;
	order_queue_initialize();
	order_queue_destroy();
	order_queue_initialize();
	order_queue_insert(110,1);
	order_queue_insert(111,1);
	order_queue_insert(110,1);
	order_queue_insert(110,-1);
	
	for(int i=0; i<6;i++){
	
	    if(!order_queue_isempty()){
		temp=order_queue_pop();
		printf("Iteration: %i floor: %i, direction: %i \n",i,temp.floor,temp.direction);
		}
	
	}
	
	
	
	
	return 0;
}
