#include "common.h"

#define PROCS_MAX 8

#define PROC_UNUSED 0   // Proceso (PCB) sin usar
#define PROC_RUNNABLE 1 // Proceso (PCB) en uso

void switch_context(uint32_t *prev_sp, uint32_t *next_sp);

typedef struct {
    int pid;    
    int state;      // Estado UNUSED o RUNNABLE
    vaddr_t sp;     // Stack pointer
    uint8_t stack[8192];    // Stack del kernel
} process;

process *create_process(uint32_t pc);
