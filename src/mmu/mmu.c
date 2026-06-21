#include "mmu.h"
#include "panic.h"

void *memset(void *buf, char c, uint32_t n) {
  uint8_t *p = (uint8_t *)buf;
  while (n--)
    *p++ = c;
  return buf;
}

void *memcpy(void *dst, const void *src, uint32_t n) {
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;
  while (n--)
    *d++ = *s++;
  return dst;
}

paddr_t kpage() {
  static paddr_t next_paddr = (paddr_t)__free_ram;
  paddr_t paddr = next_paddr;
  next_paddr += PAGE_SIZE;

  if (next_paddr > (paddr_t)__free_ram_end) {
    panic("Esta cara la memoria >.<");
  }

  memset((void *)paddr, 0, PAGE_SIZE);
  return paddr;
}

paddr_t knpages(uint32_t n) {
  if (n <= 0) {
    panic("MAMA; ME ESTAN PIDIENDO MEMORIA NEGATIVA!!");
  }
  paddr_t paddr = kpage();
  for (uint32_t i = 1; i < n; i++) {
    kpage();
  }
  return paddr;
}
