#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 33546
#define HOST "129.241.187.161"
#define MY_IP "129.241.187.143"
#define MY_PORT 0


int main(){

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
                printf("error");
                return -1;
        }
        server_addr->sin_port = htons(PORT);
        server_addr->sin_addr = host_addr;
        server_addr->sin_family = AF_INET;

        if(connect(socketfd, (struct sockaddr* )server_addr,sizeof(*server_addr)) == -1){
                printf("error");
                return -1;
        }
        char buf[1024];
        recv(socketfd, buf, sizeof(buf), 0);
        printf("%s\n", buf);

        char* message = "herming er teit\0";
        send(socketfd,message,strlen(message)+1,0);

        recv(socketfd, buf, sizeof(buf), 0);
        printf("%s\n", buf);

        return 0;
}
