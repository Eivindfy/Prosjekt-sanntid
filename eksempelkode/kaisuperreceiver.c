#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 34933
#define ADDRESS "129.241.187.161"



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
int numberofchar;



numberofchar=read(fd,buffer,1024);
for (int i=0;i < numberofchar; i++){
printf("%c",buffer[i]);
}

close(fd);


return 0;
}
