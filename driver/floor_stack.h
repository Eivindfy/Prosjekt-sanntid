#ifndef FLOOR_STACK_H
#define FLOOR_STACK_H



#define FLOORSTACKMAXSIZE 128

struct FLOORSTACK {
int stack[FLOORSTACKMAXSIZE];
int top;
};

struct FLOORSTACK floor_stack;


int floor_stack_pop();
int floor_stack_display();
void floor_stack_clear();
int floor_stack_isempty();
int floor_stack_insert(int floor, int up);


#endif
