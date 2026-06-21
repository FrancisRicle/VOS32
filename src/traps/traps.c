#include "traps.h"
#include "panic.h"
#include "scheduler.h"
void interrupts_handler(uint32_t pc, uint32_t scause, trap_frame_t *tf) {
  switch (CAUSE_ID(scause)) {
  case TIMER_INTERRUPT:
    schedule();
    yield(pc, tf);
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
void exceptions_handler(uint32_t scause, uint32_t pc, trap_frame_t *tf,
                        uint32_t stval) {
  switch (CAUSE_ID(scause)) {
  case USYSCALL_EXP:
    break;
  case KSYSCALL_EXP:
    break;
  case ILLEGAL_INSTRUPCION_EXP:
    panic("ILLEGAL INSTRUPCION EXCEPTION");
  default:
    panic("UNHANDLED EXCEPTION");
  }
}
void traps_handler(trap_frame_t *tf) {
  uint32_t scause = exception_cause();
  uint32_t stval = exception_value();
  uint32_t pc = exception_pc();
  if (IS_INTERRUPT(scause)) {
    interrupts_handler(pc, scause, tf);
  } else {
    exceptions_handler(scause, pc, tf, stval);
  }
}
