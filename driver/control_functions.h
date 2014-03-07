#ifndef CONTROL_FUNCTIONS_H
#define CONTROL_FUNCTIONS_H

int go_to_floor(int socketfd);

void * elevator_control(void* socketfd_void);

int elevator_control_init();

#endif
