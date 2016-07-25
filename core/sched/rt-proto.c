#include <core/sched/scheduler_skeleton.h>
#include <config.h>
#include <arch/armv7.h>
#include <stdlib.h>
#include <debug.h>
#include <stdbool.h>

#include <lib/list.h>
#include <core/timer.h>

struct entry_data_rt {
    vcpuid_t vcpuid;
    uint32_t tick_reset_val;

    struct list_head head;
};

struct sched_data_rt {
    struct list_head *current;
    struct list_head runqueue;
};

/**
 * Scheduler related data initialization
 */
void sched_rt_init(struct scheduler *s)
{
    struct sched_data_rt *sd = (struct sched_data_rt *) (s + 1);

    /* Check scheduler config */
    /* Allocate memory for system-wide data */
    /* Initialize data */
    sd->current = NULL;
    LIST_INITHEAD(&sd->runqueue);
}

int sched_rt_vcpu_register(struct scheduler *s, struct sched_entry *e)
{
    // struct sched_data_rt *sd = (struct sched_data_rt *) (s + 1);
    struct entry_data_rt *ed = (struct entry_data_rt *) (e + 1);

    /* FIXME:(igkang) Hardcoded. should use function parameter's value for tick_reset_val init. */
    ed->tick_reset_val = 5;
    LIST_INITHEAD(&ed->head);

    return 0;
}

int sched_rt_vcpu_unregister(struct scheduler *s, struct sched_entry *e)
{
    /* Check if vcpu is registered */
    /* Check if vcpu is detached. If not, request detachment.*/
    /* If we have requested detachment of vcpu,
     *   let's wait until it is detached by main scheduling routine */

    return 0;
}

int sched_rt_vcpu_attach(struct scheduler *s, struct sched_entry *e)
{
    struct sched_data_rt *sd = (struct sched_data_rt *) (s + 1);
    struct entry_data_rt *ed = (struct entry_data_rt *) (e + 1);

    /* Add it to runqueue */
    LIST_ADDTAIL(&ed->head, &sd->runqueue);

    return 0;
}

int sched_rt_vcpu_detach(struct scheduler *s, struct sched_entry *e)
{
    // struct sched_data_rt *sd = (struct sched_data_rt *) (s + 1);
    struct entry_data_rt *ed = (struct entry_data_rt *) (e + 1);

    /* Check if vcpu is attached */
    /* Remove it from runqueue by setting will_detached flag*/
    /* Set entry_data_rt's fields */

    LIST_DELINIT(&ed->head);

    return 0;
}

/**
 * Main scheduler routine in RR policy implmentation
 */
int sched_rt_do_schedule(struct scheduler *s, uint64_t *expiration)
{
    struct sched_data_rt *sd = (struct sched_data_rt *) (s + 1);

    /* TODO:(igkang) change type to bool */
    struct entry_data_rt *next_ed = NULL;
    bool is_switching_needed = false;
    int next_vcpuid = VCPUID_INVALID;

    /* check pending attach list
     *      then attach them to runqueue */
    /* TODO:(igkang) write code to attach pending attach requests */

    /* TODO:(igkang) improve logical code structure to make it easier to read */

    /* determine next vcpu to be run
     *  - if there is an detach-pending vcpu than detach it. */
    if (sd->current == NULL) { /* No vCPU is running */
        if (!LIST_IS_EMPTY(&sd->runqueue)) { /* and there are some vcpus waiting */
            is_switching_needed = true;
        }
    } else { /* There's a vCPU currently running */
        struct entry_data_rt *current_ed = NULL;
        struct sched_entry *current_e = NULL;

        /* put current entry back to runqueue */
        current_ed = LIST_ENTRY(struct entry_data_rt, sd->current, head);
        LIST_ADDTAIL(sd->current, &sd->runqueue);

        /* let's switch as tick is over */
        sd->current = NULL;

        current_e = ((struct sched_entry *) current_ed) - 1;
        current_e->state = SCHED_WAITING;

        is_switching_needed = true;
    }

    /* update scheduling-related data (like tick) */
    if (is_switching_needed) {
        /* move entry from runqueue to current */
        sd->current = sd->runqueue.next;
        LIST_DELINIT(sd->current);

        next_ed = LIST_ENTRY(struct entry_data_rt, sd->current, head);

        *expiration =
            timer_get_timenow() + MSEC(1) * (uint64_t) next_ed->tick_reset_val;
    }

    /* vcpu of current entry will be the next vcpu */
    if (sd->current != NULL) {
        struct sched_entry *next_e = NULL;
        next_ed = LIST_ENTRY(struct entry_data_rt, sd->current, head);

        next_e = ((struct sched_entry *) next_ed) - 1;
        next_e->state = SCHED_RUNNING;

        /* set return next_vcpuid value */
        next_vcpuid = next_e->vcpuid;
    }

    return next_vcpuid;
}

/* TODO:(igkang) assign proper function's address to s-algo struct */
const struct sched_policy sched_rt_proto = {
    .size_sched_extra = sizeof(struct sched_data_rt),
    .size_entry_extra = sizeof(struct entry_data_rt),

    .init = sched_rt_init,
    .register_vcpu = sched_rt_vcpu_register,
    .unregister_vcpu = sched_rt_vcpu_unregister,
    .attach_vcpu = sched_rt_vcpu_attach,
    .detach_vcpu = sched_rt_vcpu_detach,
    .do_schedule = sched_rt_do_schedule
};
