#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>

#include "tcpudpchannel.h"


// erstatt desse her med ei headerfil med  definisjonar eller noko
#define UDPADDRESS "127.0.0.1"
#define UDPPORT 1234
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 1243
#define BUFFERLENGTH 1024
//

// VIRKER IKKJE SANNSYNELIGVIS
//
//
//
//
// MÅ NOK BINDE TCPSOCKET FØR DU BRUKER DENNE FUNKSJONEN
//
// SEND PÅ SAMME UDPADDRESSE OG PORT ALLTID????

int initializetcpudpchannel(){
	printf("initializing channel \n");
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

	//printf("socketpair created\n");
	
	pthread_t channel;
	printf("This is the file descriptor sent to the channel: %i \n", fd[0]);
	pthread_create(&channel,NULL, tcpudpchannel, (void *)&fd[0]);
	printf("done creating thread in initialize\n");
	return fd[1];

}


void *tcpudpchannel(void * tcp_socketfdvoid){

printf("tcpudpchannel thread created\n  this is the tcp void file descriptor: %i \n", tcp_socketfdvoid);

int tcp_socketfd = * ((int*) tcp_socketfdvoid);

printf("this is the tcp int file descriptor: %i \n", tcp_socketfd);

char buffer[BUFFERLENGTH];
int transferstatus;

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



bind(udp_socketfd, (struct sockaddr*)&udp_socket_address, udp_address_length);


// ------------------ receiving from tcp --------------------

printf("creating FD_SET\n");
int fd_max = (tcp_socketfd > udp_socketfd) ? tcp_socketfd : udp_socketfd;   // returnerer den som er størst
// Legger fd-ene i master_set
printf("fd_max complete \n");
fd_set master_set;
printf("master_set created\n");
FD_ZERO(&master_set);
printf("master_set used as input in FD_ZERO\n    tcp_socketfd is: %i \n udp_socketfd is: %i \n",tcp_socketfd,udp_socketfd);
FD_SET(tcp_socketfd,&master_set);
printf("put tcp_socketfd in master_set\n");
FD_SET(udp_socketfd,&master_set);
//
struct timeval tv;
tv.tv_sec = 100;
tv.tv_usec = 0;

printf("starting select operation \n");
while(1){
	select(fd_max,&master_set,NULL,NULL,&tv);

	if( FD_ISSET(tcp_socketfd,&master_set)){

		transferstatus = recv(tcp_socketfd,buffer,(int)sizeof(buffer),0);
		// printf("test: %s \n",buffer);
		if (transferstatus<0){
			perror("Failure receiving from TCP in tcpudpchannel\n");
			
		}

		transferstatus=sendto(udp_socketfd,buffer,sizeof(buffer),0,(struct 			 			sockaddr*)&udp_socket_address,udp_address_length);
		if (transferstatus<0){
			perror("Failure sending to UDP in tcpudpchannel\n");
			
	  }

	}

	else if( FD_ISSET(udp_socketfd,&master_set)){
		printf("this is the buffer before receiving from udp: %s , size of it: %i \n",buffer,sizeof(buffer));

		transferstatus=recvfrom(udp_socketfd,buffer,sizeof(buffer),0,(struct 					  sockaddr*)&udp_socket_address, &udp_address_length);
		if ( transferstatus < 0 ){
			perror("Failure receiving from UDP in tcpudpchannel\n");
			
		}

		

		transferstatus=send(tcp_socketfd,buffer,sizeof(buffer),0);
		if( transferstatus < 0 ){
			perror("Failure sending to TCP in tcpudpchannel\n");
		
		}

	}
}
}

