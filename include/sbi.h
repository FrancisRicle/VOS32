#pragma once
#include "stdint.h"

#define SBI_EID_CONSOLE_PUTCHAR 1
#define SBI_EID_CONSOLE_GETCHAR 1
#define SBI_FID_LEGACY 0
#define SBI_EID_SET_TIME 0x54494D45
#define SBI_FID 0

typedef struct {
  long error;
  long value;
} sbiret_t;

sbiret_t sbi_call(long arg0, long arg1, long arg2, long arg3, long arg4,
                  long arg5, long fid, long eid);

sbiret_t sbi_set_timer(uint64_t stime_value);

sbiret_t sbi_console_putchar(char c);
