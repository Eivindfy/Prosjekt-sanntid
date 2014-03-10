#include "utility_functions.h"
#define IDLE  -1
#define DOWN  1
#define UP  2
#define BUTTON_DOWN 1
#define BUTTON_UP 2
#define BUTTON_BOTH 3
#define BUTTON_PENDING 4
#define BUTTON_NONE 0


// viss ingen heiser er ledige, vent til ein er ledig


int handle_message(char* recv_buffer ,int *elevator_status,int *elevator_floor,int *floor_status, int socketfd){ 
        char send_buffer[1024];
        switch recv_buffer[0]
            case 'I':
                int elevator_number = get_elevator_from_buffer();
                elevator_status[elevator_number] = IDLE;
                for ( int i = 0; i < N_FLOOR; i++){
                    if(floor_status[i] != BUTTON_NONE && floor_status[i] != BUTTON_PENDING){
                       send_buffer[0] = 'R';
                       insert_floor_into_buffer(i,send_buffer);
                       insert_elevator_into_buffer(elevator_number,send_buffer);
                       send(socketfd,send_buffer,sizeof(send_buffer),0);
                       //kanskje gi tilbakemelding her
                       elevator_status[elevator_number] = i;
                       floor_status[i] = floor_status[i] == BUTTON_BOTH ? floor_status[i] = BUTTON_PENDING : floor_status[i] =BUTTON_NONE;
                       break;
                    }
                } 
                case 'd':
                    int floor_number = get_floor_from_buffer();
                    if(floor_status[floor_number] == BUTTON_DOWN || floor_status[floor_number] == BUTTON_NONE){
                        floor_status[floor_number] = BUTTON_DOWN;
                    }
                    else if (floor_status[floor_number] == BUTTON_PENDING) {
                        return 0;
                    }
                    else{
                        floor_status[floor_number] = BUTTON_BOTH;
                    }
                    for (int i = 0; i < N_ELEVATOR; i++){
                        if(elevator_status[i] == IDLE){
                            send_buffer[0] = 'R';
                            insert_floor_into_buffer(floor_number,send_buffer);
                            insert_elevator_into_buffer(elevator_number,send_buffer);
                            send(socketfd,send_buffer,sizeof(send_buffer),0);
                            elevator_status[i] = floor_number;
                            floor_status[floor_number] = floor_status[floor_number] == BUTTON_BOTH ? BUTTON_PENDING : BUTTON_NONE;
                            break;
                        }
                        else if(elevator_floor[i] > floor_number && elevator_status[i] <= floor_number){
                            send_buffer[0] = 'R';
                            insert_floor_into_buffer(floor_number,send_buffer);
                            insert_elevator_into_buffer(elevator_number,send_buffer);
                            send(socketfd,send_buffer,sizeof(send_buffer),0);
                            floor_status[floor_number] = floor_status[floor_number] == BUTTON_BOTH ? BUTTON_PENDING : BUTTON_NONE;
                            break
                        }
                case 'u':
                    int floor_number = get_floor_from_buffer();
                    if(floor_status[floor_number] == BUTTON_UP || floor_status[floor_number] == BUTTON_NONE){
                        floor_status[floor_number] = BUTTON_UP;
                    }
                    else if (floor_status[floor_number] == BUTTON_PENDING) {
                        return 0;
                    }
                    else{
                        floor_status[floor_number] = BUTTON_BOTH;
                    }
                    for (int i = 0; i < N_ELEVATOR; i++){
                        if(elevator_status[i] == IDLE){
                            send_buffer[0] = 'R';
                            insert_floor_into_buffer(floor_number,send_buffer);
                            insert_elevator_into_buffer(elevator_number,send_buffer);
                            send(socketfd,send_buffer,sizeof(send_buffer),0);
                            elevator_status[i] = floor_number;
                            floor_status[floor_number] = floor_status[floor_number] == BUTTON_BOTH ? BUTTON_PENDING : BUTTON_NONE;
                            break;
                        }
                        else if(elevator_floor[i] > floor_number && elevator_status[i] <= floor_number){
                            send_buffer[0] = 'R';
                            insert_floor_into_buffer(floor_number,send_buffer);
                            insert_elevator_into_buffer(elevator_number,send_buffer);
                            send(socketfd,send_buffer,sizeof(send_buffer),0);
                            floor_status[floor_number] = floor_status[floor_number] == BUTTON_BOTH ? BUTTON_PENDING : BUTTON_NONE;
                            break
                        }
                    }

                
            
}
