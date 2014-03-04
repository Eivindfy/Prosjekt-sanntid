#include "floor_stack.h"



int pop_floor_stack(){
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
int push_floor_stack(int floor){
	if(floor_stack.top >= FLOORSTACKMAXSIZE - 1){
		return 0;
	}
	else{
		floor_stack.top=floor_stack.top+1;
		floor_stack.stack[floor_stack.top]=floor;
		return 1;
	}
}

int display_floor_stack(){
	if(floor_stack.top==-1){
		return -1;
	}
	else{
		return floor_stack.stack[floor_stack.top];
	}
}

void clear_floor_stack(){
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


