#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 20005
#define HOST "129.241.187.161"
#define MY_IP "129.241.187.143"
#define MY_PORT 10



int main(){
	
	struct sockaddr_in *server_addr;
	struct sockaddr_in temp;
	server_addr = &temp;
	int socketfd, n;
	char buffer[1024];
	char *tempmsg;

	socketfd = socket(AF_INET, SOCK_DGRAM,0);
	if(socketfd== -1){
		printf("error opening socket");
		return -1;
	}
	
	struct in_addr host_addr;
	if(inet_pton(AF_INET, HOST,&host_addr) <=0){
		printf("error");
		return -1;
	} 	
	server_addr->sin_port = htons(PORT);
	server_addr->sin_addr = host_addr; 
	server_addr->sin_family = AF_INET;
	
  socklen_t addrlen = sizeof(server_addr);
  tempmsg = "historical printer coverage";
	strcpy(buffer,tempmsg);
	n = sendto(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, addrlen);
  if (n < 0){
		printf("error in sendto");
		return -1;
	}

	n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, &addrlen);
	if(n<0){
	    printf("error in recvfrom");
	    return -1;
	 } 


	return 0;
}
