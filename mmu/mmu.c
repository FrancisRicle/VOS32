#include "../include/common.h"

extern char __free_ram[], __free_ram_end[];

paddr_t knext_free_page() {
    static paddr_t next_paddr = (paddr_t) __free_ram;
    paddr_t paddr = next_paddr;
    next_paddr += PAGE_SIZE;

    if (next_paddr > (paddr_t) __free_ram_end) {
        PANIC("Esta cara la memoria >.<")
    }

    memset((void*) paddr, 0, PAGE_SIZE);
    return paddr;
}

paddr_t kn_free_pages(uint32_t n) {
    if (n <= 0) {
        PANIC("MAMA; ME ESTAN PIDIENDO MEMORIA NEGATIVA!!")
    }
    paddrt_t paddr = knext_free_page();
    for (uint32_t i = 1; i < n; i++){
        knext_free_page();
    }
    return paddr;
}