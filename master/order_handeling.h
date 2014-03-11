#ifndef ORDER_HANDELING_H
#define ORDER_HANDELING_H

int handle_message(char* recv_buffer ,int *elevator_status,int *elevator_floor,int *floor_status, int socketfd);

#endif
