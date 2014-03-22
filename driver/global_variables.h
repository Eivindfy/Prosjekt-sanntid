#ifndef GLOBAL_VARIABLES_H


#define N_ELEVATORS 2
#define N_FLOORS 4

#define DIRECTION_UP 1
#define DIRECTION_DOWN -1

#define GLOBAL_VARIABLES_H
#ifdef  MAIN_FILE
int global_direction;
int global_current_floor; // starts at zero 
int global_destination; //	starts at zero
int global_idle;
int global_stop_array[N_FLOORS];
#else
extern int global_direction;
extern int global_current_floor;
extern int global_destination;
extern int global_idle;
extern int global_stop_array[N_FLOORS];
#endif
int initialize_global_variables();

#endif



// HUSK Å DEFINE MAIN FILE I MAIN!!!!!!!


// #define MAIN_FILE     i main!!!!!
