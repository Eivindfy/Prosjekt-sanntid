#ifndef FILE_IO_H
#define FILE_IO_H


int write_backup_master(char* filename, int* elevator_status, int* elevator_floor, struct ORDER_QUEUE* root);

int retrieve_backup_master(char* filename, int* elevator_status, int* elevator_floor, struct ORDER_QUEUE* root);


#endif
