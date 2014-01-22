#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define ADDRESS "127.0.0.1"




int main(){
int descriptor=0;

fd = socket(AF_INET,SOCK_STREAM,0);  //PF_INET ???????
struct sockaddr_in address;

address.sin_family = AF_INET;
address.sin_port = htons(PORT);
inet_pton(AF_INET, "ADDRESS", &address.sin_addr)



 
if (-1 == connect(fd, (struct sockaddr *)&address, sizeof(address)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    
    
//gjer noko
    

return 0;
}

