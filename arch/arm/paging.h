#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>
#include "lpae.h"

void paging_init();
void paging_create(addr_t base);
void paging_add_mapping(addr_t va, addr_t pa, uint8_t mem_attr, uint32_t size);
void paging_add_ipa_mapping(addr_t base, addr_t ipa, addr_t pa, uint8_t mem_attr, uint8_t af, uint32_t size);

#endif /* __MM_H__*/
