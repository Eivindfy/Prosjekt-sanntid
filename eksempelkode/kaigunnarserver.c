#include <sys/socket.h>
#include <sys/types.h>
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
int fd = socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in address;

address.sin_family = AF_INET;
address.sin_port = htons(PORT);

inet_pton(AF_INET,ADDRESS, &address.sin_addr);

bind(fd,(struct sockaddr *)&address,sizeof(address));

listen(fd, 0);
int ny_sock;
socklen_t addr_size = sizeof address;

ny_sock = accept(fd, (struct sockaddr *)&address, &addr_size);
char buffer[1024];
char* message;
//recv(ny_sock, buffer, sizeof(buffer), 0);
//printf("%s\n", buffer);

message = "Server says hello";
send(ny_sock, message, strlen(message)+1, 0);

recv(ny_sock, buffer, sizeof(buffer),0);
printf("%s\n", buffer);

return 0;


}
