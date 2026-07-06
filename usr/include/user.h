#pragma once
#include "stdint.h"
uint32_t syscall(uint32_t sysid, uint32_t arg1);
__attribute__((noreturn)) void exit(void);
