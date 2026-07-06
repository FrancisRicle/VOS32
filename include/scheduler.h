#include "process.h"
#include "traps.h"
#define TIMER_FREQ_HZ 10000000UL
//                     2000000UL  <- 500ms
//                        10000UL  <- 1ms
#define OP_MS 10000UL // per ms

#define TICK_INTERVAL_MS(X) ((X) * OP_MS)

uint64_t current_time(void);
void timer(void);
void schedule(void);
void scheduler(void);
void uret(uint32_t pc);
uint32_t nextproc(uint32_t exclude_pid);
void savecurrproc(uint32_t pc, trap_frame_t *currtf);
void loadnextproc(uint32_t nextpid, trap_frame_t *currtf);
