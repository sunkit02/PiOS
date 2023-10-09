#ifndef MM_PSR_H
#define MM_PSR_H

int get_cpsr();
int save_cpsr();
int get_spsr();
int mmu_enabled();
int enable_mmu();

void invoke_reset_handler(void);

#endif // !MM_PSR_H
