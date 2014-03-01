#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include "tcpudpchannel.h"


// erstatt desse her med ei headerfil med  definisjonar eller noko
#define UDPADDRESS "129.241.187.158"
#define UDPPORT 12345
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 12435
#define BUFFERLENGTH 1024
//


// SEND PÅ SAMME UDPADDRESSE OG PORT ALLTID????

int initializetcpudpchannel(){
	printf("initializing channel \n");
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

	//printf("socketpair created\n");
	
	
	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;
	
	
	pthread_t channel;
	printf("This is the file descriptor sent to the channel: %i \n", fd[0]);
	pthread_create(&channel,NULL, tcpudpchannel, dynamic_void_pointer);
	printf("done creating thread in initialize\n");
	return fd[1];

}








void *tcpudpchannel(void* tcp_socketfdvoid){

printf("tcpudpchannel thread created\n");

int tcp_socketfd = *((int*)tcp_socketfdvoid);
free(tcp_socketfdvoid);

char buffer[BUFFERLENGTH];
int transferstatus;
int rc;

// ---------------- setting up udp -------------------------

int udp_socketfd = socket(AF_INET,SOCK_DGRAM,0);

struct sockaddr_in udp_socket_address;


struct in_addr udp_address;
if(inet_pton(AF_INET,UDPADDRESS,&udp_address)<=0){
	perror("failure assigning UDP address in tcpudpchannel\n");
}



udp_socket_address.sin_port = htons(UDPPORT);
udp_socket_address.sin_addr = udp_address;
udp_socket_address.sin_family = AF_INET;

socklen_t udp_address_length = sizeof(udp_socket_address);
int broadcast = 1;
rc = setsockopt(udp_socketfd, SOL_SOCKET, SO_REUSEADDR, &broadcast, sizeof(broadcast));
if ( rc <0 )
    perror("Error seting socket option\n");

rc = setsockopt(udp_socketfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
if ( rc <0 )
    perror("Error seting socket option\n");



rc = bind(udp_socketfd, (struct sockaddr*)&udp_socket_address, udp_address_length);
if( rc < 0)
    perror("Error binding udp socketn\n");

// ------------------ receiving from tcp --------------------

printf("creating FD_SET\n");
int fd_max = (tcp_socketfd > udp_socketfd) ? tcp_socketfd : udp_socketfd;   // returnerer den som er størst
// Legger fd-ene i master_set
printf("fd_max complete \n");
fd_set master_set;
printf("master_set created\n");
FD_ZERO(&master_set);
printf("master_set used as input in FD_ZERO\n- tcp_socketfd is: %i \n- udp_socketfd is: %i \n",tcp_socketfd,udp_socketfd);
FD_SET(tcp_socketfd,&master_set);
FD_SET(udp_socketfd,&master_set);
//
struct timeval tv;
tv.tv_sec = 100;
tv.tv_usec = 0;

printf("starting select operation \n");
printf("Fd_max is: %d \n", fd_max);
while(1){
	select(fd_max+1,&master_set,NULL,NULL,&tv);
    
	if( FD_ISSET(tcp_socketfd,&master_set)){
        
        
        printf("CHANNEL: receiving from TCP\n");
		transferstatus = recv(tcp_socketfd,buffer,(int)sizeof(buffer),0);
		printf("CHANNEL: received from TCP, message is: %s \n",buffer);
		if (transferstatus<0){
			perror("Failure receiving from TCP in tcpudpchannel\n");
		}
		
        
        printf("CHANNEL: sending to UDP\n");
		transferstatus=sendto(udp_socketfd,buffer,sizeof(buffer),0,(struct 			 			sockaddr*)&udp_socket_address,udp_address_length);
		printf("CHANNEL: sent to UDP\n");
		if (transferstatus<0){
			perror("Failure sending to UDP in tcpudpchannel\n");
	    }
	    printf("Transfer status: %s \n", strerror(errno));

	}

	else if( FD_ISSET(udp_socketfd,&master_set)){
	//	printf("this is the buffer before receiving from udp: %s , size of it: %i \n",buffer,sizeof(buffer));


        printf("CHANNEL: Receiving from UDP\n");
		transferstatus=recvfrom(udp_socketfd,buffer,sizeof(buffer),0,(struct 					  sockaddr*)&udp_socket_address, &udp_address_length);
		printf("CHANNEL: Received from UDP, message is: %s \n", buffer);
		if ( transferstatus < 0 ){
			perror("Failure receiving from UDP in tcpudpchannel\n");
		}
	

		
        printf("CHANNEL: Sending to TCP\n");
		transferstatus=send(tcp_socketfd,buffer,sizeof(buffer),0);
        printf("CHANNEL: Sent to TCP\n");
        
		if( transferstatus < 0 ){
			perror("Failure sending to TCP in tcpudpchannel\n");
		}
 
	}
}
}
