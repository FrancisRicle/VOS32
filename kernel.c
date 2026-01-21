#include "common.h"

void kmain(void) {
    // Limpiamos BSS
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    kputs("Hola Mundo desde el Kernel!\n");
    kputs("Estructura: kmain(C) -> kputs(libc) -> kputc(asm)\n");

    for (;;);
}
