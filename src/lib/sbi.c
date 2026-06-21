#include "sbi.h"
sbiret_t sbi_set_timer(uint64_t stime_value) {
  return sbi_call((long)(uint32_t)(stime_value),
                  (long)(uint32_t)(stime_value >> 32), 0, 0, 0, 0, SBI_FID,
                  SBI_EID_SET_TIME);
}

sbiret_t sbi_console_putchar(char c) {
  return sbi_call(c, 0, 0, 0, 0, 0, SBI_FID_LEGACY, SBI_EID_CONSOLE_PUTCHAR);
}
