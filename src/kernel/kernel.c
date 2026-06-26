#include "console.h"
#include "mmu.h"
#include "process.h"
#include "scheduler.h"
#include "traps.h"

void halt(void);

void proc_a_entry(void) {
  puts("\nstarting process A\n");
  while (1) {
    puts("A");
  }
}

void proc_b_entry(void) {
  puts("\nstarting process B\n");
  while (1) {
    puts("B");
  }
}

void logo(void) {
  puts("#########################################################\n");
  puts("#*         *                    ==========+ ===========+#\n");
  puts("# *       *  * * * *    * * * *           |            |#\n");
  puts("#  *     * *         * *                  |            |#\n");
  puts("#   *   *  *         *  * * * * ==========+ +==========+#\n");
  puts("#    * * = *         *         *          | |           #\n");
  puts("#RISC *      * * * *    * * * *           | |           #\n");
  puts("#                               ==========+ +===========#\n");
  puts("#########################################################\n");
}

void kmain(void) {
  logo();
  traps();      // seteamos el trap_handler
  scheduler();  // habilitamos el timer
  interrupts(); // habilitamos interrupciones
  init_kernel_table();
  init_procs();
  create_process((uint32_t)proc_a_entry);
  create_process((uint32_t)proc_b_entry);
  enable_mmu(kernel_table);
  run_procs();
  halt();
}
