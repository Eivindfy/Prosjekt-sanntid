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
#include "utility_functions.h"
#include <unistd.h>

#define PORT 33546
#define HOST "129.241.187.158"
#define MY_IP "129.241.187.158"
#define MY_PORT 20000
#define NUMBER_OF_CONNECTIONS 10
#define BUFFER_SIZE 1024

struct socket_pack{
	int intern_com;
	int extern_com;
};

void* server_client_comunication(void* spvoid){
	char message[BUFFER_SIZE];
	struct socket_pack *sp = (struct socket_pack *) spvoid; 
	fd_set communicationfd_set;
	int fdmax;
	struct timeval timeout;
	FD_ZERO(&communicationfd_set);
	FD_SET(sp->intern_com, &communicationfd_set);
	FD_SET(sp->extern_com, &communicationfd_set);
	fdmax = sp->intern_com >= sp->extern_com ? sp->intern_com : sp->extern_com;
//	printf("SERVERCLIENT: pthread_created\n");
	while(1){
		timeout.tv_sec = 3*60;
		timeout.tv_usec = 0;
		FD_SET(sp->intern_com, &communicationfd_set);
		FD_SET(sp->extern_com, &communicationfd_set);
		if(select(fdmax+1, &communicationfd_set, NULL, NULL, &timeout) <= 0 ){
			printf("Error in select in server_client_comunication");
//			return -1;
		}
//		printf("SERVERCLIENT: message recieved in server_client_comunilation\n");
		for(int i = 0; i <= fdmax; i++){
			if(FD_ISSET(i, &communicationfd_set)){
//					printf("SERVERCLIENT: message recieved in server_client_comunilation\n");
					if(i == sp->intern_com){
//						printf("SERVERCLIENT: message sent\n");
						recv(sp->intern_com, message, sizeof(message),0);
						send(sp->extern_com, message, sizeof(message),0);
					}
					else if(i == sp->extern_com){
						recv(sp->extern_com, message, sizeof(message),0);
						send(sp->intern_com, message, sizeof(message),0);
					}
			}		
		}
	}
} 

void *servermodule(void *module_sockfdvoid){
	int module_sockfd = *(int *) module_sockfdvoid;


	// Kode for å la andre koble til denne maskinen
	// Rekkefølge
	// *Lage socket  -  socket() samt sette variablene til sockaddr_in
	// *Ordne instillingene  -  setsocketopt()
	// *Binde  -  bind()
	// *Lytte  -  listen()
	// *Aksepter  -  accept()
	// *Sende og motta meldinger  -  send() og recv()
	
	
	// Lager master og midlertidig file desctriptor list samt timeout
	fd_set  masterfd_set;
	fd_set  readfd_set;
	struct timeval timeout;
	int fdmax;
	int intern_comunication_sockets[NUMBER_OF_CONNECTIONS];
	for( int i = 0; i < NUMBER_OF_CONNECTIONS; i++){
		intern_comunication_sockets[i] = 0;
	}
	char buffer[1024];

	// Lager socket og initialiserer og setter verdier til sockaddr_in
	struct sockaddr_in *server_addr;
	struct sockaddr_in temp;
	server_addr = &temp;
	int serverfd, newfd;

	serverfd = socket(AF_INET, SOCK_STREAM,0);

	if(serverfd== -1){
	       printf("Error opening socket");
//	       return -1;
	}
	server_addr->sin_port = htons(PORT);
	server_addr->sin_addr.s_addr = INADDR_ANY;
	server_addr->sin_family = AF_INET;

	//setter master fd til 0 og timeout til 3 minutter 
	FD_ZERO(&masterfd_set);
	FD_ZERO(&readfd_set);
	fdmax = serverfd;
	// Forandrer på instillingene slik at socketen/porten er gjenbrukbar 
	int yes = 1; // Denne er 1 fordi vi skal slå på SO_REUSEADDR
	if(setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(*server_addr))==-1){
		printf("Error setting socket as readable: %i", errno);
//		return -1;
	}
	
	// Binder socketen
	if(bind(serverfd, (struct sockaddr* ) server_addr, sizeof(*server_addr))==-1){
		printf("error binding socket: %i",errno);
//		return -1;
	}
	
	// Lytter på denne porten
	listen(serverfd,NUMBER_OF_CONNECTIONS);
	
	FD_SET(serverfd, &readfd_set);
	FD_SET(module_sockfd, &readfd_set);
	
//	printf("SERVERCLIENT: setup complete: fdmax = %d , module_sockfd = %d\n",fdmax,module_sockfd);
//	memcpy(&readfd_set, &masterfd_set, sizeof(masterfd_set));

	while(1){
//		memcpy(&readfd_set, &masterfd_set, sizeof(masterfd_set));
//		printf("SERVERCLIENT: waiting for select: fdmax = %d , module_sockfd = %d\n",fdmax,module_sockfd);
		timeout.tv_sec = 3*60;
		timeout.tv_usec = 0;
		FD_SET(module_sockfd, &readfd_set);
		FD_SET(serverfd, &readfd_set);
		for( int i = 0; i < sizeof(intern_comunication_sockets);i++){
			if(intern_comunication_sockets[i] == 0)
				break;
			FD_SET(intern_comunication_sockets[i], &readfd_set);
		}
		if(select(fdmax+1, &readfd_set, NULL, NULL, &timeout)<=0){
			printf("Error i select\n");
//			return -1; 
		}
//		printf("SERVERCLIENT: select initiated\n");
		for (int i = 0; i <= fdmax; i++){
			if (FD_ISSET( i, &readfd_set)){
//				printf("SERVERCLIENT: fd selected %d\n",i);
				if(i == serverfd) {
//					printf("SERVERCLIENT: client conected\n");
					newfd =  accept(serverfd, NULL, 0);
					int pair_of_sock[2];
					socketpair(AF_UNIX, SOCK_STREAM, 0, pair_of_sock);  
					struct socket_pack *sp;
					struct socket_pack temp;
					sp = &temp;
					sp->intern_com = pair_of_sock[0];
					sp->extern_com = newfd;
//					printf("SERVERCLIENT: new socketfd %d\n", newfd);
					for(int j = 0; j < NUMBER_OF_CONNECTIONS; j++){
						if(intern_comunication_sockets[j] == 0)
							intern_comunication_sockets[j] = pair_of_sock[1];
							break;
					}
					FD_SET(pair_of_sock[1], & readfd_set);
					fdmax = fdmax >pair_of_sock[1] ? fdmax : pair_of_sock[1];  
					pthread_t thread;
					if(pthread_create(&thread, NULL, server_client_comunication , (void *) sp) == -1){
						printf("Error creating pthread.\n");
//						return -1;
					}	
				}
				for( int j = 0; j < NUMBER_OF_CONNECTIONS; j++){
					if( i == intern_comunication_sockets[j]){
						recv(i,buffer,sizeof(buffer),0);
						if(insert_elevator_into_buffer(j,buffer)==-1){
							printf("SERVERCLIENT: error inserting elevator into buffer\n");
						}
//						printf("SERVERCLIENT: recieved message from client: %s\n", buffer);
						send(module_sockfd,buffer,sizeof(buffer),0);
						break;
					}
				}
				if(i == module_sockfd){
//					printf("SERVERCLIENT: recieved message from server\n");
					recv(module_sockfd, buffer, sizeof(buffer), 0);
					int client_id = get_elevator_from_buffer(buffer);
//					printf("SERVERCLIENT: sending message: %s to client: %d and fd: %d\n",	buffer, client_id, intern_comunication_sockets[client_id]);
					send(intern_comunication_sockets[client_id],buffer,sizeof(buffer),0);
				}
			}
		}
	}
}


int server_init(){
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);

	int* dynamic_int_pointer =  malloc(sizeof(*dynamic_int_pointer));
	*dynamic_int_pointer = fd[0];
	void* dynamic_void_pointer;
	dynamic_void_pointer = (void*)dynamic_int_pointer;

	pthread_t server_thread;
	
	pthread_create(&server_thread,NULL, servermodule, dynamic_void_pointer);
	return fd[1];
}


int client_init(){
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
//	printf("CLIENT: initialised\n");
	sleep(1);
	return socket_pair[1];
}
