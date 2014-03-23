#define MAIN_FILE

#include "serverclient.h"
#include "tcpudpchannel.h"
#include <sys/socket.h>
#include <sys/types.h>
#include "order_handeling.h"
#include "global_variables.h"
#include <sys/time.h>
#include <stdio.h>
#include "queue.h"
#include "fault_tolerance_master.h"
#include "master_backup.h"




int main (){
	int elevator_status[N_ELEVATORS];
	int elevator_floor[N_ELEVATORS];
	int maxfd = 0;
	for(  int i = 0 ; i < N_ELEVATORS; i++){
	 	elevator_status[i] = -1;
		elevator_floor[i] = -1;
	}
	int master_backupfd = master_backup_init();
	maxfd = maxfd > master_backupfd ? maxfd : master_backupfd;
	int tcp_socketfd = server_init();
	maxfd = maxfd > tcp_socketfd ? maxfd : tcp_socketfd;
	fd_set socket_set;
	FD_ZERO(&socket_set);
	struct timeval timeout;
	char recv_buffer[1024];
	char send_buffer[1024];
	global_host_ip = MY_IP;
	order_queue_initialize();
	retrieve_backup_master("master_backup.txt",elevator_status,elevator_floor,root);
	
	while(1){
		timeout.tv_sec = 3*60;
		timeout.tv_usec = 0;
		FD_SET(tcp_socketfd,&socket_set);
		FD_SET(master_backupfd,&socket_set);
		select(maxfd + 1, &socket_set, NULL, NULL, &timeout);
		for(int i = 0; i <= maxfd; i++){
			if(FD_ISSET(i, &socket_set)){
				if(i == tcp_socketfd){
					recv(tcp_socketfd, recv_buffer, sizeof(recv_buffer), 0);
					printf("MAIN: recieved message: %s\n ",recv_buffer);
					if(recv_buffer[0] == 'a'|| recv_buffer[0] == 'i'){
						send(master_backupfd, recv_buffer, sizeof(recv_buffer),0);
					}
					else{
//						printf("MAIN: recived message: %s\n ",recv_buffer);
						handle_message(recv_buffer,elevator_status,elevator_floor,root,tcp_socketfd);
					}
				}
			}
		}
		write_backup_master("master_backup.txt",elevator_status,elevator_floor,root);
		backup_tostring("master_backup.txt", send_buffer, sizeof(send_buffer));
//		send(tcp_socketfd,send_buffer,sizeof(recv_buffer), 0);
	}
}

