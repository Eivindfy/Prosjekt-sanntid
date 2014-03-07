#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

void* server_client_comunication(void* spvoid);

void *servermodule(void *module_sockfdvoid);

int server_init();

int create_client();

#endif
