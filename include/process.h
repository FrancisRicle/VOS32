#include "traps.h"

#define PROCS_MAX 4
#define PROCS_BASE 0x1000000

typedef enum {
  PROC_NULL,
  PROC_RUNNABLE,
  PROC_RUNNING,
  PROC_SLEEPING,
} process_state_e;

typedef struct {
  uint8_t pid;
  process_state_e state;
  uint32_t epc;
  uint32_t *table1;
  trap_frame_t tf;
} process_t;

void pinit(void);
void create_process(const void *image, uint32_t image_size);

extern uint32_t currpid;
extern process_t procs[PROCS_MAX];
