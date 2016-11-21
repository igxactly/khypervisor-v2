#include "record.h"

#include <stdio.h>
#include <stdbool.h>
#include <core/timer.h>

uint64_t irq_count;
uint64_t irq_time;

#if PRINT_EACH_IRQ
struct irq_info {
    uint32_t irq;
    unsigned long occured;
    unsigned long time;
} irqs[NR_MAX_IRQS];
#endif

uint64_t trap_count;
uint64_t trap_time;

#if PRINT_EACH_TRAP
struct trap_info {
    uint32_t trap;
    unsigned long occured;
    unsigned long time;
} traps[NR_MAX_TRAPS];
#endif

void print_info(uint64_t exec_time)
{
#if DO_IRQ_RECORDING && PRINT_EACH_IRQ
    for (int i = 0; i < irq_count; i++) {
        if (i == NR_MAX_IRQS) break;

        printf("irq : %u, occured: %lu, time spent: %lu ns\n",
                irqs[i].irq, irqs[i].occured, irqs[i].time);
    }
#endif

#if DO_TRAP_RECORDING && PRINT_EACH_TRAP
    for (int i = 0; i < trap_count; i++) {
        if (i == NR_MAX_TRAPS) break;

        printf("trap : %u, occured: %lu, time spent: %lu ns\n",
                traps[i].trap, traps[i].occured, traps[i].time);
    }
#endif

#if DO_IRQ_RECORDING
    printf("total irqs: %llu, time spent: %llu, average: %llu ns/irq\n",
            irq_count, irq_time, irq_time/irq_count);
#endif
#if DO_TRAP_RECORDING
    printf("total traps: %llu, time spent: %llu, average: %llu ns/trap\n",
            trap_count, trap_time, trap_time/trap_count);
#endif
#if DO_EXEC_RECORDING
    printf("total execution time: %llu ns\n",
            exec_time);
#endif
}

void dump_info(void)
{
    static bool do_print_info = false;
    static uint64_t start_time, stop_time;

    if (do_print_info) {
        stop_time = NOW();
        print_info(stop_time - start_time);
    } else {
        start_time = NOW();
    }

    do_print_info = !do_print_info;
    irq_count = 0;
    irq_time = 0;
    trap_count = 0;
    trap_time = 0;
}

uint64_t irq_start_time, irq_stop_time;

void start_irq_recording(void)
{
    irq_start_time = NOW();
}

void stop_irq_recording(uint32_t irq)
{
    irq_stop_time = NOW();

#if PRINT_EACH_IRQ
    if (irq_count < NR_MAX_IRQS) {
        irqs[irq_count].irq = irq;
        irqs[irq_count].occured = irq_start_time;
        irqs[irq_count].time = (irq_stop_time - irq_start_time);
    }
#endif

    irq_time += (irq_stop_time - irq_start_time);
    irq_count++;
}

uint64_t trap_start_time, trap_stop_time;

void start_trap_recording(void)
{
    trap_start_time = NOW();
}

void stop_trap_recording(uint32_t trap)
{
    trap_stop_time = NOW();

#if PRINT_EACH_TRAP
    if (trap_count < NR_MAX_IRQS) {
        traps[irq_count].trap = trap;
        traps[irq_count].occured = trap_start_time;
        traps[irq_count].time = (trap_stop_time - trap_start_time);
    }
#endif

    trap_time += (trap_stop_time - trap_start_time);
    trap_count++;
}
