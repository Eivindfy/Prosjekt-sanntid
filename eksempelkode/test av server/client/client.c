//oppgave 2 oving 3


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

#define PORT 33546
#define HOST "129.241.187.158"
#define MY_IP "129.241.187.150"
#define MY_PORT 20000
#define NUMBER_OF_CONNECTIONS 10
#define BUFFER_SIZE 1024

struct socket_pack{
	int intern_com;
	int extern_com;
};

void* server_client_comunication(void* spvoid){
	sleep(1);
	char message[BUFFER_SIZE];
	printf("CLIENT: start pthread\n");
	struct socket_pack *sp = (struct socket_pack *) spvoid; 
	printf("CLIENT: socket pack created\n");
	fd_set communicationfd_set;
	int fdmax;
	int rc;
	struct timeval timeout;
	timeout.tv_sec = 3*60;
	timeout.tv_usec = 0;
	FD_ZERO(&communicationfd_set);
	FD_SET(sp->intern_com, &communicationfd_set);
	FD_SET(sp->extern_com, &communicationfd_set);
	fdmax = sp->intern_com >= sp->extern_com ? sp->intern_com : sp->extern_com;
	printf("CLIENT: pthread created: sp->interncom = %d, sp->extern_com = %d, fdmax = %d \n", sp->intern_com, sp->extern_com, fdmax);
	while(1){
		if((rc=select(fdmax+1, &communicationfd_set, NULL, NULL, &timeout)) <= 0 ){
			printf("Error in select in server_client_comunication");
//			return -1;
		}
//		printf("CLIENT: select initiated %d\n", rc);
		for(int i = 0; i <= fdmax+1; i++){
			if(FD_ISSET(i, &communicationfd_set)){
					printf("CLIENT: select initiated %d\n", i);

					if(i == sp->intern_com){
						printf("CLIENT: sending message\n");
						recv(sp->intern_com, message, sizeof(message),0);
						send(sp->extern_com, message, sizeof(message),0);
					}
					else if(i == sp->extern_com){
						printf("CLIENT: recieving message\n");
						recv(sp->extern_com, message, sizeof(message),0);
						send(sp->intern_com, message, sizeof(message),0);
					}
			}		
		}
	}
} 


int create_client(){
	// kode for å koble til og server og sende og motta melding
	// Rekkefølge
	// * Lage socket  -  socket() og sette variablene i sockaddr_in
	// * Koble til  -  connect()
	// * Motta velkomstmelding  -  recv()
	// * Sende og motta meldinger  -  send()


	// Lager socket og initialisere en sockaddr_in og setter dens verdier.
	struct sockaddr_in *server_addr;
	struct sockaddr_in temp;
	server_addr = &temp;
	int socketfd;
	int socket_pair[2];
	struct socket_pack sp;
	pthread_t channel;
	socketfd = socket(AF_INET, SOCK_STREAM,0); 
	if(socketfd== -1){
		printf("error opening socket");
		return -1;
	}
	
	struct in_addr host_addr;
	if(inet_pton(AF_INET, HOST,&host_addr) <=0){
		printf("error creating host address");
		return -1;
	} 	
	server_addr->sin_port = htons(PORT);
	server_addr->sin_addr = host_addr; 
	server_addr->sin_family = AF_INET;
		
	
	// Kobler til serveren ved hjelp av socketen og server_addr som er castet fra sockaddr_in til sockaddr
	if(connect(socketfd, (struct sockaddr* )server_addr,sizeof(*server_addr)) == -1){
		printf("error connecting to server: %s \n", strerror(errno));
		return -1;
	}
	socketpair(PF_LOCAL, SOCK_STREAM, 0, socket_pair);
	sp.intern_com = socket_pair[0];
	sp.extern_com = socketfd;
	struct socket_pack * dynamic_sp_pointer = malloc(sizeof(*dynamic_sp_pointer));
	*dynamic_sp_pointer = sp;
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*) dynamic_sp_pointer;
	pthread_create(&channel, NULL, server_client_comunication, dynamic_void_pointer);
	printf("CLIENT: initialised\n");
	sleep(1);
	return socket_pair[1];
}
