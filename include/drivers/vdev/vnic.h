#ifndef __VNIC_H__
#define __VNIC_H__

/* See FastModels FVP Ref. Manual - Table 7-3 */
#define VNIC_IRQ                47
#define VNIC_BASE               0x1A000000

#define VNIC_BSR(x)            (x + 0x0E)   // RW

// #define VNIC_(x) (x + 0x04)   // RO
// #define VNIC_(x) (x + 0x08)   // RW
// #define VNIC_(x) (x + 0x0C)   // WO
// #define VNIC_(x) (x + 0x10)   // RO
// #define VNIC_(x) (x + 0x14)   // RO
// #define VNIC_(x) (x + 0x18)   // RW

#endif
