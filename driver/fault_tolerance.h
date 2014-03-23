#ifndef FAULT_TOLERANCE_H
#define FAULT_TOLERANCE_H

void * backup_module(void * socketfd_void);
int backup_module_init();
int watchdog_spamer_init();
void * watchdog_spamer();

#endif
