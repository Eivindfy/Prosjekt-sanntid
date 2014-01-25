//oppgave 2 oving 3


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 33546
#define HOST "129.241.187.161"
#define MY_IP "129.241.187.150"
#define MY_PORT 20000




//void* accept_thread(void * arrg){
//	socklen_t addr_size = sizeof local_addr;
//        if(accept(socket2fd, (struct sockaddr* )local_addr, &addr_size)==-1){
//                printf("error");
//                return -1;
//        }
//}


int main(){
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
		printf("error connecting to server");
		return -1;
	}
	
	// Mottar velkomstmeldingen og printer den til terminalen
	char buf[1024];
	recv(socketfd, buf, sizeof(buf), 0);

	printf(":%s\n:", buf);



	// Kode for å la andre koble til denne maskinen
	// Rekkefølge
	// *Lage socket  -  socket() samt sette variablene til sockaddr_in
	// *Ordne instillingene  -  setsocketopt()
	// *Binde  -  bind()
	// *Lytte  -  listen()
	// *aksepterr  -  accept()
	// *Sende og motta meldinger  -  send() og recv()
	
	

	// Lager socket og initialiserer og setter verdier til sockaddr_in
	struct sockaddr_in *local_addr;
        struct sockaddr_in temp2;
        local_addr = &temp2;
        int socket2fd;

	socket2fd = socket(AF_INET, SOCK_STREAM,0);

	if(socket2fd== -1){
                printf("error opening socket");
                return -1;
        }

        struct in_addr local_in_addr;
        if(inet_pton(AF_INET, MY_IP,&local_in_addr) <=0){
                printf("error");
                return -1;
        }
        local_addr->sin_port = htons(MY_PORT);
        local_addr->sin_addr = local_in_addr;
        local_addr->sin_family = AF_INET;



	// Forteller server at den skal koble til denne maskinen
	char* message = "Connect to: 129.241.187.150:20000\0";
	send(socketfd,message,strlen(message)+1,0);
	
	// Forandrer på instillingene slik at socketen/porten er gjenbrukbar 
	int yes = 1; // Denne er 1 fordi vi skal slå på SO_REUSEADDR
	if(setsocketopt(socket2fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(*local_addr)=-1){
		printf("Error setting socket as readable: %i", errno);
		return -1;
	}
	
	// Binder socketen
	if(bind(socket2fd, (struct sockaddr* ) local_addr, sizeof(*local_addr))==-1){
		printf("error binding socket: %i",errno);
		return -1;
	}
	
	// Lytter på denne porten
	listen(socket2fd,0);
	

//	pthread_t accept_thr;
//	pthread_create(&accept_thr,

	int new_sock;

	socklen_t addr_size = sizeof local_addr;
	// Aksepterer inkommende henvendelse 
	new_sock=accept(socket2fd, (struct sockaddr* )local_addr, &addr_size);
	if(new_sock ==-1){
		printf("error");
		return -1;
	}
	
	// Mottar velkomstmelding
	recv(new_sock, buf, sizeof(buf), 0);
	printf("%s\n", buf);
	
	//Sender melding 
	message = "Hei ny melding!";	
	send(new_sock,message,strlen(message)+1,0);

	// Mottar svar
	recv(new_sock, buf, sizeof(buf), 0);
        printf("%s\n", buf);
	

	return 0;
}
