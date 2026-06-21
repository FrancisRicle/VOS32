#pragma once
#include "stdint.h"
#define IS_INTERRUPT(X) ((X) >> 31)
#define CAUSE_ID(X) ((X) & 0x0000000F)
#define ILLEGAL_INSTRUPCION_EXP 2
#define USYSCALL_EXP 8
#define KSYSCALL_EXP 9
#define TIMER_INTERRUPT 5
#define EXTERNAL_INTERRUPT 9
#define SOFTWARE_INTERRUPT 1

uint32_t exception_cause(void);
uint32_t exception_value(void);
uint32_t exception_pc(void);

typedef struct {
  uint32_t ra;
  uint32_t gp;
  uint32_t tp;
  uint32_t t0;
  uint32_t t1;
  uint32_t t2;
  uint32_t t3;
  uint32_t t4;
  uint32_t t5;
  uint32_t t6;
  uint32_t a0;
  uint32_t a1;
  uint32_t a2;
  uint32_t a3;
  uint32_t a4;
  uint32_t a5;
  uint32_t a6;
  uint32_t a7;
  uint32_t s0;
  uint32_t s1;
  uint32_t s2;
  uint32_t s3;
  uint32_t s7;
  uint32_t s8;
  uint32_t s9;
  uint32_t s10;
  uint32_t s11;
  uint32_t sp;
} trap_frame_t;

void interrupts(void);
void traps(void);
void exceptions_handler(uint32_t scause, uint32_t pc, trap_frame_t *tf,
                        uint32_t stval);
void interrupts_handler(uint32_t pc, uint32_t scause, trap_frame_t *tf);
