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

#define HOST "129.241.187.255"
#define PORT 25000

int main (){
	printf("hei\n");
	struct sockaddr_in *server_addr;
	struct sockaddr_in temp;
	server_addr = &temp;
	int socketfd, n;
	char buffer[1024];
	fd_set udpset;
	struct timeval tv;
	int tall = 0;
	
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
	FD_SET(socketfd, &udpset);

	tv.tv_sec = 2;
	tv.tv_usec = 0;
    int ret;
	socklen_t addrlen = sizeof(*server_addr);
	if ((ret=select(socketfd+1, &udpset, NULL, NULL, &tv)) < 0){
        printf("Error in select. %s \n ", strerror(errno));
        return -1;
    }
    int was_back=0;
    printf("%d \n", socketfd);
	if (FD_ISSET(socketfd,  &udpset)){
        printf("backup \n");
		n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, &addrlen);
		if(n<0){
		  printf("error in recvfrom");
		  return -1;
		}
        printf("%s \n",buffer);
		if (buffer[0] == '2'){
			strcpy(buffer,"1");
            printf("%s \n",buffer);
            usleep(100000);
			int miss_count = 0;
			while(1) {
				ret = select(socketfd+1, &udpset, NULL, NULL, &tv);
                printf("%d, %d\n",miss_count,ret);
                was_back = 1;
				if(FD_ISSET(socketfd, &udpset) ){
					n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, &addrlen);
					if(n<0){
						printf("error in recvfrom");//
						return -1;
					}
                    usleep(500000);
					miss_count = 0;
                    printf("%s\n",buffer);
				}
				else{
					miss_count ++;
					if(miss_count >= 10){
						break;
					}
				}
			}
		}
	}
    setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	system("mate-terminal -e ./test");
	strcpy(buffer,"2");
	for( int i = 0; i <10 ;i++){
		n = sendto(socketfd, buffer, 1024, 0, (struct sockaddr *) server_addr, addrlen);
        printf("sending \n");
		if (n < 0){
			printf("error in sendto. %s \n", strerror(errno));
    	return -1;
		}
        usleep(10000);
	}
    
    if(was_back)
        return -1;
	FILE * fr = fopen("/tmp/test.txt", "r");
    
	if (fr){
		char filebuff[16];
		fgets(filebuff, 16, (FILE*)fr); 
		tall = atoi(filebuff);
        fclose(fr);
	}
	else 
		tall = 0;
	printf("her\n");


	

	while(1){
        FILE *fw = fopen("/tmp/test.txt", "w");
    	if (!fw){
    		printf("Failed to open file for writing");
    		return -1;
    	}
		printf("%i\n",tall++);
		fprintf(fw, "%i", tall);
		n = sendto(socketfd, buffer, 1024, 0, (struct sockaddr *)server_addr, addrlen);
		if (n < 0){
			printf("error in sendto");
			return -1;
		}
        fclose(fw);
		usleep(500000);
	}

		
	


	return 0;
}

