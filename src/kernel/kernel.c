#include "console.h"
#include "mmu.h"
#include "scheduler.h"
#include "traps.h"

void halt(void);
extern char _binary_usr_bin_sh_bin_start[], _binary_usr_bin_sh_bin_size[];
extern char _binary_usr_bin_init_bin_start[], _binary_usr_bin_init_bin_size[];

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
  kinitpt();    // mapeamos el kernel
  pinit();      // inicializamos los procesos
  create_process(_binary_usr_bin_init_bin_start,
                 (uint32_t)_binary_usr_bin_init_bin_size);
  create_process(_binary_usr_bin_sh_bin_start,
                 (uint32_t)_binary_usr_bin_sh_bin_size);
  rootpt(kernel_table);
  halt(); // esperamos por interrupciones
}
