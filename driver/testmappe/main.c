//#define MAIN_FILE

//#include "global_variables.h"
#include <stdio.h>
#include "queue.h"
//#include "utility_functions.h"
//#include <string.h>




int main(){
	
	struct order_queue temp;
	order_queue_isempty();
	order_queue_initialize();
	order_queue_insert(0110,1);
	order_queue_insert(0111,1);
	order_queue_insert(0110,1);
	order_queue_insert(0110,-1);
	for(int i=0; i<4;i++){
		temp=order_queue_pop();
		printf("floor: %i, direction: %i \n",temp.floor,temp.direction);
	
	}
	
	
	
	
	return 0;
}
