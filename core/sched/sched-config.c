#include <core/sched/sched-config.h>
#include <core/sched/scheduler_skeleton.h>

const struct sched_policy *schedconf_g_policy[NR_CPUS] = {
    &sched_rt_rm,
    &sched_rr,
    &sched_rr,
    &sched_rr
};

/* vcpu -> pcpu */
uint32_t schedconf_g_vcpu_to_pcpu_map[TOTAL_VCPUS] = {
    0,
    0,
    // 0,
    1
};

uint32_t schedconf_rm_tick_interval_ms[NR_CPUS] = {
    1000,
    0,
    0,
    0
};

uint32_t schedconf_rm_period_budget[TOTAL_VCPUS][2] = {
    {10, 5},
    {10, 5},
    // {10, 2},
    {0, }
};

/*
uint32_t schedconf_rr_slice[TOTAL_VCPUS] = {
    0,
    0,
    // 0,
    5
};
*/
