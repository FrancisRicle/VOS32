#pragma once
#include "stdint.h"
#define PAGE_SIZE 4096

// Define la macro como la funcion dada por el compilador
#define is_aligned(value, align) __builtin_is_aligned(value, align)

#define vpn1_index(vaddr) (vaddr >> 22) & 0x3ff
#define vpn0_index(vaddr) (vaddr >> 12) & 0x3ff

#define SATP_SV32 (1u << 31) // bit que habilita paginacion en registro satp
// FLags de las paginas de memoria
#define PAGE_V (1 << 0) // Valid
#define PAGE_R (1 << 1) // Read
#define PAGE_W (1 << 2) // Write
#define PAGE_X (1 << 3) // Execute
#define PAGE_U (1 << 4) // User

extern char __free_ram[], __free_ram_end[];
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
extern uint32_t *kernel_table;
void mapmega(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);
void rootpt(uint32_t *ppn);
void kmap(uint32_t *pt);
void kinitpt(void);
void *memset(void *buf, char c, uint32_t n);
void *memcpy(void *dst, const void *src, uint32_t n);
void mappage(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);
paddr_t phypage(void);
paddr_t nphypages(uint32_t n);
