#ifndef FLOOR_STACK_H
#define FLOOR_STACK_H



#define FLOORSTACKMAXSIZE 128

struct FLOORSTACK {
int stack[FLOORSTACKMAXSIZE];
int top;
};

struct FLOORSTACK floor_stack;


int pop_floor_stack();
int push_floor_stack();
int display_floor_stack_top();
void clear_floor_stack();


#endif