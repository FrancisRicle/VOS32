#include "process.h"
#include "mmu.h"
#include "panic.h"
#include <stdint.h>

extern char __kernel_base[];

process_t procs[PROCS_MAX];
uint32_t currpid;

void pinit() {
  currpid = -1;
  for (uint8_t i = 0; i < PROCS_MAX; i++) {
    procs[i].state = PROC_NULL;
    procs[i].pid = i;
    procs[i].epc = PROCS_BASE;
  }
}

void mapproc(uint32_t *pt, const void *image, uint32_t image_size) {
  for (uint32_t page_offset = 0; page_offset < image_size;
       page_offset += PAGE_SIZE) {
    paddr_t upage = phypage();
    uint32_t remaining = image_size - page_offset;
    uint32_t copy_size = PAGE_SIZE <= remaining ? PAGE_SIZE : remaining;
    memcpy((void *)upage, image + page_offset, copy_size);
    mappage(pt, PROCS_BASE + page_offset, upage,
            PAGE_U | PAGE_R | PAGE_W | PAGE_X);
  }
}
void create_process(const void *image, uint32_t image_size) {
  uint8_t pid = 0;
  while (pid < PROCS_MAX && procs[pid].state != PROC_NULL) {
    pid++;
  }
  if (pid >= PROCS_MAX) {
    panic("PROCS LIMIT");
  }
  procs[pid].epc = (uint32_t)PROCS_BASE;
  procs[pid].state = PROC_RUNNABLE;
  memset(&procs[pid].tf, 0x0, sizeof(trap_frame_t));
  procs[pid].tf.ra = (uint32_t)PROCS_BASE;
  procs[pid].table1 = (uint32_t *)phypage();
  kmap(procs[pid].table1);
  mapproc(procs[pid].table1, image, image_size);
}
uint32_t *currtable1() { return procs[currpid].table1; }
