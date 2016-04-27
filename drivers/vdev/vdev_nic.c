#include <stdio.h>
#include <vdev.h>
#include <core/vm/vcpu.h>
#include <drivers/vdev/vnic.h>
#include <io.h>
#include <irq-chip.h>

extern struct virq_chip *virq_hw;

static int32_t vnic_read(void *pdata, uint32_t offset);
static int32_t vnic_write(void *pdata, uint32_t offset, uint32_t *addr);
static int32_t vnic_create(void **pdata);

struct smc91x {
    /* internal state of virtual NIC(smc91x) goes here */
    uint32_t smc91x_bsr;

    /* ... more struct fields needded */
};

struct vdev_module smc91x_vnic = {
    .name = "vdev_smc91x",
    .base = VNIC_BASE,
    .size = 0x1000000, /* 16MB */
    .read = vnic_read,
    .write = vnic_write,
    .create = vnic_create,
};

#include <stdlib.h>
static int32_t vnic_create(void **pdata)
{
    struct smc91x *vnic = malloc(sizeof(struct smc91x));

    *pdata = vnic;
    return 0;
}

static int32_t vnic_write(void *pdata, uint32_t offset, uint32_t *addr)
{
    // struct smc91x *smc91x = pdata;

    /*
    switch (offset) {
    case VNIC_BSR(0):
        smc91x->smc91x_bsr = readl(addr);
        writel(smc91x->smc91x_bsr, VNIC_BSR(VNIC_BASE));
        break;

    default:
        break;
    }

    return 0; */

    printf("%s addr:%\n", __func__, offset, addr);

    uint16_t data = readw(addr);
    printf("%s o:%x d:%x\n", __func__, offset, data);

    writew(data, VNIC_BASE + offset);
    return 0;
}

static int32_t vnic_read(void *pdata, uint32_t offset)
{
    // struct smc91x *smc91x = pdata;

    /*
    switch (offset) {
    case VNIC_BSR(0):
        return smc91x->smc91x_bsr;
        break;

    default:
        break;
    }
    return 0; */
    uint16_t data = readw(VNIC_BASE + offset);
    printf("%s o:%x d:%x\n", __func__, offset, data);
    return data;
}

static int owner_id = 0;
static void vdev_smc91x_irq_handler(int irq, void *regs, void *pdata)
{
    if (irq != VNIC_IRQ) {
        printf("Uncorrect irq nuber\n");
        return;
    }

    struct vcpu *vcpu = vcpu_find(owner_id);
    virq_hw->forward_irq(vcpu, VNIC_IRQ, VNIC_IRQ, INJECT_SW);
}

hvmm_status_t vdev_smc91x_init()
{
    hvmm_status_t result = HVMM_STATUS_SUCCESS; /* originally was HVMM_STATUS_BUSY; //???? Why busy?  */

    vdev_register(&smc91x_vnic);
    vdev_irq_handler_register(VNIC_IRQ, vdev_smc91x_irq_handler);

    return result;
}

vdev_module_init(vdev_smc91x_init);

