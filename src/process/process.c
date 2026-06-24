#include "process.h"
#include "mmu.h"
#include "panic.h"

extern char __kernel_base[];

process_t procs[PROCS_MAX];
process_t *curr_proc;

void init_procs() {
  for (uint8_t i = 0; i < PROCS_MAX; i++) {
    procs[i].state = PROC_NULL;
    procs[i].pid = i + 1;
    procs[i].sepc = PROCS_BASE;
  }
}

void create_process(uint32_t pc) {
  uint8_t p = 0;
  while (p < PROCS_MAX && procs[p].state != PROC_NULL) {
    p++;
  }
  if (p > PROCS_MAX) {
    panic("PROCS LIMIT");
  }
  procs[p].sepc = pc;
  procs[p].state = PROC_RUNNABLE;
  memset(&procs[p].tf, 0x0, sizeof(trap_frame_t));
  memset(&procs[p].stack, 0x0, sizeof(procs[p].stack));
  procs[p].tf.sp = (uint32_t)(procs[p].stack + sizeof(procs[p].stack));
  procs[p].tf.ra = pc;
  uint32_t *page_table = (uint32_t *) kpage();
  for (paddr_t paddr = (paddr_t) __kernel_base; paddr < (paddr_t) __free_ram_end; paddr += PAGE_SIZE) {
    map_page(page_table, paddr, paddr, PAGE_R | PAGE_W | PAGE_X);
  }
  procs[p].page_table = page_table;
}
void run_procs() {
  uint8_t p = 0;
  while (p < PROCS_MAX && procs[p].state != PROC_RUNNABLE) {
    p++;
  }
  curr_proc = &procs[p];
  curr_proc->state = PROC_RUNNING;
  exec(curr_proc->sepc, procs[p].tf.sp);
}
