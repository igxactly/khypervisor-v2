#include <stdio.h>
#include <arch/irq.h>
#include <config.h>
#include <core/vm/vcpu.h>
#include <arch/armv7/smp.h>
#include <irq-chip.h>
#include <types.h>
#include <core/scheduler.h>

#define VIRQ_MIN_VALID_PIRQ     16
#define VIRQ_NUM_MAX_PIRQS      MAX_IRQS

static irq_handler_t irq_handlers[MAX_IRQS];
static irq_handler_t vdev_irq_handlers[MAX_IRQS];

#include <arch_regs.h>

hvmm_status_t do_irq(struct core_regs *regs)
{
    uint32_t irq = irq_hw->ack();

    irq_hw->eoi(irq);

    if (irq == 47) {
        printf("1 %s %d\n", __func__, irq);
    }

    if (irq < 16) {
        // SGI Handler
        printf("SGI Occurred\n");
    } else if (irq_handlers[irq]) {
        // Handler for Hypervisor
        irq_handlers[irq](irq, regs, 0);
        irq_hw->dir(irq);
    } else if (vdev_irq_handlers[irq]) {
        if (irq == 47) {
            printf("2 %s %d\n", __func__, irq);
        }
        // Handler for VMs
        vdev_irq_handlers[irq](irq, regs, 0);
    } else {
        if (irq == 47) {
            printf("%s %d\n", __func__, irq);
        }
        // Not found handler that just forward irq to VMs
        is_guest_irq(irq);
    }

    return HVMM_STATUS_SUCCESS;
}

void irq_init()
{
    set_irqchip_type();
    write_cp32((0x10 | 0x8), HCR);
}

void register_irq_handler(uint32_t irq, irq_handler_t handler)
{
    if (irq < MAX_IRQS) {
        irq_handlers[irq] = handler;
    }
}

void register_vdev_irq_handler(uint32_t irq, irq_handler_t handler)
{
    if (irq < MAX_IRQS) {
        vdev_irq_handlers[irq] = handler;
    }
}
