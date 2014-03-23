#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define WATCHDOGHOST "127.0.0.1"
#define WATCHDOGPORT 25000

int main (){



/////////////////////////////////////////////////////////////////////////
//////////////////   opprett udp-socket    /////////////////////////////
////////////////////////////////////////////////////////////////////////
	printf("Starting watchdog\n");
	struct sockaddr_in *server_addr;
	struct sockaddr_in temp;
	server_addr = &temp;
	int socketfd, n;
	char buffer[1024];
	fd_set udpset;
	struct timeval tv;
	
	socketfd = socket(AF_INET, SOCK_DGRAM,0);
	if(socketfd== -1){
		printf("error opening socket");
		return -1;
	}
									
	struct in_addr host_addr;
	if(inet_pton(AF_INET, WATCHDOGHOST,&host_addr) <=0){
		printf("error");
		return -1;
	} 	
	server_addr->sin_port = htons(WATCHDOGPORT);
	server_addr->sin_addr = host_addr; 
	server_addr->sin_family = AF_INET;
	int yes = 1;
	
	if(setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) ==-1){
		printf("Error setting socket as readable: %i", errno);
		return -1;
	}


	
	if(bind(socketfd, (struct sockaddr *) server_addr, sizeof(*server_addr)) < 0){
		printf("Error in bind. %s \n", strerror(errno));
		return -1;
	}
    
	FD_ZERO(&udpset);
	



/////////////////////////////////////////////////////////////////////////
//////////////////   her begynner watchdog   ////////////////////////////
////////////////////////////////////////////////////////////////////////

	
	socklen_t addrlen = sizeof(*server_addr);
	int misses = 0;
	while(1){
		tv.tv_sec = 0;
		tv.tv_usec = 100000;
		FD_SET(socketfd, &udpset);
		if ((select(socketfd+1, &udpset, NULL, NULL, &tv)) < 0){
        	printf("Error in select. %s \n ", strerror(errno));
        	return -1;
    	}

		if (FD_ISSET(socketfd,  &udpset)){
			n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, &addrlen);
			if(n<0){
		  		printf("error in recvfrom");
		  		return -1;
			}
			if(buffer[0]=='W'){
				misses=0;
			}
		}
		else{
			misses++;
		}
		
		if(misses>5){
			////////////////////////////////////////////////////////////////////////
			////////////////////////////  STARTA NYTT OG LAG HELVETE ///////////////
			////////////////////////////////////////////////////////////////////////
			printf("WATCHDOG: client is dead\n");
			exit(1);
		}
	}
	
	
	
		
	


	return 0;
}


