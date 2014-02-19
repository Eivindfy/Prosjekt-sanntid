#define _POSIX_C_SOURCE	199309
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

// erstatt desse her med ei headerfil med  definisjonar eller noko
#define UDPADDRESS "129.241.187.255"
#define UDPPORT 12340
#define TCPADDRESS "127.0.0.1"
#define TCPPORT 1243
#define BUFFERLENGTH 1024
//


// denne og udpclient1 virker

int main(){

struct sockaddr_in from_udp_socket_address;
int udp_socketfd=socket(AF_INET,SOCK_DGRAM,0);
char buffer[BUFFERLENGTH];
int so_broadcast = 1;
setsockopt(udp_socketfd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));


struct in_addr from_udp_address;
if(inet_pton(AF_INET,UDPADDRESS,&from_udp_address)<=0){
	printf("failure assigning UDP address in udpclient\n");
	return -1;
}



from_udp_socket_address.sin_port = htons(UDPPORT);
from_udp_socket_address.sin_addr = from_udp_address;
from_udp_socket_address.sin_family = AF_INET;



socklen_t udp_address_length = sizeof(from_udp_socket_address);


int transferstatus=-1;
int i = 0;
while(1){
	printf("g\n");
	char* message = "Hei\n";
	strcpy(buffer,message); 
	transferstatus = sendto(udp_socketfd,buffer,BUFFERLENGTH, 0, (struct sockaddr*)&from_udp_socket_address,udp_address_length);
	if(transferstatus<0){
		printf("error sending to UDP in udpclient2 %s \n", strerror(errno));
			return -1;
	}
    

	
    usleep(1000000);

	i++;
	if( i == 100000)
		break;
}
return 0;
}
