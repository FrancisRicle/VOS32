#include "../include/common.h"
#include "../include/scheduler.h"

void klogo(void){
  kputs("#########################################################\n");
  kputs("#*         *                    ==========+ ===========+#\n");
  kputs("# *       *  * * * *    * * * *           |            |#\n");
  kputs("#  *     * *         * *                  |            |#\n");
  kputs("#   *   *  *         *  * * * * ==========+ +==========+#\n");
  kputs("#    * * = *         *         *          | |           #\n");
  kputs("#RISC *      * * * *    * * * *           | |           #\n");
  kputs("#                               ==========+ +===========#\n");
  kputs("#########################################################\n");
}
void handle_trap(struct trap_frame *f) {
    uint32_t scause = get_scause();
    uint32_t stval = get_stval();
    uint32_t user_pc = get_sepc();
    kputs("unexpected trap scause=");
    kputd(scause);
    kputs(" stval=");
    kputd(stval);
    kputs(" user_pc=");
    kputd(user_pc);
    PANIC("PANIC");
}

void delay(void) {
    for (int i = 0; i < 30000000; i++)
        __asm__ __volatile__("nop"); // do nothing
}

process *proc_a;
process *proc_b;

void proc_a_entry(void) {
    kputs("\nstarting process A\n");
    while (1) {
        kputc('A');
        switch_context(&proc_a->sp, &proc_b->sp);
        delay();
    }
}

void proc_b_entry(void) {
    kputs("\nstarting process B\n");
    while (1) {
        kputc('B');
        switch_context(&proc_b->sp, &proc_a->sp);
        delay();
    }
}
#define TIMER_FREQ_HZ 10000000UL
#define TICK_INTERVLA (TIMER_FREQ_HZ / 2)

#define SBI_EXT_TIME 0x54494D45L
#define SBI_EXT_TIME_SET_TIMER 0

sbiret sbi_set_timer(unsigned long long stime_value) {
    sbiret sbi_ret = sbi_call(
        (long)(uint32_t)(stime_value),
        (long)(uint32_t)(stime_value >> 32),
        0,0,0,0,
        SBI_EXT_TIME_SET_TIMER,
        SBI_EXT_TIME);
    return sbi_ret;
}

void kmain(void) {
    klogo();
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);
    init_traps();
    
    init_int();
    long now = get_time();
    sbi_set_timer(now + TICK_INTERVLA);
    init_timer();
    
    /*proc_a = create_process((uint32_t) proc_a_entry);
    proc_b = create_process((uint32_t) proc_b_entry);

    proc_a_entry();*/
    //PANIC("NO DEBERIAS ESTAR ACA, TENGO MIEDO");
    halt();
}
