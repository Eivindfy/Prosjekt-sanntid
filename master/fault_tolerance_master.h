#ifndef FAULT_TOLERANCE_MASTER_H
#define FAULT_TOLETANCE_MASTER_H


void * master_backup(void * socketfd_void);
int master_backup_init();
void* alivespam(void * ap);

#endif
