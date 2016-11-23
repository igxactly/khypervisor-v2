#include <record.h>

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

void print_info(uint64_t exec_time)
{
#if DO_IRQ_RECORDING && PRINT_EACH_IRQ
    unsigned long min_time = 0xFFFFFFFF;
    unsigned long max_time = 0;
    uint64_t avg = irq_time / irq_count;
    uint64_t stdev_sq = 0;
    for (int i = 0; i < irq_count; i++) {
        if (i == NR_MAX_IRQS) break;

        if (min_time > irqs[i].time)
            min_time = irqs[i].time;

        if (max_time < irqs[i].time)
            max_time = irqs[i].time;

        uint64_t dev_sq;
        dev_sq = (irqs[i].time > avg) ? irqs[i].time - avg : avg - irqs[i].time;

        stdev_sq += dev_sq * dev_sq;

        printf("irq : %u, occured: %lu, time spent: %lu ns, dev: %lu\n",
                irqs[i].irq, irqs[i].occured, irqs[i].time);
    }

    stdev_sq = stdev_sq / irq_count;
#endif

#if DO_IRQ_RECORDING
    printf("total irqs: %llu, time spent: %llu, average: %llu ns/irq\n",
            irq_count, irq_time, irq_time/irq_count);
#endif

#if DO_IRQ_RECORDING && PRINT_EACH_IRQ
    printf("mintime: %lu, maxtime: %lu, stdev^2: %llu ns/irq\n",
            min_time, max_time, stdev_sq);
#endif

#if DO_EXEC_RECORDING
    printf("total execution time: %llu ns\n",
            exec_time);
#endif
}

void dump_info(void)
{
    static uint32_t count_do_print_info = 0;
    static uint64_t start_time, stop_time;

    if (0 == count_do_print_info) {
        start_time = NOW();
        irq_count = 0;
        irq_time = 0;
        count_do_print_info++;

    } else if (1000 <= count_do_print_info) {
        stop_time = NOW();
        print_info(stop_time - start_time);
        count_do_print_info = 0;
    } else {
        count_do_print_info++;
    }
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
