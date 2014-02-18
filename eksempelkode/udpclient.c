#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

// erstatt desse her med ei headerfil med  definisjonar eller noko
#define UDPADDRESS "129.241.187.255"
#define UDPPORT 12340
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 1243
#define BUFFERLENGTH 1024
//



// denne og udpclient2 virker


int main(){
struct sockaddr_in from_udp_socket_address;
struct sockaddr_storage remote_address;
int udp_socketfd=socket(AF_INET,SOCK_DGRAM,0);
char buffer[BUFFERLENGTH];


struct in_addr from_udp_address;
if(inet_pton(AF_INET,UDPADDRESS,&from_udp_address)<=0){
	printf("failure assigning UDP address in udpclient\n");
	return -1;
}

from_udp_socket_address.sin_port = htons(UDPPORT);
from_udp_socket_address.sin_addr = from_udp_address;
from_udp_socket_address.sin_family = AF_INET;

socklen_t udp_address_length = sizeof(from_udp_socket_address);

bind(udp_socketfd, (struct sockaddr *)&from_udp_socket_address, sizeof(from_udp_socket_address)); 

int transferstatus=-1;
while(1){
	printf("g\n");
	transferstatus = recvfrom(udp_socketfd,buffer,BUFFERLENGTH, 0, (struct sockaddr*)&remote_address,&udp_address_length);
	if(transferstatus<0){
		printf("error receiving from UDP in udpclient\n");
			return -1;
	}
	else{
				printf("%s\n",buffer);

	}
}
return 0;
}
