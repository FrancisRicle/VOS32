#include "traps.h"
#include "console.h"
#include "mmu.h"
#include "panic.h"
#include "scheduler.h"
#include <stdint.h>
void syscall_handler(trap_frame_t *tf) {
  uint32_t pc = exception_pc();
  switch (tf->a0) {
  case 2:
    putc((char)tf->a1);
    break;
  default:
    panic("SYSCALL UNIMPLEMENTED");
  }
  uret(pc + 4);
}
void interrupts_handler(uint32_t scause, trap_frame_t *tf) {
  uint32_t pc = exception_pc();
  switch (CAUSE_ID(scause)) {
  case TIMER_INTERRUPT:
    schedule();
    uint32_t nextpid = nextproc(currpid);
    savecurrproc(pc, tf);
    loadnextproc(nextpid, tf);
    if (procs[nextpid].epc == PROCS_BASE) {
      uinterrupts();
    }
    rootpt(procs[nextpid].table1);
    uret(procs[nextpid].epc);
    currpid = nextpid;
    break;
  case EXTERNAL_INTERRUPT:
    panic("EXTERNAL INTERRUPT HANDLER UNIMPLEMENTED");
    break;
  case SOFTWARE_INTERRUPT:
    panic("SOFTWARE INTERRUPT HANDLER UNIMPLEMENTED");
    break;
  default:
    panic("UNHANDLED INTERRUPT");
  }
}
void exceptions_handler(uint32_t scause, trap_frame_t *tf) {
  switch (CAUSE_ID(scause)) {
  case USYSCALL_EXP:
    syscall_handler(tf);
    break;
  case KSYSCALL_EXP:
    break;
  case ILLEGAL_INSTRUPCION_EXP:
    panic("ILLEGAL INSTRUPCION EXCEPTION");
  case LOAD_PAGE_FAULT_EXP:
    panic("LOAD PAGE FAULT EXCEPTION");
  case INSTRUCTION_PAGE_FAULT_EXP:
    panic("INSTRUCTION PAGE FAULT EXCEPTION");
  case STORE_PAGE_FAULT_EXP:
    panic("STORE PAGE FAULT EXCEPTION");
  default:
    panic("UNHANDLED EXCEPTION");
  }
}
void traps_handler(trap_frame_t *tf) {
  uint32_t scause = exception_cause();
  if (IS_INTERRUPT(scause)) {
    interrupts_handler(scause, tf);
  } else {
    exceptions_handler(scause, tf);
  }
}
