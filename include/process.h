#include "traps.h"
#include <stdint.h>

#define PROCS_MAX 2
#define PROCS_BASE 0x80000200

typedef enum {
  PROC_NULL,
  PROC_RUNNABLE,
  PROC_RUNNING,
  PROC_SLEEPING,
} process_state_e;

typedef struct {
  uint8_t pid;
  process_state_e state;
  uint32_t sepc;
  uint8_t stack[4096];
  trap_frame_t tf;
} process_t;

void init_procs(void);
void run_procs(void);
void exec(uint32_t sepc, uint32_t *stack);
void create_process(uint32_t pc);

extern process_t *curr_proc;
extern process_t procs[2];
