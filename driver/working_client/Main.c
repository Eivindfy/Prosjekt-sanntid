#define MAIN_FILE
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include "buttons.h"
#include "serverclient.h"
#include "control_functions.h"
#include "floor_control.h"
#include "tcpudpchannel.h"
#include "global_variables.h"
//#define NULL 0


int main(){
	int maxfd = 0;
//	int udp_socketfd = tcpudpchannel_init();
//	maxfd = udp_socketfd;
// Maybe check if there is a master server here
	initialize_global_variables();
	mutex_init();
	int tcp_socketfd = client_init();
	maxfd = tcp_socketfd > maxfd ? tcp_socketfd : maxfd;
	int button_socketfd = button_init();
	maxfd = button_socketfd > maxfd ? button_socketfd : maxfd;
	int elevator_control_socketfd = elevator_control_init();
	maxfd = elevator_control_socketfd > maxfd ? elevator_control_socketfd : maxfd;
	printf("MAIN: elevator control initiated\n");
	int floor_control_socketfd = floor_control_init();
	maxfd = floor_control_socketfd > maxfd ? floor_control_socketfd : maxfd;
	printf("MAIN: floor control initiated\n");
	printf("MAIN: global variables initiated\n");

	fd_set socket_set;
	FD_ZERO(&socket_set);
	struct timeval timeout;
	char recv_buffer[1024];
	
	while(1){
//	  printf("MAIN: making socket set for tcp:%d\n", tcp_socketfd);
		timeout.tv_sec = 3*60;
		timeout.tv_usec = 0;
//        FD_SET(udp_socketfd ,&socket_set);
 	  FD_SET(tcp_socketfd ,&socket_set);
//		printf("MAIN: making socket set for button:%d\n", button_socketfd);
    FD_SET(button_socketfd ,&socket_set);
//		printf("MAIN: making socket set for elevator control:%d\n", elevator_control_socketfd);
    FD_SET(elevator_control_socketfd ,&socket_set);
//		printf("MAIN: making socket set for floor_control:%d\n", floor_control_socketfd);
	  FD_SET(floor_control_socketfd ,&socket_set);
//		printf("MAIN: waiting for select\n");
		select(maxfd + 1, &socket_set, NULL, NULL, &timeout);
		printf("MAIN: select initiated\n");
		for( int i = 0; i <= maxfd; i ++){
			if(FD_ISSET(i,&socket_set)){
//				if(i == udp_socketfd){
//					recv(i,recv_buffer,sizeof(recv_buffer),0);
//				}
				if(i == tcp_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					printf("MAIN: recieved message from master: %s\n",recv_buffer);
					send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0);
				}
				else if(i == button_socketfd){
     			   recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
//					printf("MAIN: sent message: %s\n",recv_buffer);
					if(recv_buffer[0] == 'c'){
						send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0);
					}
				}
				else if(i == elevator_control_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					printf("MAIN: recieved message from elevator_control: %s\n",recv_buffer);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
					if(recv_buffer[0] == 'r'){  
						printf("MAIN: sent message to floor_control: %s\n",recv_buffer);
						send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0); 
					}
				}
				else if(i == floor_control_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
					printf("MAIN: sent message to master: %s\n",recv_buffer);
          }
			}
		}
	}
    return 0;
}
