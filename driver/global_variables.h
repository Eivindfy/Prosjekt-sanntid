#ifndef GLOBAL_VARIABLES_H


#define N_ELEVATORS 1
#define N_FLOORS 4

#define DIRECTION_UP 1
#define DIRECTION_DOWN -1
#define MY_IP "129.241.187.156"

#define GLOBAL_VARIABLES_H
#ifdef  MAIN_FILE
int global_direction;
int global_current_floor; // starts at zero 
int global_destination; //	starts at zero
int global_idle;
int global_stop_array[N_FLOORS];
char* global_host_ip;
#else
extern int global_direction;
extern int global_current_floor;
extern int global_destination;
extern int global_idle;
extern char* global_host_ip;
extern int global_stop_array[N_FLOORS];
#endif
int initialize_global_variables();

#endif



// HUSK Å DEFINE MAIN FILE I MAIN!!!!!!!


// #define MAIN_FILE     i main!!!!!
