#include "common.h"

void kmain(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    kputs("Inicializando VOS32\n");
    kputs("Ctrl-a h para ayuda en QEMU\n");

    for (;;);
}
