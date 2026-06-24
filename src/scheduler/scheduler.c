#include "scheduler.h"
#include "mmu.h"
#include "process.h"
#include "sbi.h"
#include "traps.h"

void schedule() {
  uint64_t now = current_time();
  sbi_set_timer(now + TICK_INTERVAL_MS(5000));
}

void scheduler() {
  schedule();
  timer();
}

void yield(uint32_t pc, trap_frame_t *tf) {
  curr_proc->sepc = pc;
  memcpy(&curr_proc->tf, tf, sizeof(trap_frame_t));
  curr_proc->state = PROC_RUNNABLE;
  process_t *next = 0x0;
  for (uint8_t p = 0; p < PROCS_MAX; p++) {
    if (&procs[p] != curr_proc && procs[p].state == PROC_RUNNABLE) {
      next = &procs[p];
      break;
    }
  }
  memcpy(tf, &next->tf, sizeof(trap_frame_t));
  next->state = PROC_RUNNING;
  curr_proc = next;
  yield_a(next->sepc);
}
