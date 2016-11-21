#include <vm_config.h>
#include <config.h>
#include <size.h>

struct vm_config vm_conf[] = {
    { 1, SZ_512M, 0x40000000 },
    { 1, SZ_256M, 0x90000000 },
    { 1, SZ_256M, 0xA0000000 }
};
