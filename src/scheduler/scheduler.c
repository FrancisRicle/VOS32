#include "scheduler.h"
#include "mmu.h"
#include "sbi.h"
#include "traps.h"

void schedule() {
  uint64_t now = current_time();
  sbi_set_timer(now + TICK_INTERVAL_MS(500));
}

void scheduler() {
  schedule();
  timer();
}

uint32_t nextproc(uint32_t exclude) {
  uint32_t next = exclude;
  do {
    next++;
    if (next == PROCS_MAX)
      next = 0;
  } while (procs[next].state != PROC_RUNNABLE);
  return next;
}

void savecurrproc(uint32_t currpc, trap_frame_t *currtf) {
  procs[currpid].epc = currpc;
  memcpy(&procs[currpid].tf, currtf, sizeof(trap_frame_t));
}
void loadnextproc(uint32_t nextpid, trap_frame_t *currtf) {
  memcpy(currtf, &procs[nextpid].tf, sizeof(trap_frame_t));
}
