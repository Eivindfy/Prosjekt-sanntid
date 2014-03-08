#include "channels.h"
#include "elev.h"
#include "io.h"
#include "global_variables.h"


#include <stdio.h>
#include <sys/socket.h>

#include <assert.h>


//tenker å ha ein thread som går til ein destination og stopper på etasjer som finnes i global_stop_array, så ei utanforløkke som oppdaterer stop_array med hensyn på det den får fra master og rapporterer tilbake. Må ha ein abort-variabel som slutter heisen. FUCK, TRENGER MUTEXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


// global variable direction= 1 for up and -1 for down, 0 for IDLE/stopped




void* floor_control(void* socketfd_void){

int socketfd = *((int*)socketfd_void));
free(socketfd_void);

int floor_request = 0;
char receive_buffer[1024];
char send_buffer[1024];


   while(1){
       
			if(0 > recv(socketfd,receive_buffer,sizeof(receive_buffer),0)){
				perror("Error receiving from main in floor_control\n");
			}
        
			char control_character = receive_buffer[0];

			
        
        // IF GETS SOMETHING FROM TASK MANAGER
			if(control_character>='A' && control_character <= 'Z'){
        
				floor_request = get_floor_from_buffer(receive_buffer);
				if(floor_request < 0){
					perror("could not get proper floor from buffer from main in floor_control\n");
				}
				else{
        
        			if(global_direction==0){
            		set_global_stop_array(floor_request,1);
            		global_destination=floor_request;
						send_buffer[0]='Y';
						insert_floor_into_buffer(send_buffer,9999);
            		send(socketfd,send_buffer,sizeof(send_buffer),0);
        			}
        			else if(  (global_direction==1 && (floor_request>global_current_floor && floor_request<global_destination))    ||    (global_direction==-1 && (floor_request<global_current_floor && floor_request > global_destination))   ){
            		set_global_stop_array(floor_request,1);
            		send_buffer[0]='Y';
						insert_floor_into_buffer(send_buffer,9999);
            		send(socketfd,send_buffer,sizeof(send_buffer),0);                
					}
        			else{
            		send_buffer[0]='N';
						insert_floor_into_buffer(send_buffer,9999);
            		send(socketfd,send_buffer,sizeof(send_buffer),0);
        			}
				}
			}
        
        
        
        
        
        // IF GETS SOMETHING FROM BUTTON
        else if(control_character == 'c'){
				floor_request = get_floor_from_buffer(receive_buffer);
        
                        
        		if(  (global_direction==1 && floor_request > global_destination) || (global_direction==-1 && floor_request < global_destination) ){
            	set_global_stop_array(floor_request,1);
            	global_destination=floor_request;    
				}
        		else{
            	set_global_stop_array(floor_request,1);
        		}
        
    		}    
		}
        else if(control_character == 'r'){
            int stop_array_is_empty = 1;
            if (global_direction == 1){
                for(int i = 0; i > N_FLOORS; i ++){
                    if (get_global_stop_array(i)){
                        global_destination = i;
                        stop_array_is_empty = 0;
                        break;
                    }
                }
            }
				else if (global_direction == -1){
					for(int i = N_FLOORS; i > 0; i--){
                    if (get_global_stop_array(i)){
                        global_destination = i;
                        stop_array_is_empty = 0;
                        break;
                    }
                }
            }
            if(stop_array_is_empty){
                global_direction = 0;
            }
        }
}


int floor_control_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
 	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t flor_control_thread;
                                                                 
	pthread_create(&floor_control_thread,NULL, floor_control, dynamic_voidpointer);
	return fd[1];
}
