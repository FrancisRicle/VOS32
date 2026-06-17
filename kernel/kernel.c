#include "../include/common.h"
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
void kmain(void) {
    klogo();
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);
    init_traps();
    // TESTING DE MEMORIA
    paddr_t paddr01 = knext_free_page();
    paddr_t paddr02 = kn_free_pages(10);
    kputs("Hay memoria ^w^\n");
    kputs("Primer direccion:\n");
    kputh(paddr01);
    kputs("\nSegunda direccion:\n");
    kputh(paddr02);
    paddr_t demasiada_mem = kn_free_pages(16384);
    halt();
}
