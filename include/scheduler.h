#include "traps.h"
#define TIMER_FREQ_HZ 10000000UL

#define TICK_INTERVAL (TIMER_FREQ_HZ / 2) // 500ms

uint64_t current_time(void);
void timer(void);
void schedule(void);
void scheduler(void);
void yield(uint32_t pc, trap_frame_t *tf);
void yield_a(uint32_t pc);
void switch_context(trap_frame_t *curr_tf, trap_frame_t *next_tf);
