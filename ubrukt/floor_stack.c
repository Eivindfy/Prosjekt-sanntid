#include "floor_stack.h"
#include "global_variables.h"



int floor_stack_pop(){
	if(floor_stack.top==-1){
		return -1;
	} 
	else{
		int temp = floor_stack.stack[floor_stack.top];
		floor_stack.top=floor_stack.top-1;
		return temp;
	}

}

// returns 0 if unsuccessful
int floor_stack_insert(int floor, int up){
	if(floor_stack.top >= FLOORSTACKMAXSIZE - 1){
		return 0;
	}
	else{
	
	   for(int i=0; 
		floor_stack.top=floor_stack.top+1;
		floor_stack.stack[floor_stack.top]=floor;
		return 1;
	}
}

int floor_stack_display(){
	if(floor_stack.top==-1){
		return -1;
	}
	else{
		return floor_stack.stack[floor_stack.top];
	}
}

void floor_stack_clear(){
	floor_stack.top=-1;
	
	/*
	for(int i=0; i<FLOORSTACKMAXSIZE; i++){
		floor_stack.stack[i]=-1;
	}*/
}

int floor_stack_isempty(){
	if(floor_stack.top==-1){
		return 1;
	}
	else{
		return 0;
	}
}

