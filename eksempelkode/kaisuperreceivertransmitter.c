#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 50000
#define ADDRESS "127.0.0.1"



int main(){


int fd = socket(AF_INET,SOCK_STREAM,0);  //PF_INET ???????
struct sockaddr_in address;

address.sin_family = AF_INET;
address.sin_port = htons(PORT);

//lager AF_INET addresse som pc forstaar ut av ADDRESS og legger inn i address.sin_addr
inet_pton(AF_INET, ADDRESS, &address.sin_addr);




if (-1 == connect(fd, (struct sockaddr *)&address, sizeof(address)))
    {
      perror("connect failed");
      close(fd);
      exit(EXIT_FAILURE);
    }

char buffer[1024];
char ballorstring[1024]="ballor";
printf("Type \"ballor\" to exit\n");

read(fd,buffer,sizeof(buffer));
printf("SERVER SAYS: \n"); 
printf("%s",buffer);
printf("\n");
	 

while(1){
read(fd,buffer,sizeof(buffer));

printf("SERVER SAYS: \n");

printf("%s",buffer);
printf("\n");

printf("YOU SAY: \n");
fgets(buffer,1024,stdin);
printf("\n");
if(strncmp(ballorstring,buffer,6)==0){
    close(fd);
    return 0;
}


write(fd,buffer,sizeof(buffer));
}



return 0;
}
