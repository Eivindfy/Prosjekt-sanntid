#include "utility_functions.h"
#define IDLE  0
#define DOWN  1
#define UP  2
#define BUTTON_DOWN 1
#define BUTTON_UP 2
#define BUTTON_BOTH 3
#define BUTTON_NONE 0



handle_message(char* recv_buffer ,int *elevator_status,int *elevator_floor,int *floor_status){
        int elevator_number = get_elevator_from_buffer();
        char send_buffer[1024];
        switch recv_buffer[0]
            case 'I':
                elevator_status[elevator_number] = IDLE;
                for ( int i = 0; i < N_FLOOR; i++){
                    if(floor_status[i] != BUTTON_NONE){
                        
                    }
                } 
            
}
