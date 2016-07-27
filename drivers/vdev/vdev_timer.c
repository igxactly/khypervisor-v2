#include <stdio.h>
#include <vdev.h>
#include <core/timer.h>
#include <arch/irq.h>
#include <arch/armv7.h>
#include <core/scheduler.h>
#include <config.h>
#include <irq-chip.h>

// #define DEBUG

#define VTIMER_IRQ 30 /* NS PL1 Timer */

extern struct virq_chip *virq_hw;

/* represents a generic timer w/o SE,VE (NS PL1, PL0 timer) */
struct vdev_timer {
    /* data for hypervisor */
    uint64_t p_ct_offset;

    /* regs for guest */
    uint32_t k_ctl;

    uint32_t p_ctl;
    uint64_t p_cval;

    uint32_t v_ctl;
    uint64_t v_cval;
    uint64_t v_off;
};

/*
CP64  CNTPCT
CP64  CNTVCT
CP64  CNTP_CVAL
CP64  CNTV_CVAL
CP64  CNTVOFF
CP64  CNTHP_CVAL

CP32  CNTFRQ
CP32  CNTKCTL
CP32  CNTP_TVAL
CP32  CNTP_CTL
CP32  CNTV_TVAL
CP32  CNTV_CTL
CP32  CNTHCTL
CP32  CNTHP_TVAL
CP32  CNTHP_CTL
 */

bool vdev_timer_access32(uint8_t dir, uint32_t *rt) {
    return false;
}

bool vdev_timer_access64(uint8_t dir, uint32_t *rt_low, uint32_t *rt_high) {
    return false;
}

#if 0
static hvmm_status_t vdev_vtimer_access_handler(uint32_t write,
                                                uint32_t offset, uint32_t *pvalue, enum vdev_access_size access_size)
{
    printf("%s: %s offset:%d value:%x\n", __func__,
           write ? "write" : "read",
           offset, write ? *pvalue : (uint32_t) pvalue);
    hvmm_status_t result = HVMM_STATUS_BAD_ACCESS;
    uint32_t vmid = get_current_vcpuid();
    if (!write) {
        /* READ */
        switch (offset) {
        case 0x0:
            *pvalue = vtimer_regs[vmid].vtimer_mask;
            result = HVMM_STATUS_SUCCESS;
            break;
        }
    } else {
        /* WRITE */
        switch (offset) {
        case 0x0:
            vtimer_regs[vmid].vtimer_mask = *pvalue;
            vtimer_changed_status(vmid, *pvalue);
            result = HVMM_STATUS_SUCCESS;
            break;
        }
    }
    return result;
}

static int32_t vdev_vtimer_read(struct arch_vdev_trigger_info *info)
{
    uint32_t offset = info->fipa - _vdev_timer_info.base;

    return vdev_vtimer_access_handler(0, offset, info->value, info->sas);
}

static int32_t vdev_vtimer_write(struct arch_vdev_trigger_info *info)
{
    uint32_t offset = info->fipa - _vdev_timer_info.base;

    return vdev_vtimer_access_handler(1, offset, info->value, info->sas);
}

static hvmm_status_t vdev_vtimer_post(struct core_regs *regs)
{
    uint8_t isize = 4;

    if (regs->cpsr & 0x20) { /* Thumb */
        isize = 2;
    }

    regs->pc += isize;

    return 0;
}

static int32_t vdev_vtimer_check(struct arch_vdev_trigger_info *info)
{
    uint32_t offset = info->fipa - _vdev_timer_info.base;

    if (info->fipa >= _vdev_timer_info.base &&
            offset < _vdev_timer_info.size) {
        return 0;
    }
    return VDEV_NOT_FOUND;
}

void callback_timer(void *pdata, uint32_t *delay_tick)
{
    vmid_t vmid = get_current_vcpuid();

    if (_timer_status[vmid] == 0)
        // TODO:(igkang) make '0' parameter as named constant.
    {
        virq_inject(vmid, VTIMER_IRQ, 0, INJECT_SW);
    }

    /* FIXME:(igkang) hardcoded */
    *delay_tick = 1 * TICKTIME_1MS / 50;
}

/* TODO:(igkang) modify vdev_timer to use new timer manager API */
static hvmm_status_t vdev_vtimer_reset(void)
{
    int i;
    // struct timer timer;
    uint32_t cpu = smp_processor_id();

    if (!cpu) {
        for (i = 0; i < NUM_GUESTS_STATIC; i++) {
            _timer_status[i] = 1;
        }
    }

    // timer.interval = TICKTIME_1MS;
    // timer.callback = &callback_timer;

    // timer_set(&timer, GUEST_TIMER);

    return HVMM_STATUS_SUCCESS;
}

struct vdev_ops _vdev_hvc_vtimer_ops = {
    .init = vdev_vtimer_reset,
    .check = vdev_vtimer_check,
    .read = vdev_vtimer_read,
    .write = vdev_vtimer_write,
    .post = vdev_vtimer_post,
};

struct vdev_module _vdev_hvc_vtimer_module = {
    .name = "K-Hypervisor vDevice vTimer Module",
    .author = "Kookmin Univ.",
    .ops = &_vdev_hvc_vtimer_ops,
};

hvmm_status_t vdev_vtimer_init()
{
    hvmm_status_t result = HVMM_STATUS_BUSY;

    result = vdev_register(VDEV_LEVEL_LOW, &_vdev_hvc_vtimer_module);
    if (result == HVMM_STATUS_SUCCESS) {
        printf("vdev registered:'%s'\n", _vdev_hvc_vtimer_module.name);
    } else {
        printf("%s: Unable to register vdev:'%s' code=%x\n",
               __func__, _vdev_hvc_vtimer_module.name, result);
    }

    return result;
}

// vdev_module_low_init(vdev_vtimer_init);

#endif

