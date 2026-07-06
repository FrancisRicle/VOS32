#include "mmu.h"
#include "panic.h"
#include <stdint.h>
uint32_t *kernel_table;

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

paddr_t nphypages(uint32_t n) {
  if (n <= 0) {
    panic("MAMA; ME ESTAN PIDIENDO MEMORIA NEGATIVA!!");
  }
  static paddr_t next_paddr = 0;
  if (next_paddr == 0)
    next_paddr = (paddr_t)&__free_ram;
  paddr_t paddr = next_paddr;
  next_paddr += n * PAGE_SIZE;

  if (next_paddr > (paddr_t)__free_ram_end) {
    panic("Esta cara la memoria >.<");
  }

  memset((void *)paddr, 0, n * PAGE_SIZE);
  return paddr;
}
paddr_t phypage() { return nphypages(1); }

void mappage(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags) {
  if (!is_aligned(vaddr, PAGE_SIZE))
    panic("Virtual ADDR no esta alineada");
  if (!is_aligned(paddr, PAGE_SIZE))
    panic("Physical ADDR no esta alineada");

  uint32_t vpn1 = vpn1_index(vaddr); // posicion en la tabla de tablas
  if (!(table1[vpn1] & PAGE_V)) {    // si no hay sig nivel lo creamos
    uint32_t pt_addr = phypage();
    table1[vpn1] = ((pt_addr / PAGE_SIZE) << 10 | PAGE_V);
  }

  uint32_t vpn0 = vpn0_index(vaddr);
  uint32_t *table0 = (uint32_t *)((table1[vpn1] >> 10) * PAGE_SIZE);
  table0[vpn0] = ((paddr / PAGE_SIZE) << 10) | flags | PAGE_V;
}

void mapmega(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags) {
  if (!is_aligned(vaddr, PAGE_SIZE * 1024))
    panic("vaddr no alineada a megapage");
  if (!is_aligned(paddr, PAGE_SIZE * 1024))
    panic("paddr no alineada a megapage");
  uint32_t vpn1 = vpn1_index(vaddr);
  table1[vpn1] = ((paddr / PAGE_SIZE) << 10) | flags | PAGE_V;
}

void kmap(uint32_t *pt) {
  mapmega(pt, 0x80000000, 0x80000000, PAGE_R | PAGE_W | PAGE_X);
}

void kinitpt(void) {
  kernel_table = (uint32_t *)phypage();
  kmap(kernel_table);
}
