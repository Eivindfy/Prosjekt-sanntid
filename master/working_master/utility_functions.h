#ifndef utility_functions_h
#define utility_functions_h


int floor_to_string(int floor, char* string);
int insert_floor_into_buffer(int floor, char* buffer);
int get_floor_from_buffer(char* buffer);
int set_global_stop_array(int floor, int value);
int get_global_stop_array(int floor);
int get_elevator_from_buffer(char* buffer);
int insert_elevator_into_buffer(int elevator, char* buffer);
int get_global_destination();
int set_global_destination(int value);
int mutex_init();

#endif
