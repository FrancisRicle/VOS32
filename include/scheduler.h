#include "traps.h"
#define TIMER_FREQ_HZ 10000000UL
//                     2000000UL  <- 500ms
//                        10000UL  <- 1ms
#define OP_MS 10000UL // per ms

#define TICK_INTERVAL_MS(X) ((X) * OP_MS)
#define TICK_INTERVAL (TICK_INTERVAL / 2)

uint64_t current_time(void);
void timer(void);
void schedule(void);
void scheduler(void);
void yield(uint32_t pc, trap_frame_t *tf);
void yield_a(uint32_t pc);
void switch_context(trap_frame_t *curr_tf, trap_frame_t *next_tf);
