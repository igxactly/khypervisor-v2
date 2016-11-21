#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdint.h>

#define DO_EXEC_RECORDING 1

#define DO_IRQ_RECORDING  1
#define DO_TRAP_RECORDING 0

#define PRINT_EACH_IRQ  1
#define PRINT_EACH_TRAP 0

#define NR_MAX_IRQS  1000
#define NR_MAX_TRAPS 1000

void dump_info(void);

void start_irq_recording(void);
void stop_irq_recording(uint32_t irq);

void start_trap_recording(void);
void stop_trap_recording(uint32_t trap);
#endif
