#include "tcpudpchannel.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>


void * backup_module(void * socketfd_void){
	int tcpsocketfd = *(int*) socketfd_void;
	free(tcp_socketfd_void);

	int udp_socketfd = tcpudpchannel_init();
	char[1024] send_buffer;
	
	send(se
	
}


int backup_module_init(){

int fd[2];
socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);


int* dynamic_int_pointer = malloc(sizeof(*dynamic_int_pointer));
*dynamic_int_pointer = fd[0];
void* dynamic_void_pointer;
dynamic_void_pointer = (void*)dynamic_int_pointer;


pthread_t backup;

pthread_create(&backup,NULL, backup_module, dynamic_void_pointer);

return fd[1];

}
