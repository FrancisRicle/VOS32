#include "scheduler.h"
// #include "mmu.h"
#include "process.h"
#include "sbi.h"
#include "traps.h"

void schedule() {
  uint64_t now = current_time();
  sbi_set_timer(now + TICK_INTERVAL);
}

void scheduler() {
  schedule();
  timer();
}

// void switch_context(trap_frame_t *curr_tf, trap_frame_t *next_tf) {
//   // memcpy(&curr_proc->tf, curr_tf, sizeof(trap_frame_t));
//   // memcpy(curr_tf, next_tf, sizeof(trap_frame_t));
// }

void yield(uint32_t pc, trap_frame_t *tf) {
  curr_proc->sepc = pc;
  uint8_t p = 0;
  while (p < PROCS_MAX && procs[p].state != PROC_RUNNABLE) {
    p++;
  }
  curr_proc->state = PROC_RUNNABLE;
  yield_a(procs[p].sepc);
  *tf = procs[p].tf;
  procs[p].state = PROC_RUNNING;
  curr_proc = &procs[p];
}
