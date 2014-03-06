#include "channels.h"
#include "elev.h"
#include "io.h"


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
       
        //RECEIVE FROM SOCKETFD
        if(0 > recv(socketfd,receive_buffer,sizeof(receive_buffer),0)){
        perror("Error receiving from main in floor_control\n");
        }
        
        //
        // IF GETS SOMETHING FROM TASK MANAGER
        //
        
        floor_request = ;// logikk for å ta ut i fra buffer
        
        if(direction==0){
            stop_array[floor_request]=1;
            destination=floor_request;
            //send confirmation to task manager
        }
        else if(  (direction==1 && (floor_request>current_floor && floor_request<destination))    ||    (direction==-1 && (floor_request<current_floor && floor_request > destination))   ){
            stop_array[floor_request]=1;
            //send confirmation to task manager                
        }
        else{
        
            //send declination to task manager
        }
        
        
        
        
        // ENDIF
        
        
        
        //
        // IF GETS SOMETHING FROM BUTTON
        //
        
        floor_request = ;// Logikk for å ta ut i frå buffer
        
                        
        if(  (direction==1 && floor_request > destination) || (direction==-1 && floor_request < destination) ){
            stop_array[floor_request]=1;
            destination=floor_request;    
        }
        else{
            stop_array[floor_request]=1;
        }
        
        
   }
}


int floor_control_init(){
	int fd[3];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
 	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t flor_control_thread;
                                                                 
	pthread_create(&floor_control_thread,NULL, floor_control, dynamic_voidpointer);
	return fd[2];
}
