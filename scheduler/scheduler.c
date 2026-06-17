#include "../include/scheduler.h"

process procs[PROCS_MAX];

process *create_process(uint32_t pc) {
    process *proc = NULL;
    int i;
    for (i = 0; i < PROCS_MAX; i++) {
        if (procs[i].state == PROC_UNUSED) {
            proc = &procs[i];
            break;
        }
    }
    if (!proc) 
        PANIC("No hay espacio para mas procesos! (al señor K le gusta esto)");

    uint32_t *sp = (uint32_t *) &proc->stack[sizeof(proc->stack)];

    for (int i = 0; i < 12; i++) {
        *--sp = 0; // Aca esta limpiando 
    }
    *--sp = (uint32_t) pc;

    proc->pid = i+1;
    proc->sp = (uint32_t) sp;
    proc->state = PROC_RUNNABLE;
    return proc;
}