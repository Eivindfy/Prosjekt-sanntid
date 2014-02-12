#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>



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
// VIRKER IKKJE

void* udptcpchannel(int udp_socketfd){

char buffer[BUFFERLENGTH];
int transferstatus;

// ---------------- receiving from udp -------------------------

struct sockaddr_in from_udp_socket_address;


struct in_addr from_udp_address;
if(inet_pton(AF_INET,UDPADDRESS,&from_udp_address)<=0){
printf("failure assigning UDP address in udptcpchannel\n");
exit(1);
}

from_udp_socket_address.sin_port = htons(UDPPORT);
from_udp_socket_address.sin_addr = from_udp_address;
from_udp_socket_address.sin_family = AF_INET;

socklen_t udp_address_length = sizeof(from_udp_socket_address);

transferstatus = recvfrom(udp_socketfd,buffer,BUFFERLENGTH, 0, (struct sockaddr*)from_udp_socket_address,udp_address_length);
if(transferstatus<0){
	printf("error receiving from UDP in udptcpchannel\n");
	exit(1);
}

// ------------------ sending to tcp --------------------

struct sockaddr_in to_tcp_socket_address;

struct in_addr to_tcp_address;
if(inet_pton(AF_INET,TCPADDRESS,&to_tcp_address)<=0){
printf("failure assigning TCP in udptcpchannel\n");
exit(1);
}

to_tcp_socket_address.sin_port = htons(TCPPORT);
to_tcp_socket_address.sin_addr = to_tcp_address;
to_tcp_socket_address.sin_family = AF_INET;

socklen_t tcp_address_length = sizeof(to_tcp_socket_address);

int tcp_socketfd = socket(AF_INET,SOCK_STREAM,0);

if(connect(tcp_socketfd,(struct sockaddr* )&to_tcp_socket_address,sizeof(to_tcp_socket_address))<0){
printf("failure in tcp connection in udptcpchannel\n");
close(fd);
exit(1);
}

transferstatus = send(tcp_socketfd,buffer, BUFFERLENGTH,0);
if(transferstatus<0){
printf("error transferring to TCP in udptcpchannel\n");
exit(1);

}

}
