#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>


// erstatt desse her med ei headerfil med  definisjonar eller noko
#define UDPADDRESS "127.0.0.1"
#define UDPPORT 1234
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 1243
#define BUFFERLENGTH 1024
//





void *tcpudpchannel(void * tcp_socketfdvoid);
// VIRKER IKKJE SANNSYNELIGVIS
//
//
//
//
// MÅ NOK BINDE TCPSOCKET FØR DU BRUKER DENNE FUNKSJONEN
//
// SEND PÅ SAMME UDPADDRESSE OG PORT ALLTID????

int initializetcpudpchannel(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	pthread_t channel;
	pthread_create(&channel,NULL, tcpudpchannel, &fd[0]);
	return fd[1];

}


void *tcpudpchannel(void * tcp_socketfdvoid){

int tcp_socketfd = * (int*) tcp_socketfdvoid;
char buffer[BUFFERLENGTH];
int transferstatus;

// ---------------- setting up udp -------------------------

int udp_socketfd = socket(AF_INET,SOCK_DGRAM,0);

struct sockaddr_in udp_socket_address;


struct in_addr udp_address;
if(inet_pton(AF_INET,UDPADDRESS,&udp_address)<=0){
	printf("failure assigning UDP address in tcpudpchannel\n");
	exit(1);
}

udp_socket_address.sin_port = htons(UDPPORT);
udp_socket_address.sin_addr = udp_address;
udp_socket_address.sin_family = AF_INET;

socklen_t udp_address_length = sizeof(udp_socket_address);



bind(udp_socketfd, (struct sockaddr*)&udp_socket_address, udp_address_length);


// ------------------ receiving from tcp --------------------

int fd_max = (tcp_socketfd > udp_socketfd) ? tcp_socketfd : udp_socketfd;   // returnerer den som er størst
// Legger fd-ene i master_set
fd_set master_set;
FD_ZERO(&master_set);
FD_SET(tcp_socketfd,&master_set);
FD_SET(udp_socketfd,&master_set);
//
struct timeval tv;
tv.tv_sec = 1000;
tv.tv_usec = 50;

while(1){
	select(fd_max,&master_set,NULL,NULL,&tv);

	if( FD_ISSET(tcp_socketfd,&master_set)){

		transferstatus = recv(tcp_socketfd,buffer,sizeof(buffer),0);
		if (transferstatus<0){
			printf("Failure receiving from TCP in tcpudpchannel\n");
			exit(1);
		}

		transferstatus=sendto(udp_socketfd,buffer,sizeof(buffer),0,(struct sockaddr*)&udp_socket_address,udp_address_length);
		if (transferstatus<0){
			printf("Failure sending to UDP in tcpudpchannel\n");
			exit(1);
	  }

	}

	else if( FD_ISSET(udp_socketfd,&master_set)){

		transferstatus=recvfrom(udp_socketfd,buffer,sizeof(buffer),0,(struct sockaddr*)&udp_socket_address, &udp_address_length);
		if ( transferstatus < 0 ){
			printf("Failure receiving from UDP in tcpudpchannel\n");
			exit(1);
		}

		transferstatus=send(tcp_socketfd,buffer,sizeof(buffer),0);
		if( transferstatus < 0 ){
		printf("Failure sending to TCP in tcpudpchannel\n");
		exit(1);
		}

	}
}
}

