#ifndef __GENERIC_TIMER_H___
#define __GENERIC_TIMER_H___

#include <stdint.h>
#include <asm/asm.h>

/* Generic Timer */

/* *** from sys/arch/arm/cortex/gtmr_intr.h of NetBSD *** */
/*-
 * Copyright (c) 2013 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Matt Thomas of 3am Software Foundry.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * The ARM Generic Timer defines 4 PPIs (Private Peripheral Interrupts).
 * These are same for the A7 and A15 mpcores.
 */
#define IRQ_GTMR_PPI_HTIMER     26  // PL2 Hypervisor Timer
#define IRQ_GTMR_PPI_VTIMER     27  // PL0 Virtual Timer
#define IRQ_GTMR_PPI_PTIMER_S   29  // PL1 Secure Physical Timer
#define IRQ_GTMR_PPI_PTIMER_NS  30  // PL1 Non-Secure Physical Timer


/* *** from sys/arch/arm/include/asm.h of NetBSD *** */
/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  from: @(#)asm.h 5.5 (Berkeley) 5/7/91
 */

#define __BIT(n)    (1 << (n))
#define __BITS(hi,lo)   ((~((~0)<<((hi)+1)))&((~0)<<(lo)))

/* *** from sys/arch/arm/include/armreg.h of NetBSD *** */
/*
 * Copyright (c) 2016 Ingu Kang
 * Copyright (c) 1998, 2001 Ben Harris
 * Copyright (c) 1994-1996 Mark Brinicombe.
 * Copyright (c) 1994 Brini.
 * All rights reserved.
 *
 * This code is derived from software written for Brini by Mark Brinicombe
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by Brini.
 * 4. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BRINI ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BRINI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* Defines for ARM Generic Timer */
#define ARM_CNTCTL_ENABLE       __BIT(0) // Timer Enabled
#define ARM_CNTCTL_IMASK        __BIT(1) // Mask Interrupt
#define ARM_CNTCTL_ISTATUS      __BIT(2) // Interrupt is pending

#define ARM_CNTKCTL_PL0PTEN     __BIT(9)
#define ARM_CNTKCTL_PL0VTEN     __BIT(8)
#define ARM_CNTKCTL_EVNTI       __BITS(7,4)
#define ARM_CNTKCTL_EVNTDIR     __BIT(3)
#define ARM_CNTKCTL_EVNTEN      __BIT(2)
#define ARM_CNTKCTL_PL0PCTEN        __BIT(1)
#define ARM_CNTKCTL_PL0VCTEN        __BIT(0)

#define ARM_CNTHCTL_EVNTI       __BITS(7,4)
#define ARM_CNTHCTL_EVNTDIR     __BIT(3)
#define ARM_CNTHCTL_EVNTEN      __BIT(2)
#define ARM_CNTHCTL_PL1PCTEN        __BIT(1)
#define ARM_CNTHCTL_PL1VCTEN        __BIT(0)

#define ARMREG_READ_INLINE(name, __insnstring)          \
static inline uint32_t armreg_##name##_read(void)       \
{                               \
    uint32_t __rv;                      \
    __asm __volatile("mrc " __insnstring : "=r"(__rv)); \
    return __rv;                        \
}

#define ARMREG_WRITE_INLINE(name, __insnstring)         \
static inline void armreg_##name##_write(uint32_t __val)    \
{                               \
    __asm __volatile("mcr " __insnstring :: "r"(__val));    \
}

#define ARMREG_READ_INLINE2(name, __insnstring)         \
static inline uint32_t armreg_##name##_read(void)       \
{                               \
    uint32_t __rv;                      \
    __asm __volatile(__insnstring : "=r"(__rv));    \
    return __rv;                        \
}

#define ARMREG_WRITE_INLINE2(name, __insnstring)        \
static inline void armreg_##name##_write(uint32_t __val)    \
{                               \
    __asm __volatile(__insnstring :: "r"(__val));       \
}

#define ARMREG_READ64_INLINE(name, __insnstring)        \
static inline uint64_t armreg_##name##_read(void)       \
{                               \
    uint64_t __rv;                      \
    __asm __volatile("mrrc " __insnstring : "=r"(__rv));    \
    return __rv;                        \
}

#define ARMREG_WRITE64_INLINE(name, __insnstring)       \
static inline void armreg_##name##_write(uint64_t __val)    \
{                               \
    __asm __volatile("mcrr " __insnstring :: "r"(__val));   \
}

/* cp15 c14 Generic Timer Registers */
ARMREG_READ_INLINE(cnt_frq, "p15,0,%0,c14,c0,0") /* Counter Frequency Register */
ARMREG_WRITE_INLINE(cnt_frq, "p15,0,%0,c14,c0,0") /* Counter Frequency Register */

ARMREG_READ64_INLINE(cntp_ct, "p15,0,%Q0,%R0,c14") /* Physical Count Register */
ARMREG_WRITE64_INLINE(cntp_ct, "p15,0,%Q0,%R0,c14") /* Physical Count Register */
ARMREG_READ64_INLINE(cntv_ct, "p15,1,%Q0,%R0,c14") /* Virtual Count Register */
ARMREG_WRITE64_INLINE(cntv_ct, "p15,1,%Q0,%R0,c14") /* Virtual Count Register */
ARMREG_READ64_INLINE(cntv_off, "p15,4,%Q0,%R0,c14") /* Virtual Count Offset Register */
ARMREG_WRITE64_INLINE(cntv_off, "p15,4,%Q0,%R0,c14") /* Virtual Count Offset Register */

ARMREG_READ_INLINE(cnth_ctl, "p15,4,%0,c14,c1,0") /* Timer PL2 Control Register */
ARMREG_WRITE_INLINE(cnth_ctl, "p15,4,%0,c14,c1,0") /* Timer PL2 Control Register */

ARMREG_READ_INLINE(cnthp_ctl, "p15,4,%0,c14,c2,1") /* PL2 Physical Timer Control Register */
ARMREG_WRITE_INLINE(cnthp_ctl, "p15,4,%0,c14,c2,1") /* PL2 Physical Timer Control Register */
ARMREG_READ_INLINE(cnthp_tval, "p15,4,%0,c14,c2,0") /* PL2 Physical TimerValue Register */
ARMREG_WRITE_INLINE(cnthp_tval, "p15,4,%0,c14,c2,0") /* PL2 Physical TimerValue Register */
ARMREG_READ64_INLINE(cnthp_cval, "p15,6,%Q0,%R0,c14") /* PL2 Physical Timer CompareValue Register */
ARMREG_WRITE64_INLINE(cnthp_cval, "p15,6,%Q0,%R0,c14") /* PL2 Physical Timer CompareValue Register */

ARMREG_READ_INLINE(cntk_ctl, "p15,0,%0,c14,c1,0") /* Timer PL1 Control Register */
ARMREG_WRITE_INLINE(cntk_ctl, "p15,0,%0,c14,c1,0") /* Timer PL1 Control Register */

ARMREG_READ_INLINE(cntp_ctl, "p15,0,%0,c14,c2,1") /* PL1 Physical Timer Control Register */
ARMREG_WRITE_INLINE(cntp_ctl, "p15,0,%0,c14,c2,1") /* PL1 Physical Timer Control Register */
ARMREG_READ_INLINE(cntp_tval, "p15,0,%0,c14,c2,0") /* PL1 Physical TimerValue Register */
ARMREG_WRITE_INLINE(cntp_tval, "p15,0,%0,c14,c2,0") /* PL1 Physical TimerValue Register */
ARMREG_READ64_INLINE(cntp_cval, "p15,2,%Q0,%R0,c14") /* PL1 Physical Timer CompareValue Register */
ARMREG_WRITE64_INLINE(cntp_cval, "p15,2,%Q0,%R0,c14") /* PL1 Physical Timer CompareValue Register */

ARMREG_READ_INLINE(cntv_ctl, "p15,0,%0,c14,c3,1") /* Virtual Timer Control Register */
ARMREG_WRITE_INLINE(cntv_ctl, "p15,0,%0,c14,c3,1") /* Virtual Timer Control Register */
ARMREG_READ_INLINE(cntv_tval, "p15,0,%0,c14,c3,0") /* Virtual TimerValue Register */
ARMREG_WRITE_INLINE(cntv_tval, "p15,0,%0,c14,c3,0") /* Virtual TimerValue Register */
ARMREG_READ64_INLINE(cntv_cval, "p15,3,%Q0,%R0,c14") /* PL1 Virtual Timer CompareValue Register */
ARMREG_WRITE64_INLINE(cntv_cval, "p15,3,%Q0,%R0,c14") /* PL1 Virtual Timer CompareValue Register */

#endif /* INCLUDE_ARCH_ARM_ARMV7_GENERIC_TIMER_H_ */
