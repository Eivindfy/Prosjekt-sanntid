//oppgave 2 oving 3


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 33546
#define HOST "129.241.187.161"
#define MY_IP "129.241.187.150"
#define MY_PORT 20000
#define NUMBER_OF_CONNECTION 10



int main(){



	// Kode for å la andre koble til denne maskinen
	// Rekkefølge
	// *Lage socket  -  socket() samt sette variablene til sockaddr_in
	// *Ordne instillingene  -  setsocketopt()
	// *Binde  -  bind()
	// *Lytte  -  listen()
	// *Aksepter  -  accept()
	// *Sende og motta meldinger  -  send() og recv()
	
	
	// Lager master og midlertidig file desctriptor list samt timeout
	fd_set = masterfd_set;
	fd_set = readfd_set;
	struct timeval timeout;
	int fdmax;


	// Lager socket og initialiserer og setter verdier til sockaddr_in
	struct sockaddr_in *server_addr;
  struct sockaddr_in temp;
  local_addr = &temp;
  int serverfd, newfd;

	serverfd = socket(AF_INET, SOCK_STREAM,0);

	if(serverfd== -1){
       printf("Error opening socket");
       return -1;
  }

//struct in_addr server_in_addr;

//if(inet_pton(AF_INET, MY_IP,&server_in_addr) <=0){
//     printf("error");
//     return -1;
//}


  server_addr->sin_port = htons(MY_PORT);
  server_addr->sin_addr.s_addr = INADDR_ANY;
  server_addr->sin_family = AF_INET;

	//setter master fd til 0 og timeout til 3 minutter 
	FD_ZERO(&masterfd_set);
	FS_ZERO(&tempfd_set);
	fdmax = serverfd;
	timeout.tv_sec = 3*60;
	timeout.tv_usec = 0;
	
	// Forandrer på instillingene slik at socketen/porten er gjenbrukbar 
	int yes = 1; // Denne er 1 fordi vi skal slå på SO_REUSEADDR
	if(setsocketopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(*server_addr)=-1){
		printf("Error setting socket as readable: %i", errno);
		return -1;
	}
	
	// Binder socketen
	if(bind(serverfd, (struct sockaddr* ) server_addr, sizeof(*server_addr))==-1){
		printf("error binding socket: %i",errno);
		return -1;
	}
	
	// Lytter på denne porten
	listen(serverfd,NUMBER_OF_CONNECTIONS);
	
	FD_SET(serverfd, &masterfd_set);


	while(true){
		memcpy(&readfd_set, &masterfd_set, sizeof(master_set));
		if(select(NUMBER_OF_CONNECTIONS+1, &readfd_set, NULL, NULL, &timeout)<=0){
			printf("Error i select");
			return -1; 
		}
		for (int i = 0; i <= fdmax; i++){
			if (FD_ISSET( i, &readfd)){
				if(i == serverfd) {
					newfd =  accept(serverfd, NULL, 0);
					SPAWN NEW THREAD FOR Å HÅDTERE TILKOBLINGENE	
				}
			}
		}
						
			
			
	}






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
