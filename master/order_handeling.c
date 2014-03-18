#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include "utility_functions.h"
#include "queue.h"
#define IDLE  -1
#define DOWN  1
#define UP  2
#define BUTTON_DOWN 1
#define BUTTON_UP 2
#define BUTTON_BOTH 3
#define BUTTON_PENDING 4
#define BUTTON_NONE 0
#define N_FLOOR 4
#define N_ELEVATOR 2

// Hvis ingen heiser er ledige, vent til ein er ledig


int handle_message(char* recv_buffer ,int *elevator_status,int *elevator_floor,struct ORDER_QUEUE *floor_status, int socketfd){ 
	char send_buffer[1024];
		switch (recv_buffer[0]){
			case 'I':{
				int elevator_number = get_elevator_from_buffer(recv_buffer);
				elevator_status[elevator_number] = IDLE;
				printf("HANDLE_MESSAGE: elevator %i is idle\n",elevator_number);
				if(!order_queue_isempty()){
					int floor_number = order_queue_pop().floor;
					send_buffer[0] = 'R';
					insert_floor_into_buffer(floor_number,send_buffer);
					insert_elevator_into_buffer(elevator_number,send_buffer);
					send(socketfd,send_buffer,sizeof(send_buffer),0);
					//kanskje gi tilbakemelding her
					elevator_status[elevator_number] = floor_number;
				}
				break;
			}
			case 'd':{ printf("HANDLE_MESSAGE: down button pressed\n");
				int floor_number = get_floor_from_buffer(recv_buffer);
				int order_given = 0;
				for (int i = 0; i < N_ELEVATOR; i++){
					if(elevator_status[i] == IDLE){
						send_buffer[0] = 'R';
						insert_floor_into_buffer(floor_number,send_buffer);
						insert_elevator_into_buffer(i,send_buffer);
						send(socketfd,send_buffer,sizeof(send_buffer),0);
						elevator_status[i] = floor_number;
						order_given = 1; 
						printf("HANDLE_MESSAGE: order given to elevator %i\n",i);
						break;
					}
					else if(elevator_floor[i] > floor_number && elevator_status[i] <= floor_number){
						send_buffer[0] = 'R';
						insert_floor_into_buffer(floor_number,send_buffer);
						insert_elevator_into_buffer(i,send_buffer);
						send(socketfd,send_buffer,sizeof(send_buffer),0);
						order_given = 1;
						break;
					}
				}
				if(!order_given){
					order_queue_insert(floor_number,BUTTON_DOWN);
				}
				break;
			}
			case 'u':{
				int floor_number = get_floor_from_buffer(recv_buffer);
				int order_given = 0;
				for (int i = 0; i < N_ELEVATOR; i++){
					if(elevator_status[i] == IDLE){
						send_buffer[0] = 'R';
						insert_floor_into_buffer(floor_number,send_buffer);
						insert_elevator_into_buffer(i,send_buffer);
						send(socketfd,send_buffer,sizeof(send_buffer),0);
						elevator_status[i] = floor_number;
						order_given = 1; 
						break;
					}
					else if(elevator_floor[i] < floor_number && elevator_status[i] >= floor_number){
						send_buffer[0] = 'R';
						insert_floor_into_buffer(floor_number,send_buffer);
						insert_elevator_into_buffer(i,send_buffer);
						send(socketfd,send_buffer,sizeof(send_buffer),0);
						order_given = 1; 
						break;
					}
    			}
    		if(!order_given){
					order_queue_insert(floor_number,BUTTON_UP);
			}
			break;
		}
		case 'r':{
			int elevator_number = get_elevator_from_buffer(recv_buffer);
			int floor_number = get_floor_from_buffer(recv_buffer);
			if(elevator_floor[elevator_number]<elevator_status[elevator_number]){
				order_queue_remove(floor_number,UP);
			}
			else{
				order_queue_remove(floor_number,DOWN);
			}
			break;
		}
		case 'f':{
			elevator_floor[get_elevator_from_buffer(recv_buffer)] = get_floor_from_buffer(recv_buffer);
			break;
		}
		case 'g':{
			elevator_status[get_elevator_from_buffer(recv_buffer)] = get_floor_from_buffer(recv_buffer);
			break;
		}
	}              
	return 1;
}
