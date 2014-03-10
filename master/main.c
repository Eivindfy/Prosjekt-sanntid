#include "serverclient.h"
#include "tcpudpchannel.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>


int main (){
    int elevator_status[N_ELEVATORS];
    int elevator_floor[N_ELEVATORS];
    int floor_status[N_FLOORS];

    int maxfd;
    int udp_socketfd = tcpudpchannel_init();
    maxfd = udp_socketfd;
    int tcp_socketfd = int server_init();
    maxfd = max_socketfd > tcp_socketfd ? maxfd : tcp_socketfd;
    fd_set socket_set;
    FD_ZERO(&socket_set);
    struct timeval timeout;
    timeout.tv_sec = 3*60;
    timeout.tv_usec = 0;
    char recv_buffer[1024];

    while(1){
        FD_SET(tcp_socketfd,&socket_set);
        FD_SET(udp_socketfd,&socket_set);
        select(maxfd + 1, &socket_set, NULL, NULL, &timeout);
        for(int i = 0; i <= maxfd; i++){
            if(FD_ISSET(i, &socket_set)){
                if(i == tcp_socketfd){
                    recv(tcp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
                    
                }
            
            }
        }
    }

    
}

