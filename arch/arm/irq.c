#include <stdio.h>
#include <arch/irq.h>
#include <config.h>
#include <core/vm/vcpu.h>
#include <arch/armv7/smp.h>
#include <irq-chip.h>
#include <types.h>
#include <core/scheduler.h>
#include "record.h"

#define VIRQ_MIN_VALID_PIRQ     16
#define VIRQ_NUM_MAX_PIRQS      MAX_IRQS

static irq_handler_t irq_handlers[MAX_IRQS];

hvmm_status_t do_irq(struct core_regs *regs)
{
#if DO_IRQ_RECORDING
    start_irq_recording();
#endif
    uint32_t irq = irq_hw->ack();

    irq_hw->eoi(irq);

    if (irq_handlers[irq](irq, regs, 0) != VM_IRQ) {
        irq_hw->dir(irq);
    }

#if DO_IRQ_RECORDING
    stop_irq_recording(irq);
#endif
    return HVMM_STATUS_SUCCESS;
}

void irq_init()
{
    set_irqchip_type();
    write_cp32((0x10 | 0x8), HCR);
    irq_handler_init(irq_handlers);
}

void register_irq_handler(uint32_t irq, irq_handler_t handler, uint8_t polarity)
{
    if (irq < MAX_IRQS) {
        irq_handlers[irq] = handler;
    }
    irq_hw->set_irq_type(irq, polarity);
    irq_hw->enable(irq);
}

