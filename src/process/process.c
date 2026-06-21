#include "process.h"
#include "mmu.h"
#include "panic.h"

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
  procs[p].tf.sp = (uint32_t)&procs[p].stack[sizeof(procs[p].stack) - 1];
}
void run_procs() {
  uint8_t p = 0;
  while (p < PROCS_MAX && procs[p].state != PROC_RUNNABLE) {
    p++;
  }
  curr_proc = &procs[p];
  curr_proc->state = PROC_RUNNING;
  exec(curr_proc->sepc, &procs[p].tf.sp);
}
