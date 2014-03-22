#ifndef ORDER_HANDELING_H
#define ORDER_HANDELING_H
#include "queue.h"

int handle_message(char* recv_buffer ,int *elevator_status,int *elevator_floor,struct ORDER_QUEUE * floor_status, int socketfd);

#endif
