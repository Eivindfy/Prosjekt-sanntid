#define MAIN_FILE
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time>
#include "buttons.h"
#include "serverclient.h"
#include "control_functions.h"
#include "floor_control.h"
#include "tcpudpchannel.h"


int main(){
	int maxfd;
	int udp_socketfd = tcpudpchannel_init();
	maxfd = udp_socketfd;
	// Maybe check if there is a master server here

	int tcp_socketfd = client_init();
	maxfd = tcp_socketfd > maxfd ? tcp_socketfd : maxfd;
	int button_socketfd = button_init();
	maxfd = button_socketfd > maxfd ? button_socketfd : maxfd;
	int elevator_control_socketfd = elevator_control_init();
	maxfd = elevator_control_socketfd > maxfd ? elevator_control_socketfd : maxfd;
	int floor_control_socketfd = floor_control_init();
	maxfd = floor_control_socketfd > maxfd ? floor_control_socketfd : maxfd;

	fd_set socket_set;
	FD_ZERO(&socket_set);
	struct timeval timeout;
	timeout.tv_sec = 3*60;
        timeout.tv_usec = 0;
	
	char recv_buffer[1024]
	
	while(1){

        FD_SET(udp_socketfd ,&socket_set);
        FD_SET(tcp_socketfd ,&socket_set);
        FD_SET(button_socketfd ,&socket_set);
        FD_SET(elevator_control_socketfd ,&socket_set);
        FD_SET(floor_control_socketfd ,&socket_set);

		select(maxfd + 1, &socket_set, NULL, NULL, &timeout);
		
		for( int i = 0; i <= maxfd, i ++){
			if(FD_ISSET(i,&socket_set)){
				if(i == udp_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
				}
				else if(i == tcp_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0);
				}
				else if(i == button_socketfd){
                    recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
					if(recv_buffer[0] == 'c'){
						send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0);
        			}
                }
				else if(i == elevator_control_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
                    if(recv_buffer[0] == 'r'){  
					    send(floor_control_socketfd,recv_buffer,sizeof(recv_buffer),0); 
                    }
                }
				else if(i == floor_control_socketfd){
					recv(i,recv_buffer,sizeof(recv_buffer),0);
					send(tcp_socketfd,recv_buffer,sizeof(recv_buffer),0);
                }
			}
		}
	}
    return 0;
}
