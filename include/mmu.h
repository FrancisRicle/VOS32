#pragma once
#include "stdint.h"
#define PAGE_SIZE 4096
extern char __free_ram[], __free_ram_end[];
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
void *memset(void *buf, char c, uint32_t n);
void *memcpy(void *dst, const void *src, uint32_t n);
paddr_t kpage(void);
paddr_t knpage(uint32_t n);
